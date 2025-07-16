#include <cstddef>
#include <iomanip>
#include <regex>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "err.h"
#include "msg.h"
#include "node/df_node_parser.h"

const std::regex hlop::df_node_parser::NODE_LIST_REGEX{R"(([^,\[\]]+\[[^\[\]]+\])|([^,\[\]]+))"};
const std::regex hlop::df_node_parser::NODE_REGEX{R"(([a-zA-Z]\d+)([a-zA-Z]\d+)([a-zA-Z]\d+))"};

const std::vector<std::string> hlop::df_node_parser::parse_node_list(const std::string &node_list_str) {
	std::vector<std::string> nodes;
	auto beg = std::sregex_iterator(node_list_str.begin(),
	                                node_list_str.end(),
	                                NODE_LIST_REGEX);
	auto end = std::sregex_iterator();

	for (auto it = beg; it != end; ++it) {
		std::string group = it->str();
		std::smatch match;
		std::regex range_re(R"((.*)\[(.*)\])");
		if (!std::regex_match(group, match, range_re)) {
			if (!std::regex_match(group, NODE_REGEX))
				HLOP_ERR(hlop::format("invalid node format {}", group));
			nodes.emplace_back(group);
			continue;
		}
		std::string prefix = match[1];
		std::string ranges = match[2];
		std::stringstream ss{ranges};
		std::string token;
		while (std::getline(ss, token, ',')) {
			std::size_t dash = token.find('-');
			if (dash == std::string::npos) {
				if (!std::regex_match(prefix + token, NODE_REGEX))
					HLOP_ERR(hlop::format("invalid node format {}", prefix + token));
				nodes.emplace_back(prefix + token);
				continue;
			}
			int start = std::stoi(token.substr(0, dash));
			int end = std::stoi(token.substr(dash + 1));
			int width = token.substr(0, dash).size();
			for (int i = start; i <= end; ++i) {
				std::ostringstream oss;
				oss << prefix << std::setw(width) << std::setfill('0') << i;
				if (!std::regex_match(oss.str(), NODE_REGEX))
					HLOP_ERR(hlop::format("invalid node format {}", oss.str()));
				nodes.emplace_back(oss.str());
			}
		}
	}
	return std::move(nodes);
}
