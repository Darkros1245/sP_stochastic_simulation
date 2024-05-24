#ifndef DUPLICATE_KEY_EXCEPTION_H
#define DUPLICATE_KEY_EXCEPTION_H

#include <stdexcept>

namespace stochastic {
	template<typename TKey>
	class Duplicate_key_exception : public std::runtime_error {
	private:
		std::string _msg;
		TKey _key;
	public:
		explicit Duplicate_key_exception(std::string const& msg, TKey const& key): std::runtime_error{msg}, _msg{msg}, _key{key} {}
		const char* what() const noexcept override {
			return this->_msg.c_str();
		}

		TKey get_key() {
			return this->_key;
		}
	};
}


#endif