#ifndef __AUX_H__
#define __AUX_H__

#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "err.h"
#include "magic_enum/magic_enum.hpp"
#include "msg.h"

namespace hlop {
/// @brief check whether the given number is the power of 2
/// @param x
/// @return return true when x is the power of 2
bool is_pof2(int x);

/// @brief round up x to the minimum power of 2 number
/// @param x int32
/// @return return the minimum number
int pof2_ceil(int x);

/// @brief round down x to the maximum power of 2 number
/// @param x int32
/// @return return the minimum number
int pof2_floor(int x);

/// @brief convert string list to vector
/// @tparam T value type
/// @param l string list
/// @param skip skip begin n item
/// @return return vector of item in this string
template <typename T>
const std::vector<T> stov(const std::string &l, int skip = 0) {
	std::vector<T> res;
	std::stringstream ss{l};
	std::string item;
	int count = 0;
	while (std::getline(ss, item, ',')) {
		if (count < skip) {
			++count;
			continue;
		}
		std::stringstream iss(item);
		T value;
		iss >> value;
		if (iss.fail() || !iss.eof())
			HLOP_ERR(hlop::format("cannot convert '{}' to target type", item));
		res.push_back(value);
	}
	return std::move(res);
}

/// @brief convert vector to string list
/// @tparam T value type
/// @param v vector
/// @return return string contain the item in vector, split by ","
template <typename T>
const std::string vtos(const std::vector<T> &v) {
	std::ostringstream oss;
	for (const auto &i : v)
		oss << i << ", ";
	return oss.str();
}

template <typename Enum>
std::string_view enum_name(Enum e) {
	const auto &name = magic_enum::enum_name(e);
	if (name.empty())
		HLOP_ERR("invalid enum value");
	return name;
}

template <typename Enum>
Enum enum_cast(const std::string &name) {
	const auto e = magic_enum::enum_cast<Enum>(name);
	if (!e.has_value())
		HLOP_ERR(hlop::format("invalid enum name: {}", name));
	return e.value();
}
} // namespace hlop

#endif // __AUX_H__