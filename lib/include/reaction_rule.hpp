#ifndef REACTION_RULE_HPP
#define REACTION_RULE_HPP

#include <string>
#include <utility>
#include <vector>

#include "agent.hpp"
#include "enviroment.hpp"
#include "intrinsic.hpp"
#include "symbol_table.hpp"

namespace stochastic {
	class Reaction_rule {
	private:
		std::vector<Agent> _inputs;
		std::vector<Agent> _products;
		Intrinsic _intrinsic;
		double _delay{};

	public:
		Reaction_rule(std::vector<Agent> inputs, Intrinsic intrinsic, std::vector<Agent> products): _inputs{std::move(inputs)}, _products{std::move(products)}, _intrinsic{intrinsic} {}
		
		std::vector<Agent>& get_inputs();
		std::vector<Agent>& get_products();
		Intrinsic get_intrinsic() const;
		
		Reaction_rule operator>>=(Expr const& expr);
		Reaction_rule operator>>=(Agent const& agent);
		Reaction_rule operator>>=(Enviroment);

		void set_delay(Symbol_table<std::string, int> st);
		double get_delay() const;
	};
}

#endif