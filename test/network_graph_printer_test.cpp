#include <doctest/doctest.h>
#include <string>
#include <sstream>

#include "agent.hpp"
#include "enviroment.hpp"
#include "expr.hpp"
#include "intrinsic.hpp"
#include "network_graph_printer.hpp"
#include "reaction_rule.hpp"
#include "vessel.hpp"

// Requirement 9: Implement unit tests (e.g. test symbol table methods, their failure cases, and pretty-printing of
// reaction rules).
TEST_CASE("Network_graph_printer_test")
{
    SUBCASE("Network_graph_printer_agent_test")
    {
        stochastic::Network_graph<std::string, int> ng{};
        const stochastic::Agent agent{"agent"};
        std::ostringstream ss;
        ng(agent, ss);

        const auto expected = std::format(R"({}[label="{}",shape="box",style="filled",fillcolor="cyan"];{})",
                                          agent.get_name(), agent.get_name(), "\n");

        CHECK(ss.str() == expected);
    }

    SUBCASE("Network_graph_printer_intrinsic_test")
    {
        stochastic::Network_graph<std::string, int> ng{};
        const stochastic::Intrinsic intrinsic{5};
        std::ostringstream ss;
        int num = 0;
        ng(intrinsic, num, ss);

        const auto expected = std::format(R"(I{}[label="{}",shape="oval",style="filled",fillcolor="yellow"];{})", num,
                                          intrinsic.get_rate(), "\n");

        CHECK(ss.str() == expected);
    }

    SUBCASE("Network_graph_printer_enviroment_test")
    {
        stochastic::Network_graph<std::string, int> ng{};
        const stochastic::Enviroment enviroment{};
        std::ostringstream ss;
        ng(enviroment, ss);

        const auto expected =
            std::format(R"({}[label="{}",shape="box",style="filled",fillcolor="purple"];{})", "env", "env", "\n");

        CHECK(ss.str() == expected);
    }

    SUBCASE("Network_graph_printer_vessel_with_product_test")
    {
        stochastic::Network_graph<std::string, int> ng{};
        stochastic::Vessel<std::string, int> vessel{""};
        stochastic::Agent agent1{"agent1"};
        stochastic::Agent agent2{"agent2"};
        stochastic::Agent agent3{"agent3"};
        stochastic::Agent agent4{"agent4"};
        const stochastic::Intrinsic intrinsic{5};
        stochastic::Reaction_rule rr{(agent1 + agent2) >> intrinsic >>= agent3 + agent4};
        vessel.add(rr);
        std::ostringstream ss;
        auto num = 0;

        ng(vessel, ss);

        const auto expected = "digraph {\n" +
                              std::format(R"({}[label="{}",shape="box",style="filled",fillcolor="cyan"];{})",
                                          agent1.get_name(), agent1.get_name(), "\n") +
                              std::format("{} -> I{}{}", agent1.get_name(), num, "\n") +
                              std::format(R"({}[label="{}",shape="box",style="filled",fillcolor="cyan"];{})",
                                          agent2.get_name(), agent2.get_name(), "\n") +
                              std::format("{} -> I{}{}", agent2.get_name(), num, "\n") +
                              std::format(R"(I{}[label="{}",shape="oval",style="filled",fillcolor="yellow"];{})", num,
                                          intrinsic.get_rate(), "\n") +
                              std::format(R"({}[label="{}",shape="box",style="filled",fillcolor="cyan"];{})",
                                          agent3.get_name(), agent3.get_name(), "\n") +
                              std::format("I{} -> {}{}", num, agent3.get_name(), "\n") +
                              std::format(R"({}[label="{}",shape="box",style="filled",fillcolor="cyan"];{})",
                                          agent4.get_name(), agent4.get_name(), "\n") +
                              std::format("I{} -> {}{}", num, agent4.get_name(), "\n") + "}";

        CHECK(ss.str() == expected);
    }

    SUBCASE("Network_graph_printer_vessel_with_enviroment_test")
    {
        stochastic::Network_graph<std::string, int> ng{};
        stochastic::Vessel<std::string, int> vessel{""};
        stochastic::Agent agent1{"agent1"};
        stochastic::Agent agent2{"agent2"};
        stochastic::Enviroment enviroment{};
        const stochastic::Intrinsic intrinsic{5};
        stochastic::Reaction_rule rr{(agent1 + agent2) >> intrinsic >>= enviroment};
        vessel.add(rr);
        std::ostringstream ss;
        auto num = 0;

        ng(vessel, ss);

        const auto expected =
            "digraph {\n" +
            std::format(R"({}[label="{}",shape="box",style="filled",fillcolor="cyan"];{})", agent1.get_name(),
                        agent1.get_name(), "\n") +
            std::format("{} -> I{}{}", agent1.get_name(), num, "\n") +
            std::format(R"({}[label="{}",shape="box",style="filled",fillcolor="cyan"];{})", agent2.get_name(),
                        agent2.get_name(), "\n") +
            std::format("{} -> I{}{}", agent2.get_name(), num, "\n") +
            std::format(R"(I{}[label="{}",shape="oval",style="filled",fillcolor="yellow"];{})", num,
                        intrinsic.get_rate(), "\n") +
            std::format(R"({}[label="{}",shape="box",style="filled",fillcolor="purple"];{})", "env", "env", "\n") +
            std::format("I{} -> env{}", num, "\n") + "}";

        CHECK(ss.str() == expected);
    }
}