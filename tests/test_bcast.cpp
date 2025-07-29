#include <iostream>
#include <vector>

#include "bcast.h"
#include "m_debug.h"
#include "platform.h"
#include "struct/node_list.h"
#include "struct/type.h"

int main(int argc, char const *argv[]) {
	hlop::node_list_t l{hlop::platform::DF,
	                    "g09r2n[16-17]",
	                    8,
	                    {.node_arrange = hlop::rank_arrangement::BLOCK,
	                     .core_arrange = hlop::rank_arrangement::CYCLIC}};
	INFO("node list: {}", l);
	hlop::bcast b{};
	std::vector<double> res;
	for (int i = 0; i < 21; ++i)
		res.emplace_back(b.predict(hlop::algo_type::BINOMIAL, l, 1 << i, 0));
	for (const auto &i : res)
		std::cout << i << std::endl;

	return 0;
}