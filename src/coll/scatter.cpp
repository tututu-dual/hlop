#include "scatter.h"
#include "collective.h"
#include "structs/node_list.h"
#include "structs/types.h"

hlop::scatter::scatter() : hlop::collective() {
	initialize_ftbl();
}

double hlop::scatter::binomial(const hlop::node_list_t &nl, int msg_size) {
	return 0.0;
}

void hlop::scatter::initialize_ftbl() {
	ftbl[hlop::algo_type::BINOMIAL] = [this](const hlop::node_list_t &nl, int msg_size) -> double {
		return this->binomial(nl, msg_size);
	};
}
