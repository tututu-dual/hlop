#include <algorithm>
#include <iostream>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

#include "aux.h"
#include "err.h"
#include "msg.h"
#include "node/df_node_parser.h"
#include "platform.h"
#include "struct/node_list.h"
#include "struct/type.h"

const std::unordered_map<hlop::rank_arrange, std::function<int(int, int)>> hlop::node_list::rank_arrange_map = {
    {hlop::rank_arrange::BLOCK, [](int rank, int nnode) -> int { return rank / nnode; }},
    {hlop::rank_arrange::CYCLIC, [](int rank, int nnode) -> int { return rank % nnode; }},
    {hlop::rank_arrange::PLANE, [](int rank, int nnode) -> int {
	     HLOP_ERR("plane rank arrangement is not implemented yet");
	     return -1; // unreachable
     }},
    {hlop::rank_arrange::ARBITRARY, [](int rank, int nnode) -> int {
	     HLOP_ERR("arbitrary rank arrangement is not implemented yet");
	     return -1; // unreachable
     }}};

hlop::node_list::node_list(hlop::platform_t pf, const std::string &node_list_str, int ppn) {
	if (ppn > hlop::df_node_parser::NODE_CORES)
		HLOP_ERR(hlop::format("number of process per node(={}) must less equal to {}", ppn, hlop::df_node_parser::NODE_CORES));

	switch (pf) {
	case hlop::platform::DF:
		nlist = hlop::df_node_parser::parse_node_list(node_list_str);
		platform = hlop::platform::DF;
		node_cores = hlop::df_node_parser::NODE_CORES;
		numa_cores = hlop::df_node_parser::NUMA_CORES;
		max_network_level = hlop::df_node_parser::MAX_NETWORK_LEVEL;
		nproc_per_node = ppn;
		node_regex = hlop::df_node_parser::NODE_REGEX;
		break;
	case hlop::platform::TH:
		HLOP_ERR("TH platform is not implemented yet");
		break;
	default:
		break;
	}
}

hlop::node_list::node_list(hlop::platform_t pf, const std::string &node_list_str, int ppn, std::vector<int> ranks)
    : node_list(pf, node_list_str, ppn) {
	if ((*std::max_element(ranks.begin(), ranks.end())) > ppn * nlist.size() ||
	    (*std::min_element(ranks.begin(), ranks.end())) < 0)
		HLOP_ERR(hlop::format("ranks should be in range [0, {}]", ppn * nlist.size() - 1));
	for (int i = 0; i < ranks.size(); ++i)
		rmap.emplace(ranks[i], nlist.at(i / ppn));
}

hlop::node_list::node_list(hlop::platform_t pf, const std::string &node_list_str, int ppn, hlop::rank_arrange_t rule)
    : node_list(pf, node_list_str, ppn) {
	for (int i = 0; i < ppn * nlist.size(); ++i)
		rmap.emplace(i, nlist.at(rank_arrange_map.at(rule)(i, nlist.size())));
}

const int hlop::node_list::get_node_cores() const { return node_cores; }

const int hlop::node_list::get_numa_cores() const { return numa_cores; }

const int hlop::node_list::get_max_network_level() const { return max_network_level; }

const int hlop::node_list::get_node_num() const { return nlist.size(); }

std::vector<std::string_view> hlop::node_list::get_node_list() const {
	return {nlist.begin(), nlist.end()};
}

const int hlop::node_list::get_ppn() const { return nproc_per_node; }

const std::unordered_map<int, const std::string &> &hlop::node_list::get_ranks() const { return rmap; }

const hlop::platform_t hlop::node_list::get_platform() const { return platform; }

const int hlop::node_list::get_level(const std::string &node1, const std::string &node2) const {
	if (!has_node(node1))
		HLOP_ERR(hlop::format("node {} not in this list", node1));
	if (!has_node(node2))
		HLOP_ERR(hlop::format("node {} not in this list", node2));

	std::smatch m1, m2;
	if (std::regex_match(node1, m1, node_regex) && std::regex_match(node2, m2, node_regex)) {
		int len = m1.size();
		for (int i = 1; i < len; ++i) {
			if (m1[i] != m2[i])
				return len - i - 1;
		}
	}
	HLOP_ERR(hlop::format("undefined net level between {} and {}", node1, node2));
	return -1; // unreachable
}

const int hlop::node_list::get_level(const hlop::comm_pair_t &cp) const {
	return get_level(cp.get_src_node(), cp.get_dst_node());
}

const std::string &hlop::node_list::get_node_id_by_rank(int rank) const {
	return rmap.at(rank);
}

const std::vector<std::string_view> hlop::node_list::get_top_k_nodes(int k) const {
	if (k <= 0 || k > get_node_num())
		HLOP_ERR(hlop::format("value k(={}): should be in range [1, {}]", k, get_node_num()));

	return {nlist.begin(), nlist.begin() + k};
}

bool hlop::node_list::has_node(const std::string &node) const {
	return std::find(nlist.begin(), nlist.end(), node) != nlist.end();
}

std::ostream &hlop::operator<<(std::ostream &os, const node_list &nl) {
	const std::string snl = hlop::vtos<std::string_view>(nl.get_node_list());
	os << snl;
	return os;
}