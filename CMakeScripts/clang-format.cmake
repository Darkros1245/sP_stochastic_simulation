file(GLOB_RECURSE ALL_SOURCE_FILES "../src/*.cpp" "../src/*.hpp" "../lib/*.cpp" "../lib/*.hpp" "../test/*.cpp")

# Run clang-format on all source files
execute_process(
    COMMAND /usr/bin/clang-format -style=file -i ${ALL_SOURCE_FILES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)