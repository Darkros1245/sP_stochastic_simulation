#ifndef VESSEL_H
#define VESSEL_H

#include <string>
#include <utility>

#include "agent.hpp"
#include "enviroment.hpp"
#include "symbol_table.hpp"

namespace stochastic {
	class Vessel {
	private:
		std::string	_name;
		Enviroment env {};
		Symbol_table<std::string, int> _st;

	public:
		explicit Vessel(std::string name): _name{std::move(name)} {}

		[[nodiscard]] Enviroment environment() const;
		Agent add(std::string const& name, int num);
	};
}

#endif