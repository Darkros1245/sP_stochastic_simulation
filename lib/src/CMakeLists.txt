include("../../CMakeScripts/matplotplusplus.cmake")
include("../../CMakeScripts/libcoro.cmake")

add_library(stochastic_simulation_lib STATIC "agent.cpp" "expr.cpp" "intrinsic.cpp" "reaction_rule.cpp")
target_include_directories(stochastic_simulation_lib PUBLIC "../include" "../exceptions" "../examples")

target_link_libraries(stochastic_simulation_lib PUBLIC matplot libcoro)