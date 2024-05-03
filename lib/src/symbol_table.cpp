#include "symbol_table.hpp"
#include "duplicate_key_exception.hpp"
#include "no_exist_exception.hpp"
#include <string>

namespace stochastic {
	template <typename Key, typename Value>
	void Symbol_table<Key, Value>::insert(Key const& key, Value const& value) {
		if (this->_map.contains(key))
			throw Duplicate_key_exception{std::string{"The provided key already exists"}};
		this->_map.insert({key, value});
	
	}

	template <typename Key, typename Value>
	Value& Symbol_table<Key, Value>::get_value(Key const& key) {
		if (!this->_map.contains(key))
			throw No_exist_exception{std::string{"The provided key does not exist"}};
		return this->_map[key];
	}

}