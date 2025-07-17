#include <iostream>

#include "aux.h"
#include "node/df_node_parser.h"
#include "platform.h"

std::ostream &hlop::operator<<(std::ostream &os, const hlop::platform &p) {
	os << hlop::enum_name(p);
	return os;
}

const int hlop::node_parser::get_node_cores(hlop::platform_t pf) {
	switch (pf) {
	case hlop::platform::DF:
		return hlop::df_node_parser::NODE_CORES;
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
		return hlop::df_node_parser::NUMA_CORES;
	case hlop::platform::TH:
		HLOP_ERR("TH platform is not implemented yet");
		return -1; // unreachable
	default:
		HLOP_ERR("unknown platform type");
		return -1; // unreachable
	}
}

const int hlop::node_parser::get_max_network_level(hlop::platform_t pf) {
	switch (pf) {
	case hlop::platform::DF:
		return hlop::df_node_parser::MAX_NETWORK_LEVEL;
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
		return hlop::df_node_parser::NODE_REGEX;
	case hlop::platform::TH:
		HLOP_ERR("TH platform is not implemented yet");
		return hlop::df_node_parser::NODE_REGEX; // placeholder
	default:
		HLOP_ERR("unknown platform type");
		return hlop::df_node_parser::NODE_REGEX; // placeholder
	}
}

const std::vector<std::string> hlop::node_parser::parser_node_list(hlop::platform_t pf, const std::string &node_list_str) {
	switch (pf) {
	case hlop::platform::DF:
		return hlop::df_node_parser::parse_node_list(node_list_str);
	case hlop::platform::TH:
		HLOP_ERR("TH platform is not implemented yet");
		return hlop::df_node_parser::parse_node_list(node_list_str); // placeholder
	default:
		HLOP_ERR("unknown platform type");
		return hlop::df_node_parser::parse_node_list(node_list_str); // placeholder
	}
}