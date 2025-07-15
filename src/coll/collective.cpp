#include <map>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "collective.h"
#include "err.h"
#include "m_debug.h"
#include "param/param.h"
#include "resources.h"
#include "struct/comm_pair.h"

const hlop::param_t hlop::collective::df_hlop_param{hlop::RESOURCE_BASE + hlop::DF_HLOP_PARAM};
const hlop::collective::predictor_handler hlop::collective::unimpl =
    [](const hlop::node_list_t &nl, int msg_size) -> double {
	HLOP_ERR("unimplemented algorithm");
	return 0.0;
};

hlop::collective::collective()
    : small_scales_param{std::nullopt}, other_param{std::nullopt} {}

hlop::collective::collective(const std::string &small_scales_param_filepath)
    : small_scales_param{small_scales_param_filepath}, other_param{std::nullopt} {}

hlop::collective::collective(const std::string &small_scales_param_filepath, const std::string &other_param_filepath)
    : small_scales_param{small_scales_param_filepath}, other_param{other_param_filepath} {}

bool hlop::collective::has_algo(hlop::algo_type algo) const {
	return ftbl.find(algo) != ftbl.end();
}

const std::vector<hlop::algo_type> hlop::collective::get_algos() const {
	std::vector<hlop::algo_type> res;
	for (const auto &i : ftbl)
		res.emplace_back(i.first);
	return std::move(res);
}

const double hlop::collective::predict(hlop::algo_type algo,
                                       const hlop::node_list_t &nl,
                                       int msg_size) const {
	return ftbl.at(algo)(nl, msg_size);
}

const std::map<hlop::comm_pair, int> hlop::collective::get_contentions(
    const std::vector<hlop::comm_pair> &pairs) const {
	std::map<hlop::comm_pair, int> res;
	for (const auto &p : pairs)
		res[p] = res.find(p) == res.end() ? 1 : res[p] + 1;

	return std::move(res);
}

double hlop::collective::binomial_aux(const hlop::node_list_t &nl, int msg_size, int root) {
	double cost = 0.0;
	const auto &ranks = nl.get_ranks();
	int comm_size = ranks.size(), mask = hlop::pof2_ceil(comm_size);
	std::deque<int> hold;
	hold.emplace_back(root);

	mask >>= 1;
	while (mask > 0) {
		// gen comm pair
		std::vector<hlop::comm_pair> p;
		for (const auto &h : hold) {
			int src_rank = h;
			int relative_rank = (src_rank >= root) ? (src_rank - root) : (src_rank - root + comm_size);
			if (relative_rank + mask < comm_size) {
				int dst_rank = src_rank + mask;
				if (dst_rank >= comm_size)
					dst_rank -= comm_size;
				hold.emplace_back(dst_rank);
				p.emplace_back(nl.get_node_id_by_rank(src_rank), src_rank,
				               nl.get_node_id_by_rank(dst_rank), dst_rank);
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
				tmp_cost = df_hlop_param.get_param(msg_size,
				                                   "L0",
				                                   "PING",
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
		mask >>= 1;
		cost += max_cost;
	}
	return cost;
}