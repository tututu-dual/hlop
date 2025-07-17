#include "bcast.h"
#include "m_debug.h"
#include "platform.h"
#include "struct/node_list.h"
#include "struct/type.h"

int main(int argc, char const *argv[]) {
	hlop::node_list_t l{hlop::platform::DF, "h10r1n[18-19],h10r2n[00-02],k03r3n[00-02]", 16, hlop::rank_arrange::CYCLIC};
	INFO("node list: {}", l);
	hlop::bcast b{};
	for (int i = 0; i < 10; ++i) {
		double res = b.predict(hlop::algo_type::BINOMIAL, l, 1 << i, 0);
		INFO("res[{}]: {}", i, res);
	}

	return 0;
}
