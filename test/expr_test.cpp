#include <doctest/doctest.h>

#include "agent.hpp"
#include "expr.hpp"

// Requirement 9: Implement unit tests (e.g. test symbol table methods, their failure cases, and pretty-printing of reaction rules).
TEST_CASE("Expr_test")
{
    SUBCASE("Expr_get_agents_test")
    {
        std::string const name{"test"};
        const stochastic::Agent agent{"test"};

        auto const expr = stochastic::Expr{} + agent;

        CHECK(expr.get_agents()[0].get_name() == name);
    }

    SUBCASE("Expr_addition_test")
    {
        const stochastic::Agent agent{"agent"};
        auto const expr = stochastic::Expr{} + agent;

        CHECK(expr.get_agents()[0].get_name() == agent.get_name());
    }

    SUBCASE("Expr_to_reaction_rule_test")
    {
        const stochastic::Agent agent{"agent"};
        const stochastic::Intrinsic intrinsic{0};
        auto expr = stochastic::Expr{} + agent;
        auto reaction_rule = expr >> intrinsic;

        CHECK(reaction_rule.get_inputs()[0].get_name() == agent.get_name());
        CHECK(reaction_rule.get_intrinsic().get_rate() == intrinsic.get_rate());
        CHECK(reaction_rule.get_products().empty());
    }
}