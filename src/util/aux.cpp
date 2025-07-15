#include "aux.h"
#include "err.h"

bool hlop::is_pof2(int x) {
	if (x <= 0)
		HLOP_ERR("require x > 0");
	return (x & (x - 1)) == 0;
}

int hlop::pof2_ceil(int x) {
	if (x <= 0)
		HLOP_ERR("require x > 0");
	--x;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	++x;
	return x;
}

int hlop::pof2_floor(int x) {
	if (x <= 0)
		HLOP_ERR("require x > 0");
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	return x - (x >> 1);
}