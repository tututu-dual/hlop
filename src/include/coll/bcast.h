#ifndef __BCAST_H__
#define __BCAST_H__

#include "collective.h"
#include "structs/node_list.h"

namespace hlop {
class bcast : public hlop::collective {
public:
	bcast();
	~bcast() = default;

private:
	double binomial(const hlop::node_list_t &nl, int msg_size);
	double scatter_recursive_doubling_allgather(const hlop::node_list_t &nl, int msg_size);
	double scatter_ring_allgather(const hlop::node_list_t &nl, int msg_size);
	double smp(const hlop::node_list_t &nl, int msg_size);

private:
	void initialize_ftbl() override;
};
} // namespace hlop

#endif // __BCAST_H__