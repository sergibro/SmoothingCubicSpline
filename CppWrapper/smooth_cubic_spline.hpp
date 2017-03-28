#pragma once
#include "smooth_cubic_spline_utils.hpp"

template<class T = LD>
class smooth_cubic_spline
{
protected:
	// Number of data
	int data_number;
	// Smoothing parameter.
	T lambda = 0.9;
	// Input points.
	std::vector<T> x_input;
	// Input values.
	std::vector<T> y_input;
	// Calculation util.
	smooth_cubic_spline_utils<T> *spline_math = new smooth_cubic_spline_utils<T>;
	// Initialization flag.
	bool is_initialized = false;
	// Calculation flag.
	bool is_calculated = false;

public:

	smooth_cubic_spline() {}
	virtual ~smooth_cubic_spline() {}

	// Sets smoothing parameter.
	virtual void set_lambda(T l)
	{
		lambda = l;
	}
	// Returns input grid.
	virtual std::vector<T> get_x()
	{
		return x_input;
	}
	// Loads input data.
	virtual void load(const std::vector<T>& x, const std::vector<T>& y)
	{
		if (x.size() != y.size())
			throw std::exception("Wrong input data");
		x_input = x;
		y_input = y;
		data_number = y.size();
		(*spline_math).load(x, y);
		is_initialized = true;
	}
	// Calculates spline parameters.
	virtual void calculate()
	{
		if (!is_initialized)
			throw std::exception("Spline is not initialised.");
		// Estimate the optimal rigidity.
		//estimate_rigidity(); // for dependent lambda use set lambda after tape_start(X);
		// Solve underlying linear system to find spline coefficients.
		(*spline_math).Solve(lambda);
		is_calculated = true;
	}
	// Estimates the best rigidity value for smoothing spline.
	virtual void estimate_rigidity()
	{
		int n = y_input.size();
		// Rigidity value lies between 0 and 1.
		if (n < 1) lambda = 1e-6;
		std::vector<T> sT(n);
		// Estimating the variance of the set of delta y instead of y to consider the rotation of the function.
		for (int i = 0; i < n - 1; i++)
			sT[i] = y_input[i + 1] - y_input[i];
		T variance = 0;
		T t = sT[0];
		// Estimation of the variance.
		for (int i = 1; i < n; i++)
		{
			t += sT[i];
			T diff = ((i + 1) * sT[i]) - t;
			variance += (diff * diff) / ((i + 1.0) * i);
		}
		T varSt = variance / (n - 1);
		// Calculating the value of the rigidity.
		lambda = 1.0 / (varSt * std::pow(n, 1.0 / 2) + 1);
	}
	// Returns spline value at a specified point.
	virtual T value_at(T point)
	{
		if (!is_calculated)
			throw new std::exception("Spline is not calculated.");
		return (*spline_math).value_at(point);
	}

	virtual std::vector<T> fitted_values()
	{
		return (*spline_math).get_fitted_values();
	}
	// Returns lambda.
	virtual T get_lambda()
	{
		return lambda;
	}

	virtual std::vector<T> spline_vec(std::vector<T> x0, std::vector<T> y0)
	{
		load(x0, y0);
		calculate();
		return fitted_values();
	}
};

template<class T>
std::string convertToStr(T *var)
{
	std::ostringstream ss;
	ss << *var;
	return ss.str();
}

// Reads data from .csv file.
template <class T>
inline void read_file(std::string name, std::vector<T>& x, std::vector<T>& y)
{
	std::vector<T> ref;
	std::ifstream in(name);
	std::string a;
	int n = 0;
	while (!in.eof())
	{
		in >> a;
		n++;
	}
	n--;
	x.resize(n);
	y.resize(n);
	in.close();
	if (n < 6)
	{
		x = { 0, 1, 2, 3, 4, 5 };
		y = { 1, 1, 1, 1, 1, 1 };
		return;
	}
	std::ifstream in1(name);
	for (int i = 0; i < n; i++)
	{
		in1 >> a;
		if (!i && (a[a[0] == '-' ? 1 : 0] > '9' || a[a[0] == '-' ? 1 : 0] < '0')) std::cout << std::endl << "Not a number! " + a << std::endl << std::endl; // check for correct read data
		std::string value = "";
		int d = 0;
		for (int j = 0; j < a.size(); j++)
		{
			if (a[j] == 44)
			{
				if (d == 0)
				{
					x[i] = (T)atof(value.c_str());
					d = 1;
				}
				else
				{
					y[i] = (T)atof(value.c_str());
					d = 0;
				}
				value = "";
			}
			else value += a[j];
			if (j == (a.size() - 1))
			{
				if (d == 1)	y[i] = (T)atof(value.c_str());
				else ref.push_back((T)atof(value.c_str()));
			}
		}
	}
	in1.close();
}

