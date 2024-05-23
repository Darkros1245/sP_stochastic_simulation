#include "agent.hpp"
#include "expr.hpp"

namespace stochastic {
	int Agent::test(int num) {
		return num + num;
	}

	std::string Agent::get_name() const {
		return this->_name;
	}

	Expr Agent::operator+(Agent const& agent) const {
		Expr expr{};
		return { expr + *this + agent };
	}

	Reaction_rule Agent::operator>>(Intrinsic intrinsic) const {
		return { { *this }, intrinsic, {} };
	}
}

