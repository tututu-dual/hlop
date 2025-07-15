#include <iostream>

#include "aux.h"
#include "structs/types.h"

std::ostream &hlop::operator<<(std::ostream &os, const hlop::op_type &op) {
	os << hlop::enum_name(op);
	return os;
}

std::ostream &hlop::operator<<(std::ostream &os, const hlop::algo_type &algo) {
	os << hlop::enum_name(algo);
	return os;
}