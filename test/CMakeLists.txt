include(doctest.cmake)

add_executable(agent_test "agent_test.cpp")
target_link_libraries(agent_test PRIVATE doctest::doctest_with_main stochastic_simulation_lib)
add_test(NAME agent_test COMMAND agent_test)