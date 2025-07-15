#ifndef __DF_NODE_PARSER_H__
#define __DF_NODE_PARSER_H__

#include <regex>
#include <string>
#include <vector>

namespace hlop {
class df_node_parser {
public:
	static constexpr int NODE_CORES{30};
	static constexpr int NUMA_CORES{4};
	static constexpr int MAX_NETWORK_LEVEL{3};
	static const std::regex NODE_REGEX;

	/// @brief resolving node list string
	/// @param node_list_str
	/// @return
	static const std::vector<std::string> parse_node_list(const std::string &node_list_str);

private:
	static const std::regex NODE_LIST_REGEX;
};
typedef df_node_parser df_node_parser_t;
} // namespace hlop

#endif // __DF_NODE_PARSER_H__