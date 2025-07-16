#ifndef __ALLGATHER_H__
#define __ALLGATHER_H__

#include "collective.h"
#include "struct/node_list.h"

namespace hlop {
class allgather : public hlop::collective {
public:
	allgather();
	~allgather() = default;

private:
	double brucks(const hlop::node_list_t &nl, int msg_size, const hlop::algo_diff_param_t &dp);
	double k_brucks(const hlop::node_list_t &nl, int msg_size, const hlop::algo_diff_param_t &dp);
	double recursive_doubling(const hlop::node_list_t &nl, int msg_size, const hlop::algo_diff_param_t &dp);
	double ring(const hlop::node_list_t &nl, int msg_size, const hlop::algo_diff_param_t &dp);

private:
	/**
	 * @brief Initializes the function table for the allgather operation.
	 * @return void.
	 */
	void initialize_ftbl() override;
};
} // namespace hlop

#endif // __ALLGATHER_H__