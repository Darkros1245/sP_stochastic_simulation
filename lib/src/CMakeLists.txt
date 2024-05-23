add_library(stochastic_simulation_lib STATIC "agent.cpp" "expr.cpp" "intrinsic.cpp" "pretty_printer.cpp" "reaction_rule.cpp" "vessel.cpp")
target_include_directories(stochastic_simulation_lib PUBLIC "../include")
target_include_directories(stochastic_simulation_lib PUBLIC "../exceptions")