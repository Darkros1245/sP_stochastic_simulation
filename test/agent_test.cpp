#include <doctest/doctest.h>
#include "agent.hpp"

TEST_CASE("Agent_test") {
	SUBCASE("test_test") {
		Agent agent {};
		CHECK(agent.test(5) == 10);
	}
}