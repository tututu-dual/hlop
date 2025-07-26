#include "m_debug.h"
#include "scatter.h"
#include "struct/node_list.h"
#include "struct/type.h"

int main(int argc, char const *argv[]) {
	hlop::node_list_t l{hlop::platform::DF,
	                    "g11r4n[01-03]",
	                    16,
	                    {.node_arrange = hlop::rank_arrangement::BLOCK,
	                     .core_arrange = hlop::rank_arrangement::BLOCK}};
	INFO("node list: {}", l);
	hlop::scatter s{};
	auto res = s.predict(hlop::algo_type::BINOMIAL, l, 4 * l.get_rank_num(), 0);
	INFO("result: {}", res);
	return 0;
}
