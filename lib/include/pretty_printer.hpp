#ifndef PRETTY_PRINTER_HPP
#define PRETTY_PRINTER_HPP

#include "printer.hpp"
#include "vessel.hpp"
#include "agent.hpp"
#include "intrinsic.hpp"
#include "enviroment.hpp"
#include "symbol_table.hpp"

namespace stochastic
{
    template <typename Key, typename Value>
    class Pretty_printer : public Printer<Key, Value>
    {
    public:
        inline void operator()(Agent const& agent, Symbol_table<Key, Value> st, std::string const& seperator,
                               std::ostream& stream) const
        {
            stream << seperator << agent.get_name() << ":" << st.get_value(agent.get_name());
        }

        inline void operator()(Intrinsic const& intrinsic, std::ostream& stream) const
        {
            stream << " >> " << intrinsic.get_rate() << " >>= ";
        }

        inline void operator()(Enviroment, std::ostream& stream) const { stream << "enviroment"; }

        inline void operator()(Vessel<Key, Value> const& vessel, std::ostream& stream) const override
        {
            for (auto& reaction_rule : vessel.get_reaction_rules()) {
                std::string seperator;  // Default value of string is ""
                for (auto const& agent : reaction_rule.get_inputs()) {
                    (*this)(agent, vessel.get_symbol_table(), seperator, stream);
                    seperator = " + ";
                }
                (*this)(reaction_rule.get_intrinsic(), stream);
                if (reaction_rule.get_products().size() == 0) {
                    (*this)(vessel.environment(), stream);
                } else {
                    seperator = "";
                    for (auto const& agent : reaction_rule.get_products()) {
                        (*this)(agent, vessel.get_symbol_table(), seperator, stream);
                        seperator = " + ";
                    }
                }
                stream << "\n";
            }
        }
    };
}  // namespace stochastic

#endif