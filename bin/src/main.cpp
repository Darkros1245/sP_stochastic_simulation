#include <algorithm>
#include <fstream>
#include <iostream>
#include <matplot/matplot.h>
#include <matplot/freestanding/plot.h>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "circadian_rhythm.hpp"
#include "covid-19.hpp"
#include "exponential_decay.hpp"
#include "network_graph_printer.hpp"
#include "pretty_printer.hpp"
#include "vessel.hpp"
#include "could_not_open_file_exception.hpp"

void pretty_print_vessel(stochastic::Vessel<std::string, int> const& vessel);
void print_network_graph(stochastic::Vessel<std::string, int> const& vessel);
void run_circadian_rhythm_simulation(int time);
void run_seihr_simulation(int population, int time);
void run_exponential_decay_simulation(int A_amount, int B_amount, int C_amount, int time);
void get_hospitalization_peak(int population, int time);
void get_hospitalization_average(int population, int time);

// Requirement 5: Demonstrate the application of the library on the three examples (shown in Fig. 1, 2, 3).
int main()
{
    auto time = 100;
    const auto Nsmall = 10000;
    const auto Nnj = 589755;
    const auto Ndk = 5822763;

    pretty_print_vessel(circadian_rhythm());
    print_network_graph(circadian_rhythm());

    run_circadian_rhythm_simulation(time);

    run_seihr_simulation(Nsmall, 100);

    get_hospitalization_peak(Nsmall, time);
    get_hospitalization_peak(Nnj, time);
    get_hospitalization_peak(Ndk, time);
    get_hospitalization_average(Nsmall, time);

    time = 1500;

    // A(0)=100, B(0)=0 , C=1
    run_exponential_decay_simulation(100, 0, 1, time);
    // A(0)=100, B(0)=0 , C=2
    run_exponential_decay_simulation(100, 0, 2, time);
    // A(0)=50 , B(0)=50, C=1
    run_exponential_decay_simulation(50, 50, 1, time);

    return 0;
}

// Requirement 2: Provide pretty-printing of the reaction network in a) human readable format and b) network graph (e.g. Fig. 4).
void pretty_print_vessel(stochastic::Vessel<std::string, int> const& vessel)
{
    vessel.print(stochastic::Pretty_printer<std::string, int>{}, std::cout);
}

// Requirement 2: Provide pretty-printing of the reaction network in a) human readable format and b) network graph (e.g. Fig. 4).
void print_network_graph(stochastic::Vessel<std::string, int> const& vessel)
{
    std::ofstream stream{"network_graphs/test.dot"};
    if (!stream.is_open()) {
        throw stochastic::Could_not_open_file_exception{"Could not open file: network_graphs/test.dot"};
    }

    vessel.print(stochastic::Network_graph<std::string, int>{}, stream);
}

void run_circadian_rhythm_simulation(int time)
{
    auto circadian_vessel = circadian_rhythm();

    std::vector<double> X_coord;
    std::vector<double> C_coord;
    std::vector<double> A_coord;
    std::vector<double> R_coord;

    const std::vector<std::string> to_observe = {"C", "A", "R"};
    for (auto & [current_time, observed] : circadian_vessel.simulate(time, to_observe)) {
        X_coord.push_back(current_time);
        C_coord.push_back(observed["C"]);
        A_coord.push_back(observed["A"]);
        R_coord.push_back(observed["R"]);
    }

    // Requirement 6: Display simulation trajectories of how the amounts change. External tools/libraries can be used to visualize.
    matplot::plot(X_coord, C_coord, X_coord, A_coord, X_coord, R_coord);
    matplot::show();
}

void run_seihr_simulation(int population, int time)
{
    auto covid_vessel = seihr(population);

    std::vector<double> X_coord;
    std::vector<double> S_coord;
    std::vector<double> E_coord;
    std::vector<double> I_coord;
    std::vector<double> H_coord;
    std::vector<double> R_coord;

    const std::vector<std::string> to_observe{"S", "E", "I", "H", "R"};

    for (auto & [current_time, observed] : covid_vessel.simulate(time, to_observe)) {
        X_coord.push_back(current_time);
        S_coord.push_back(observed["S"]);
        E_coord.push_back(observed["E"]);
        I_coord.push_back(observed["I"]);
        H_coord.push_back(observed["H"] * 1000);
        R_coord.push_back(observed["R"]);
    }

    // Requirement 6: Display simulation trajectories of how the amounts change. External tools/libraries can be used to visualize.
    matplot::plot(X_coord, S_coord, X_coord, E_coord, X_coord, I_coord, X_coord, H_coord, X_coord, R_coord);
    matplot::show();
}

void run_exponential_decay_simulation(int A_amount, int B_amount, int C_amount, int time)
{
    auto exponential_decay_vessel = exponential_decay(A_amount, B_amount, C_amount);

    std::vector<double> X_coord;
    std::vector<double> A_coord;
    std::vector<double> B_coord;
    std::vector<double> C_coord;

    const std::vector<std::string> to_observe = {"A", "B", "C"};
    for (auto & [current_time, observed] : exponential_decay_vessel.simulate(time, to_observe)) {
        X_coord.push_back(current_time);
        A_coord.push_back(observed["A"]);
        B_coord.push_back(observed["B"]);
        C_coord.push_back(observed["C"]);
    }

    // Requirement 6: Display simulation trajectories of how the amounts change. External tools/libraries can be used to visualize.
    matplot::plot(X_coord, A_coord, X_coord, B_coord, X_coord, C_coord);
    matplot::show();
}

// Requirement 7: Implement a generic support for (any) user-supplied state observer function object or provide a lazy trajectory
// generation interface (coroutine). The observer itself should be supplied by the user/test and not be part of
// the library. To demonstrate the generic support, estimate the peak of hospitalized agents in Covid-19 example
// without storing entire trajectory data. Record the peak hospitalization values for population sizes of NNJ and
// NDK .
void get_hospitalization_peak(int population, int time)
{
    auto covid_vessel = seihr(population);
    auto peak = -1;
    const auto amount = 1;

    const std::vector<std::string> to_observe{"H"};

    for (size_t i = 0; i < amount; ++i)
    {
        for (auto & [_, observed] : covid_vessel.simulate(time, to_observe)) {
            peak = std::max(peak, observed["H"]);
        }
    }
    
    std::cout << "--------------------PEAK--------------------"
              << "\n";
    std::cout << "Max hospitalized agents: " << peak << "\n";
    std::cout << "--------------------------------------------"
              << "\n";
}

// Requirement 8: Implement support for multiple computer cores by parallelizing the computation of several simulations at the
// same time. Estimate the likely (average) value of the hospitalized peak over 100 simulations.
void get_hospitalization_average(int population, int time)
{
    auto covid_vessel = seihr(population);
    auto peak = -1;
    auto avg_peak = -1;

    const std::vector<std::string> to_observe{"H"};

    for (auto & simulation_result : covid_vessel.simulate(time, to_observe, 100)) {
        for (auto & [_, observed] : simulation_result) {
            peak = std::max(peak, observed["H"]);
        }

        avg_peak = avg_peak == -1 ? peak : (avg_peak + peak) / 2;
    }

    std::cout << "--------------------avg_peak----------------"
              << "\n";
    std::cout << "Average hospitalized agents: " << avg_peak << "\n";
    std::cout << "--------------------------------------------"
              << "\n";
}