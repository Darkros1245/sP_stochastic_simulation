add_library(stochastic_simulation_lib STATIC "agent.cpp" "vessel.cpp" "symbol_table.cpp" "expr.cpp" "term.cpp")
target_include_directories(stochastic_simulation_lib PUBLIC "../include")
target_include_directories(stochastic_simulation_lib PUBLIC "../exceptions")