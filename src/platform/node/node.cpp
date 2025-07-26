#include <iostream>
#include <string>
#include <unordered_map>

#include "err.h"
#include "msg.h"
#include "node/node.h"

hlop::node::node(const std::string &node_str) : node_name(node_str) {}

const std::string &hlop::node::name() const { return node_name; }

void hlop::node::bind_core(int rank, int core) const {
	if (core < 0 || core >= node_cores())
		HLOP_ERR(hlop::format("core {} is not in range [0, {}]", core, node_cores() - 1));
	if (rank_core_map.size() >= node_cores())
		HLOP_ERR("cannot bind more cores than available on the node.");
	if (rank_core_map.find(rank) != rank_core_map.end())
		HLOP_ERR(hlop::format("rank {} is already bound to core {}", rank, rank_core_map[rank]));
	rank_core_map[rank] = core;
}

const int hlop::node::get_unit_id(int rank) const {
	return get_core(rank) / ncore_per_unit();
}

const int hlop::node::get_core_level(int rank1, int rank2) const {
	int unit1 = get_unit_id(rank1),
	    unit2 = get_unit_id(rank2);
	for (int i = 0; i <= max_core_level(); ++i) {
		if ((unit1 >> i) == (unit2 >> i))
			return i;
	}
	HLOP_ERR(hlop::format("undefined core level in node {} between {} and {}", name(), rank1, rank2));
	return -1; // unreachable
}

const int hlop::node::get_core(int rank) const {
	auto it = rank_core_map.find(rank);
	if (it == rank_core_map.end())
		HLOP_ERR(hlop::format("rank {} is not bound to any core in node {}", rank, name()));
	return it->second;
}

std::ostream &hlop::operator<<(std::ostream &os, const node_t &n) {
	os << n.name() << "{ ";
	for (const auto &rc : n.rank_core_map)
		os << "{" << rc.first << ", " << rc.second << "} ";
	os << "}";
	return os;
}