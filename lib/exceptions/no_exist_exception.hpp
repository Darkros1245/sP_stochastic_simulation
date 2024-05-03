#ifndef NO_EXIST_EXCEPTION_H
#define NO_EXIST_EXCEPTION_H

#include <stdexcept>

namespace stochastic {
	class No_exist_exception : public std::runtime_error {
	private:
		std::string _msg;
	public:
		explicit No_exist_exception(const std::string& msg): std::runtime_error(msg), _msg{msg} {}
		const char* what() const noexcept override {
			return this->_msg.c_str();
		}
	};
}


#endif