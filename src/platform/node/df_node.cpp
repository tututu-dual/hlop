#include <cstddef>
#include <iomanip>
#include <memory>
#include <regex>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "err.h"
#include "node/df_node.h"
#include "node/node.h"

const std::regex hlop::df_node::NODE_LIST_REGEX{R"(([^,\[\]]+\[[^\[\]]+\])|([^,\[\]]+))"};
const std::regex hlop::df_node::NODE_REGEX{R"(([a-zA-Z]\d+)([a-zA-Z]\d+)([a-zA-Z]\d+))"};

const std::vector<hlop::const_node_ptr> hlop::df_node::parse_node_list(const std::string &node_list_str) {
	std::vector<hlop::const_node_ptr> nodes;
	auto node_names = parse_node_list_aux(node_list_str);
	for (const auto &name : node_names)
		nodes.emplace_back(std::make_shared<const hlop::df_node>(name));
	return nodes;
}

const std::vector<std::string> hlop::df_node::parse_node_list_aux(const std::string &node_list_str) {
	std::vector<std::string> nodes;
	auto beg = std::sregex_iterator(node_list_str.begin(), node_list_str.end(),
	                                hlop::df_node::NODE_LIST_REGEX);
	auto end = std::sregex_iterator();

	for (auto it = beg; it != end; ++it) {
		std::string group = it->str();
		std::smatch match;
		std::regex range_re(R"((.*)\[(.*)\])");
		if (!std::regex_match(group, match, range_re)) {
			nodes.emplace_back(group);
			continue;
		}
		std::string prefix = match[1];
		std::string ranges = match[2];
		std::stringstream ss{ranges};
		std::string token;
		while (std::getline(ss, token, ',')) {
			std::size_t dash = token.find('-');
			if (dash == std::string::npos) {
				nodes.emplace_back(prefix + token);
				continue;
			}
			int start = std::stoi(token.substr(0, dash));
			int end = std::stoi(token.substr(dash + 1));
			int width = token.substr(0, dash).size();
			for (int i = start; i <= end; ++i) {
				std::ostringstream oss;
				oss << prefix << std::setw(width) << std::setfill('0') << i;
				nodes.emplace_back(oss.str());
			}
		}
	}
	return nodes;
}

hlop::df_node::df_node(const std::string &node_str)
    : node(node_str),
      node_levels{std::string_view{node_name.c_str(), hlop::df_node::TOP_LEVEL_IDX},
                  std::string_view{node_name.c_str(), hlop::df_node::MID_LEVEL_IDX},
                  std::string_view{node_name.c_str(), hlop::df_node::BOTTOM_LEVEL_IDX}} {
	if (!std::regex_match(node_name, hlop::df_node::NODE_REGEX))
		HLOP_ERR(hlop::format("invalid node format {}", node_name));
}

bool hlop::df_node::operator==(const hlop::node_t &other) const {
	const auto *other_df_node = operator_cast(other);
	return node_name == other_df_node->node_name;
}

bool hlop::df_node::operator!=(const hlop::node_t &other) const {
	return !operator==(other);
}

bool hlop::df_node::operator<(const hlop::node_t &other) const {
	const auto *other_df_node = operator_cast(other);
	return node_name < other_df_node->node_name;
}

bool hlop::df_node::operator>(const hlop::node_t &other) const {
	return !operator<(other) && !operator==(other);
}

const int hlop::df_node::operator-(const hlop::node_t &other) const {
	const auto *other_df_node = operator_cast(other);
	for (int i = 0; i < get_max_node_level(); ++i) {
		if (node_levels[i] != other_df_node->node_levels[i])
			return get_max_node_level() - i - 1;
	}
	HLOP_ERR(hlop::format("undefined net level between {} and {}", name(), other_df_node->name()));
	return -1; // unreachable
}

const hlop::df_node *hlop::df_node::operator_cast(const hlop::node_t &other) const {
	if (this == &other)
		return this;
	const auto *other_df_node = dynamic_cast<const df_node *>(&other);
	if (other_df_node == nullptr)
		HLOP_ERR("cannot compare df_node with non-df_node type");
	return other_df_node;
}

const int hlop::df_node::get_max_node_level() const {
	return hlop::df_node::MAX_NODE_LEVEL;
}

const int hlop::df_node::get_max_core_level() const {
	return hlop::df_node::MAX_CORE_LEVEL;
}

const int hlop::df_node::get_numa_num() const {
	return hlop::df_node::NUMA_NUM;
}

const int hlop::df_node::get_ncore_per_node() const {
	return hlop::df_node::NCORE_PER_NODE;
}

const int hlop::df_node::get_ncore_per_numa() const {
	return hlop::df_node::NCORE_PER_NUMA;
}

const int hlop::df_node::get_ncore_per_unit() const {
	return hlop::df_node::NCORE_PER_UNIT;
}

const std::regex &hlop::df_node::get_node_regex() const {
	return hlop::df_node::NODE_REGEX;
}
