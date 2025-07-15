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
/**
 * @brief check whether the given number is the power of 2
 * @param x int, given number
 * @return return true when x is the power of 2
 * @throw hlop_err, if x is not a positive integer
 */
bool is_pof2(int x);

/**
 * @brief round up to the next power of 2
 * @param x: int32, given number
 * @return return the next power of 2 of x
 * @throw hlop_err, if x is not a positive integer
 */
int pof2_ceil(int x);

/**
 * @brief  round down to the previous power of 2
 * @param x int32, given number
 * @return return the previous power of 2 of x
 * @throw hlop_err, if x is not a positive integer
 */
int pof2_floor(int x);

/**
 * @brief string to vector conversion
 * @tparam T type of the vector item
 * @param l string, string format like "1,2,3,4,5"
 * @param skip int, default 0, number of items to skip from the beginning
 * @return vector<T>, converted from the string
 * @throw hlop_err, if the string contains invalid items
 * @note The string is split by comma, and the items are converted to type T.
 * If the conversion fails, an hlop_err is thrown.
 * If skip is greater than the number of items, the result will be empty.
 * If skip is negative, it will be treated as 0.
 * If the string is empty, an empty vector will be returned.
 */
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

/**
 * @brief vector to string conversion
 * @tparam T type of the vector item
 * @param v vector<T>, vector to be converted
 * @return string, converted from the vector like "1, 2, 3, 4, 5, "
 */
template <typename T>
const std::string vtos(const std::vector<T> &v) {
	std::ostringstream oss;
	for (const auto &i : v)
		oss << i << ", ";
	return oss.str();
}

/**
 * @brief enum to string conversion
 * @tparam Enum enum type
 * @param e Enum, enum value
 * @return string_view, the name of the enum value
 * @throw hlop_err, if the enum value is invalid
 * @note This function uses magic_enum to convert enum to string.
 * It will throw an hlop_err if the enum value is not valid.
 */
template <typename Enum>
std::string_view enum_name(Enum e) {
	const auto &name = magic_enum::enum_name(e);
	if (name.empty())
		HLOP_ERR("invalid enum value");
	return name;
}

/**
 * @brief string to enum conversion
 * @tparam Enum enum type
 * @param name string, the name of the enum value
 * @return Enum, the enum value
 * @throw hlop_err, if the name is not a valid enum name
 * @note This function uses magic_enum to convert string to enum.
 * It will throw an hlop_err if the name is not a valid enum name.
 */
template <typename Enum>
Enum enum_cast(const std::string &name) {
	const auto e = magic_enum::enum_cast<Enum>(name);
	if (!e.has_value())
		HLOP_ERR(hlop::format("invalid enum name: {}", name));
	return e.value();
}
} // namespace hlop

#endif // __AUX_H__