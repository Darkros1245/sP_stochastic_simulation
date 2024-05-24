#ifndef AGENT_H
#define AGENT_H

#include "intrinsic.hpp"
#include <string>

namespace stochastic {
	class Expr;
	class Reaction_rule;

	class Agent {
	private:
		std::string _name;

	public:
		explicit Agent(std::string const& name): _name{name} {};
		int test(int num);

		[[nodiscard]] std::string get_name() const noexcept;

		Expr operator+(Agent const& agent) const;
		Reaction_rule operator>>(Intrinsic intrinsic) const;
	};
}


#endif