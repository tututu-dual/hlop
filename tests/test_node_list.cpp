#include "m_debug.h"
#include "struct/node_list.h"
#include "struct/type.h"

int main(int argc, char const *argv[]) {
	hlop::node_list_t nlist{hlop::platform::DF,
	                        "i10r4n[03-04,08-09,13-14,16,18-19]",
	                        16,
	                        {.node_arrange = hlop::rank_arrangement::BLOCK,
	                         .core_arrange = hlop::rank_arrangement::BLOCK}};
	INFO_VEC("node list", nlist.get_node_list());
	INFO_VEC("top 5", nlist.get_top_k_nodes(5));
	// nlist.get_node_list()[0] = hlop::df_node_t{"i10r4n03"};
	return 0;
}