#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include <iostream>

namespace hlop {
/**
 * @brief enum class platform.
 * The platforms are:
 * - DF
 * - TH
 * - UNKNOWN
 */
enum class platform {
	DF,
	TH,
	UNKNOWN
};
typedef platform platform_t;

std::ostream &operator<<(std::ostream &os, const hlop::platform &p);
} // namespace hlop

#endif // __PLATFORM_H__