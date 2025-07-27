#ifndef __COLLECTIVE_H__
#define __COLLECTIVE_H__

#include <functional>
#include <map>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include "param/param.h"
#include "struct/comm_pair.h"
#include "struct/node_list.h"
#include "struct/type.h"

namespace hlop {
/// @brief this variant is used to pass algorithm-specific parameters to the collective operations.
typedef std::variant<int, void *> algo_diff_param_t;

/**
 * @brief class collective.
 * This class is the base class for all collective operations.
 * It provides a common interface for predicting the performance of different algorithms
 * and checking the availability of algorithms.
 * Derived classes should implement the specific algorithms and their predictions.
 */
class collective {
public:
	using predictor_handler = std::function<double(const hlop::node_list_t &, int, const hlop::algo_diff_param_t &)>;

protected:
	static const hlop::param_t hlop_param_lat;
	static const hlop::param_t hlop_param_bw;

public:
	collective();
	collective(const std::string &small_scales_param_filepath);
	collective(const std::string &small_scales_param_filepath, const std::string &other_param_filepath);
	virtual ~collective() = default;

public:
	/**
	 * @brief check if the operation is implemented.
	 * @param algo algo_type, the algorithm type to check.
	 * @return bool, true if the algorithm is implemented, false otherwise.
	 */
	bool has_algo(hlop::algo_type algo) const;
	/**
	 * @brief get the list of available algorithms.
	 * @return vector<algo_type>, the list of available algorithms.
	 */
	const std::vector<hlop::algo_type> get_algos() const;
	/**
	 * @brief predict the performance of an algorithm.
	 * @param algo algo_type, the algorithm type to predict.
	 * @param nl node_list, the node list to use for prediction.
	 * @param msg_size int, the message size to use for prediction.
	 * @param dp algo_diff_param_t, the algorithm-specific parameters.
	 * @return double, the predicted performance of the algorithm.
	 */
	const double predict(hlop::algo_type algo, const hlop::node_list_t &nl, int msg_size, const hlop::algo_diff_param_t &dp) const;

protected:
	/**
	 * @fixme
	 * @brief get the contention in a set of communication pairs.
	 * @param pairs vector<comm_pair>, the communication pairs to check for contention.
	 * @return map<comm_pair, int>, a map of communication pairs to contention counts.
	 */
	const std::map<hlop::comm_pair, int> get_contentions(const std::vector<hlop::comm_pair> &pairs) const;

	/**
	 * @brief calculate the cost of this communication round.
	 * @param nl node_list, where communication happens.
	 * @param pairs vector<comm_pair>, the communication pairs involved in this round.
	 * @param msg_size int, the size of the message being communicated.
	 * @return double, the cost of this communication round.
	 */
	virtual const double calc_cost(const hlop::node_list_t &nl,
	                               const std::vector<hlop::comm_pair> &pairs,
	                               int msg_size) const;
	/**
	 * @brief initialize the function table with predictor handlers.
	 * @return void.
	 * @note This function should populate the ftbl with the predictor handlers for each algorithm.
	 * It is called in the constructor of the derived class to ensure that the function table is initialized
	 * before any predictions are made.
	 * Derived classes should implement this function to provide the specific predictors for each algorithm.
	 */
	virtual void initialize_ftbl() = 0;

protected:
	std::unordered_map<hlop::algo_type, predictor_handler> ftbl;
	std::optional<const hlop::param> small_scales_param;
	std::optional<const hlop::param> other_param;
};
} // namespace hlop

#endif // __COLLECTIVE_H__