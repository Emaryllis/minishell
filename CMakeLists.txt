cmake_minimum_required(VERSION 3.10)

project(Minishell VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/srcs/*.c")
list(FILTER SOURCES EXCLUDE REGEX ".*/srcs/tests/.*\\.c$")
file(GLOB HEADERS "${CMAKE_SOURCE_DIR}/minish.h" "${CMAKE_SOURCE_DIR}/libft/libft.h")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

# --------------------------------------------------------
# VALGRIND LEAK CHECK
# --------------------------------------------------------

add_custom_target(leak_check
        COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp ./Minishell
        DEPENDS Minishell
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
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
set_target_properties(libft PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libft/libft.a
)
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
