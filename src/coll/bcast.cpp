#include <vector>

#include "bcast.h"
#include "collective.h"
#include "err.h"
#include "m_debug.h"
#include "struct/comm_pair.h"
#include "struct/node_list.h"
#include "struct/type.h"

hlop::bcast::bcast() : hlop::collective() {
	initialize_ftbl();
}

double hlop::bcast::binomial(const hlop::node_list_t &nl,
                             int msg_size,
                             const hlop::algo_diff_param_t &dp) {
	// check if the root is valid
	if (!std::holds_alternative<int>(dp))
		HLOP_ERR("invalid algo_diff_param_t for binomial algorithm");

	int root = std::get<int>(dp);
	double cost = 0.0;
	const auto &ranks = nl.get_ranks();
	int comm_size = nl.get_rank_num(),
	    mask = hlop::pof2_ceil(comm_size);
	std::vector<bool> has_value(comm_size, false);
	has_value[root] = true;

	// simulate the sender procedure
	mask >>= 1;
	while (mask > 0) {
		INFO("mask = {}", mask);
		// generate communication pairs
		std::vector<hlop::comm_pair> p;
		for (int rank = 0; rank < comm_size; ++rank) {
			int relative_rank = (rank >= root) ? (rank - root) : (rank - root + comm_size);
			if (relative_rank + mask < comm_size && has_value[rank]) {
				int dst_rank = rank + mask;
				if (dst_rank >= comm_size)
					dst_rank -= comm_size;
				if (!has_value[dst_rank]) {
					has_value[dst_rank] = true;
					hlop::comm_pair tcp{nl.get_node_id_by_rank(rank), rank,
					                    nl.get_node_id_by_rank(dst_rank), dst_rank};
					DEBUG("{}, transport message size: {}", tcp, msg_size);
					p.emplace_back(std::move(tcp));
				}
			}
		}
		// get contention and calculate cost
		double max_cost = 0;
		const auto contention = get_contentions(p);
		for (const auto &c : contention) {
			double tmp_cost;
			int nc = c.second;
			const auto &cp = c.first;
			if (cp.is_intra_pair())
				tmp_cost = df_hlop_param.get_param(msg_size,
				                                   "L0",
				                                   "PING",
				                                   std::to_string(nc));
			else
				tmp_cost = df_hlop_param.get_param(msg_size,
				                                   "L1",
				                                   std::to_string(nl.get_level(cp)),
				                                   "PING",
				                                   std::to_string(nc));
			max_cost = std::max(tmp_cost, max_cost);
			INFO("{}, contention: {}; cost: {}", cp, nc, tmp_cost);
		}
		// next loop
		mask >>= 1;
		cost += max_cost;
	}
	return cost;
}

double hlop::bcast::scatter_recursive_doubling_allgather(const hlop::node_list_t &nl,
                                                         int msg_size,
                                                         const hlop::algo_diff_param_t &dp) {
	HLOP_ERR("unimplemented algorithm scatter recursive doubling allgather");
	return 0.0;
}

double hlop::bcast::scatter_ring_allgather(const hlop::node_list_t &nl,
                                           int msg_size,
                                           const hlop::algo_diff_param_t &dp) {
	HLOP_ERR("unimplemented algorithm scatter ring allgather");
	return 0.0;
}

double hlop::bcast::smp(const hlop::node_list_t &nl,
                        int msg_size,
                        const hlop::algo_diff_param_t &dp) {
	HLOP_ERR("unimplemented algorithm smp");
	return 0.0;
}

void hlop::bcast::initialize_ftbl() {
	ftbl.insert({hlop::algo_type::BINOMIAL,
	             [this](const hlop::node_list_t &nl, int msg_size, const hlop::algo_diff_param_t &dp) -> double {
		             return this->binomial(nl, msg_size, dp);
	             }});
	ftbl.insert({hlop::algo_type::SCATTER_RECURSIVE_DOUBLING_ALLGATHER,
	             [this](const hlop::node_list_t &nl, int msg_size, const hlop::algo_diff_param_t &dp) -> double {
		             return this->scatter_recursive_doubling_allgather(nl, msg_size, dp);
	             }});
	ftbl.insert({hlop::algo_type::SCATTER_RING_ALLGATHER,
	             [this](const hlop::node_list_t &nl, int msg_size, const hlop::algo_diff_param_t &dp) -> double {
		             return this->scatter_ring_allgather(nl, msg_size, dp);
	             }});
	ftbl.insert({hlop::algo_type::SMP,
	             [this](const hlop::node_list_t &nl, int msg_size, const hlop::algo_diff_param_t &dp) -> double {
		             return this->smp(nl, msg_size, dp);
	             }});
}