template <class T>
inline void read_and_prepare_data(std::string name, std::vector<T>& x, std::vector<T>& y)
{
	// Load data from file.
	read_file(name, x, y);

	std::vector<std::vector<T>> for_sort(y.size());
	for (auto j = 0; j < y.size(); ++j)
	{
		for_sort.at(j).push_back(x.at(j));
		for_sort.at(j).push_back(y.at(j));
	}
	sort(for_sort.begin(), for_sort.end());
	x.clear();
	y.clear();
	auto x_tmp = for_sort.at(0).at(0);
	for (int j = 0; j < for_sort.size(); ++j)
	{
		if (for_sort.at(j).at(0) - x_tmp > eps_test || !j)
		{
			x.push_back(for_sort.at(j).at(0));
			y.push_back(for_sort.at(j).at(1));
			x_tmp = for_sort.at(j).at(0);
		}
	}
}

template <class T>
T delta(const std::vector<T>& y_res, const std::vector<T>& y_data)
{
	auto n = y_res.size();
	T d = 0;
	for (auto i = 0; i < n; ++i)
	{
		d += (y_res[i] - y_data[i]) * (y_res[i] - y_data[i]);
	}
	return std::sqrt(d / n);
}

// Estimates the best rigidity value for smoothing spline.
template <class T>
T estimate_rigidity(const std::vector<T>& y)
{
	T lambda = 0.9;
	int n = y.size();
	// Rigidity value lies between 0 and 1.
	if (n < 1) lambda = 1e-6;
	std::vector<T> sT(n);
	// Estimating the variance of the set of delta y instead of y to consider the rotation of the function.
	for (int i = 0; i < n - 1; i++)
		sT[i] = y[i + 1] - y[i];
	T variance = 0;
	T t = sT[0];
	// Estimation of the variance.
	for (int i = 1; i < n; i++)
	{
		t += sT[i];
		T diff = ((i + 1) * sT[i]) - t;
		variance += (diff * diff) / ((i + 1.0) * i);
	}
	T varSt = variance / (n - 1);
	// Calculating the value of the rigidity.
	lambda = 1.0 / (varSt * std::pow(n, 1.0 / 2) + 1);
	return lambda;
}

// Finite-difference smooth spline derivatives.
template<typename T, typename TSpline>
std::vector<std::vector<T>> finite_difference_derivatives(TSpline spline, std::vector<T>& x, std::vector<T> y, const int& point_number, const double& step = 1e-3)
{
	std::vector<std::vector<T>> derivative(point_number);
	int n = y.size();
	int n_mult = n / (point_number + 1); // if end or slope value here we can't change 0 and n - 1 points
	for (int i = 0; i < point_number; ++i)
	{
		if (diff_with_respect_to_y) y[(i + 1) * n_mult] += step / 2;
		else x[(i + 1) * n_mult] += step / 2;
		std::vector<T> right = spline.spline_vec(x, y);
		if (diff_with_respect_to_y) y[(i + 1) * n_mult] -= step;
		else x[(i + 1) * n_mult] -= step;
		std::vector<T> left = spline.spline_vec(x, y);
		if (diff_with_respect_to_y) y[(i + 1) * n_mult] += step / 2;
		else x[(i + 1) * n_mult] += step / 2;
		derivative[i].resize(point_number);
		for (int j = 0; j < point_number; j++)
			derivative[i][j] = (right[(j + 1) * n_mult] - left[(j + 1) * n_mult]) / step;
	}
	return derivative;
}

template<class T = LD>
inline void spline_cubic_smooth_example(const std::string& fileName, std::vector<T>& x, std::vector<T>& y, std::vector<T>& y_f, double& lambda)
{
	read_and_prepare_data(fileName, x, y);
	int points_num = x.size();
	smooth_cubic_spline<T> spline;
	spline.load(x, y);
	lambda = ((lambda < 0 || lambda > 1) ? estimate_rigidity(y) : lambda);
	spline.set_lambda(lambda);
	auto clock_time = clock();
	spline.calculate();
	clock_time = clock() - clock_time;
	y_f = spline.fitted_values();
	T dev = delta(y_f, y);
}
