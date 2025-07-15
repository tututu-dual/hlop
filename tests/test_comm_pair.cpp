#include <memory>

#include "m_debug.h"
#include "struct/comm_pair.h"

int main(int argc, char const *argv[]) {
	hlop::comm_pair_t p1{"i10r4n03", 3, "i10r4n04", 4};
	hlop::comm_pair_t p2{"i10r4n09", 9, std::make_shared<hlop::comm_pair>("i10r4n03", 3, "i10r4n04", 4)};
	hlop::comm_pair_t p3{"i10r4n03", 3, "i10r4n04", 4};
	hlop::comm_pair_t p4{"i10r4n09", 9, std::shared_ptr<hlop::comm_pair>{new hlop::comm_pair{"i10r4n03", 3, "i10r4n04", 3}}};
	INFO("p1: {}", p1);
	INFO("p2: {}", p2);
	INFO("p1 {} p3", (p1 == p3 ? "==" : "!="));
	INFO("p2 {} p4", (p2 == p4 ? "==" : "!="));
	return 0;
}
