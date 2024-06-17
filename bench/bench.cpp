#include <benchmark/benchmark.h>
#include <string>
#include <vector>

#include "circadian_rhythm.hpp"
#include "covid-19.hpp"
#include "exponential_decay.hpp"
#include "vessel.hpp"

// Requirement 10: Benchmark and compare the stochastic simulation performance (e.g. the time it takes to compute 100 simulations
// a single core, multiple cores, or improved implementation). Record the timings and make your conclusions.
static void circadian_rhythm_simulation_1_thread(benchmark::State& state){
	for (auto _ : state) {
		const auto end_time = 100;
		const std::vector<std::string> to_observe = {"C", "A", "R"};
		const auto amount = 10;

		auto vessel = circadian_rhythm();
		for (auto _ : vessel.simulate(end_time, to_observe, amount, 1)) {}
	}
}
BENCHMARK(circadian_rhythm_simulation_1_thread);

static void circadian_rhythm_simulation_max_thread(benchmark::State& state){
	for (auto _ : state) {
		const auto end_time = 100;
		const std::vector<std::string> to_observe = {"C", "A", "R"};
		const auto amount = 10;

		auto vessel = circadian_rhythm();
		for (auto _ : vessel.simulate(end_time, to_observe, amount)) {}
	}
}
BENCHMARK(circadian_rhythm_simulation_max_thread);

static void seihr_simulation_1_thread(benchmark::State& state) {
	for (auto _ : state) {
		const auto population = 10000;
		const auto end_time = 100;
		const std::vector<std::string> to_observe { "S", "E", "I", "H", "R" };
		const auto amount = 100;

		auto vessel = seihr(population);
		for (auto _ : vessel.simulate(end_time, to_observe, amount, 1)) {}
	}
}
BENCHMARK(seihr_simulation_1_thread);

static void seihr_simulation_max_thread(benchmark::State& state) {
	for (auto _ : state) {
		const auto population = 10000;
		const auto end_time = 100;
		const std::vector<std::string> to_observe { "S", "E", "I", "H", "R" };
		const auto amount = 100;

		auto vessel = seihr(population);
		for (auto _ : vessel.simulate(end_time, to_observe, amount)) {}
	}
}
BENCHMARK(seihr_simulation_max_thread);

static void exponential_decay_simulation_1_thread(benchmark::State& state){
	for (auto _ : state) {
		const auto a_amount = 100;
		const auto b_aomunt = 0;
		const auto c_amount = 1;
		const auto end_time = 100;
		const std::vector<std::string> to_observe = {"A", "B", "C"};
		const auto amount = 100;

		auto vessel = exponential_decay(a_amount, b_aomunt, c_amount);
		for (auto _ : vessel.simulate(end_time, to_observe, amount, 1)) {}
	}
}
BENCHMARK(exponential_decay_simulation_1_thread);

static void exponential_decay_simulation_max_thread(benchmark::State& state){
	for (auto _ : state) {
		const auto a_amount = 100;
		const auto b_aomunt = 0;
		const auto c_amount = 1;
		const auto end_time = 100;
		const std::vector<std::string> to_observe = {"A", "B", "C"};
		const auto amount = 100;

		auto vessel = exponential_decay(a_amount, b_aomunt, c_amount);
		for (auto _ : vessel.simulate(end_time, to_observe, amount)) {}
	}
}
BENCHMARK(exponential_decay_simulation_max_thread);

static void get_hospitalization_peak_simulation_1_thread(benchmark::State& state) {
	for (auto _ : state) {
		const auto population = 589755;
		const auto end_time = 100;
		const std::vector<std::string> to_observe{"H"};
		const auto amount = 10;
		auto peak = -1;

		auto vessel = seihr(population);
		for (auto & simulation_result : vessel.simulate(end_time, to_observe, amount, 1)) {
	        for (auto & [_, observed] : simulation_result) {
	            peak = std::max(peak, observed["H"]);
	        }
	    }
	}
}
BENCHMARK(get_hospitalization_peak_simulation_1_thread);

static void get_hospitalization_peak_simulation_max_thread(benchmark::State& state) {
	for (auto _ : state) {
		const auto population = 589755;
		const auto end_time = 100;
		const std::vector<std::string> to_observe{"H"};
		const auto amount = 10;
		auto peak = -1;

		auto vessel = seihr(population);
		for (auto & simulation_result : vessel.simulate(end_time, to_observe, amount)) {
	        for (auto & [_, observed] : simulation_result) {
	            peak = std::max(peak, observed["H"]);
	        }
	    }
	}
}
BENCHMARK(get_hospitalization_peak_simulation_max_thread);

BENCHMARK_MAIN();