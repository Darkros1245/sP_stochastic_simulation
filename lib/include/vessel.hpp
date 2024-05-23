#ifndef VESSEL_H
#define VESSEL_H

#include <string>
#include <utility>
#include <vector>

#include "reaction_rule.hpp"
#include "agent.hpp"
#include "enviroment.hpp"
#include "symbol_table.hpp"

namespace stochastic {
	class Vessel {
	private:
		std::string	_name;
		Enviroment _env {};
		Symbol_table<std::string, int> _st {};
		std::vector<Reaction_rule> _reaction_rules;

	public:
		explicit Vessel(std::string name): _name{std::move(name)} {}

		[[nodiscard]] Enviroment environment() const;
		std::vector<Reaction_rule> get_reaction_rules() const;
		Symbol_table<std::string, int> get_symbol_table() const;
		Agent add(std::string const& name, int num);
		void add(Reaction_rule const& reaction_rule);
		void simulate(int end_time);
	};
}

#endif