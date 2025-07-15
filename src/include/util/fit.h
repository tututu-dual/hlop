#ifndef __FIT_H__
#define __FIT_H__

#include <functional>
#include <gsl/gsl_vector.h>
#include <vector>

namespace hlop {
/// @brief fit function parameters, like A * e ^ (-B * x) +C
struct exponential_params {
	double A;
	double B;
	double C;
};
typedef exponential_params exponential_params_t;

extern const std::function<double(double, double, double, double)> exp_fit_func_1;
extern const std::function<double(double, hlop::exponential_params_t)> exp_fit_func_2;

/// @brief residual function
/// @param params
/// @param data
/// @param residuals
/// @return
int exponential_residual(const gsl_vector *params, void *data, gsl_vector *residuals);

/// @brief curve fit exponential function
/// @param x_data
/// @param y_data
/// @param initial_guess
/// @return return the parameters in function
hlop::exponential_params_t curve_fit_exponential(const std::vector<double> &x_data, const std::vector<double> &y_data,
                                                 const std::vector<double> &initial_guess);
} // namespace hlop

#endif // __FIT_H__