#include <doctest/doctest.h>

#include "intrinsic.hpp"

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