#include <vector>

#include "allgather.h"
#include "err.h"
#include "m_debug.h"
#include "struct/type.h"

hlop::allgather::allgather() : hlop::collective() {
	initialize_ftbl();
}

double hlop::allgather::brucks(const hlop::node_list_t &nl,
                               int msg_size,
                               const hlop::algo_diff_param_t &dp) {
	HLOP_ERR("unimplemented algorithm brucks");
	return 0.0;
}

double hlop::allgather::k_brucks(const hlop::node_list_t &nl,
                                 int msg_size,
                                 const hlop::algo_diff_param_t &dp) {
	HLOP_ERR("unimplemented algorithm k brucks");
	return 0.0;
}

double hlop::allgather::recursive_doubling(const hlop::node_list_t &nl,
                                           int msg_size,
                                           const hlop::algo_diff_param_t &dp) {
	// check if the root is valid
	if (!std::holds_alternative<int>(dp))
		HLOP_ERR("invalid algo_diff_param_t for binomial algorithm");

	int root = std::get<int>(dp);
	double cost = 0.0;
	const auto &ranks = nl.get_ranks();
	int comm_size = nl.get_rank_num(),
	    mask = 0x01;

	while (mask < comm_size) {
		INFO("mask = {}", mask);
		// generate communication pairs
		std::vector<hlop::comm_pair> p;
		for (int rank = 0; rank < comm_size; ++rank) {
			int relative_rank = (rank >= root) ? (rank - root) : (rank - root + comm_size);
			int relative_dst = relative_rank ^ mask;
			if (relative_dst < comm_size) {
				int dst_rank = (relative_dst + root) % comm_size;
				hlop::comm_pair tcp{nl.get_node_id_by_rank(rank), rank,
				                    nl.get_node_id_by_rank(dst_rank), dst_rank};
				INFO("{}, transport message size: {}", tcp, msg_size);
				p.emplace_back(std::move(tcp));
			}
		}
		// get contention and calculate cost
		double max_cost = 0;
		const auto contention = get_contentions(p);
		for (const auto &c : contention) {
			double tmp_cost;
			int nc = c.second >> 1; // each pair occurs twice
			const auto &cp = c.first;
			INFO("{}, contention: {}", cp, nc);
			if (cp.is_intra_pair())
				tmp_cost = df_hlop_param.get_param(msg_size,
				                                   "L0",
				                                   "DUPLEX",
				                                   std::to_string(nc));
			else
				tmp_cost = df_hlop_param.get_param(msg_size,
				                                   "L1",
				                                   std::to_string(nl.get_level(cp)),
				                                   "DUPLEX",
				                                   std::to_string(nc));
			max_cost = std::max(tmp_cost, max_cost);
		}
		// next loop
		mask <<= 1;
		cost += max_cost;
	}
	return cost;
}

double hlop::allgather::ring(const hlop::node_list_t &nl,
                             int msg_size,
                             const hlop::algo_diff_param_t &dp) {
	HLOP_ERR("unimplemented algorithm ring");
	return 0.0;
}

void hlop::allgather::initialize_ftbl() {
	ftbl.insert({hlop::algo_type::BRUCKS,
	             [this](const hlop::node_list_t &nl, int msg_size, const hlop::algo_diff_param_t &dp) -> double {
		             return this->brucks(nl, msg_size, dp);
	             }});
	ftbl.insert({hlop::algo_type::K_BRUCKS,
	             [this](const hlop::node_list_t &nl, int msg_size, const hlop::algo_diff_param_t &dp) -> double {
		             return this->k_brucks(nl, msg_size, dp);
	             }});
	ftbl.insert({hlop::algo_type::RECURSIVE_DOUBLING,
	             [this](const hlop::node_list_t &nl, int msg_size, const hlop::algo_diff_param_t &dp) -> double {
		             return this->recursive_doubling(nl, msg_size, dp);
	             }});
	ftbl.insert({hlop::algo_type::RING,
	             [this](const hlop::node_list_t &nl, int msg_size, const hlop::algo_diff_param_t &dp) -> double {
		             return this->ring(nl, msg_size, dp);
	             }});
}