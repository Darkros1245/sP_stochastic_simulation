#include "vessel.hpp"
#include "agent.hpp"
#include "enviroment.hpp"
#include "symbol_table.hpp"

namespace stochastic {
	Enviroment Vessel::environment() const {
		return this->env;
	}

	Agent Vessel::add(std::string const& name, int num) {
		this->_st.insert(name, num);
		return Agent {name, num};
	}

}