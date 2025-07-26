#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "aux.h"
#include "node/df_node.h"
#include "node/node.h"
#include "platform.h"

std::ostream &hlop::operator<<(std::ostream &os, const hlop::platform_t &p) {
	os << hlop::enum_name(p);
	return os;
}

const int hlop::node_parser::get_max_node_level(hlop::platform_t pf) {
	switch (pf) {
	case hlop::platform::DF:
		return hlop::df_node::MAX_NODE_LEVEL;
	case hlop::platform::TH:
		HLOP_ERR("TH platform is not implemented yet");
		return -1; // unreachable
	default:
		HLOP_ERR("unknown platform type");
		return -1; // unreachable
	}
}

const int hlop::node_parser::get_node_cores(hlop::platform_t pf) {
	switch (pf) {
	case hlop::platform::DF:
		return hlop::df_node::NODE_CORES;
	case hlop::platform::TH:
		HLOP_ERR("TH platform is not implemented yet");
		return -1; // unreachable
	default:
		HLOP_ERR("unknown platform type");
		return -1; // unreachable
	}
}

const int hlop::node_parser::get_max_core_level(hlop::platform_t pf) {
	switch (pf) {
	case hlop::platform::DF:
		return hlop::df_node::MAX_CORE_LEVEL;
	case hlop::platform::TH:
		HLOP_ERR("TH platform is not implemented yet");
		return -1; // unreachable
	default:
		HLOP_ERR("unknown platform type");
		return -1; // unreachable
	}
}

const int hlop::node_parser::get_numa_cores(hlop::platform_t pf) {
	switch (pf) {
	case hlop::platform::DF:
		return hlop::df_node::NUMA_CORES;
	case hlop::platform::TH:
		HLOP_ERR("TH platform is not implemented yet");
		return -1; // unreachable
	default:
		HLOP_ERR("unknown platform type");
		return -1; // unreachable
	}
}

const int hlop::node_parser::get_ncore_per_numa(hlop::platform_t pf) {
	switch (pf) {
	case hlop::platform::DF:
		return hlop::df_node::NCORE_PER_NUMA;
	case hlop::platform::TH:
		HLOP_ERR("TH platform is not implemented yet");
		return -1; // unreachable
	default:
		HLOP_ERR("unknown platform type");
		return -1; // unreachable
	}
}

const int hlop::node_parser::get_ncore_per_unit(hlop::platform_t pf) {
	switch (pf) {
	case hlop::platform::DF:
		return hlop::df_node::NCORE_PER_UNIT;
	case hlop::platform::TH:
		HLOP_ERR("TH platform is not implemented yet");
		return -1; // unreachable
	default:
		HLOP_ERR("unknown platform type");
		return -1; // unreachable
	}
}

const std::regex &hlop::node_parser::get_node_regex(hlop::platform_t pf) {
	switch (pf) {
	case hlop::platform::DF:
		return hlop::df_node::NODE_REGEX;
	case hlop::platform::TH:
		HLOP_ERR("TH platform is not implemented yet");
		return hlop::df_node::NODE_REGEX; // placeholder
	default:
		HLOP_ERR("unknown platform type");
		return hlop::df_node::NODE_REGEX; // placeholder
	}
}

const std::regex &hlop::node_parser::get_node_list_regex(hlop::platform_t pf) {
	switch (pf) {
	case hlop::platform::DF:
		return hlop::df_node::NODE_LIST_REGEX;
	case hlop::platform::TH:
		HLOP_ERR("TH platform is not implemented yet");
		return hlop::df_node::NODE_LIST_REGEX; // placeholder
	default:
		HLOP_ERR("unknown platform type");
		return hlop::df_node::NODE_LIST_REGEX; // placeholder
	}
}

const std::vector<hlop::const_node_ptr> hlop::node_parser::parse_node_list(hlop::platform_t pf, const std::string &node_list_str) {
	switch (pf) {
	case hlop::platform::DF:
		return hlop::df_node::parse_node_list(node_list_str);
	case hlop::platform::TH:
		HLOP_ERR("TH platform is not implemented yet");
		return hlop::df_node::parse_node_list(node_list_str); // placeholder
	default:
		HLOP_ERR("unknown platform type");
		return hlop::df_node::parse_node_list(node_list_str); // placeholder
	}
}