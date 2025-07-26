#ifndef __ALLTOALL_H__
#define __ALLTOALL_H__

#include "collective.h"

namespace hlop {
class alltoall : public collective {
public:
	alltoall();
	~alltoall() = default;

private:
private:
	void initialize_ftbl() override;
};
} // namespace hlop

#endif // __ALLTOALL_H__