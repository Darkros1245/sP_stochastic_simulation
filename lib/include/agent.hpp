#ifndef AGENT_H
#define AGENT_H

#include <string>

#include "intrinsic.hpp"

namespace stochastic
{
    class Expr;
    class Reaction_rule;

    class Agent
    {
    private:
        std::string _name;

    public:
        explicit Agent(std::string const& name): _name{name} {};

        [[nodiscard]] std::string get_name() const noexcept;

        Expr operator+(Agent const& agent) const;
        Reaction_rule operator>>(Intrinsic intrinsic) const;

        bool operator==(Agent const& other) const;
    };
}  // namespace stochastic

#endif