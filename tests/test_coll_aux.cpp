
#include "collective.h"
#include "m_debug.h"
#include "struct/type.h"

class coll : public hlop::collective {
public:
	coll();
	~coll() = default;

private:
	void initialize_ftbl() override;
};

coll::coll() {
	initialize_ftbl();
}

void coll::initialize_ftbl() {
	ftbl.insert({hlop::algo_type::BINOMIAL,
	             [this](const hlop::node_list_t &nl, int msg_size) -> double {
		             return this->binomial_aux(nl, msg_size);
	             }});
	ftbl.insert({hlop::algo_type::RECURSIVE_DOUBLING,
	             [this](const hlop::node_list_t &nl, int msg_size) -> double {
		             return this->recursive_doubling_aux(nl, msg_size);
	             }});
}

int main(int argc, char const *argv[]) {
	hlop::node_list_t l{hlop::platform::DF, "g11r4n[01-03]", 16, hlop::rank_arrange::CYCLIC};
	INFO("node list: {}", l);
	coll c;
	INFO("predict result: {}", c.predict(hlop::algo_type::RECURSIVE_DOUBLING, l, 4));
	return 0;
}