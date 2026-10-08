cmake_minimum_required(VERSION 3.14)
project(stopwatch)

# Set C++ standard (e.g., C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Option to treat warnings as errors (enabled by default)
option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" ON)

# Set output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Create executable target
add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        include/
)

# Specify source files with PRIVATE visibility
target_sources(${PROJECT_NAME}
    PRIVATE
        src/main.cpp
)

# Add warnings and treat as errors if option is enabled
target_compile_options(${PROJECT_NAME}
    PRIVATE
        $<$<C_COMPILER_ID:GNU,Clang>:-Wall -Wextra>
        $<$<AND:$<C_COMPILER_ID:GNU,Clang>,$<BOOL:${WARNINGS_AS_ERRORS}>>:-Werror>
        $<$<C_COMPILER_ID:MSVC>:/W4>
        $<$<AND:$<C_COMPILER_ID:MSVC>,$<BOOL:${WARNINGS_AS_ERRORS}>>:/WX>
)

message(STATUS "Warnings as errors: ${WARNINGS_AS_ERRORS}")
message(STATUS "Binary output directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")