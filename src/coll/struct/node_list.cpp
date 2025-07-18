#include <algorithm>
#include <iostream>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

#include "aux.h"
#include "err.h"
#include "msg.h"
#include "platform.h"
#include "struct/node_list.h"
#include "struct/type.h"

hlop::node_list::node_list(hlop::platform_t pf, const std::string &node_list_str, int ppn)
    : platform(pf),
      node_cores(hlop::node_parser::get_node_cores(pf)),
      numa_cores(hlop::node_parser::get_numa_cores(pf)),
      max_network_level(hlop::node_parser::get_max_network_level(pf)),
      node_regex(hlop::node_parser::get_node_regex(pf)),
      nlist(hlop::node_parser::parser_node_list(pf, node_list_str)),
      nproc_per_node(ppn),
      rank_arrangement_map(
          {{hlop::rank_arrangement::BLOCK, [this](int rank) -> int { return rank / nproc_per_node; }},
           {hlop::rank_arrangement::CYCLIC, [this](int rank) -> int { return rank % nlist.size(); }},
           {hlop::rank_arrangement::PLANE, [this](int rank) -> int {
	            HLOP_ERR("plane rank arrangement is not implemented yet");
	            return -1; // unreachable
            }},
           {hlop::rank_arrangement::ARBITRARY, [this](int rank) -> int {
	            HLOP_ERR("arbitrary rank arrangement is not implemented yet");
	            return -1; // unreachable
            }}}) {
	if (ppn > node_cores)
		HLOP_ERR(hlop::format("number of process per node(={}) must less equal to {}", ppn, node_cores));
}

hlop::node_list::node_list(hlop::platform_t pf,
                           const std::string &node_list_str,
                           int ppn,
                           std::vector<int> ranks)
    : node_list(pf, node_list_str, ppn) {
	if ((*std::max_element(ranks.begin(), ranks.end())) > ppn * nlist.size() ||
	    (*std::min_element(ranks.begin(), ranks.end())) < 0)
		HLOP_ERR(hlop::format("ranks should be in range [0, {}]", ppn * nlist.size() - 1));
	for (int i = 0; i < ranks.size(); ++i)
		rmap.emplace(ranks[i], nlist.at(i / ppn));
}

hlop::node_list::node_list(hlop::platform_t pf,
                           const std::string &node_list_str,
                           int ppn,
                           hlop::rank_arrangement_t rule)
    : node_list(pf, node_list_str, ppn) {
	for (int i = 0; i < ppn * nlist.size(); ++i)
		rmap.emplace(i, nlist.at(rank_arrangement_map.at(rule)(i)));
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

const int hlop::node_list::get_rank_num() const { return rmap.size(); }

const hlop::platform_t hlop::node_list::get_platform() const { return platform; }

const int hlop::node_list::get_level(const std::string &node1, const std::string &node2) const {
	if (!has_node(node1))
		HLOP_ERR(hlop::format("node {} not in this list", node1));
	if (!has_node(node2))
		HLOP_ERR(hlop::format("node {} not in this list", node2));

	std::smatch m1, m2;
	if (std::regex_match(node1, m1, node_regex) &&
	    std::regex_match(node2, m2, node_regex)) {
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
	if (rmap.find(rank) == rmap.end())
		HLOP_ERR(hlop::format("rank {} not in this list", rank));
	return rmap.at(rank);
}

std::vector<std::string_view> hlop::node_list::get_top_k_nodes(int k) const {
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