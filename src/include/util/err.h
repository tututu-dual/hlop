#ifndef __ERR_H__
#define __ERR_H__

#include <stdexcept>

#include "msg.h"

#define HLOP_ERR(msg) \
	throw hlop_err { __FILE__, __func__, __LINE__, (msg) }

namespace {
/// @note use HLOP_ERR instead of this class
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