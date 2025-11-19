cmake_minimum_required(VERSION 3.10)

project(Minishell VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.c")
file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/src/*.h")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

add_custom_target(leak_check
        COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp ./Minishell
        DEPENDS Minishell
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMENT "Leak Check with Valgrind"
)

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
