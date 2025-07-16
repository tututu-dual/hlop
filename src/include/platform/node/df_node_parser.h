#ifndef __DF_NODE_PARSER_H__
#define __DF_NODE_PARSER_H__

#include <regex>
#include <string>
#include <vector>

namespace hlop {
/**
 * @brief class df node parser.
 * This class is used to parse node list strings in the format of
 * "node1,node2,node3,..." or "node[1-5],node6,node7,...", etc.
 * Each node can be a single node or a range of nodes.
 */
class df_node_parser {
public:
	static constexpr int NODE_CORES{30};
	static constexpr int NUMA_CORES{4};
	static constexpr int MAX_NETWORK_LEVEL{3};
	static const std::regex NODE_REGEX;
	static const std::regex NODE_LIST_REGEX;

	/**
	 * @brief parse a node list string.
	 * @param node_list_str string, e.g., "node1,node2,node3" or "node[1-5],node6,node7".
	 * @return vector<string>, vector of node names.
	 * @throws hlop_err, if node format is invalid.
	 */
	static const std::vector<std::string> parse_node_list(const std::string &node_list_str);
};
typedef df_node_parser df_node_parser_t;
} // namespace hlop

#endif // __DF_NODE_PARSER_H__