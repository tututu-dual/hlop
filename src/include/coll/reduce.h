#ifndef __REDUCE_H__
#define __REDUCE_H__

#include "collective.h"

namespace hlop {
class reduce : public collective {
public:
	reduce();
	~reduce() = default;

private:
private:
	void initialize_ftbl() override;
};
} // namespace hlop

#endif // __REDUCE_H__