#include <utility>

#include "expr.hpp"
#include "reaction_rule.hpp"
#include "intrinsic.hpp"
#include "agent.hpp"

namespace stochastic
{
    [[nodiscard]] std::vector<Agent> Expr::get_agents() const noexcept { return this->_agents; }

    Expr Expr::operator+(Agent const& agent)
    {
        this->_agents.push_back(agent);
        return *this;
    }

    Reaction_rule Expr::operator>>(Intrinsic intrinsic) { return {std::move(this->_agents), intrinsic, {}}; }
}  // namespace stochastic