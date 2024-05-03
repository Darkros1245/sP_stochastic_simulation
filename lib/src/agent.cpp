#include "agent.hpp"

namespace stochastic {
	int Agent::test(int num) {
		return num + num;
	}

	int Agent::get_quantity() const {
		return this->_quantity;
	}

	void Agent::inc_quantity() {
		this->_quantity++;
	}

	void Agent::dec_quantity() {
		this->_quantity--;
	}
}

