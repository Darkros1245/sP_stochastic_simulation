add_library(stochastic_simulation_lib STATIC agent.cpp)
add_executable(main main.cpp)
target_link_libraries(main PRIVATE stochastic_simulation_lib)