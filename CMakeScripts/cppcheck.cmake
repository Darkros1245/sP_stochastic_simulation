file(GLOB_RECURSE ALL_SOURCE_FILES "../src/*.cpp" "../src/*.hpp" "../lib/*.cpp" "../lib/*.hpp" "../test/*.cpp")

execute_process(
    COMMAND /usr/bin/cppcheck
    --enable=warning,performance,portability,missingInclude
    --suppress=missingIncludeSystem
    -I "../lib/include"
    -I "../lib/exceptions"
    -I "../bin/include"
    ${ALL_SOURCE_FILES}
    --quiet
    --language=c++
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)