#include <iostream>
#include <string>

#include "pretty_printer.hpp"
#include "agent.hpp"
#include "intrinsic.hpp"
#include "enviroment.hpp"
#include "reaction_rule.hpp"
#include "vessel.hpp"


namespace stochastic {
	void Pretty_printer::operator()(Agent const& agent, Symbol_table<std::string, int> st, std::string const& seperator) const {
		std::cout << seperator << agent.get_name() << ":" << st.get_value(agent.get_name());
	}

	void Pretty_printer::operator()(Intrinsic const& intrinsic) const {
		std::cout << " >> " << intrinsic.get_rate() << " >>= ";
	}

	void Pretty_printer::operator()(Enviroment) const {
		std::cout << "enviroment";
	}

	void Pretty_printer::operator()(Vessel const& vessel) const {
		for (auto & reaction_rule : vessel.get_reaction_rules()) {
			std::string seperator;
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
}
