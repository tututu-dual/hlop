#include <vector>

#include "collective.h"
#include "m_debug.h"
#include "scatter.h"
#include "struct/node_list.h"
#include "struct/type.h"

hlop::scatter::scatter() : hlop::collective() {
	initialize_ftbl();
}

double hlop::scatter::binomial(const hlop::node_list_t &nl,
                               int msg_size,
                               const hlop::algo_diff_param_t &dp) {
	if (!std::holds_alternative<int>(dp))
		HLOP_ERR("invalid algo_diff_param_t for binomial algorithm");

	int root = std::get<int>(dp);
	double cost = 0.0;
	const auto &ranks = nl.get_ranks();
	int comm_size = nl.get_rank_num(),
	    mask = hlop::pof2_ceil(comm_size),
	    scatter_size = (msg_size + comm_size - 1) / comm_size;
	msg_size = msg_size * comm_size / 4;
	std::vector<int> subtree_msg_size(comm_size, 0);
	subtree_msg_size[root] = msg_size;

	// simulate the sender procedure
	mask >>= 1;
	while (mask > 0) {
		INFO("mask = {}", mask);
		// generate communication pairs
		DEBUG("generate communication pairs: ");
		std::vector<hlop::comm_pair> p;
		for (int rank = 0; rank < comm_size; ++rank) {
			int relative_rank = (rank >= root) ? (rank - root) : (rank - root + comm_size);
			if (relative_rank + mask < comm_size && subtree_msg_size[rank] > 0) {
				int dst_rank = rank + mask;
				if (dst_rank >= comm_size)
					dst_rank -= comm_size;
				if (subtree_msg_size[dst_rank] == 0) {
					subtree_msg_size[dst_rank] = subtree_msg_size[rank] - scatter_size * mask;
					subtree_msg_size[rank] = scatter_size * mask;
					hlop::comm_pair tcp{nl.get_node_ptr_by_rank(rank), rank,
					                    nl.get_node_ptr_by_rank(dst_rank), dst_rank};
					DEBUG("{}", tcp);
					DEBUG("transport {} bytes from rank {} to rank {}", subtree_msg_size[dst_rank], rank, dst_rank);
					p.emplace_back(std::move(tcp));
				}
			}
		}
		DEBUG_VEC("communication pairs: ", p);
		cost += calc_cost(nl, p, msg_size);
		// next loop
		mask >>= 1;
	}
	return cost;
}

void hlop::scatter::initialize_ftbl() {
	ftbl.insert({hlop::algo_type::BINOMIAL,
	             [this](const hlop::node_list_t &nl, int msg_size, const hlop::algo_diff_param_t &dp) -> double {
		             return this->binomial(nl, msg_size, dp);
	             }});
}
