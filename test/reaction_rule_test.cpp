#include <doctest/doctest.h>
#include <ranges>
#include <string>
#include <vector>
#include <random>

#include "agent.hpp"
#include "enviroment.hpp"
#include "expr.hpp"
#include "intrinsic.hpp"
#include "reaction_rule.hpp"
#include "vessel.hpp"

// Requirement 9: Implement unit tests (e.g. test symbol table methods, their failure cases, and pretty-printing of reaction rules).
TEST_CASE("Reaction_rule_test")
{
    SUBCASE("Reaction_rule_get_input_test")
    {
        const std::vector<stochastic::Agent> inputs{stochastic::Agent{"agent1"}, stochastic::Agent{"agent2"}};
        const stochastic::Intrinsic intrinsic{5};
        const std::vector<stochastic::Agent> outputs{};
        stochastic::Reaction_rule rr{inputs, intrinsic, outputs};

        for (auto const& [i, input] : rr.get_inputs() | std::ranges::views::enumerate) {
            CHECK(input == inputs[i]);
        }
    }

    SUBCASE("Reaction_rule_get_product_test")
    {
        const std::vector<stochastic::Agent> inputs{};
        const stochastic::Intrinsic intrinsic{5};
        const std::vector<stochastic::Agent> outputs{stochastic::Agent{"agent1"}, stochastic::Agent{"agent2"}};
        stochastic::Reaction_rule rr{inputs, intrinsic, outputs};

        for (auto const& [i, input] : rr.get_inputs() | std::ranges::views::enumerate) {
            CHECK(input == outputs[i]);
        }
    }

    SUBCASE("Reaction_rule_get_intrinsic_test")
    {
        const std::vector<stochastic::Agent> inputs{};
        const stochastic::Intrinsic intrinsic{5};
        const std::vector<stochastic::Agent> outputs{};
        stochastic::Reaction_rule rr{inputs, intrinsic, outputs};

        CHECK(rr.get_intrinsic() == intrinsic);
    }

    SUBCASE("Reaction_rule_operator>>=Expr_test")
    {
        const std::vector<stochastic::Agent> inputs{};
        const stochastic::Intrinsic intrinsic{5};
        const std::vector<stochastic::Agent> outputs{};
        const stochastic::Agent agent1{"agent1"};
        const stochastic::Agent agent2{"agent2"};
        const auto expr = agent1 + agent2;
        stochastic::Reaction_rule rr{inputs, intrinsic, outputs};
        rr >>= expr;

        for (auto const& [i, input] : rr.get_products() | std::ranges::views::enumerate) {
            CHECK(input == expr.get_agents()[i]);
        }
    }

    SUBCASE("Reaction_rule_operator>>=Agent_test")
    {
        const std::vector<stochastic::Agent> inputs{};
        const stochastic::Intrinsic intrinsic{5};
        const std::vector<stochastic::Agent> outputs{};
        const stochastic::Agent agent{"agent"};
        stochastic::Reaction_rule rr{inputs, intrinsic, outputs};
        rr >>= agent;

        CHECK(rr.get_products()[0] == agent);
    }

    SUBCASE("Reaction_rule_operator>>=Enviroment_test")
    {
        const std::vector<stochastic::Agent> inputs{};
        const stochastic::Intrinsic intrinsic{5};
        const std::vector<stochastic::Agent> outputs{};
        const stochastic::Enviroment enviroment{};
        stochastic::Reaction_rule rr{inputs, intrinsic, outputs};
        rr >>= enviroment;

        CHECK(rr.get_products().empty());
    }

    SUBCASE("Reaction_rule_get_and_set_delay_test")
    {
        stochastic::Vessel<std::string, int> vessel{""};
        const auto agent = vessel.add("agent", 5);
        const std::vector<stochastic::Agent> inputs{agent};
        const stochastic::Intrinsic intrinsic{5};
        const std::vector<stochastic::Agent> outputs{};
        stochastic::Reaction_rule rr{inputs, intrinsic, outputs};

        std::random_device rd;
        std::mt19937_64 gen(rd());

        rr.set_delay(vessel.get_symbol_table(), gen);

        CHECK(rr.get_delay() >= 0);
    }
}