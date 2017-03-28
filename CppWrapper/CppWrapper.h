// CppWrapper.h
#pragma once
#include "smooth_cubic_spline.hpp"
#include "smooth_cubic_spline_utils.hpp"

using namespace System;
using namespace System::Collections::Generic;

namespace CppWrapper {

	public ref class CppWrapperClass
	{
	public:
		CppWrapperClass(char* fileName);
		CppWrapperClass(char* fileName, double lambda);
		List<double>^ x();
		List<double>^ y();
		List<double>^ yRes();
		double^ getLambda();
	private:
		std::vector<LD>& x_ = *(new std::vector<LD>());
		std::vector<LD>& y_ = *(new std::vector<LD>());
		std::vector<LD>& y_fitted = *(new std::vector<LD>());
		double& lambda_ = *(new double(-1.0));
	};
}
