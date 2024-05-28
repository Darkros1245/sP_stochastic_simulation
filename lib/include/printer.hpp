#ifndef PRINTER_HPP
#define PRINTER_HPP

namespace stochastic {
	template<typename Key, typename Value>
	class Vessel;

	template<typename Key, typename Value>
	class Printer {
	public:
		Printer() = default;
		virtual ~Printer() noexcept = default;
		virtual void operator()(Vessel<Key, Value> const& vessel) const = 0;
	};
}

#endif