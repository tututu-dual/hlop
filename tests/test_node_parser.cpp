#include "m_debug.h"
#include "platform.h"

int main(int argc, char const *argv[]) {
	auto v = hlop::node_parser::parse_node_list(hlop::platform::DF, "i10r4n[03-04,16,18-19]");
	v[0]->bind_core(0, 0);
	INFO_VEC("node list", v);
	return 0;
}
