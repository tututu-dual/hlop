#include <iostream>
#include <string>

#include "param/param.h"

int main(int argc, char const *argv[]) {
	std::string path = "/home/huang/project/H-Lop/resources/东方超算N-Hop参数.csv";
	hlop::param_t p{path};
	std::cout << p.get_categorys().size() << std::endl;

	const auto &range = p.get_msg_size_range();
	for (const auto &i : range) {
		const auto &v = p.get_param(std::pow(2, static_cast<int>(i)), "L0", "PING", "1");
		std::cout << v << ",";
	}
	std::cout << std::endl;

	for (const auto &i : range) {
		const auto &v = p.get_param(std::pow(2, static_cast<int>(i)) + 5, "L0", "PING", "1");
		std::cout << v << ",";
	}
	std::cout << std::endl;
	return 0;
}
