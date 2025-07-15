#include <iostream>

#include "aux.h"
#include "platform.h"

std::ostream &hlop::operator<<(std::ostream &os, const hlop::platform &p) {
	os << hlop::enum_name(p);
	return os;
}