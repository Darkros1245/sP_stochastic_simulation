#ifndef EXPR_HPP
#define EXPR_HPP

#include <vector>

#include "agent.hpp"
#include "intrinsic.hpp"
#include "reaction_rule.hpp"

namespace stochastic {
	class Expr {
	private:
		std::vector<Agent> _agents;

	public:
		std::vector<Agent> get_agents() const;
		Expr operator+(Agent const& agent);
		Reaction_rule operator>>(Intrinsic intrinsic);
	};
}

#endif