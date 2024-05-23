#ifndef CONSTANT_H
#define CONSTANT_H

namespace stochastic {
	class Intrinsic {
	private:
		const double _rate;

	public:
		Intrinsic(double rate): _rate{rate} {}
		double get_rate() const;
		double operator*(double lhs) const;
	};
}

#endif