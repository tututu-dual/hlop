#ifndef __ERR_H__
#define __ERR_H__

#include <stdexcept>
#include <string>

#include "msg.h"

#define HLOP_ERR(msg) \
	throw hlop_err { __FILE__, __func__, __LINE__, (msg) }

namespace {
/**
 * @brief class hlop err.
 * hlop_err is a runtime error class for hlop library.
 * It provides a formatted error message with file, function, and line number.
 * @note Use HLOP_ERR instead of this class.
 * This class is for internal use only.
 * Using HLOP_ERR will provide a formatted error message.
 */
class hlop_err : public std::runtime_error {
public:
	hlop_err(const char *file, const char *func, int line, const std::string &msg)
	    : std::runtime_error(hlop::format("[{}:{}]@{}: {}", file, line, func, msg)) {}
	hlop_err(const char *file, const char *func, int line, const char *msg)
	    : std::runtime_error(hlop::format("[{}:{}]@{}: {}", file, line, func, msg)) {}
	hlop_err(const hlop_err &other)
	    : std::runtime_error(other.what()) {}
	hlop_err &operator=(const hlop_err &other) {
		if (this != &other) {
			std::runtime_error::operator=(other);
		}
		return *this;
	}
};
} // namespace

#endif // __ERR_H__