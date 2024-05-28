#ifndef PRETTY_PRINTER_HPP
#define PRETTY_PRINTER_HPP

#include "printer.hpp"
#include "vessel.hpp"
#include "agent.hpp"
#include "intrinsic.hpp"
#include "enviroment.hpp"
#include "symbol_table.hpp"

namespace stochastic {
	template<typename Key, typename Value>
	class Pretty_printer : public Printer<Key, Value> {
	public:
		inline void operator()(Agent const& agent, Symbol_table<Key, Value> st, std::string const& seperator) const {
			std::cout << seperator << agent.get_name() << ":" << st.get_value(agent.get_name());
		}

		inline void operator()(Intrinsic const& intrinsic) const {
			std::cout << " >> " << intrinsic.get_rate() << " >>= ";
		}

		inline void operator()(Enviroment) const {
			std::cout << "enviroment";
		}

		inline void operator()(Vessel<Key, Value> const& vessel) const override {
			for (auto & reaction_rule : vessel.get_reaction_rules()) {
				std::string seperator;		// Default value of string is ""
				for (auto const& agent : reaction_rule.get_inputs()) {
					(*this)(agent, vessel.get_symbol_table(), seperator);
					seperator = " + ";
				}
				(*this)(reaction_rule.get_intrinsic());
				if (reaction_rule.get_products().size() == 0) {
					(*this)(vessel.environment());
				} else {
					seperator = "";
					for (auto const& agent : reaction_rule.get_products()) {
						(*this)(agent, vessel.get_symbol_table(), seperator);
						seperator = " + ";
					}
				}
				std::cout << std::endl;
			}
		}
	};
}

#endif