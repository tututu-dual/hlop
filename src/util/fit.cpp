#include <cmath>
#include <cstddef>
#include <functional>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_multifit_nlinear.h>
#include <gsl/gsl_vector.h>
#include <vector>

#include "err.h"
#include "fit.h"

const std::function<double(double, double, double, double)> hlop::exp_fit_func_1 =
    [](double x, double A, double B, double C) -> double { return A * std::exp(-B * x) + C; };

const std::function<double(double, hlop::exponential_params_t)> hlop::exp_fit_func_2 =
    [](double x, hlop::exponential_params_t p) -> double { return hlop::exp_fit_func_1(x, p.A, p.B, p.C); };

int hlop::exponential_residual(const gsl_vector *params, void *data, gsl_vector *residuals) {
	// 解析函数参数
	double A = gsl_vector_get(params, 0);
	double B = gsl_vector_get(params, 1);
	double C = gsl_vector_get(params, 2);

	// 获取数据点
	const std::vector<double> *data_ptr = static_cast<const std::vector<double> *>(data);
	const auto &x = data_ptr->data();
	const auto &y = x + data_ptr->size() / 2;
	std::size_t n = data_ptr->size() / 2;

	// 计算每个数据点的残差
	for (std::size_t i = 0; i < n; ++i) {
		double model = exp_fit_func_1(x[i], A, B, C);
		gsl_vector_set(residuals, i, y[i] - model);
	}

	return GSL_SUCCESS;
}

hlop::exponential_params_t hlop::curve_fit_exponential(const std::vector<double> &x_data,
                                                       const std::vector<double> &y_data,
                                                       const std::vector<double> &initial_guess) {
	// 验证输入数据
	if (x_data.size() != y_data.size())
		HLOP_ERR("x_data and y_data must have the same size");

	if (initial_guess.size() != 3)
		HLOP_ERR("initial guess requires 3 parameters: A, B, C");

	// 合并数据（x和y放在同一个数组中）
	std::vector<double> data;
	data.reserve(x_data.size() + y_data.size());
	data.insert(data.end(), x_data.begin(), x_data.end());
	data.insert(data.end(), y_data.begin(), y_data.end());

	const std::size_t n = x_data.size(); // 数据点数量
	const std::size_t p = 3;             // 参数数量 (A, B, C)

	// 配置GSL非线性最小二乘法求解器
	gsl_multifit_nlinear_parameters fdf_params = gsl_multifit_nlinear_default_parameters();

	// 选择Levenberg-Marquardt算法
	fdf_params.trs = gsl_multifit_nlinear_trs_lm;

	// 分配求解器工作空间
	gsl_multifit_nlinear_workspace *workspace =
	    gsl_multifit_nlinear_alloc(gsl_multifit_nlinear_trust, &fdf_params, n, p);

	// 定义残差函数
	gsl_multifit_nlinear_fdf fdf;
	fdf.f = hlop::exponential_residual;
	fdf.df = nullptr;  // 不提供解析雅可比（使用数值差分）
	fdf.fvv = nullptr; // 不提供二阶导
	fdf.n = n;
	fdf.p = p;
	fdf.params = &data;

	// 设置初始参数
	gsl_vector *params = gsl_vector_alloc(p);
	for (std::size_t i = 0; i < p; ++i)
		gsl_vector_set(params, i, initial_guess[i]);

	// 初始化求解器
	gsl_multifit_nlinear_init(params, &fdf, workspace);

	// 执行优化迭代 (最大100次)
	int status;
	int iter;
	std::size_t max_iter = 100;
	double xtol = 1e-8, gtol = 1e-8, ftol = 0.0;
	status = gsl_multifit_nlinear_driver(max_iter, xtol, gtol, ftol, NULL, NULL, &iter, workspace);

	// 检查收敛状态
	if (status != GSL_SUCCESS)
		HLOP_ERR("fitting did not converge");

	// 获取优化后的参数
	hlop::exponential_params_t results;
	results.A = gsl_vector_get(workspace->x, 0);
	results.B = gsl_vector_get(workspace->x, 1);
	results.C = gsl_vector_get(workspace->x, 2);

	// 输出优化信息
	gsl_matrix *J = gsl_matrix_alloc(p, p);
	gsl_multifit_nlinear_covar(workspace->J, 0.0, J);

	double chi = gsl_blas_dnrm2(workspace->f);
	double dof = n - p;
	double c = GSL_MAX_DBL(1, chi / sqrt(dof));

	// 清理资源
	gsl_matrix_free(J);
	gsl_vector_free(params);
	gsl_multifit_nlinear_free(workspace);

	return results;
}