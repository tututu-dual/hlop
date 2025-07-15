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
/**
 * @brief class collective.
 * This class is the base class for all collective operations.
 * It provides a common interface for predicting the performance of different algorithms
 * and checking the availability of algorithms.
 * Derived classes should implement the specific algorithms and their predictions.
 */
class collective {
protected:
	using predictor_handler = std::function<double(const hlop::node_list_t &, int)>;

public:
	collective();
	collective(const std::string &small_scales_param_filepath);
	collective(const std::string &small_scales_param_filepath, const std::string &other_param_filepath);
	virtual ~collective() = default;

public:
	/**
	 * @brief check if the operation is implemented
	 * @param algo algo_type, the algorithm type to check
	 * @return bool, true if the algorithm is implemented, false otherwise
	 */
	virtual bool has_algo(hlop::algo_type algo) const;
	/**
	 * @brief get the list of available algorithms
	 * @return vector<algo_type>, the list of available algorithms
	 */
	virtual const std::vector<hlop::algo_type> get_algos() const;
	/**
	 * @brief predict the performance of an algorithm
	 * @param algo algo_type, the algorithm type to predict
	 * @param nl node_list, the node list to use for prediction
	 * @param msg_size int, the message size to use for prediction
	 * @return double, the predicted performance of the algorithm
	 */
	virtual const double predict(hlop::algo_type algo, const hlop::node_list_t &nl, int msg_size) const;
	/**
	 * @brief get the contention in a set of communication pairs
	 * @param pairs vector<comm_pair>, the communication pairs to check for contention
	 * @return map<comm_pair, int>, a map of communication pairs to contention counts
	 */
	virtual const std::map<hlop::comm_pair, int> get_contentions(const std::vector<hlop::comm_pair> &pairs) const;

protected:
	/**
	 * @brief initialize the function table with predictor handlers
	 * @return void
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

protected:
	static const hlop::param_t df_hlop_param;
	static const hlop::collective::predictor_handler unimpl;
};
} // namespace hlop

#endif // __COLLECTIVE_H__