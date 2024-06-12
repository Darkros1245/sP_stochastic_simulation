#include "intrinsic.hpp"

namespace stochastic
{
    double Intrinsic::get_rate() const { return this->_rate; }

    bool Intrinsic::operator==(Intrinsic const& other) const { return this->_rate == other.get_rate(); }
}  // namespace stochastic