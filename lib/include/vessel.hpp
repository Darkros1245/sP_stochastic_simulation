#ifndef VESSEL_H
#define VESSEL_H

#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <coro/coro.hpp>
#include <coro/generator.hpp>
#include <algorithm>
#include <tuple>

#include "printer.hpp"
#include "reaction_rule.hpp"
#include "agent.hpp"
#include "enviroment.hpp"
#include "symbol_table.hpp"
#include "no_exist_exception.hpp"

namespace stochastic
{
    template <typename Key, typename Value>
    class Vessel
    {
    private:
        std::string _name;
        Enviroment _env{};
        Symbol_table<Key, Value> _st{};
        std::vector<Reaction_rule> _reaction_rules;

    public:
        explicit Vessel(std::string name): _name{std::move(name)} {}

        [[nodiscard]] Enviroment environment() const { return this->_env; }

        std::vector<Reaction_rule> get_reaction_rules() const { return this->_reaction_rules; }

        Symbol_table<Key, Value> get_symbol_table() const { return this->_st; }

        Agent add(Key const& name, Value const& num)
        {
            this->_st.insert(name, num);
            return Agent{name};
        }

        void add(Reaction_rule const& reaction_rule) { this->_reaction_rules.push_back(reaction_rule); }

        coro::generator<std::tuple<double, std::unordered_map<Key, int>>> simulate(int end_time,
                                                                                   std::vector<Key> const& to_observe)
        {
            auto current_time = 0.0;

            std::unordered_map<Key, int> observed = {};

            try {
                for (auto const& observe : to_observe) {
                    observed.insert({observe, this->_st.get_value(observe)});
                }
            } catch (No_exist_exception<std::string>& exception) {
                throw No_exist_exception<std::string>{std::string{exception.what()} + ": " + exception.get_key(),
                                                      exception.get_key()};
            }

            co_yield {current_time, observed};

            while (current_time <= end_time) {
                for (auto& reaction_rule : this->_reaction_rules) {
                    reaction_rule.set_delay(this->_st);
                }

                auto reaction = std::min_element(this->_reaction_rules.begin(), this->_reaction_rules.end(),
                                                 [](Reaction_rule const& a, Reaction_rule const& b) -> bool {
                                                     return a.get_delay() < b.get_delay();
                                                 });

                current_time += reaction->get_delay();

                auto& st = this->_st;

                if (std::ranges::all_of(reaction->get_inputs(), [&st](Agent const& agent) -> bool {
                        return st.get_value(agent.get_name()) > 0;
                    })) {
                    for (auto const& agent : reaction->get_inputs()) {
                        this->_st.get_value(agent.get_name())--;
                    }

                    for (auto const& agent : reaction->get_products()) {
                        this->_st.get_value(agent.get_name())++;
                    }
                }

                for (auto const& observe : to_observe) {
                    observed[observe] = this->_st.get_value(observe);
                }

                co_yield {current_time, observed};
            }

            co_return;
        }

        void print(Printer<Key, Value> const& printer, std::ostream& stream) const { printer(*this, stream); }
    };
}  // namespace stochastic

#endif