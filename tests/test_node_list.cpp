#include "m_debug.h"
#include "struct/node_list.h"
#include "struct/type.h"

int main(int argc, char const *argv[]) {
	hlop::node_list_t nlist{hlop::platform::DF,
	                        "i10r4n[03-04]",
	                        16,
	                        {.node_arrange = hlop::rank_arrangement::BLOCK,
	                         .core_arrange = hlop::rank_arrangement::CYCLIC}};
	INFO_VEC("node list", nlist.get_node_list());
	return 0;
}