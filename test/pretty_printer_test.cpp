#include <doctest/doctest.h>
#include <format>
#include <sstream>

#include "agent.hpp"
#include "expr.hpp"
#include "pretty_printer.hpp"
#include "symbol_table.hpp"

TEST_CASE("Pretty_printer_test")
{
    SUBCASE("Pretty_printer_agent_test_without_seperator")
    {
        stochastic::Pretty_printer<std::string, int> pp{};
        stochastic::Agent const agent{"agent"};
        stochastic::Symbol_table<std::string, int> st{};
        st.insert("agent", 5);
        std::string seperator;

        std::ostringstream ss;
        pp(agent, st, seperator, ss);

        auto const expected = std::format("{}{}:{}", seperator, agent.get_name(), st.get_value(agent.get_name()), "\n");

        CHECK(ss.str() == expected);
    }

    SUBCASE("Pretty_printer_agent_test_with_seperator")
    {
        stochastic::Pretty_printer<std::string, int> pp{};
        stochastic::Agent const agent{"agent"};
        stochastic::Symbol_table<std::string, int> st{};
        st.insert("agent", 5);
        std::string seperator = "+";

        std::ostringstream ss;
        pp(agent, st, seperator, ss);

        auto const expected = std::format("{}{}:{}", seperator, agent.get_name(), st.get_value(agent.get_name()), "\n");

        CHECK(ss.str() == expected);
    }

    SUBCASE("Pretty_printer_intrinsic_test")
    {
        stochastic::Pretty_printer<std::string, int> pp{};
        stochastic::Intrinsic const intrinsic{5};
        std::ostringstream ss;
        pp(intrinsic, ss);

        auto const expected = std::format(" >> {} >>= ", intrinsic.get_rate(), "\n");

        CHECK(ss.str() == expected);
    }

    SUBCASE("Pretty_printer_enviroment_test")
    {
        stochastic::Pretty_printer<std::string, int> pp{};
        stochastic::Enviroment const enviroment{};
        std::ostringstream ss;
        pp(enviroment, ss);

        auto const expected = std::format("enviroment");

        CHECK(ss.str() == expected);
    }

    SUBCASE("Pretty_printer_vessel_with_product_test")
    {
        stochastic::Pretty_printer<std::string, int> pp{};
        stochastic::Vessel<std::string, int> vessel{""};
        auto agent1 = vessel.add("agent1", 1);
        auto agent2 = vessel.add("agent2", 2);
        auto agent3 = vessel.add("agent3", 3);
        auto agent4 = vessel.add("agent4", 4);
        stochastic::Intrinsic const intrinsic{5};
        stochastic::Reaction_rule rr{(agent1 + agent2) >> intrinsic >>= agent3 + agent4};
        vessel.add(rr);
        std::ostringstream ss;

        pp(vessel, ss);

        auto const expected =
            std::format("{}:{} + {}:{} >> {} >>= {}:{} + {}:{}{}", agent1.get_name(),
                        vessel.get_symbol_table().get_value(agent1.get_name()), agent2.get_name(),
                        vessel.get_symbol_table().get_value(agent2.get_name()), intrinsic.get_rate(), agent3.get_name(),
                        vessel.get_symbol_table().get_value(agent3.get_name()), agent4.get_name(),
                        vessel.get_symbol_table().get_value(agent4.get_name()), "\n");

        CHECK(ss.str() == expected);
    }

    SUBCASE("Pretty_printer_vessel_with_enviroment_test")
    {
        stochastic::Pretty_printer<std::string, int> pp{};
        stochastic::Vessel<std::string, int> vessel{""};
        auto agent1 = vessel.add("agent1", 1);
        auto agent2 = vessel.add("agent2", 2);
        stochastic::Enviroment enviroment{};
        stochastic::Intrinsic const intrinsic{5};
        stochastic::Reaction_rule rr{(agent1 + agent2) >> intrinsic >>= enviroment};
        vessel.add(rr);
        std::ostringstream ss;

        pp(vessel, ss);

        auto const expected = std::format("{}:{} + {}:{} >> {} >>= {}{}", agent1.get_name(),
                                          vessel.get_symbol_table().get_value(agent1.get_name()), agent2.get_name(),
                                          vessel.get_symbol_table().get_value(agent2.get_name()), intrinsic.get_rate(),
                                          "enviroment", "\n");

        CHECK(ss.str() == expected);
    }
}