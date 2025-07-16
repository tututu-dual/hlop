#ifndef __SCATTER_H__
#define __SCATTER_H__

#include "collective.h"
#include "struct/node_list.h"

namespace hlop {
/**
 * @brief class scatter.
 * This class implements the scatter collective operation.
 * It provides an algorithm for scattering messages across nodes.
 * The algorithm include binomial.
 */
class scatter : public hlop::collective {
public:
	scatter();
	~scatter() = default;

private:
	/**
	 * @brief predicts the performance of the binomial algorithm.
	 * @param nl node_list, the node list to use for prediction.
	 * @param msg_size int, the message size to use for prediction.
	 * @param dp algo_diff_param, the algorithm-specific parameters (e.g., root rank).
	 * @return double, the predicted performance of the binomial algorithm.
	 */
	double binomial(const hlop::node_list_t &nl, int msg_size, const hlop::algo_diff_param_t &dp);

private:
	/**
	 * @brief Initializes the function table for the broadcast operation.
	 * @return void.
	 */
	void initialize_ftbl() override;
};
} // namespace hlop

#endif // __SCATTER_H__