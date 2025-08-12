#include "allgather.h"
#include "m_debug.h"
#include "struct/node_list.h"
#include "struct/type.h"

int main(int argc, char const *argv[]) {
	hlop::node_list_t l{hlop::platform::DF,
	                    "g12r1n01,h07r2n08",
	                    8,
	                    {.node_arrange = hlop::rank_arrangement::BLOCK,
	                     .core_arrange = hlop::rank_arrangement::BLOCK}};
	INFO("node list: {}", l);
	hlop::allgather a{};
	std::vector<double> res;
	for (int i = 0; i < 21; ++i)
		res.emplace_back(a.predict(hlop::algo_type::RECURSIVE_DOUBLING, l, 1 << i, 0));
	for (const auto &i : res)
		std::cout << i << std::endl;

	return 0;
}
