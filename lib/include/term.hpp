#ifndef TERM_H
#define TERM_H

#include "expr.hpp"

namespace stochastic {
	class Term {
	public:
		Expr operator+(Term const& lhs, Term const& rhs);
	};
}

#endif