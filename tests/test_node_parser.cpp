#include "aux.h"
#include "m_debug.h"
#include "node/df_node_parser.h"

int main(int argc, char const *argv[]) {
	auto v = hlop::df_node_parser::parse_node_list("i10r4n[03-04,08-09,13-14,16,18-19],i11r1n[02-03,08-09,11-12,14,19],i11r2n[01,04,14-15],g03r2n01,i11r3n[01,16-17],g01r2n00,g02r4n11");
	INFO_VEC("node list", v);
	return 0;
}
