#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <unordered_map>

namespace stochastic {
	template <typename Key, typename Value>
	class Symbol_table {
	private:
		std::unordered_map<Key, Value> _map;

	public:
		void insert(Key const& key, Value const& value);
		Value& get_value(Key const& key);
	};
}

#endif