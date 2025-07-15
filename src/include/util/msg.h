#ifndef __MSG_H__
#define __MSG_H__

#include <cstddef>
#include <sstream>
#include <string>

namespace {
inline void format_impl(std::ostringstream &oss, const std::string &fmt) {
	oss << fmt;
}

template <typename T, typename... Args>
inline void format_impl(std::ostringstream &oss, const std::string &fmt, T value, Args... args) {
	std::size_t pos = fmt.find("{}");
	if (pos != std::string::npos) {
		oss << fmt.substr(0, pos) << value;
		format_impl(oss, fmt.substr(pos + 2), args...);
	} else {
		oss << fmt << std::endl;
	}
}
} // namespace

namespace hlop {
template <typename... Args>
const std::string format(const std::string &fmt, Args... args) {
	std::ostringstream oss;
	format_impl(oss, fmt, args...);
	return oss.str();
}
} // namespace hlop

#endif // __MSG_H__