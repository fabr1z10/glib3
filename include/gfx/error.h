#pragma once

#include <exception>
#include <string>
#include <sstream>

class Error : public std::exception {
public:
    Error(const std::string& file, long line, const std::string& msg = "") {
        std::stringstream stream;
        stream << file << ", " << line << ": " << msg;
        m_msg = stream.str();
    }
    ~Error() throw() {}
    const char* what() const throw() {
        return m_msg.c_str();
    }
private:
    std::string m_msg;
};

#define GLIB_FAIL(message) { \
	std::ostringstream _glib_msg_stream; \
	_glib_msg_stream << message; \
	throw Error(__FILE__, __LINE__, _glib_msg_stream.str()); \
}


