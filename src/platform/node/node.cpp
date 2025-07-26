#include <iostream>
#include <map>
#include <string>

#include "err.h"
#include "node/node.h"

void hlop::node::bind_core(int rank, int core) {
	if (rank_core_map.size() > node_cores())
		HLOP_ERR("Cannot bind more cores than available on the node.");
	if (rank_core_map.find(rank) != rank_core_map.end())
		HLOP_ERR("Rank " + std::to_string(rank) + " is already bound to a core.");
	rank_core_map[rank] = core;
}

const int hlop::node::get_unit_id(int rank) const {
	int core = get_core(rank);
	return core / ncore_per_unit();
}

const int hlop::node::get_core(int rank) const {
	auto it = rank_core_map.find(rank);
	if (it == rank_core_map.end())
		HLOP_ERR("Rank " + std::to_string(rank) + " is not bound to any core.");
	return it->second;
}

std::ostream &hlop::operator<<(std::ostream &os, const hlop::node &n) {
	os << n.name();
	return os;
}

const int hlop::get_core_level(const node &n, int rank1, int rank2) {
	int unit1 = n.get_unit_id(rank1),
	    unit2 = n.get_unit_id(rank2);
	if (unit1 == unit2) // same unit
		return 0;
	for (int i = 1; i <= n.max_core_level(); ++i) {
		if ((unit1 >> i) == (unit2 >> i))
			return i;
	}
	return n.max_core_level(); // never reach here
}