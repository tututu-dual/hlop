#include <iostream>

#include "aux.h"
#include "struct/type.h"

std::ostream &hlop::operator<<(std::ostream &os, const op_type_t &op) {
	os << hlop::enum_name(op);
	return os;
}

std::ostream &hlop::operator<<(std::ostream &os, const algo_type_t &algo) {
	os << hlop::enum_name(algo);
	return os;
}

std::ostream &hlop::operator<<(std::ostream &os, const rank_arrangement_t &ra) {
	os << hlop::enum_name(ra);
	return os;
}