#ifndef __BCAST_H__
#define __BCAST_H__

#include "collective.h"
#include "structs/node_list.h"

namespace hlop {
/**
 * @brief class bcast.
 * This class implements the broadcast collective operation.
 * It provides various algorithms for broadcasting messages across nodes.
 * The algorithms include binomial, scatter recursive doubling allgather,
 * scatter ring allgather, and SMP (shared memory parallelism).
 */
class bcast : public hlop::collective {
public:
	bcast();
	~bcast() = default;

private:
	/**
	 * @brief predicts the performance of the binomial algorithm.
	 * @param nl node_list, the node list to use for prediction
	 * @param msg_size int, the message size to use for prediction
	 * @return double, the predicted performance of the binomial algorithm
	 */
	double binomial(const hlop::node_list_t &nl, int msg_size);
	/**
	 * @brief predicts the performance of the scatter recursive doubling allgather algorithm.
	 * @param nl node_list, the node list to use for prediction
	 * @param msg_size int, the message size to use for prediction
	 * @return double, the predicted performance of the scatter recursive doubling allgather algorithm
	 */
	double scatter_recursive_doubling_allgather(const hlop::node_list_t &nl, int msg_size);
	/**
	 * @brief predicts the performance of the scatter ring allgather algorithm.
	 * @param nl node_list, the node list to use for prediction
	 * @param msg_size int, the message size to use for prediction
	 * @return double, the predicted performance of the scatter ring allgather algorithm
	 */
	double scatter_ring_allgather(const hlop::node_list_t &nl, int msg_size);
	/**
	 * @brief predicts the performance of the SMP (shared memory parallelism) algorithm.
	 * @param nl node_list, the node list to use for prediction
	 * @param msg_size int, the message size to use for prediction
	 * @return double, the predicted performance of the SMP algorithm
	 */
	double smp(const hlop::node_list_t &nl, int msg_size);

private:
	/**
	 * @brief Initializes the function table for the broadcast operation.
	 * @return void
	 */
	void initialize_ftbl() override;
};
} // namespace hlop

#endif // __BCAST_H__