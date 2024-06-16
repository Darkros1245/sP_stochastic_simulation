#include <doctest/doctest.h>

#include "intrinsic.hpp"

// Requirement 9: Implement unit tests (e.g. test symbol table methods, their failure cases, and pretty-printing of reaction rules).
TEST_CASE("Intrinsic_test")
{
    SUBCASE("Intrinsic_get_rate_test")
    {
        auto const rate = 5;
        const stochastic::Intrinsic intrinsic{rate};

        CHECK(intrinsic.get_rate() == rate);
    }

    SUBCASE("Intrinsic_equals_test")
    {
        const stochastic::Intrinsic intrinsic{5};

        CHECK(intrinsic == intrinsic);
    }
}