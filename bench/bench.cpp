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
		auto const end_time = 100;
		std::vector<std::string> const to_observe = {"C", "A", "R"};
		auto const amount = 10;

		auto vessel = circadian_rhythm();
		vessel.simulate(end_time, to_observe, amount, 1);
	}
}
BENCHMARK(circadian_rhythm_simulation_1_thread);

static void circadian_rhythm_simulation_max_thread(benchmark::State& state){
	for (auto _ : state) {
		auto const end_time = 100;
		std::vector<std::string> const to_observe = {"C", "A", "R"};
		auto const amount = 10;

		auto vessel = circadian_rhythm();
		vessel.simulate(end_time, to_observe, amount);
	}
}
BENCHMARK(circadian_rhythm_simulation_max_thread);

static void seihr_simulation_1_thread(benchmark::State& state) {
	for (auto _ : state) {
		auto const population = 10000;
		auto const end_time = 100;
		std::vector<std::string> const to_observe { "S", "E", "I", "H", "R" };
		auto const amount = 100;

		auto vessel = seihr(population);
		vessel.simulate(end_time, to_observe, amount, 1);
	}
}
BENCHMARK(seihr_simulation_1_thread);

static void seihr_simulation_max_thread(benchmark::State& state) {
	for (auto _ : state) {
		auto const population = 10000;
		auto const end_time = 100;
		std::vector<std::string> const to_observe { "S", "E", "I", "H", "R" };
		auto const amount = 100;

		auto vessel = seihr(population);
		vessel.simulate(end_time, to_observe, amount);
	}
}
BENCHMARK(seihr_simulation_max_thread);

static void exponential_decay_simulation_1_thread(benchmark::State& state){
	for (auto _ : state) {
		auto const a_amount = 100;
		auto const b_aomunt = 0;
		auto const c_amount = 1;
		auto const end_time = 100;
		std::vector<std::string> const to_observe = {"A", "B", "C"};
		auto const amount = 100;

		auto vessel = exponential_decay(a_amount, b_aomunt, c_amount);
		vessel.simulate(end_time, to_observe, amount, 1);
	}
}
BENCHMARK(exponential_decay_simulation_1_thread);

static void exponential_decay_simulation_max_thread(benchmark::State& state){
	for (auto _ : state) {
		auto const a_amount = 100;
		auto const b_aomunt = 0;
		auto const c_amount = 1;
		auto const end_time = 100;
		std::vector<std::string> const to_observe = {"A", "B", "C"};
		auto const amount = 100;

		auto vessel = exponential_decay(a_amount, b_aomunt, c_amount);
		vessel.simulate(end_time, to_observe, amount);
	}
}
BENCHMARK(exponential_decay_simulation_max_thread);

static void get_hospitalization_peak_simulation_1_thread(benchmark::State& state) {
	for (auto _ : state) {
		auto const population = 589755;
		auto const end_time = 100;
		std::vector<std::string> const to_observe{"H"};
		auto const amount = 10;
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
		auto const population = 589755;
		auto const end_time = 100;
		std::vector<std::string> const to_observe{"H"};
		auto const amount = 10;
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