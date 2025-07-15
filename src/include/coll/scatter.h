#ifndef __SCATTER_H__
#define __SCATTER_H__

#include "collective.h"
#include "structs/node_list.h"

namespace hlop {
class scatter : public hlop::collective {
public:
	scatter();
	~scatter() = default;

public:
	double binomial(const hlop::node_list_t &nl, int msg_size);

private:
	void initialize_ftbl() override;
};
} // namespace hlop

#endif // __SCATTER_H__