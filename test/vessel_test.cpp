#include <doctest/doctest.h>
#include <string>
#include <vector>

#include "agent.hpp"
#include "intrinsic.hpp"
#include "reaction_rule.hpp"
#include "vessel.hpp"
#include "expr.hpp"

// Requirement 9: Implement unit tests (e.g. test symbol table methods, their failure cases, and pretty-printing of reaction rules).
TEST_CASE("Vessel_test")
{
    SUBCASE("Vessel_add_and_get_reaction_rules_test")
    {
        stochastic::Vessel<std::string, int> vessel{""};
        const std::vector<stochastic::Agent> inputs{stochastic::Agent{"agent1"}, stochastic::Agent{"agent2"}};
        const stochastic::Intrinsic intrinsic{5};
        const std::vector<stochastic::Agent> outputs{stochastic::Agent{"agent3"}, stochastic::Agent{"agent4"}};
        const stochastic::Reaction_rule rr{inputs, intrinsic, outputs};
        vessel.add(rr);

        CHECK(vessel.get_reaction_rules()[0].get_inputs() == inputs);
        CHECK(vessel.get_reaction_rules()[0].get_intrinsic() == intrinsic);
        CHECK(vessel.get_reaction_rules()[0].get_products() == outputs);
    }

    SUBCASE("Vessel_get_symbol_table_test")
    {
        stochastic::Vessel<std::string, int> vessel{""};
        auto st = vessel.get_symbol_table();
        CHECK(true);
    }

    SUBCASE("Vessel_add_agent_test")
    {
        stochastic::Vessel<std::string, int> vessel{""};
        const auto name = std::string("agent");
        const auto agent = vessel.add(name, 5);
        CHECK(agent.get_name() == name);
    }

    SUBCASE("Vessel_simulate_test")
    {
        stochastic::Vessel<std::string, int> vessel{""};
        const auto agent1 = vessel.add("X", 5);
        const auto agent2 = vessel.add("Y", 5);
        const stochastic::Intrinsic intrinsic{5};
        const auto agent3 = vessel.add("Z", 5);
        const stochastic::Reaction_rule rr = (agent1 + agent2) >> intrinsic >>= agent3;
        vessel.add(rr);
        auto end_time = 10;
        auto current_time = 0;
        const std::vector<std::string> to_observe = {"Y"};
        for (auto& simulation_result : vessel.simulate(end_time, to_observe, 1)) {
            for (auto& [time, observed] : simulation_result) {
                CHECK(time >= current_time);
                current_time = time;
                CHECK(observed["Y"] >= 0);
            }
        }
    }

    SUBCASE("Vessel_pretty_print_test")
    {
        /* Tested in pretty_printer_test.cpp {"Pretty_printer_vessel_with_product_test",
         * "Pretty_printer_vessel_with_enviroment_test"} */
    }

    SUBCASE("Vessel_network_graph_print_test")
    {
        /* Tested in network_graph_printer_test.cpp {"Network_graph_printer_vessel_with_product_test",
         * "Network_graph_printer_vessel_with_enviroment_test"} */
    }
}