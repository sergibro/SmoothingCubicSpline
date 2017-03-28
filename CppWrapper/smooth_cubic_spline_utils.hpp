#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#define eps_test 1e-5
#define LD long double

using namespace std;

template<class T = LD>
class smooth_cubic_spline_utils
{
protected:
	// Number of input points.
	int data_number;
	// Spline sections.
	std::vector<T> x;
	std::vector<T> y;
	// u, v and w params
	std::vector<std::vector<T>> uvw_;
	// Auxiliary variables.
	std::vector<std::vector<T>> auxiliaries;
	// Spline coefficients.
	std::vector<std::vector<T>> coefficients;
	// Fitted values.
	std::vector<T> y_fitted;

public:

	smooth_cubic_spline_utils() {}
	virtual ~smooth_cubic_spline_utils() {}

	virtual std::vector<T> get_fitted_values()
	{
		return y_fitted;
	}
	// Spline initialisation from X, Y input arrays.
	virtual void load(const std::vector<T>& x0, const std::vector<T>& y0)
	{
		// Number of points.
		data_number = x0.size();
		// Initialise spline input data.
		x = x0;
		y = y0;
	}
	// Calculate spline coefficients.
	virtual void Solve(T lambda)
	{
		coefficients.resize(3);
		for (int i = 0; i < 3; i++)
			coefficients[i].resize(data_number - 1); // n - 1 -> n
													 // Calculate spline helper variables.
		calculate_helper_variables(x, auxiliaries);
		calculate_q();
		// Bound smoothing parameter value to avoid problems with NaN.
		T lambdaMin = 1e-7;
		T lambdaMax = 1 - 1e-7;
		if (lambda < lambdaMin)
			lambda = lambdaMin;
		else if (lambda > lambdaMax)
			lambda = lambdaMax;
		// Internal smoothing parameter: transform lambda -> mu = 2 * (1 - lambda) / (3 * lambda).
		T mu = 2 * (1 - lambda) / (3 * lambda);
		// Prepare system of linear equations: calculate diagonal, first and second upper diagonal vectors u, v, w, respectively.
		prepare_linear_system(mu);
		// Find b-coefficients in splines in auxiliaries[4] array.
		find_b_coefficients(uvw_, auxiliaries);
		std::vector<T> d_coeffs;
		// Find the rest of spline parameters.
		find_all_coefficients(mu, d_coeffs);
		coefficients.push_back(d_coeffs);
		fitted_values();
	}

	virtual void fitted_values()
	{
		int n = data_number;
		y_fitted.resize(n);
		for (int i = 0; i < n; i++)
			y_fitted[i] = value_at(x[i]);
	}
	// Get spline derivative at point x with possible extrapolation.
	virtual T value_at(T point)
	{
		int n = data_number;
		if (point < x[0])
		{
			T diff = point - x[0];
			return coefficients[0][0] * std::pow(diff, 3) + coefficients[1][0] * std::pow(diff, 2) +
				coefficients[2][0] * diff + coefficients[3][0];
		}
		else if (point > x[n - 1])
		{
			T diff = point - x[n - 1];
			return coefficients[0][n - 2] * std::pow(diff, 3) + coefficients[1][n - 2] * std::pow(diff, 2) +
				coefficients[2][n - 2] * diff + coefficients[3][n - 2];
		}

		// Check for requested x within spline.
		for (int j = 0; j < data_number - 1; j++)
			if (point >= x[j] && point <= x[j + 1])
				return value_in_section(point, j);

		// If spline section for requested x was not found, return empty.
		throw std::exception("Value not found.");
	}

	virtual T value_in_section(T point, int section)
	{
		T diff = point - x[section];
		return coefficients[0][section] * std::pow(diff, 3) + coefficients[1][section] * std::pow(diff, 2) +
			coefficients[2][section] * diff + coefficients[3][section];
	}

