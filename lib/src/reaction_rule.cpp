#include <vector>

#include "reaction_rule.hpp"
#include "agent.hpp"
#include "intrinsic.hpp"
#include "expr.hpp"
#include "enviroment.hpp"

namespace stochastic
{
    std::vector<Agent>& Reaction_rule::get_inputs() { return this->_inputs; }

    std::vector<Agent>& Reaction_rule::get_products() { return this->_products; }

    Intrinsic Reaction_rule::get_intrinsic() const { return this->_intrinsic; }

    Reaction_rule Reaction_rule::operator>>=(Expr const& expr)
    {
        this->_products = expr.get_agents();
        return *this;
    }

    Reaction_rule Reaction_rule::operator>>=(Agent const& agent)
    {
        this->_products = {agent};
        return *this;
    }

    Reaction_rule Reaction_rule::operator>>=(Enviroment) { return *this; }

    double Reaction_rule::get_delay() const { return this->_delay; }
}  // namespace stochastic