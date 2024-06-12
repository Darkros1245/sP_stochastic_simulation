include("../CMakeScripts/doctest.cmake")

function(add_doctest test_name test_source)
    add_executable(${test_name} ${test_source})
    target_link_libraries(${test_name} PRIVATE doctest::doctest_with_main stochastic_simulation_lib)
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()


add_doctest(agent_test "agent_test.cpp")
add_doctest(expr_test "expr_test.cpp")
add_doctest(intrinsic_test "intrinsic_test.cpp")
add_doctest(network_graph_printer_test "network_graph_printer_test.cpp")
add_doctest(pretty_printer_test "pretty_printer_test.cpp")
add_doctest(reaction_rule_test "reaction_rule_test.cpp")
add_doctest(symbol_table_test "symbol_table_test.cpp")
add_doctest(vessel_test "vessel_test.cpp")