	virtual void calculate_q()
	{
		int n = y.size();
		for (int i = 1; i < n - 1; ++i)
			auxiliaries[4][i - 1] = 3 * (y[i + 1] - y[i]) / auxiliaries[1][i] - 3 * (y[i] - y[i - 1]) / auxiliaries[1][i - 1];
	}
	// Prepare system of linear equations: calculate all non-zero matrix elements.
	virtual void prepare_linear_system(T mu)
	{
		int n = auxiliaries[0].size() + 2;
		uvw_.resize(3);
		uvw_[0].resize(n - 2);
		uvw_[1].resize(n - 3);
		uvw_[2].resize(n - 4);
		std::vector<T>& u = uvw_[0];
		std::vector<T>& v = uvw_[1];
		std::vector<T>& w = uvw_[2];
		std::vector<T>& p = auxiliaries[0];
		std::vector<T>& h = auxiliaries[1];
		std::vector<T>& r = auxiliaries[2];
		std::vector<T>& f = auxiliaries[3];
		for (int i = 0; i < n - 4; i++)
		{
			u[i] = mu * (std::pow(r[i], 2) + std::pow(f[i], 2) + std::pow(r[i + 1], 2)) + p[i];
			v[i] = mu * r[i + 1] * (f[i] + f[i + 1]) + h[i + 1];
			w[i] = mu * r[i + 1] * r[i + 2];
		}
		u[n - 4] = mu * (std::pow(r[n - 4], 2) + std::pow(f[n - 4], 2) + std::pow(r[n - 3], 2)) + p[n - 4];
		u[n - 3] = mu * (std::pow(r[n - 3], 2) + std::pow(f[n - 3], 2) + std::pow(r[n - 2], 2)) + p[n - 3];
		v[n - 4] = mu * r[n - 3] * (f[n - 4] + f[n - 3]) + h[n - 3];
	}
	// Calculate all spline coefficients.
	virtual void find_all_coefficients(T mu, std::vector<T>& D)
	{
		D = find_d_coefficients(mu, y, auxiliaries);
		// Compact variable name for number of data points.
		int n = D.size() + 1;
		coefficients.resize(3);
		for (int i = 0; i < 3; i++)
			coefficients[i].resize(n - 1);
		coefficients[0][0] = auxiliaries[4][0] / (3 * auxiliaries[1][0]);
		coefficients[1][0] = 0.0;
		coefficients[2][0] = (D[1] - D[0]) / auxiliaries[1][0] - auxiliaries[4][0] * auxiliaries[1][0] / 3;
		coefficients[0][1] = (auxiliaries[4][1] - auxiliaries[4][0]) / (3 * auxiliaries[1][1]);
		coefficients[1][1] = auxiliaries[4][0];
		coefficients[2][1] = auxiliaries[4][0] * auxiliaries[1][0] + coefficients[2][0];
		for (int i = 2; i < n - 2; i++)
		{
			coefficients[0][i] = (auxiliaries[4][i] - auxiliaries[4][i - 1]) / (3 * auxiliaries[1][i]);
			coefficients[1][i] = auxiliaries[4][i - 1];
			coefficients[2][i] = (auxiliaries[4][i - 1] + auxiliaries[4][i - 2]) * auxiliaries[1][i - 1] + coefficients[2][i - 1];
		}
		// Since q[n - 1] = 0.
		coefficients[0][n - 2] = (0 - auxiliaries[4][n - 3]) / (3 * auxiliaries[1][n - 2]);
		coefficients[1][n - 2] = auxiliaries[4][n - 3];
		coefficients[2][n - 2] = (auxiliaries[4][n - 3] + auxiliaries[4][n - 4]) * auxiliaries[1][n - 3] + coefficients[2][n - 3];
	}
	// Initialise spline helper variables.
	virtual void calculate_helper_variables(const std::vector<T>& x0, std::vector<std::vector<T>>& aux)
	{
		int n = x0.size();
		for (int i = 0; i < n - 1; i++)
			if (x0[i] >= x0[i + 1])
				throw("Incorrect data: x values must be sorted and distinct.");
		aux.resize(5);
		// p.
		aux[0].resize(n - 2);
		// h.
		aux[1].resize(n - 1);
		// r.
		aux[2].resize(n - 1);
		// f.
		aux[3].resize(n - 2);
		// q.
		aux[4].resize(n - 2);

		aux[1][0] = x0[1] - x0[0];
		aux[2][0] = 3 / aux[1][0];
		for (int i = 1; i < n - 1; ++i)
		{
			aux[1][i] = x0[i + 1] - x0[i];
			aux[2][i] = 3 / aux[1][i];
			aux[0][i - 1] = 2 * (aux[1][i - 1] + aux[1][i]);
			aux[3][i - 1] = -(aux[2][i - 1] + aux[2][i]);
		}
	}
	// Calculate spline B coefficients (solution of linear system of equations).
	inline void find_b_coefficients(std::vector<std::vector<T>>& uvw, std::vector<std::vector<T>>& aux)
	{
		std::vector<T>& q_ = aux[4];
		solve_spline_five_diagonal_system(uvw, q_);
	}
	// Solve system for spline.
	template<typename Array>
	inline void solve_spline_five_diagonal_system(std::vector<Array>& uvw, Array& q_)
	{
		Array& u = uvw[0];
		Array& v = uvw[1];
		Array& w = uvw[2];
		int n = uvw[0].size() + 2;
		// Factorization procedure.
		w[0] /= u[0];
		v[0] /= u[0];
		u[1] -= u[0] * std::pow(v[0], 2);
		v[1] = (v[1] - u[0] * v[0] * w[0]) / u[1];
		w[1] /= u[1];
		for (int i = 3; i <= n - 4; i++)
		{
			T& ui = u[i - 1];
			T& vi = v[i - 1];
			T& wi = w[i - 1];
			ui -= u[i - 3] * std::pow(w[i - 3], 2) + u[i - 2] * std::pow(v[i - 2], 2);
			vi = (vi - u[i - 2] * v[i - 2] * w[i - 2]) / ui;
			wi /= ui;
		}
		T& un = u[n - 4];
		T& unn = u[n - 3];
		T& wn = w[n - 5];
		un -= u[n - 6] * std::pow(w[n - 6], 2) + u[n - 5] * std::pow(v[n - 5], 2);
		v[n - 4] = (v[n - 4] - u[n - 5] * v[n - 5] * wn) / un;
		unn -= u[n - 5] * std::pow(wn, 2) + un * std::pow(v[n - 4], 2);
		// Forward substitution.
		q_[1] -= v[0] * q_[0];
		for (int i = 2; i < n - 2; ++i)
			q_[i] += (-v[i - 1] * q_[i - 1] - w[i - 2] * q_[i - 2]);
		for (int i = 0; i < n - 2; ++i)
			q_[i] /= u[i];
		// Back substitution.
		q_[n - 4] -= v[n - 4] * q_[n - 3];
		for (int i = n - 5; i >= 0; --i)
			q_[i] -= (v[i] * q_[i + 1] + w[i] * q_[i + 2]);
	}
	// Calculate spline D coefficients.
	template<typename Array>
	inline std::vector<T> find_d_coefficients(T mu, const Array& y0, std::vector<std::vector<T>>& aux)
	{
		int n = y0.size();
		std::vector<T> result(n - 1);
		result[0] = y0[0] - mu * aux[2][0] * aux[4][0];
		result[1] = y0[1] - mu * (aux[3][0] * aux[4][0] + aux[2][1] * aux[4][1]);
		for (int i = 2; i < n - 2; ++i)
			result[i] = y0[i] - mu * (aux[2][i - 1] * aux[4][i - 2] + aux[3][i - 1] * aux[4][i - 1] + aux[2][i] * aux[4][i]);
		result[n - 2] = y0[n - 2] - mu * (aux[2][n - 3] * aux[4][n - 4] + aux[3][n - 3] * aux[4][n - 3]);
		return result;
	}
};
