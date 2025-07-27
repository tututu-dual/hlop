#ifndef __PARAM_H__
#define __PARAM_H__

#include <cmath>
#include <functional>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "aux.h"
#include "fit.h"

namespace hlop {
/// @brief predefined exponential function 1.
extern const std::function<double(double, hlop::exponential_params_t)> exp_fit_func_2;

/**
 * @brief class param.
 * This class loads parameters from a resources file and provides methods to access
 * parameters based on message size and category labels.
 * It supports checking for the existence of categories and retrieving parameters
 * based on message size and labels.
 * It also provides a fitting function for parameters that are not present in the parameter file.
 * The parameters are expected to be in the form of a vector where the index corresponds to the
 * logarithm base 2 of the message size.
 * @throws hlop_err if the resources file cannot be opened, is empty, or has invalid format.
 */
class param {
public:
	using param_t = hlop::param;

public:
	/**
	 * @brief default constructor.
	 * @note This constructor is deleted to prevent instantiation without parameters.
	 * It is intended to ensure that the class is always initialized with a valid resources file.
	 */
	param() = delete;
	/**
	 * @brief constructor.
	 * @param resources_file string, path to the resources file.
	 * @throws hlop_err, if the resources file cannot be opened, is empty, or has invalid format.
	 */
	param(const std::string &resources_file);
	~param() = default;

private:
	/**
	 * @brief load parameters from resources file, auxiliary function.
	 * @param resources_file string, path to the resources file.
	 * @throws hlop_err, if the resources file cannot be opened or is empty or has invalid format.
	 */
	void load_params(const std::string &resources_file);

public:
	/**
	 * @brief get all categories.
	 * @return vector<string_view>, containing all categories.
	 */
	const std::vector<std::string_view> get_categorys() const;
	/**
	 * @brief get message size range.
	 * @return vector<double>, containing the message size range in powers of 2.
	 */
	const std::vector<double> &get_msg_size_range() const;

private:
	/**
	 * @brief check if a category exists, auxiliary function.
	 * @param param_category string, the category to check.
	 * @return bool, true if the category exists, false otherwise.
	 */
	bool has_category(const std::string &param_category) const;
	/**
	 * @brief get parameters for a specific category, auxiliary function.
	 * @param param_category string, the category to get parameters for.
	 * @return vector<double>, the parameters for the given category.
	 * @throws hlop_err, if the category does not exist.
	 */
	const std::vector<double> &get_params(const std::string &param_category) const;
	/**
	 * @brief fit function for parameters that are not present in the parameter file, auxiliary function.
	 * @param y vector<double>, the parameters to fit.
	 * @return function<double(double)>, a function that fits the parameters.
	 */
	std::function<double(double)> fit(const std::vector<double> &y) const;

public:
	/**
	 * @brief check if a category exists.
	 * @tparam Labels labels type.
	 * @param labels Labels, concatenated labels to a category.
	 * @return bool, true if the category exists, false otherwise.
	 */
	template <typename... Labels>
	bool has_category(const Labels &...labels);
	/**
	 * @brief get parameter based on message size and labels.
	 * @tparam Labels labels type.
	 * @param msg_size int, message size.
	 * @param labels Labels, concatenated labels to a category.
	 * @return double, the parameter value for the given message size and labels.
	 */
	template <typename... Labels>
	const double get_param(int msg_size, const Labels &...labels) const;

private:
	/**
	 * @brief concatenate labels to a category, auxiliary function.
	 * @tparam Labels labels type.
	 * @param labels Labels, concatenated labels to a category.
	 * @return string, the concatenated category name.
	 */
	template <typename... Labels>
	const std::string get_category_with_labels(const Labels &...labels) const;

private:
	std::vector<double> msg_size_pow; // length of param vector, 2 << i is the message size of this coloum
	std::unordered_map<std::string, const std::vector<double>> params;
};
typedef param::param_t param_t;

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
	return key;
}
} // namespace hlop

#endif // __PARAM_H__