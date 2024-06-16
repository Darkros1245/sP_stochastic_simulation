#ifndef COULD_NOT_OPEN_FILE_EXCEPTION_H
#define COULD_NOT_OPEN_FILE_EXCEPTION_H

#include <stdexcept>

namespace stochastic
{
    class Could_not_open_file_exception : public std::runtime_error
    {
    private:
        std::string _msg;

    public:
        explicit Could_not_open_file_exception(std::string const& msg): std::runtime_error{msg}, _msg{msg} {}
        const char* what() const noexcept override { return this->_msg.c_str(); }
    };
}  // namespace stochastic

#endif