#ifndef __PARAM_H__
#define __PARAM_H__

#include <cmath>
#include <functional>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

#include "aux.h"
#include "fit.h"

namespace hlop {
extern const std::function<double(double, hlop::exponential_params_t)> exp_fit_func_2;

/// @brief param wrapper, for L & C
class param {
public:
	param() = delete;
	explicit param(const std::string &resources_file);
	~param() = default;

public:
	/// @brief get parameter category which is string
	/// @return
	const std::vector<std::string_view> get_categorys() const;

	/// @brief message size range
	/// @return
	const std::vector<double> &get_msg_size_range() const;

public:
	/// @brief check category exist
	/// @tparam ...Labels
	/// @param ...labels
	/// @return return the category
	template <typename... Labels>
	bool has_category(const Labels &...labels);

	/// @brief get param with specific labels
	/// @tparam ...Labels
	/// @param msg_size
	/// @param ...labels
	/// @return return the parameter
	template <typename... Labels>
	const double get_param(int msg_size, const Labels &...labels) const;

private:
	/// @brief load parameters from file
	/// @param resources_file resources file path
	void load_params(const std::string &resources_file);

	/// @brief get category with given labels
	/// @tparam ...Labels
	/// @param ...labels
	/// @return return the category
	template <typename... Labels>
	const std::string get_category_with_labels(const Labels &...labels) const;

	/// @brief check category exist
	/// @param param_category
	/// @return
	bool has_category(const std::string &param_category) const;

	/// @brief get params with category
	/// @param param_category
	/// @return parameter vector as the message size increase
	const std::vector<double> &get_params(const std::string &param_category) const;

	/// @brief get parameter do not in parameter file
	/// @param y
	/// @return
	std::function<double(double)> fit(const std::vector<double> &y) const;

private:
	std::vector<double> msg_size_pow; // length of param vector, 2 << i is the message size of this coloum
	std::unordered_map<std::string, const std::vector<double>> params;
};
typedef param param_t;

template <typename... Labels>
inline bool param::has_category(const Labels &...labels) {
	const auto &key = get_category_with_labels(labels...);
	return has_category(key);
}

template <typename... Labels>
inline const double param::get_param(int msg_size, const Labels &...labels) const {
	const auto key = get_category_with_labels(labels...);
	const auto &ps = get_params(key);

	double e = std::log2(msg_size);
	int idx = static_cast<int>(e);
	if (hlop::is_pof2(msg_size) && idx < msg_size_pow.size())
		return ps[idx];
	return fit(ps)(e);
}

template <typename... Labels>
inline const std::string param::get_category_with_labels(const Labels &...labels) const {
	std::stringstream ss;
	((ss << labels << "_"), ...); // Concatenate labels with underscores
	std::string key = ss.str();
	if (key.back() == '_') {
		key.pop_back(); // Remove trailing underscore
	}
	return std::move(key);
}
} // namespace hlop

#endif // __PARAM_H__