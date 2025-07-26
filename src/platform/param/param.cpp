#include <cmath>
#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

#include "aux.h"
#include "err.h"
#include "fit.h"
#include "m_debug.h"
#include "msg.h"
#include "param/param.h"

hlop::param::param(const std::string &resources_file) { load_params(resources_file); }

const std::vector<std::string_view> hlop::param::get_categorys() const {
	std::vector<std::string_view> categories;
	for (const auto &pair : params)
		categories.emplace_back(pair.first);

	return categories;
}

const std::vector<double> &hlop::param::get_msg_size_range() const { return msg_size_pow; }

void hlop::param::load_params(const std::string &resources_file) {
	std::ifstream fin{resources_file};
	if (!fin.is_open())
		HLOP_ERR(hlop::format("failed to open resources file: {}", resources_file));

	std::string line;

	// skip first line, first line is the table head
	if (!std::getline(fin, line))
		HLOP_ERR(hlop::format("empty resources file: {}", resources_file));
	msg_size_pow = hlop::stov<double>(line, 1);
	// store the power of 2
	for (auto &m : msg_size_pow)
		m = static_cast<int>(std::log2(m));

	while (std::getline(fin, line)) {
		std::stringstream ss{line};
		std::string param_category;
		if (!std::getline(ss, param_category, ','))
			HLOP_ERR(hlop::format("invalid line format in resources file: {}", resources_file));
		params.emplace(param_category, hlop::stov<double>(line, 1));
	}
}

bool hlop::param::has_category(const std::string &param_category) const {
	const auto &it = params.find(param_category);
	if (it == params.end())
		return false;
	return true;
}

const std::vector<double> &hlop::param::get_params(const std::string &param_category) const {
	if (!has_category(param_category))
		HLOP_ERR(hlop::format("parameter category not found: {}", param_category));

	const auto &it = params.find(param_category);
	INFO("{}", it->first);
	DEBUG("{}: {}", it->first, hlop::vtos(it->second));
	return it->second;
}

std::function<double(double)> hlop::param::fit(const std::vector<double> &y) const {
	auto p = hlop::curve_fit_exponential(msg_size_pow, y, {0, 0, y[0]});
	return [=](double x) -> double {
		return hlop::exp_fit_func_2(x, p);
	};
}