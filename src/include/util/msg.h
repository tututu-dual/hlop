#ifndef __MSG_H__
#define __MSG_H__

#include <cstddef>
#include <sstream>
#include <string>

namespace {
/**
 * @brief helper function to format a string with multiple arguments.
 * @param oss ostringstream, the output stream to write the formatted string to.
 * @param fmt string, the format string containing placeholders.
 */
inline void format_impl(std::ostringstream &oss, const std::string &fmt) {
	oss << fmt;
}

/**
 * @brief helper function to format a string with multiple arguments.
 * @tparam T type of the first argument.
 * @tparam Args types of the remaining arguments.
 * @param oss ostringstream, the output stream to write the formatted string to.
 * @param fmt string, the format string containing placeholders.
 */
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
/**
 * @brief format a string with multiple arguments.
 * @tparam Args types of the arguments to format into the string.
 * @param fmt string, the format string containing placeholders.
 * @param args Args, values to format into the string.
 * @return string, the formatted string.
 */
template <typename... Args>
const std::string format(const std::string &fmt, Args... args) {
	std::ostringstream oss;
	format_impl(oss, fmt, args...);
	return oss.str();
}
} // namespace hlop

#endif // __MSG_H__