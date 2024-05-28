#ifndef NETWORK_GRAPH_PRINTER_H
#define NETWORK_GRAPH_PRINTER_H

#include <format>
#include <iostream>
#include <string>
#include <fstream>

#include "could_not_open_file_exception.hpp"
#include "printer.hpp"
#include "vessel.hpp"
#include "agent.hpp"
#include "intrinsic.hpp"
#include "enviroment.hpp"

namespace stochastic {
	template<typename Key, typename Value>
	class Network_graph : public Printer<Key, Value> {
	private:
		std::string _path;

	public:
		explicit Network_graph<Key, Value>(std::string path): _path{std::move(path)} {}

		inline void operator()(Agent const& agent, std::ofstream & ostream) const {
			ostream << std::format(R"({}[label="{}",shape="box",style="filled",fillcolor="cyan"];)", agent.get_name(), agent.get_name()) << "\n";
		}

		inline void operator()(Intrinsic const& intrinsic, int i, std::ofstream & ostream) const {
			ostream << std::format(R"(I{}[label="{}",shape="oval",style="filled",fillcolor="yellow"];)", i, intrinsic.get_rate()) << "\n";
		}

		inline void operator()(Enviroment, std::ofstream & ostream) const {
			ostream << std::format(R"({}[label="{}",shape="box",style="filled",fillcolor="purple"];)", "env", "env") << "\n";
		}

		inline void operator()(Vessel<Key, Value> const& vessel) const override {
			std::ofstream ostream { this->_path };

			if (!ostream.is_open()) {
				throw Could_not_open_file_exception{ "Could not open file: " + this->_path };
			}

			ostream << "digraph {\n";

			int i = 0;

			for (auto & reaction_rule : vessel.get_reaction_rules()) {
				for (auto const& agent : reaction_rule.get_inputs()) {
					(*this)(agent, ostream);
					ostream << std::format("{} -> I{}", agent.get_name(), i) << "\n";
				}

				(*this)(reaction_rule.get_intrinsic(), i, ostream);
				
				if (reaction_rule.get_products().size() == 0) {
					(*this)(vessel.environment(), ostream);
					ostream << std::format("I{} -> env", i) << "\n";
				} else {
					for (auto const& agent : reaction_rule.get_products()) {
						(*this)(agent, ostream);
						ostream << std::format("I{} -> {}", i, agent.get_name()) << "\n";
					}
				}
				i++;
			}
			ostream << "}";
		}
	};
}

#endif