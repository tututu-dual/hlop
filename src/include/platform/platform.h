#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include <iostream>
#include <regex>
#include <string>
#include <vector>

namespace hlop {
/**
 * @brief enum class platform.
 * The platforms are:
 * - DF
 * - TH
 * - UNKNOWN
 */
enum class platform {
	DF,
	TH,
	UNKNOWN
};
typedef platform platform_t;

std::ostream &operator<<(std::ostream &os, const hlop::platform &p);

/**
 * @brief class node_parser.
 * This class provides methods to parse node information based on the platform.
 * All methods are factory methods, meaning they return static values based on the platform type.
 */
class node_parser {
public:
	static const int get_node_cores(hlop::platform_t pf);
	static const int get_numa_cores(hlop::platform_t pf);
	static const int get_max_network_level(hlop::platform_t pf);
	static const std::regex &get_node_regex(hlop::platform_t pf);
	static const std::vector<std::string> parser_node_list(hlop::platform_t pf, const std::string &node_list_str);
};
} // namespace hlop

#endif // __PLATFORM_H__