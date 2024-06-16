cmake_minimum_required(VERSION 3.28)
project(stochastic_simulation CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

include("CMakeScripts/sanitizers.cmake")

add_custom_target(fmt
    COMMAND ${CMAKE_COMMAND} -P "${CMAKE_SOURCE_DIR}/CMakeScripts/clang-format.cmake"
    COMMENT "Running clang-format script"
)
add_custom_target(check
    COMMAND ${CMAKE_COMMAND} -P "${CMAKE_SOURCE_DIR}/CMakeScripts/cppcheck.cmake"
    COMMENT "Running cppcheck script"
)

enable_testing()

add_subdirectory("lib/src")
add_subdirectory("bin/src")
add_subdirectory("test")
add_subdirectory("bench")