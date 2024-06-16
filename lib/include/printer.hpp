#ifndef PRINTER_HPP
#define PRINTER_HPP

#include "symbol_table.hpp"
#include <ostream>

namespace stochastic
{
    template <Hashable Key, Numeric Value>
    class Vessel;

    // Requirement 2: Provide pretty-printing of the reaction network in a) human readable format and b) network graph (e.g. Fig. 4).
    template <Hashable Key, Numeric Value>
    class Printer
    {
    public:
        Printer() = default;
        virtual ~Printer() noexcept = default;
        virtual void operator()(Vessel<Key, Value> const& vessel, std::ostream& stream) const = 0;
    };
}  // namespace stochastic

#endif