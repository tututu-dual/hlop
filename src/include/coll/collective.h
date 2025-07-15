#ifndef __COLLECTIVE_H__
#define __COLLECTIVE_H__

#include <functional>
#include <map>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "param/param.h"
#include "structs/comm_pair.h"
#include "structs/node_list.h"
#include "structs/types.h"

namespace hlop {
class collective {
protected:
	using predictor_handler = std::function<double(const hlop::node_list_t &, int)>;

public:
	collective();
	collective(const std::string &small_scales_param_filepath);
	collective(const std::string &small_scales_param_filepath, const std::string &other_param_filepath);
	virtual ~collective() = default;

public:
	/// @brief check whether collective operation contain algorithm algo
	/// @param algo
	/// @return
	virtual bool has_algo(hlop::algo_type algo) const;
	/// @brief return algorithms in this operation
	/// @return
	virtual const std::vector<hlop::algo_type> get_algos() const;
	/// @brief predict using specific algorithm
	/// @param algo algorithm type
	/// @param nl node list
	/// @param msg_size message size
	/// @return
	virtual const double predict(hlop::algo_type algo, const hlop::node_list_t &nl, int msg_size) const;
	/// @brief get the contention in a communication
	/// @param pairs
	/// @return
	virtual const std::map<hlop::comm_pair, int> get_contentions(const std::vector<hlop::comm_pair> &pairs) const;

protected:
	/// @brief must call at constructor in derived class
	/// @param none
	/// @return none
	virtual void initialize_ftbl() = 0;

protected:
	std::unordered_map<hlop::algo_type, predictor_handler> ftbl;
	std::optional<const hlop::param> small_scales_param;
	std::optional<const hlop::param> other_param;

protected:
	static const hlop::param_t df_hlop_param;
	static const hlop::collective::predictor_handler unimpl;
};
} // namespace hlop

#endif // __COLLECTIVE_H__