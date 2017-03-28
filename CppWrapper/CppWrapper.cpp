// This is the main DLL file.
#include "stdafx.h"
#include "CppWrapper.h"


CppWrapper::CppWrapperClass::CppWrapperClass(char* fileName)
{
	spline_cubic_smooth_example(fileName, x_, y_, y_fitted, lambda_);
}

CppWrapper::CppWrapperClass::CppWrapperClass(char* fileName, double lambda)
{
	lambda_ = lambda;
	spline_cubic_smooth_example(fileName, x_, y_, y_fitted, lambda_);
}

List<double>^ CppWrapper::CppWrapperClass::x()
{
	List<double>^ res = gcnew List<double>();
	for (auto i = 0; i < x_.size(); ++i)
	{
		res->Add(x_[i]);
	}
	return res;
}

List<double>^ CppWrapper::CppWrapperClass::y()
{
	List<double>^ res = gcnew List<double>();
	for (auto i = 0; i < y_.size(); ++i)
	{
		res->Add(y_[i]);
	}
	return res;
}

List<double>^ CppWrapper::CppWrapperClass::yRes()
{
	List<double>^ res = gcnew List<double>();
	for(auto i = 0; i < y_fitted.size(); ++i){
		res->Add(y_fitted[i]);
	}
	return res;
}

double^ CppWrapper::CppWrapperClass::getLambda()
{
	return lambda_;
}
