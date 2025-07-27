#ifndef __DF_NODE_H__
#define __DF_NODE_H__

#include <array>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

#include "node/node.h"

namespace hlop {
class df_node : public node {
public:
	using df_node_t = hlop::df_node;
	using df_node_ptr = std::shared_ptr<hlop::df_node>;
	using df_node_ptr_t = df_node_ptr;
	using const_df_node_ptr = std::shared_ptr<const hlop::df_node>;
	using const_df_node_ptr_t = const_df_node_ptr;

public:
	static constexpr int MAX_NODE_LEVEL{3};
	static constexpr int MAX_CORE_LEVEL{3};
	static constexpr int NUMA_NUM{4};
	static constexpr int NCORE_PER_NODE{30};
	static constexpr int NCORE_PER_NUMA{8};
	static constexpr int NCORE_PER_UNIT{4};
	static constexpr int TOP_LEVEL_IDX{3};
	static constexpr int MID_LEVEL_IDX{5};
	static constexpr int BOTTOM_LEVEL_IDX{8};
	static const std::regex NODE_REGEX;
	static const std::regex NODE_LIST_REGEX;

public:
	/**
	 * @brief parse a node list string.
	 * @param node_list_str string, e.g., "node1,node2,node3" or "node[1-5],node6,node7".
	 * @return vector<node>, vector of hlop::node objects.
	 * @throws hlop_err, if node format is invalid.
	 */
	static const std::vector<hlop::const_node_ptr> parse_node_list(const std::string &node_list_str);

private:
	/**
	 * @brief parse a node list string.
	 * @param node_list_str string, e.g., "node1,node2,node3" or "node[1-5],node6,node7".
	 * @return vector<string>, vector of node names.
	 * @throws hlop_err, if node format is invalid.
	 */
	static const std::vector<std::string> parse_node_list_aux(const std::string &node_list_str);

public:
	/**
	 * @brief default constructor of df_node.
	 * @note This constructor is not accessible directly and should not be used.
	 * It is provided to prevent the creation of an empty df_node.
	 */
	df_node() = delete;
	/**
	 * @brief constructor of df_node with levels.
	 * @param node_str string, the name of the node.
	 */
	df_node(const std::string &node_str);
	~df_node() = default;

public:
	bool operator==(const hlop::node_t &other) const override;
	bool operator!=(const hlop::node_t &other) const override;
	bool operator<(const hlop::node_t &other) const override;
	bool operator>(const hlop::node_t &other) const override;
	const int operator-(const hlop::node_t &other) const override;

private:
	/**
	 * @brief cast this node to df_node.
	 * @param other node_t, the node to cast.
	 * @return const df_node *, the casted df_node pointer.
	 * @throws hlop_err, if other is not a df_node type.
	 */
	const df_node *operator_cast(const hlop::node_t &other) const;

public:
	const int get_max_node_level() const override;
	const int get_max_core_level() const override;
	const int get_numa_num() const override;
	const int get_ncore_per_node() const override;
	const int get_ncore_per_numa() const override;
	const int get_ncore_per_unit() const override;
	const std::regex &get_node_regex() const override;

private:
	const std::array<std::string_view, hlop::df_node::MAX_NODE_LEVEL> node_levels;
};
typedef df_node::df_node_t df_node_t;
typedef df_node::df_node_ptr df_node_ptr;
typedef df_node::df_node_ptr_t df_node_ptr_t;
typedef df_node::const_df_node_ptr const_df_node_ptr;
typedef df_node::const_df_node_ptr_t const_df_node_ptr_t;
} // namespace hlop

#endif // __DF_NODE_H__