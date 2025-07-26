#include <algorithm>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

#include "aux.h"
#include "err.h"
#include "msg.h"
#include "node/node.h"
#include "platform.h"
#include "struct/comm_pair.h"
#include "struct/node_list.h"
#include "struct/type.h"

hlop::node_list::node_list(hlop::platform_t pf, const std::string &node_list_str, int ppn)
    : nproc_per_node(ppn),
      platform(pf) {
	if (ppn > hlop::node_parser::get_node_cores(pf))
		HLOP_ERR(hlop::format("number of process per node(={}) must less equal to {}", ppn));
	if (!std::regex_match(node_list_str, hlop::node_parser::get_node_list_regex(pf)))
		HLOP_ERR(hlop::format("invalid node list string {} ", node_list_str));
	nlist = hlop::node_parser::parse_node_list(pf, node_list_str);
}

hlop::node_list::node_list(hlop::platform_t pf, const std::string &node_list_str,
                           int ppn, std::vector<int> ranks)
    : node_list(pf, node_list_str, ppn) {
	if ((*std::max_element(ranks.begin(), ranks.end())) > ppn * nlist.size() ||
	    (*std::min_element(ranks.begin(), ranks.end())) < 0)
		HLOP_ERR(hlop::format("ranks should be in range [0, {}]", ppn * nlist.size() - 1));
	// for (int i = 0; i < ranks.size(); ++i)
	// 	rmap.emplace(ranks[i], nlist.at(i / ppn));
}

hlop::node_list::node_list(hlop::platform_t pf, const std::string &node_list_str,
                           int ppn, hlop::arrangement_t rule)
    : node_list(pf, node_list_str, ppn) {
	int rank_num = ppn * nlist.size();
	for (int i = 0; i < rank_num; ++i) {
		switch (rule.node_arrange) {
		case hlop::rank_arrangement::BLOCK: {
			int node_idx = i / ppn;
			switch (rule.core_arrange) {
			case hlop::rank_arrangement::BLOCK: {
				int core_idx = i % ppn;
				rmap.emplace(i, nlist.at(node_idx));
				nlist.at(node_idx)->bind_core(i, core_idx);
				break;
			}
			case hlop::rank_arrangement::CYCLIC: {
				int core_idx = i % hlop::node_parser::get_numa_cores(platform);
				rmap.emplace(i, nlist.at(node_idx));
				nlist.at(node_idx)->bind_core(i, core_idx);
				break;
			}
			case hlop::rank_arrangement::PLANE: {
				HLOP_ERR("plane rank arrangement is not supported yet");
				break;
			}
			case hlop::rank_arrangement::ARBITRARY: {
				HLOP_ERR("arbitrary rank arrangement is not supported yet");
				break;
			}
			default: {
				HLOP_ERR(hlop::format("unknown core arrangement type {}", rule.core_arrange));
				break;
			}
			}
			break;
		}
		case hlop::rank_arrangement::CYCLIC: {
			int node_idx = i % nlist.size();
			switch (rule.core_arrange) {
			case hlop::rank_arrangement::BLOCK: {
				int core_idx = i / nlist.size();
				rmap.emplace(i, nlist.at(node_idx));
				nlist.at(node_idx)->bind_core(i, core_idx);
				break;
			}
			case hlop::rank_arrangement::CYCLIC: {
				int core_idx = i / nlist.size() % hlop::node_parser::get_numa_cores(platform);
				rmap.emplace(i, nlist.at(node_idx));
				nlist.at(node_idx)->bind_core(i, core_idx);
				break;
			}
			case hlop::rank_arrangement::PLANE: {
				HLOP_ERR("plane rank arrangement is not supported yet");
				break;
			}
			case hlop::rank_arrangement::ARBITRARY: {
				HLOP_ERR("arbitrary rank arrangement is not supported yet");
				break;
			}
			default: {
				HLOP_ERR(hlop::format("unknown core arrangement type {}", rule.core_arrange));
				break;
			}
			}
		}
		case hlop::rank_arrangement::PLANE: {
			HLOP_ERR("plane rank arrangement is not supported yet");
			break;
		}
		case hlop::rank_arrangement::ARBITRARY: {
			HLOP_ERR("arbitrary rank arrangement is not supported yet");
			break;
		}
		default: {
			HLOP_ERR(hlop::format("unknown rank arrangement type {}", rule.node_arrange));
			break;
		}
		}
	}
}

const hlop::platform_t hlop::node_list::get_platform() const { return platform; }

const int hlop::node_list::get_ppn() const { return nproc_per_node; }

const int hlop::node_list::get_node_num() const { return nlist.size(); }

const std::vector<hlop::const_node_ptr> &hlop::node_list::get_node_list() const { return nlist; }

const int hlop::node_list::get_rank_num() const { return rmap.size(); }

const std::unordered_map<int, hlop::const_node_ptr> &hlop::node_list::get_ranks() const { return rmap; }

const int hlop::node_list::get_level(int rank1, int rank2) const {
	const auto &node1 = get_node_by_rank(rank1);
	const auto &node2 = get_node_by_rank(rank2);
	if (node1 == node2)
		return node1.get_core_level(rank1, rank2);
	else
		return node1 - node2;
	HLOP_ERR(hlop::format("undefined net level between {} and {}", node1.name(), node2.name()));
	return -1; // unreachable
}

const int hlop::node_list::get_level(const hlop::comm_pair_t &cp) const {
	return get_level(cp.get_src_rank(), cp.get_dst_rank());
}

const hlop::node_t &hlop::node_list::get_node_by_rank(int rank) const {
	return *get_node_ptr_by_rank(rank);
}

hlop::const_node_ptr_t hlop::node_list::get_node_ptr_by_rank(int rank) const {
	if (rmap.find(rank) == rmap.end())
		HLOP_ERR(hlop::format("rank {} not in this list", rank));
	return rmap.at(rank);
}

const std::vector<hlop::const_node_ptr> hlop::node_list::get_top_k_nodes(int k) const {
	if (k <= 0 || k > get_node_num())
		HLOP_ERR(hlop::format("value k(={}): should be in range [1, {}]", k, get_node_num()));
	return {nlist.begin(), nlist.begin() + k};
}

std::ostream &hlop::operator<<(std::ostream &os, const node_list &nl) {
	const std::string snl = hlop::vtos(nl.get_node_list());
	os << snl;
	return os;
}