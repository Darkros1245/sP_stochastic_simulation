#ifndef REACTION_RULE_HPP
#define REACTION_RULE_HPP

#include <random>
#include <utility>
#include <vector>

#include "agent.hpp"
#include "enviroment.hpp"
#include "intrinsic.hpp"
#include "symbol_table.hpp"

namespace stochastic
{
    class Reaction_rule
    {
    private:
        std::vector<Agent> _inputs;
        std::vector<Agent> _products;
        Intrinsic _intrinsic;
        double _delay{};

    public:
        Reaction_rule(std::vector<Agent> inputs, Intrinsic intrinsic, std::vector<Agent> products):
            _inputs{std::move(inputs)}, _products{std::move(products)}, _intrinsic{intrinsic}
        {}

        std::vector<Agent>& get_inputs();
        std::vector<Agent>& get_products();
        Intrinsic get_intrinsic() const;

        Reaction_rule operator>>=(Expr const& expr);
        Reaction_rule operator>>=(Agent const& agent);
        Reaction_rule operator>>=(Enviroment);

        template <typename Key, typename Value>
        void set_delay(Symbol_table<Key, Value> st)
        {
            std::random_device rd;
            std::mt19937_64 gen(rd());

            std::exponential_distribution<> dist(std::accumulate(
                this->_inputs.begin(), this->_inputs.end(), this->_intrinsic.get_rate(),
                [&st](auto product, const auto& agent) { return product * st.get_value(agent.get_name()); }));

            this->_delay = dist(gen);
        }
        double get_delay() const;
    };
}  // namespace stochastic

#endif