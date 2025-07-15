#include <algorithm>
#include <deque>
#include <string>
#include <vector>

#include "aux.h"
#include "bcast.h"
#include "collective.h"
#include "err.h"
#include "m_debug.h"
#include "structs/comm_pair.h"
#include "structs/node_list.h"
#include "structs/types.h"

hlop::bcast::bcast() : hlop::collective() {
	initialize_ftbl();
}

double hlop::bcast::binomial(const hlop::node_list_t &nl, int msg_size) {
	double cost = 0.0;
	const auto ranks = nl.get_ranks();
	int procs = ranks.size(), mask = hlop::pof2_ceil(procs);
	std::deque<int> hold;
	hold.emplace_back(0);

	mask >>= 1;
	while (mask > 0) {
		// gen comm pair
		std::vector<hlop::comm_pair> p;
		for (const auto &h : hold) {
			int src_idx = h;
			int dst_idx = src_idx + mask;
			if (dst_idx < procs) {
				hold.emplace_back(dst_idx);
				int src_rank = ranks[src_idx];
				int dst_rank = ranks[dst_idx];
				p.emplace_back(nl.get_node_id_by_rank(src_rank), src_rank, nl.get_node_id_by_rank(dst_rank), dst_rank);
			}
		}
		INFO("mask = {}", mask);
		INFO_VEC("IN BCAST BINOMIAL:", p);
		// get contention
		double max_cost = 0;
		const auto contention = get_contentions(p);
		for (const auto &c : contention) {
			double tmp_cost;
			int nc = c.second;
			const auto &cp = c.first;
			if (cp.is_intra_pair())
				tmp_cost = df_hlop_param.get_param(msg_size, "L0", "PING", std::to_string(nc));
			else
				tmp_cost = df_hlop_param.get_param(msg_size, "L1", std::to_string(nl.get_level(cp)), "DUPLEX", std::to_string(nc));
			max_cost = std::max(tmp_cost, max_cost);
		}
		// next loop
		mask >>= 1;
		cost += max_cost;
	}
	return cost;
}

double hlop::bcast::scatter_recursive_doubling_allgather(const hlop::node_list_t &nl, int msg_size) {
	HLOP_ERR("unimplemented algorithm scatter recursive doubling allgather");
	return 0.0;
}

double hlop::bcast::scatter_ring_allgather(const hlop::node_list_t &nl, int msg_size) {
	HLOP_ERR("unimplemented algorithm scatter ring allgather");
	return 0.0;
}

double hlop::bcast::smp(const hlop::node_list_t &nl, int msg_size) {
	HLOP_ERR("unimplemented algorithm smp");
	return 0.0;
}

void hlop::bcast::initialize_ftbl() {
	ftbl.insert({hlop::algo_type::BINOMIAL,
	             [this](const hlop::node_list_t &nl, int msg_size) -> double {
		             return this->binomial(nl, msg_size);
	             }});
	ftbl.insert({hlop::algo_type::SCATTER_RECURSIVE_DOUBLING_ALLGATHER,
	             [this](const hlop::node_list_t &nl, int msg_size) -> double {
		             return this->scatter_recursive_doubling_allgather(nl, msg_size);
	             }});
	ftbl.insert({hlop::algo_type::SCATTER_RING_ALLGATHER,
	             [this](const hlop::node_list_t &nl, int msg_size) -> double {
		             return this->scatter_ring_allgather(nl, msg_size);
	             }});
	ftbl.insert({hlop::algo_type::SMP,
	             [this](const hlop::node_list_t &nl, int msg_size) -> double {
		             return this->smp(nl, msg_size);
	             }});
}