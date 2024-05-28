#include <string>

#include "expr.hpp"
#include "vessel.hpp"

inline stochastic::Vessel<std::string, int> exponential_decay(int A_amount, int B_amount, int C_amount) {
	auto v = stochastic::Vessel<std::string, int>{"Exponential decay"};
	
	const auto lambda = 0.001;
	const auto A = v.add("A", A_amount);
	const auto B = v.add("B", B_amount);
	const auto C = v.add("C", C_amount);

	v.add((A + C) >> lambda >>= B + C);

	return v;
}