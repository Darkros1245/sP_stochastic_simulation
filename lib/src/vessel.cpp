#include <algorithm>
#include <iostream>

#include "vessel.hpp"
#include "agent.hpp"
#include "enviroment.hpp"

namespace stochastic {
	Enviroment Vessel::environment() const {
		return this->_env;
	}

	Agent Vessel::add(std::string const& name, int num) {
		this->_st.insert(name, num);
		return Agent { name };
	}

	void Vessel::add(Reaction_rule const& reaction_rule) {
		this->_reaction_rules.push_back(reaction_rule);
	}

	void Vessel::simulate(int end_time) {
		auto current_time = 0.0;
		while (current_time <= end_time) {
			for (auto & reaction_rule : this->_reaction_rules) {
				reaction_rule.set_delay(this->_st);
			}

			auto reaction = std::min_element(
				this->_reaction_rules.begin(), 
				this->_reaction_rules.end(),
				[](Reaction_rule const& a, Reaction_rule const& b) -> bool {
					return a.get_delay() < b.get_delay(); 
				}
			);
			current_time += reaction->get_delay();
			std::cout << "Delay" << reaction->get_delay() << std::endl;

			auto & st = this->_st;

			if (std::ranges::all_of(reaction->get_inputs(), [&st](Agent const& agent) -> bool { return st.get_value(agent.get_name()) > 0; })) {
				for (auto & agent : reaction->get_inputs()) {
					this->_st.get_value(agent.get_name())--;
				}

				for (auto & agent : reaction->get_products()) {
					this->_st.get_value(agent.get_name())++;
				}
			}

			std::cout << "At time: " << current_time << std::endl;
			std::cout << "---------------------------------------" << std::endl;
			std::cout << "Inputs:" << std::endl;
			for (auto & agent : reaction->get_inputs()) {
				std::cout << agent.get_name() << ":" << this->_st.get_value(agent.get_name()) << std::endl;
			}

			std::cout << "Outputs:" << std::endl;
			for (auto & agent : reaction->get_products()) {
				std::cout << agent.get_name() << ":" << this->_st.get_value(agent.get_name()) << std::endl;
			}
		}
	}

	std::vector<Reaction_rule> Vessel::get_reaction_rules() const {
		return this->_reaction_rules;
	}

	Symbol_table<std::string, int> Vessel::get_symbol_table() const {
		return this->_st;
	}
}