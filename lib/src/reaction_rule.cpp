#include <numeric>
#include <random>
#include <string>
#include <utility>
#include <vector>

#include "reaction_rule.hpp"
#include "agent.hpp"
#include "intrinsic.hpp"
#include "expr.hpp"
#include "enviroment.hpp"
#include "symbol_table.hpp"

namespace stochastic {
	std::vector<Agent>& Reaction_rule::get_inputs() {
		return this->_inputs;
	}

	std::vector<Agent>& Reaction_rule::get_products() {
		return this->_products;
	}

	Intrinsic Reaction_rule::get_intrinsic() const {
		return this->_intrinsic;
	}

	Reaction_rule Reaction_rule::operator>>=(Expr const& expr) {
		this->_products = std::move(expr.get_agents());
		return *this;
	}

	Reaction_rule Reaction_rule::operator>>=(Agent const& agent) {
		this->_products = { agent };
		return *this;
	}

	Reaction_rule Reaction_rule::operator>>=(Enviroment) {
		return *this;
	}

	void Reaction_rule::set_delay(Symbol_table<std::string, int> st) {
		std::random_device rd;
		std::mt19937_64 gen(rd());

		std::exponential_distribution<> dist(
		    std::accumulate(
		        this->_inputs.begin(), this->_inputs.end(), this->_intrinsic.get_rate(),
		        [&st](auto product, const auto& agent) {
		            return product * st.get_value(agent.get_name());
		        }
		    )
		);

		this->_delay = dist(gen);
	}
	
	double Reaction_rule::get_delay() const {
		return this->_delay;
	}
}