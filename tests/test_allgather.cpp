#include "allgather.h"
#include "m_debug.h"
#include "struct/node_list.h"
#include "struct/type.h"

int main(int argc, char const *argv[]) {
	hlop::node_list_t l{hlop::platform::DF, "g11r4n[01-03]", 16, hlop::rank_arrange::CYCLIC};
	INFO("node list: {}", l);
	hlop::allgather a{};
	auto res = a.predict(hlop::algo_type::RECURSIVE_DOUBLING, l, 4, 0);
	INFO("result: {}", res);
	return 0;
}
