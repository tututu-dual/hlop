#ifndef __GATHER_H__
#define __GATHER_H__

#include "collective.h"

namespace hlop {
class gather : public collective {
public:
	gather();
	~gather() = default;

private:
private:
	void initialize_ftbl() override;
};
} // namespace hlop

#endif // __GATHER_H__