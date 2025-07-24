#include "aux.h"
#include "m_debug.h"
#include "struct/node_list.h"
#include "struct/type.h"

int main(int argc, char const *argv[]) {
	hlop::node_list_t nlist{hlop::platform::DF, "i10r4n[03-04,08-09,13-14,16,18-19],i11r1n[02-03,08-09,11-12,14,19],i11r2n[01,04,14-15],i11r3n[01,16-17],g01r2n00,g02r4n11,g03r2n01", 16, hlop::rank_arrangement::CYCLIC};
	INFO("{} and {} level is {}", "i10r4n03", "i11r2n01", nlist.get_inter_level("i10r4n03", "i11r2n01"));
	INFO_VEC("node list", nlist.get_node_list());
	INFO_VEC("top 5", nlist.get_top_k_nodes(5));
	return 0;
}