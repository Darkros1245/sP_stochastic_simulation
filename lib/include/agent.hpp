#ifndef AGENT_H
#define AGENT_H

#include "enviroment.hpp"
#include <string>

namespace stochastic {
	class Agent {
	private:
		std::string _name;
		int _quantity;

	public:
		Agent(std::string const& name, int quantity): _name(name), _quantity(quantity) {};
		int test(int num);

		int get_quantity() const;
		void inc_quantity();
		void dec_quantity();

		Agent operator+(Agent const& other) const;
		Agent operator>>(int delta) const;
		Agent operator>>=(Agent const& other) const;
		Agent operator>>=(Enviroment const& env) const;
	};
}


#endif