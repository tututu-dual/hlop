#ifndef __TYPES_H__
#define __TYPES_H__

#include <iostream>
#include <ostream>

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

/**
 * @brief enum class rank arrangement.
 * The rank arrangements are:
 * - BLOCK
 * - CYCLIC
 * - PLANE
 * - ARBITRARY
 */
enum class rank_arrangement {
	BLOCK,
	CYCLIC,
	PLANE,
	ARBITRARY
};
typedef rank_arrangement rank_arrangement_t;

std::ostream &operator<<(std::ostream &os, const hlop::rank_arrangement &ra);
} // namespace hlop

#endif // __TYPES_H__