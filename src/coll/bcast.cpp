#include "bcast.h"
#include "collective.h"
#include "err.h"
#include "struct/node_list.h"
#include "struct/type.h"

hlop::bcast::bcast() : hlop::collective() {
	initialize_ftbl();
}

double hlop::bcast::binomial(const hlop::node_list_t &nl, int msg_size) {
	return binomial_aux(nl, msg_size, 0);
}

double hlop::bcast::scatter_recursive_doubling_allgather(const hlop::node_list_t &nl, int msg_size) {
	HLOP_ERR("unimplemented algorithm scatter recursive doubling allgather");
	return 0.0;
}

double hlop::bcast::scatter_ring_allgather(const hlop::node_list_t &nl, int msg_size) {
	HLOP_ERR("unimplemented algorithm scatter ring allgather");
	return 0.0;
}

double hlop::bcast::smp(const hlop::node_list_t &nl, int msg_size) {
	HLOP_ERR("unimplemented algorithm smp");
	return 0.0;
}

void hlop::bcast::initialize_ftbl() {
	ftbl.insert({hlop::algo_type::BINOMIAL,
	             [this](const hlop::node_list_t &nl, int msg_size) -> double {
		             return this->binomial(nl, msg_size);
	             }});
	ftbl.insert({hlop::algo_type::SCATTER_RECURSIVE_DOUBLING_ALLGATHER,
	             [this](const hlop::node_list_t &nl, int msg_size) -> double {
		             return this->scatter_recursive_doubling_allgather(nl, msg_size);
	             }});
	ftbl.insert({hlop::algo_type::SCATTER_RING_ALLGATHER,
	             [this](const hlop::node_list_t &nl, int msg_size) -> double {
		             return this->scatter_ring_allgather(nl, msg_size);
	             }});
	ftbl.insert({hlop::algo_type::SMP,
	             [this](const hlop::node_list_t &nl, int msg_size) -> double {
		             return this->smp(nl, msg_size);
	             }});
}