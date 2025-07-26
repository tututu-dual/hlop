#include <string>
#include <string_view>

#include "err.h"
#include "node/df_node.h"
#include "node/df_node_parser.h"

hlop::df_node::df_node(const std::string &node_str)
    : node_name{node_str},
      levels{std::string_view{node_name.c_str(), df_node_parser::TOP_LEVEL_IDX},
             std::string_view{node_name.c_str(), df_node_parser::MID_LEVEL_IDX},
             std::string_view{node_name.c_str(), df_node_parser::BOTTOM_LEVEL_IDX}} {}

bool hlop::df_node::operator==(const node &other) const {
	const auto *other_df_node = dynamic_cast<const df_node *>(&other);
	if (other_df_node == nullptr)
		HLOP_ERR("Cannot compare df_node with non-df_node type");
	return node_name == other_df_node->node_name;
}

bool hlop::df_node::operator!=(const node &other) const {
	return !this->operator==(other);
}

bool hlop::df_node::operator<(const node &other) const {
	const auto *other_df_node = dynamic_cast<const df_node *>(&other);
	if (other_df_node == nullptr)
		HLOP_ERR("Cannot compare df_node with non-df_node type");
	return node_name < other_df_node->node_name;
}

bool hlop::df_node::operator>(const node &other) const {
	return !this->operator<(other) && !this->operator==(other);
}

const std::string &hlop::df_node::name() const {
	return node_name;
}

const int hlop::df_node::max_node_level() const {
	return df_node_parser::MAX_NODE_LEVEL;
}

const int hlop::df_node::node_cores() const {
	return df_node_parser::NODE_CORES;
}

const int hlop::df_node::max_core_level() const {
	return df_node_parser::MAX_CORE_LEVEL;
}

const int hlop::df_node::numa_cores() const {
	return df_node_parser::NUMA_CORES;
}

const int hlop::df_node::ncore_per_numa() const {
	return df_node_parser::NCORE_PER_NUMA;
}

const int hlop::df_node::ncore_per_unit() const {
	return df_node_parser::NCORE_PER_UNIT;
}