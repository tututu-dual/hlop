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
	std::vector<int> subtree_msg_size(comm_size, 0);
	subtree_msg_size[root] = msg_size;

	// simulate the sender procedure
	mask >>= 1;
	while (mask > 0) {
		INFO("mask = {}", mask);
		// generate communication pairs
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
					hlop::comm_pair tcp{nl.get_node_id_by_rank(rank), rank,
					                    nl.get_node_id_by_rank(dst_rank), dst_rank};
					DEBUG("{}, transport message size: {}", tcp, subtree_msg_size[dst_rank]);
					p.emplace_back(std::move(tcp));
				}
			}
		}
		// get contention and calculate cost
		// double max_cost = 0;
		// const auto contention = get_contentions(p);
		// for (const auto &c : contention) {
		// 	double tmp_cost;
		// 	int nc = c.second;
		// 	const auto &cp = c.first;
		// 	INFO("{}, contention: {}", cp, nc);
		// 	if (cp.is_intra_pair())
		// 		tmp_cost = df_hlop_param_lat.get_param(msg_size, "L0", std::to_string(nl.get_intra_level(cp)),
		// 		                                       std::to_string(nc));
		// 	else
		// 		tmp_cost = df_hlop_param_lat.get_param(msg_size, "L1", std::to_string(nl.get_inter_level(cp)),
		// 		                                       std::to_string(nc));
		// 	max_cost = std::max(tmp_cost, max_cost);
		// }
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
