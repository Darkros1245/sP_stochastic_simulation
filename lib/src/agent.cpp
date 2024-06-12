#include "agent.hpp"
#include "expr.hpp"

namespace stochastic
{
    std::string Agent::get_name() const noexcept { return this->_name; }

    Expr Agent::operator+(Agent const& agent) const { return {Expr{} + *this + agent}; }

    Reaction_rule Agent::operator>>(Intrinsic intrinsic) const { return {{*this}, intrinsic, {}}; }

    bool Agent::operator==(Agent const& other) const { return this->_name == other.get_name(); }
}  // namespace stochastic
