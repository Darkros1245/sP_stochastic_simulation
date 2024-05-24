#include <matplot/matplot.h>
#include <matplot/freestanding/plot.h>
#include <string>
#include <vector>

#include "circadian_rhythm.hpp"
#include "pretty_printer.hpp"
#include "vessel.hpp"
#include "covid-19.hpp"

void run_circadian_rhythm_simulation();
void run_seihr_simulation();

int main() {
	run_circadian_rhythm_simulation();
	//run_seihr_simulation();
	
	return 0;
}

void run_circadian_rhythm_simulation() {
	stochastic::Pretty_printer<std::string, int> pp {};
	
	auto circadian_vessel = circadian_rhythm();

	std::vector<double> X_coord;
	std::vector<double> C_coord;
	std::vector<double> A_coord;
	std::vector<double> R_coord;

	std::vector<std::string> to_observe = {"C", "A", "R"};

	for (auto & observed : circadian_vessel.simulate(100, to_observe)) {
		X_coord.push_back(observed["TIME"]);
		C_coord.push_back(observed["C"]);
		A_coord.push_back(observed["A"]);
		R_coord.push_back(observed["R"]);
	}

	matplot::plot(X_coord, C_coord, 
				  X_coord, A_coord, 
				  X_coord, R_coord);
	matplot::show();

	pp(circadian_vessel);
}

void run_seihr_simulation() {
	stochastic::Pretty_printer<std::string, int> pp {};

	auto covid_vessel = seihr(10000);

	std::vector<double> X_coord;
	std::vector<double> S_coord;
	std::vector<double> E_coord;
	std::vector<double> I_coord;
	std::vector<double> H_coord;
	std::vector<double> R_coord;

	std::vector<std::string> to_observe = {"S", "E", "I", "H", "R"};

	for (auto & observed : covid_vessel.simulate(100, to_observe)) {
		X_coord.push_back(observed["TIME"]);
		S_coord.push_back(observed["S"]);
		E_coord.push_back(observed["E"]);
		I_coord.push_back(observed["I"]);
		H_coord.push_back(observed["H"] * 1000);
		R_coord.push_back(observed["R"]);
	}

	matplot::plot(X_coord, S_coord, 
				  X_coord, E_coord, 
				  X_coord, I_coord, 
				  X_coord, H_coord, 
				  X_coord, R_coord);
	matplot::show();

	pp(covid_vessel);
}