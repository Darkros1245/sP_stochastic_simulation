#include "circadian_rhythm.hpp"
#include "pretty_printer.hpp"

int main() {
	stochastic::Vessel vessel = circadian_rhythm();
	//vessel.simulate(10);
	stochastic::Pretty_printer pp {};
	pp(vessel);
	return 0;
}