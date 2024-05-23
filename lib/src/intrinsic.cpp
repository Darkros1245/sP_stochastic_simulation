#include "intrinsic.hpp"

namespace stochastic {
	double Intrinsic::get_rate() const {
		return this->_rate;
	}

	double Intrinsic::operator*(double lhs) const {
		return this->_rate * lhs;
	}
}