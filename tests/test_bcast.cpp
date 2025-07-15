#include <cmath>

#include "bcast.h"
#include "m_debug.h"
#include "platform.h"
#include "structs/node_list.h"

auto rect = [](int m, int n) -> double {
	double logm = std::log2(m), logm2 = logm * logm, logm3 = logm2 * logm;
	double logy = 0.0;
	switch (n) {
	case 1:
		// 0.0014x3 - 0.0246x2 + 0.1782x + 0.9725
		logy = 0.0014 * logm3 - 0.0246 * logm2 + 0.1782 * logm + 0.9725;
		break;
	case 2:
		// 0.0003x3 - 0.0091x2 + 0.0321x + 1.3706
		logy = 0.0003 * logm3 - 0.0091 * logm2 + 0.0321 * logm + 1.3706;
		break;
	case 4:
		// 0.0006x3 + 0.0148x2 - 0.2268x + 3.9314
		logy = 0.0006 * logm3 + 0.0148 * logm2 - 0.2268 * logm + 3.9314;
		break;
	case 8:
		// 0.0004x3 + 0.0127x2 - 0.1621x + 3.8173
		logy = 0.0004 * logm3 + 0.0127 * logm2 - 0.1621 * logm + 3.8173;
		break;
	case 16:
		// 0.0008x3 - 0.0032x2 - 0.008x + 3.7891
		break;
	default:
		break;
	}
	return std::pow(2, logy);
};

auto rect2 = [](int m, int n) -> double {
	switch (m) {
	case 1:

		break;
	default:
		break;
	}
	return 1;
};

int main(int argc, char const *argv[]) {
	hlop::node_list_t l{hlop::platform::DF, "g11r4n19", 16};
	hlop::bcast c{};
	INFO_VEC("node list:", l.get_node_list());
	INFO("result: {}", c.predict(hlop::algo_type::BINOMIAL, l, 4));
	return 0;
}
