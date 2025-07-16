#ifndef __FIT_H__
#define __FIT_H__

#include <functional>
#include <gsl/gsl_vector.h>
#include <vector>

namespace hlop {
/// @brief exponential function parameters, A * exp(B * x) + C.
struct exponential_params {
	double A;
	double B;
	double C;
};
typedef exponential_params exponential_params_t;

/// @brief predefined exponential function 1.
extern const std::function<double(double, double, double, double)> exp_fit_func_1;
/// @brief predefined exponential function 2.
extern const std::function<double(double, hlop::exponential_params_t)> exp_fit_func_2;

/**
 * @brief exponential residual function for GSL.
 * @param params gsl_vector *, parameters of the exponential function.
 * @param data void *, pointer to the data (x and y values).
 * @param residuals gsl_vector *, vector to store the residuals.
 * @return GSL_SUCCESS on success, error code otherwise.
 */
int exponential_residual(const gsl_vector *params, void *data, gsl_vector *residuals);

/**
 * @brief curve fitting for exponential function.
 * @param x_data vector<double>, x values of the data points.
 * @param y_data vector<double>, y values of the data points.
 * @param initial_guess vector<double>, initial guess for the parameters [A, B, C].
 * @return parameters of the fitted exponential function.
 * @throws hlop_err if the input data is invalid or the fitting fails.
 */
hlop::exponential_params_t curve_fit_exponential(const std::vector<double> &x_data, const std::vector<double> &y_data,
                                                 const std::vector<double> &initial_guess);
} // namespace hlop

#endif // __FIT_H__