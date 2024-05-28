#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <unordered_map>
#include <string>

#include "duplicate_key_exception.hpp"
#include "no_exist_exception.hpp"

namespace stochastic {
	template <typename Key, typename Value>
	class Symbol_table {
	private:
		std::unordered_map<Key, Value> _map;

	public:
		void insert(Key const& key, Value const& value) {
			if (this->_map.contains(key))
				throw Duplicate_key_exception<std::string>{ std::string{"The provided key already exists"}, key };
			this->_map.insert({key, value});
		
		}

		Value& get_value(Key const& key) {
			if (!this->_map.contains(key))
				throw No_exist_exception<std::string>{ std::string{"The provided key does not exist"}, key };
			return this->_map[key];
		}
	};
}

#endif