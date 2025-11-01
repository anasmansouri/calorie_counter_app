cmake_minimum_required(VERSION 3.16)
project(calorie_counter_backend LANGUAGES CXX)

# Set C++ version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler warnings (good for dev)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 -fno-omit-frame-pointer -fno-optimize-sibling-calls")
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

# Option to build tests
option(BUILD_TESTS "Build unit and integration tests" OFF)

# External dependencies (examples)
# You can use find_package or FetchContent here
# find_package(crow CONFIG REQUIRED)
# find_package(nlohmann_json CONFIG REQUIRED)
# find_package(SQLite3 REQUIRED)

# put executables in build/bin and libs in build/lib
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add subdirectories
add_subdirectory(src)
if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
