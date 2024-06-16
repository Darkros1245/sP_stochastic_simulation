#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <concepts>
#include <cstddef>
#include <type_traits>
#include <unordered_map>
#include <string>

#include "duplicate_key_exception.hpp"
#include "no_exist_exception.hpp"

namespace stochastic
{
    template<typename T>
    concept Numeric = std::is_arithmetic_v<T>;

    template<typename T>
    concept Hashable = requires(T a) {
        { std::hash<T>{}(a) } -> std::same_as<std::size_t>;
    };

    // Requirement 3: Implement a generic symbol table to store and lookup objects of user-defined key and value types. Support
    // failure cases when a) the table does not contain a looked up symbol, b) the table already contains a symbol that
    // is being added. Demonstrate the usage of the symbol table with the reactants (names and initial counts).
    template <Hashable Key, Numeric Value>
    class Symbol_table
    {
    private:
        std::unordered_map<Key, Value> _map{};

    public:
        void insert(Key const& key, Value const& value)
        {
            if (this->_map.contains(key))
                throw Duplicate_key_exception<std::string>{std::string{"The provided key already exists"}, key};
            this->_map.insert({key, value});
        }

        Value& get_value(Key const& key)
        {
            if (!this->_map.contains(key))
                throw No_exist_exception<std::string>{std::string{"The provided key does not exist"}, key};
            return this->_map[key];
        }
    };
}  // namespace stochastic

#endif