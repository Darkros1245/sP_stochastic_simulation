#ifndef NETWORK_GRAPH_PRINTER_H
#define NETWORK_GRAPH_PRINTER_H

#include <format>

#include "printer.hpp"
#include "symbol_table.hpp"
#include "vessel.hpp"
#include "agent.hpp"
#include "intrinsic.hpp"
#include "enviroment.hpp"

namespace stochastic
{
    // Requirement 2: Provide pretty-printing of the reaction network in a) human readable format and b) network graph
    // (e.g. Fig. 4).
    template <Hashable Key, Numeric Value>
    class Network_graph : public Printer<Key, Value>
    {
    public:
        inline void operator()(Agent const& agent, std::ostream& ostream) const
        {
            ostream << std::format(R"({}[label="{}",shape="box",style="filled",fillcolor="cyan"];)", agent.get_name(),
                                   agent.get_name())
                    << "\n";
        }

        inline void operator()(Intrinsic const& intrinsic, int i, std::ostream& ostream) const
        {
            ostream << std::format(R"(I{}[label="{}",shape="oval",style="filled",fillcolor="yellow"];)", i,
                                   intrinsic.get_rate())
                    << "\n";
        }

        inline void operator()(Enviroment, std::ostream& ostream) const
        {
            ostream << std::format(R"({}[label="{}",shape="box",style="filled",fillcolor="purple"];)", "env", "env")
                    << "\n";
        }

        inline void operator()(Vessel<Key, Value> const& vessel, std::ostream& stream) const override
        {
            stream << "digraph {\n";

            int i = 0;

            for (auto& reaction_rule : vessel.get_reaction_rules()) {
                for (auto const& agent : reaction_rule.get_inputs()) {
                    (*this)(agent, stream);
                    stream << std::format("{} -> I{}", agent.get_name(), i) << "\n";
                }

                (*this)(reaction_rule.get_intrinsic(), i, stream);

                if (reaction_rule.get_products().size() == 0) {
                    (*this)(vessel.environment(), stream);
                    stream << std::format("I{} -> env", i) << "\n";
                } else {
                    for (auto const& agent : reaction_rule.get_products()) {
                        (*this)(agent, stream);
                        stream << std::format("I{} -> {}", i, agent.get_name()) << "\n";
                    }
                }
                i++;
            }
            stream << "}";
        }
    };
}  // namespace stochastic

#endif