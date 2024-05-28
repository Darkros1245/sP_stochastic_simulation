#ifndef INTRINSIC_H
#define INTRINSIC_H

namespace stochastic {
	class Intrinsic {
	private:
		const double _rate;

	public:
		Intrinsic(double rate): _rate{rate} {}
		
		double get_rate() const;
	};
}

#endif