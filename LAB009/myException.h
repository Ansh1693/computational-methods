#ifndef MYEXCEPTION_H_INCLUDED
#define MYEXCEPTION_H_INCLUDED
#include <exception>
#include <string>

class myException: public std::exception {
protected:
    /* Error message      */
std::string msg;
public:
    /* Constructor (C strings). */
    explicit myException(const char* message) : msg(message) {}
    /* Constructor (C++ STL strings). */
    explicit myException(const std::string& message) : msg(message) {}
    /* Destructor. Virtual to allow for subclassing if required. */
    virtual ~myException() noexcept {}
    /* Returns a pointer to the (constant) error description. */
    virtual const char* what() const noexcept { return msg.c_str(); }
};
#endif // MYEXCEPTION_H_INCLUDED
