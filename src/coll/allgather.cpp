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
		DEBUG("generate communication pairs: ");
		std::vector<bool> has_value(comm_size, false);
		std::vector<hlop::comm_pair> p;
		for (int rank = 0; rank < comm_size; ++rank) {
			int relative_rank = (rank >= root) ? (rank - root) : (rank - root + comm_size);
			int relative_dst = relative_rank ^ mask;
			if (relative_dst < comm_size) {
				int dst_rank = (relative_dst + root) % comm_size;
				if (has_value[dst_rank])
					continue;
				has_value[rank] = true;
				has_value[dst_rank] = true;
				hlop::comm_pair tcp{nl.get_node_ptr_by_rank(rank), rank,
				                    nl.get_node_ptr_by_rank(dst_rank), dst_rank};
				DEBUG("{}", tcp);
				DEBUG("transport {} bytes from rank {} to rank {}", msg_size, rank, dst_rank);
				p.emplace_back(std::move(tcp));
			}
		}
		DEBUG_VEC("communication pairs: ", p);
		cost += calc_cost(nl, p, msg_size * mask);
		// next loop
		mask <<= 1;
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