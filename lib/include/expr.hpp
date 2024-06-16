#ifndef EXPR_HPP
#define EXPR_HPP

#include <vector>

#include "agent.hpp"
#include "intrinsic.hpp"
#include "reaction_rule.hpp"

namespace stochastic
{
    class Expr
    {
    private:
        std::vector<Agent> _agents;

    public:
        [[nodiscard]] std::vector<Agent> get_agents() const noexcept;

        // Requirement 1: The library should overload operators to support the reaction rule typesetting directly in C++ code.
        Expr operator+(Agent const& agent);
        Reaction_rule operator>>(Intrinsic intrinsic);
    };
}  // namespace stochastic

#endif