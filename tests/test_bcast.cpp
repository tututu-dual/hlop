#include "bcast.h"
#include "m_debug.h"
#include "platform.h"
#include "struct/node_list.h"
#include "struct/type.h"
#include <vector>

int main(int argc, char const *argv[]) {
	hlop::node_list_t l{hlop::platform::DF, "h02r1n[08-09]", 8, hlop::rank_arrangement::BLOCK};
	INFO("node list: {}", l);
	hlop::bcast b{};
	std::vector<double> res;
	for (int i = 0; i < 21; ++i) {
		res.emplace_back(b.predict(hlop::algo_type::BINOMIAL, l, 1 << i, 0));
	}
	INFO_VEC("res: ", res);

	return 0;
}
