#ifndef __ALLREDUCE_H__
#define __ALLREDUCE_H__

#include "collective.h"

namespace hlop {
class allreduce : public collective {
public:
	allreduce();
	~allreduce() = default;

private:
private:
	void initialize_ftbl() override;
};
} // namespace hlop

#endif // __ALLREDUCE_H__