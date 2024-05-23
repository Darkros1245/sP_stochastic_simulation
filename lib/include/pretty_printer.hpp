#ifndef PRETTY_PRINTER_HPP
#define PRETTY_PRINTER_HPP

#include "vessel.hpp"
#include "agent.hpp"
#include "intrinsic.hpp"
#include "enviroment.hpp"
#include "symbol_table.hpp"

namespace stochastic {
	class Pretty_printer {
	public:
		void operator()(Agent const& agent, Symbol_table<std::string, int> st, std::string const& seperator) const;
		void operator()(Intrinsic const& intrinsic) const;
		void operator()(Enviroment) const;
		void operator()(Vessel const& vessel) const;
	};
}

#endif