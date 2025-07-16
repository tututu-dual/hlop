#include <map>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "collective.h"
#include "err.h"
#include "msg.h"
#include "param/param.h"
#include "resources.h"
#include "struct/comm_pair.h"

const hlop::param_t hlop::collective::df_hlop_param{hlop::RESOURCE_BASE + hlop::DF_HLOP_PARAM};

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
                                       int msg_size,
                                       const hlop::algo_diff_param_t &dp) const {
	if (!has_algo(algo))
		HLOP_ERR(hlop::format("this operation do not have algorithm {}", algo));
	return ftbl.at(algo)(nl, msg_size, dp);
}

const std::map<hlop::comm_pair, int> hlop::collective::get_contentions(const std::vector<hlop::comm_pair> &pairs) const {
	std::map<hlop::comm_pair, int> res;
	for (const auto &p : pairs)
		res[p] = res.find(p) == res.end() ? 1 : res[p] + 1;

	return std::move(res);
}