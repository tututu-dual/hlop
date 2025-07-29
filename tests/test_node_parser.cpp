#include "m_debug.h"
#include "node/df_node.h"

int main(int argc, char const *argv[]) {
	auto v = hlop::df_node::parse_node_list("i10r4n[03-04,06,08-10],j10r4n04");
	INFO_VEC("node list", v);
	return 0;
}
