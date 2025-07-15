#include <magic_enum/magic_enum.hpp>

#include "m_debug.h"
#include "struct/type.h"

int main(int argc, char const *argv[]) {
	auto name = magic_enum::enum_name(hlop::op_type::BCAST);
	INFO("{}", name);
	return 0;
}
