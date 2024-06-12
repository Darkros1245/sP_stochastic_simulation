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

int main()
{
    auto time = 100;
    const auto Nsmall = 10000;
    const auto Nnj = 589755;
    const auto Ndk = 5822763;

    pretty_print_vessel(circadian_rhythm());
    print_network_graph(circadian_rhythm());

    run_circadian_rhythm_simulation(time);

    run_seihr_simulation(Nsmall, time);

    get_hospitalization_peak(Nnj, time);
    get_hospitalization_peak(Ndk, time);

    time = 1500;

    // A(0)=100, B(0)=0 , C=1
    run_exponential_decay_simulation(100, 0, 1, time);
    // A(0)=100, B(0)=0 , C=2
    run_exponential_decay_simulation(100, 0, 2, time);
    // A(0)=50 , B(0)=50, C=1
    run_exponential_decay_simulation(50, 50, 1, time);

    return 0;
}

void pretty_print_vessel(stochastic::Vessel<std::string, int> const& vessel)
{
    vessel.print(stochastic::Pretty_printer<std::string, int>{}, std::cout);
}

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

    for (auto& [current_time, observed] : circadian_vessel.simulate(time, to_observe)) {
        X_coord.push_back(current_time);
        C_coord.push_back(observed["C"]);
        A_coord.push_back(observed["A"]);
        R_coord.push_back(observed["R"]);
    }

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

    for (auto& [current_time, observed] : covid_vessel.simulate(time, to_observe)) {
        X_coord.push_back(current_time);
        S_coord.push_back(observed["S"]);
        E_coord.push_back(observed["E"]);
        I_coord.push_back(observed["I"]);
        H_coord.push_back(observed["H"] * 1000);
        R_coord.push_back(observed["R"]);
    }

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

    for (auto& [current_time, observed] : exponential_decay_vessel.simulate(time, to_observe)) {
        X_coord.push_back(current_time);
        A_coord.push_back(observed["A"]);
        B_coord.push_back(observed["B"]);
        C_coord.push_back(observed["C"]);
    }

    matplot::plot(X_coord, A_coord, X_coord, B_coord, X_coord, C_coord);
    matplot::show();
}

void get_hospitalization_peak(int population, int time)
{
    auto covid_vessel = seihr(population);
    auto peak = -1;

    const std::vector<std::string> to_observe{"H"};

    for (auto& [_, observed] : covid_vessel.simulate(time, to_observe)) {
        peak = std::max(peak, observed["H"]);
    }

    std::cout << "--------------------PEAK--------------------"
              << "\n";
    std::cout << "Max hospitalized agents: " << peak << "\n";
    std::cout << "--------------------------------------------"
              << "\n";
}