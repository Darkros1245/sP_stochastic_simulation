#ifndef DUPLICATE_KEY_EXCEPTION_H
#define DUPLICATE_KEY_EXCEPTION_H

#include <stdexcept>

namespace stochastic {
	class Duplicate_key_exception : public std::runtime_error {
	private:
		std::string _msg;
	public:
		explicit Duplicate_key_exception(const std::string& msg): std::runtime_error(msg), _msg{msg} {}
		const char* what() const noexcept override {
			return this->_msg.c_str();
		}
	};
}


#endif