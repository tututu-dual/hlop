#include <vector>

#include "aux.h"
#include "err.h"
#include "m_debug.h"

int main(int argc, char const *argv[]) {
	auto v1 = hlop::stov<int>("");
	INFO("v1.size() = {}", v1.size());
	auto v2 = hlop::stov<double>("1.1,2,3,4");
	INFO_VEC("v2", v2);
	auto v3 = hlop::stov<double>("x,y,1.1,2,3,4", 2);
	INFO_VEC("v3", v3);
	INFO("is_pof2(1) = {}", hlop::is_pof2(1));
	INFO("pof2_ceil(7) = {}", hlop::pof2_ceil(7));
	HLOP_ERR("Test error message");
	return 0;
}
