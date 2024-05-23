#include <doctest/doctest.h>
#include "agent.hpp"

TEST_CASE("Agent_test") {
	SUBCASE("test_test") {
		stochastic::Agent agent { "test" };
		CHECK(agent.test(5) == 10);
	}
}