#include <doctest/doctest.h>
#include <string>

#include "symbol_table.hpp"

// Requirement 9: Implement unit tests (e.g. test symbol table methods, their failure cases, and pretty-printing of reaction rules).
TEST_CASE("Symbol_table_test")
{
    SUBCASE("Symbol_table_insert_and_get_value_no_exeption_test")
    {
        stochastic::Symbol_table<std::string, int> st{};
        const auto name = std::string{"agent"};
        const auto value = 5;
        st.insert(name, value);

        CHECK(st.get_value(name) == value);
    }

    SUBCASE("Symbol_table_insert_exeption_test")
    {
        stochastic::Symbol_table<std::string, int> st{};
        const auto name = std::string{"agent"};
        const auto value = 5;
        st.insert(name, value);

        try {
            st.insert(name, value);
        } catch (stochastic::Duplicate_key_exception<std::string> const&) {
            CHECK(true);
        } catch (...) {
            CHECK(false);
        }
    }

    SUBCASE("Symbol_table_get_value_exeption_test")
    {
        stochastic::Symbol_table<std::string, int> st{};
        const auto name = std::string{"agent"};
        const auto value = 5;
        st.insert(name, value);

        try {
            st.get_value("not_agent");
        } catch (stochastic::No_exist_exception<std::string> const&) {
            CHECK(true);
        } catch (...) {
            CHECK(false);
        }
    }
}