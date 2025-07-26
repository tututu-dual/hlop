#include <memory>

#include "m_debug.h"
#include "node/df_node.h"
#include "struct/comm_pair.h"

int main(int argc, char const *argv[]) {
	hlop::df_node_t node1{"i10r4n03"};
	for (int i = 0; i < 16; ++i) // even rank 0-31 -> core 0-15
		node1.bind_core(2 * i, i);
	hlop::df_node_t node2{"i10r4n04"};
	for (int i = 0; i < 16; ++i) // odd rank 0-31 -> core 0-15
		node2.bind_core(2 * i + 1, i);
	hlop::df_node_t node3{"i10r4n05"};
	for (int i = 32; i < 48; ++i) // rank 32-47 -> core 0-15
		node3.bind_core(i, i - 32);
	hlop::comm_pair_t p1{node1, 0,    // node 1, rank 0, core 0
	                     node2, 1};   // node 2, rank 1, core 0
	hlop::comm_pair_t p2{node1, 2,    // node 1, rank 2, core 1
	                     node2, 3};   // node 2, rank 3, core 1
	hlop::comm_pair_t p3{node1, 0,    // node 1, rank 0, core 0
	                     node3, 32};  // node 3, rank 32, core 0
	hlop::comm_pair_t p4_0{node1, 0,  // node 1, rank 0, core 0
	                       node1, 4}; // node 1, rank 4, core 2
	hlop::comm_pair_t p4_1{node1, 2,  // node 1, rank 2, core 1
	                       node1, 6}; // node 1, rank 6, core 3
	hlop::comm_pair_t p4{node1, 0,    // node 1, rank 0, core 0
	                     node1, 8};   // node 1, rank 8, core 4
	hlop::comm_pair_t p5{node1, 2,    // node 1, rank 2, core 1
	                     node1, 10};  // node 1, rank 10, core 5
	hlop::comm_pair_t p6{node1, 0,    // node 1, rank 0, core 0
	                     node1, 16};  // node 1, rank 16, core 8
	hlop::comm_pair_t p7{node1, 2,    // node 1, rank 2, core 1
	                     node1, 18};  // node 1, rank 18, core 9
	hlop::comm_pair_t p8{node1, 0,    // node 1, rank 0, core 0
	                     std::make_shared<hlop::comm_pair>(node2, 1, node3, 32)};
	hlop::comm_pair_t p9{node1, 0, // node 1, rank 0, core 0
	                     std::make_shared<hlop::comm_pair>(node2, 3, node3, 33)};
	hlop::comm_pair_t p10{node1, 0, // node 1, rank 0, core 0
	                      std::make_shared<hlop::comm_pair>(node2, 5, node3, 34)};
	hlop::comm_pair_t p11{node1, 0, // node 1, rank 0, core 0
	                      std::make_shared<hlop::comm_pair>(node1, 0, node1, 4)};
	hlop::comm_pair_t p12{node1, 0, // node 1, rank 0, core 0
	                      std::make_shared<hlop::comm_pair>(node1, 2, node1, 6)};
	hlop::comm_pair_t p13{node1, 0, // node 1, rank 0, core 0
	                      std::make_shared<hlop::comm_pair>(node1, 0, node1, 8)};
	hlop::comm_pair_t p14{node1, 0, // node 1, rank 0, core 0
	                      std::make_shared<hlop::comm_pair>(node1, 2, node1, 10)};

	INFO("p1 is {}", (p1.is_mid_node_pair() ? "mid" : "not mid"));
	INFO("p1 is {}", (p1.is_inter_node_pair() ? "inter" : "not inter"));
	INFO("p1 is {}", (p1.is_intra_node_pair() ? "intra" : "not intra"));
	INFO("p1 {} p2", (p1 == p2 ? "==" : "!=")); // should be ==
	INFO("p1 {} p3", (p1 == p3 ? "==" : "!=")); // should be !=

	INFO("p4 is {}", (p4.is_mid_node_pair() ? "mid" : "not mid"));
	INFO("p4 is {}", (p4.is_inter_node_pair() ? "inter" : "not inter"));
	INFO("p4 is {}", (p4.is_intra_node_pair() ? "intra" : "not intra"));
	INFO("p4_0 {} p4_1", (p4_0 == p4_1 ? "==" : "!=")); // should be ==
	INFO("p4_0 {} p4", (p4_0 == p4 ? "==" : "!="));     // should be !=
	INFO("p4 {} p5", (p4 == p5 ? "==" : "!="));         // should be ==
	INFO("p4 {} p6", (p4 == p6 ? "==" : "!="));         // should be !=
	INFO("p6 {} p7", (p6 == p7 ? "==" : "!="));         // should be ==
	INFO("p6 {} p1", (p6 == p1 ? "==" : "!="));         // should be !=

	INFO("p8 is {}", (p8.is_mid_node_pair() ? "mid" : "not mid"));
	INFO("p8 is {}", (p8.is_inter_node_pair() ? "inter" : "not inter"));
	INFO("p8 is {}", (p8.is_intra_node_pair() ? "intra" : "not intra"));
	INFO("p8 {} p9", (p8 == p9 ? "==" : "!="));
	INFO("p8 {} p10", (p8 == p10 ? "==" : "!="));
	INFO("p11 {} p12", (p11 == p12 ? "==" : "!="));
	INFO("p11 {} p13", (p11 == p13 ? "==" : "!="));
	INFO("p13 {} p14", (p13 == p14 ? "==" : "!="));

	INFO("p1 {} p4", (p1 == p4 ? "==" : "!=")); // should be !=
	INFO("p1 {} p8", (p1 == p8 ? "==" : "!=")); // should be !=
	INFO("p4 {} p8", (p4 == p8 ? "==" : "!=")); // should be !=
	return 0;
}
