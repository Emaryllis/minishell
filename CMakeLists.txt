cmake_minimum_required(VERSION 3.10)

project(Minishell VERSION 1.0 LANGUAGES C)

# Initialize constant CMake settings
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")
endif()
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/srcs/*.c")
list(FILTER SOURCES EXCLUDE REGEX ".*/srcs/tests/.*\\.c$")
file(GLOB HEADERS "${CMAKE_SOURCE_DIR}/minish.h" "${CMAKE_SOURCE_DIR}/libft/libft.h")
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
set(WRAPPER "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.sh")

# --------------------------------------------------------
# VALGRIND LEAK CHECK
# --------------------------------------------------------

add_custom_target(leak_check
        COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp $<TARGET_FILE:${PROJECT_NAME}>
        DEPENDS ${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Leak Check with Valgrind"
)

# --------------------------------------------------------
# BUILD & LINK LIBFT
# --------------------------------------------------------

add_custom_target(build_libft
        COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_SOURCE_DIR}/libft make
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/libft
        COMMENT "Building libft library..."
)
add_dependencies(${PROJECT_NAME} build_libft)

add_library(libft STATIC IMPORTED)
set_target_properties(libft PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libft/libft.a)
target_link_libraries(${PROJECT_NAME} PRIVATE libft)

# --------------------------------------------------------
# FIND READLINE
# --------------------------------------------------------

find_path(READLINE_INCLUDE_DIR readline/readline.h
        HINTS
        /opt/homebrew/opt/readline/include      # macOS ARM
        /usr/local/opt/readline/include         # macOS Intel
        /usr/include/readline                   # Linux
)

find_library(READLINE_LIBRARY readline
        HINTS
        /opt/homebrew/opt/readline/lib
        /usr/local/opt/readline/lib
        /usr/lib
        /usr/local/lib
)

if(NOT READLINE_INCLUDE_DIR OR NOT READLINE_LIBRARY)
    message(FATAL_ERROR "Readline not found. Install with: apt install libreadline-dev")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${READLINE_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${READLINE_LIBRARY})

# --------------------------------------------------------
# ADDRESS SANITIZER
# --------------------------------------------------------
option(ENABLE_ASAN "Enable AddressSanitizer" ON)
file(WRITE ${WRAPPER} "#!/bin/bash\n")
if(ENABLE_ASAN AND CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    message(STATUS "Enabling AddressSanitizer...")
    message(STATUS "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:-fsanitize=address -O1 -fno-omit-frame-pointer>
    )
    target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:-fsanitize=address>
    )

    # Suppress ASan in readline library
    file(APPEND ${WRAPPER} "export ASAN_OPTIONS=\"interceptor_via_libc=readline:halt_on_error=0:verbosity=1\"\n")
else()
    file(APPEND ${WRAPPER} "unset ASAN_OPTIONS\n")
endif()
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND echo "exec $<TARGET_FILE:${PROJECT_NAME}> \"\$@\"" >> ${WRAPPER}
        COMMAND chmod +x ${WRAPPER}
        COMMENT "Moving executable and creating ASan wrapper"
        VERBATIM
)
message("${WRAPPER}")