#include "bcast.h"
#include "m_debug.h"
#include "platform.h"
#include "struct/node_list.h"
#include "struct/type.h"

int main(int argc, char const *argv[]) {
	hlop::node_list_t l{hlop::platform::DF, "h02r1n[08-09]", 16, hlop::rank_arrangement::CYCLIC};
	INFO("node list: {}", l);
	hlop::bcast b{};
	for (int i = 0; i < 21; ++i) {
		double res = b.predict(hlop::algo_type::BINOMIAL, l, 1 << i, 0);
		INFO("res[{}]: {}", i, res);
	}

	return 0;
}
