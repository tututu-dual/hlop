#ifndef __TYPES_H__
#define __TYPES_H__

#include <iostream>

namespace hlop {
/**
 * @brief enum class operation type.
 * The operation types are:
 * - ALLGATHER
 * - ALLREDUCE
 * - ALLTOALL
 * - BCAST
 * - GATHER
 * - REDUCE
 * - SCATTER
 */
enum class op_type {
	ALLGATHER,
	ALLREDUCE,
	ALLTOALL,
	BCAST,
	GATHER,
	REDUCE,
	SCATTER
};
typedef op_type op_type_t;

std::ostream &operator<<(std::ostream &os, const hlop::op_type &op);

/**
 * @brief enum class algorithm type.
 * The algorithm types are:
 * - BINOMIAL
 * - RING
 * - RECURSIVE_DOUBLING
 * - SMP
 * - SCATTER_RING_ALLGATHER
 * - SCATTER_RECURSIVE_DOUBLING_ALLGATHER
 * - REDUCE_SCATTER_ALLGATHER
 * - REDUCE_SCATTER_GATHER
 * - PAIRWISE
 * - BRUCKS
 * - K_BRUCKS
 */
enum class algo_type {
	BINOMIAL,
	RING,
	RECURSIVE_DOUBLING,
	SMP,
	SCATTER_RING_ALLGATHER,
	SCATTER_RECURSIVE_DOUBLING_ALLGATHER,
	REDUCE_SCATTER_ALLGATHER,
	REDUCE_SCATTER_GATHER,
	PAIRWISE,
	BRUCKS,
	K_BRUCKS
};
typedef algo_type algo_type_t;

std::ostream &operator<<(std::ostream &os, const hlop::algo_type &algo);
} // namespace hlop

#endif // __TYPES_H__