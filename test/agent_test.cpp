#include <doctest/doctest.h>
#include <string>
#include <vector>

#include "agent.hpp"
#include "expr.hpp"
#include "intrinsic.hpp"

// Requirement 9: Implement unit tests (e.g. test symbol table methods, their failure cases, and pretty-printing of
// reaction rules).
TEST_CASE("Agent_test")
{
    SUBCASE("Agent_get_name_test")
    {
        const std::string name{"test"};
        const stochastic::Agent agent{name};

        CHECK(agent.get_name() == name);
    }

    SUBCASE("Agent_addition_test")
    {
        const stochastic::Agent agent1{"agent1"};
        const stochastic::Agent agent2{"agent2"};
        auto expr = agent1 + agent2;

        CHECK(expr.get_agents()[0].get_name() == agent1.get_name());
        CHECK(expr.get_agents()[1].get_name() == agent2.get_name());
    }

    SUBCASE("Agent_to_reaction_rule_test")
    {
        const stochastic::Agent agent{"agent"};
        const stochastic::Intrinsic intrinsic{0};
        auto reaction_rule = agent >> intrinsic;

        CHECK(reaction_rule.get_inputs()[0].get_name() == agent.get_name());
        CHECK(reaction_rule.get_intrinsic().get_rate() == intrinsic.get_rate());
        CHECK(reaction_rule.get_products().empty());
    }

    SUBCASE("Agent_equals_test")
    {
        const stochastic::Agent agent{"agent"};
        CHECK(agent == agent);
    }
}