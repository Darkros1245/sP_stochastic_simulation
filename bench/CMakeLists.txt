include("../CMakeScripts/benchmark.cmake")

add_executable(bench bench.cpp)
target_link_libraries(bench PRIVATE benchmark::benchmark_main stochastic_simulation_lib)