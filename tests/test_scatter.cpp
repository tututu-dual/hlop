#include "m_debug.h"
#include "scatter.h"
#include "struct/node_list.h"
#include "struct/type.h"

int main(int argc, char const *argv[]) {
	hlop::node_list_t l{hlop::platform::DF,
	                    "i02r1n[18-19]",
	                    8,
	                    {.node_arrange = hlop::rank_arrangement::BLOCK,
	                     .core_arrange = hlop::rank_arrangement::BLOCK}};
	INFO("node list: {}", l);
	hlop::scatter s{};
	std::vector<double> res;
	for (int i = 0; i < 17; ++i)
		res.emplace_back(s.predict(hlop::algo_type::BINOMIAL, l, 1 << i, 0));
	for (const auto &i : res)
		std::cout << i << std::endl;

	return 0;
}
