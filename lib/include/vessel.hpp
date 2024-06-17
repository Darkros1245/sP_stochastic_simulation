#ifndef VESSEL_H
#define VESSEL_H

#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <unordered_map>
#include <utility>
#include <vector>
#include <coro/coro.hpp>
#include <coro/generator.hpp>
#include <algorithm>
#include <tuple>
#include <thread>
#include <random>

#include "printer.hpp"
#include "reaction_rule.hpp"
#include "agent.hpp"
#include "enviroment.hpp"
#include "symbol_table.hpp"
#include "no_exist_exception.hpp"
#include "thread_pool.hpp"

namespace stochastic
{
    template <Hashable Key, Numeric Value>
    class Vessel
    {
    private:
        std::string _name;
        Enviroment _env{};
        Symbol_table<Key, Value> _st{};
        std::vector<Reaction_rule> _reaction_rules;

    public:
        // Requirement 7: Implement a generic support for (any) user-supplied state observer function object or provide
        // a lazy trajectory generation interface (coroutine). The observer itself should be supplied by the user/test
        // and not be part of the library. To demonstrate the generic support, estimate the peak of hospitalized agents
        // in Covid-19 example without storing entire trajectory data. Record the peak hospitalization values for
        // population sizes of NNJ and NDK . Requirement 4: Implement the stochastic simulation (Alg. 1) of the system
        // using the reaction rules.
        coro::generator<std::tuple<double, std::unordered_map<Key, int>>> simulate(
            int end_time, std::vector<Key> const& to_observe) const
        {
            auto st = this->_st;
            auto reaction_rules = this->_reaction_rules;

            std::random_device rd;
            std::mt19937_64 gen(rd());

            auto current_time = 0.0;

            std::unordered_map<Key, int> observed{};

            try {
                for (auto const& observe : to_observe) {
                    observed.insert({observe, st.get_value(observe)});
                }
            } catch (No_exist_exception<std::string>& exception) {
                throw No_exist_exception<std::string>{std::string{exception.what()} + ": " + exception.get_key(),
                                                      exception.get_key()};
            }

            co_yield {current_time, observed};

            while (current_time <= end_time) {
                for (auto& reaction_rule : reaction_rules) {
                    reaction_rule.set_delay(st, gen);
                }

                auto reaction = std::min_element(reaction_rules.begin(), reaction_rules.end(),
                                                 [](Reaction_rule const& a, Reaction_rule const& b) -> bool {
                                                     return a.get_delay() < b.get_delay();
                                                 });

                current_time += reaction->get_delay();

                if (std::ranges::all_of(reaction->get_inputs(), [&st](Agent const& agent) -> bool {
                        return st.get_value(agent.get_name()) > 0;
                    })) {
                    for (auto const& agent : reaction->get_inputs()) {
                        st.get_value(agent.get_name())--;
                    }

                    for (auto const& agent : reaction->get_products()) {
                        st.get_value(agent.get_name())++;
                    }
                }

                for (auto const& observe : to_observe) {
                    observed[observe] = st.get_value(observe);
                }

                co_yield {current_time, observed};
            }

            co_return;
        }

        explicit Vessel(std::string name): _name{std::move(name)} {}

        [[nodiscard]] Enviroment environment() const { return this->_env; }

        std::vector<Reaction_rule> get_reaction_rules() const { return this->_reaction_rules; }

        Symbol_table<Key, Value> get_symbol_table() const { return this->_st; }

        // Requirement 3: Implement a generic symbol table to store and lookup objects of user-defined key and value
        // types. Support failure cases when a) the table does not contain a looked up symbol, b) the table already
        // contains a symbol that is being added. Demonstrate the usage of the symbol table with the reactants (names
        // and initial counts).
        Agent add(Key const& name, Value const& num)
        {
            this->_st.insert(name, num);
            return Agent{name};
        }

        void add(Reaction_rule const& reaction_rule) { this->_reaction_rules.push_back(reaction_rule); }

        // Requirement 8: Implement support for multiple computer cores by parallelizing the computation of several
        // simulations at the same time. Estimate the likely (average) value of the hospitalized peak over 100
        // simulations.
        std::vector<std::vector<std::tuple<double, std::unordered_map<Key, int>>>> simulate(
            int end_time, std::vector<Key> const& to_observe, size_t amount, size_t thread_amount = 0)
        {
            auto num_threads = (thread_amount == 0) ? std::jthread::hardware_concurrency() : thread_amount;
            Thread_pool thread_pool{num_threads};
            std::vector<std::vector<std::tuple<double, std::unordered_map<Key, int>>>> simulation_results(amount);
            auto futures = thread_pool.dispatch(
                [this, end_time, to_observe] {
                    std::vector<std::tuple<double, std::unordered_map<Key, int>>> simulation_result{};
                    for (auto& result : this->simulate(end_time, to_observe)) {
                        simulation_result.push_back(result);
                    }
                    return simulation_result;
                },
                amount);

            for (auto& fut : futures) {
                simulation_results.push_back(fut.get());
            }

            return simulation_results;
        }

        void print(Printer<Key, Value> const& printer, std::ostream& stream) const { printer(*this, stream); }
    };
}  // namespace stochastic

#endif