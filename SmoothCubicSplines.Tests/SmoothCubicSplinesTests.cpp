#include "stdafx.h"
#include "CppUnitTest.h"
#include "smooth_cubic_spline.hpp"

#define TMPr(method_name, priority) BEGIN_TEST_METHOD_ATTRIBUTE(method_name) TEST_PRIORITY(priority) END_TEST_METHOD_ATTRIBUTE() TEST_METHOD(method_name)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SmoothCubicSplinesTests
{
	TEST_CLASS(TestTest)
	{
	public:

		TMPr(Simple1eq1, 0) // to check if test work correct
		{
			Assert::AreEqual(1, 1);
		}
	};

	TEST_CLASS(SmoothCubicSplineUtilsTest)
	{
	public:

		TMPr(InitializationSolveCheck, 1)
		{
			smooth_cubic_spline_utils<double> scsu;

			try
			{
				scsu.Solve(5);
				Assert::IsTrue(false);
			}
			catch (std::exception& ex)
			{
				auto desc = ex.what();
				Assert::AreEqual("Data is not load./Not enough points.", desc);
			}
		}

		TMPr(InitializationFittedValuesCheck, 1)
		{
			smooth_cubic_spline_utils<double> scsu;

			std::vector<double> y_fitted = scsu.get_fitted_values();

			Assert::AreEqual((size_t)0, y_fitted.size());
		}

		TMPr(LoadCheck, 1)
		{
			smooth_cubic_spline_utils<double> scsu;
			std::vector<double> x{ 3.4, 3.5, 3.6, 3.7, 3.8, 3.9 }; // sorted
			std::vector<double> x_bad{ 3.4, 3.5, 3.6, 3.7, 3.8 }; // sorted, but just 5 points
			std::vector<double> x_bad2{ 3.4, 3.5, 3.6, 3.7, 3.5, 3.9 }; // not sorted
			std::vector<double> y(6, 1.0);
			std::vector<double> y_bad(5, 6.7);

			try
			{
				scsu.load(x, y); // correct data
				Assert::IsTrue(true);
				scsu.load(x, y_bad); // x.size() != y_bad.size()
				Assert::IsTrue(false);
			}
			catch (std::exception& ex)
			{
				auto desc = ex.what();
				Assert::AreEqual("Wrong input data.", desc);
			}

			try
			{
				scsu.load(x_bad, y_bad); // points number < 6
				Assert::IsTrue(false);
			}
			catch (std::exception& ex)
			{
				auto desc = ex.what();
				Assert::AreEqual("Not enough points.", desc);
			}

			try
			{
				scsu.load(x_bad2, y); // not sorted
				Assert::IsTrue(false);
			}
			catch (std::exception& ex)
			{
				auto desc = ex.what();
				Assert::AreEqual("Incorrect data: x values must be sorted and distinct.", desc);
			}
		}

		TMPr(SolveCheck, 2)
		{
			smooth_cubic_spline_utils<double> scsu;
			
			std::vector<double> x{ 3.4, 3.5, 3.6, 3.7, 3.8, 3.9 }; // sorted
			std::vector<double> y(6, 1.0);
			scsu.load(x, y);
			Assert::IsTrue(true);

			scsu.Solve(5);
			Assert::IsTrue(true);
		}

		TMPr(FittedValuesCheck, 2)
		{
			smooth_cubic_spline_utils<double> scsu;
			std::vector<double> x{ 3.4, 3.5, 3.6, 3.7, 3.8, 3.9 }; // sorted
			std::vector<double> y(6, 1.0);
			scsu.load(x, y);
			Assert::IsTrue(true);

			std::vector<double> y_fitted = scsu.get_fitted_values();

			Assert::AreEqual((size_t)0, y_fitted.size());

			scsu.Solve(0.5);
			Assert::IsTrue(true);

			y_fitted = scsu.get_fitted_values();

			Assert::AreEqual((size_t)6, y_fitted.size());

			for (size_t i = 0; i < 6; i++)
				Assert::AreEqual(1.0, y_fitted.at(i)); // line, can check
		}

		TMPr(ValueAtCheck, 2)
		{
			smooth_cubic_spline_utils<double> scsu;
			std::vector<double> x{ 3.4, 3.5, 3.6, 3.7, 3.8, 3.9 }; // sorted
			std::vector<double> y(6, 1.0);
			scsu.load(x, y);
			Assert::IsTrue(true);
			scsu.Solve(1);
			Assert::IsTrue(true);

			double v = scsu.value_at(5);

			Assert::AreEqual(1., v);
		}

	};

	TEST_CLASS(SmoothCubicSplineTests)
	{
	public:

		TMPr(InitializationXCheck, 1)
		{
			smooth_cubic_spline<double> scs;

			std::vector<double> x = scs.get_x();

			Assert::AreEqual((size_t)0, x.size());
		}

		TMPr(InitializationValuesAtCheck, 1)
		{
			smooth_cubic_spline<double> scs;
			try
			{
				double y5 = scs.value_at(5);
			}
			catch (std::exception& ex)
			{
				auto desc = ex.what();
				Assert::AreEqual("Spline is not calculated.", desc);
			}
		}

		TMPr(InitializationCalcCheck, 1)
		{
			smooth_cubic_spline<double> scs;

			try
			{
				scs.calculate();
				Assert::IsTrue(false);
			}
			catch (std::exception& ex)
			{
				auto desc = ex.what();
				Assert::AreEqual("Spline is not initialised.", desc);
			}
		}

		TMPr(InitializationFittedValuesCheck, 1)
		{
			smooth_cubic_spline<double> scs;

			std::vector<double> y_fitted = scs.fitted_values();

			Assert::AreEqual((size_t)0, y_fitted.size());
		}

		TMPr(InitializationStartLambda, 1)
		{
			const double start_lambda = 0.9;
			smooth_cubic_spline<double> scs;
			
			double l = scs.get_lambda();

			Assert::AreEqual(start_lambda, l);
		}

		TMPr(InitializationValueAtCheck, 1)
		{
			smooth_cubic_spline<double> scs;

			try
			{
				double y5 = scs.value_at(5);
				Assert::IsTrue(false);
			}
			catch (std::exception& ex)
			{
				auto desc = ex.what();
				Assert::AreEqual("Spline is not calculated.", desc);
			}
		}

		TMPr(LambdaSetting, 2)
		{
			const double real_lambda = 0.1234;
			smooth_cubic_spline<double> scs;
			scs.set_lambda(real_lambda);
			Assert::IsTrue(true);

			double l = scs.get_lambda();

			Assert::AreEqual(real_lambda, l);
		}

		TMPr(LambdaBadSetting, 2)
		{
			const double lambdaMin = 1e-7;
			const double lambdaMax = 1 - 1e-7;
			const double bad_lambdaMin = -7;
			const double bad_lambdaMax = 7;
			smooth_cubic_spline<double> scs;

			scs.set_lambda(bad_lambdaMin);
			Assert::IsTrue(true);
			double lMin = scs.get_lambda();
			Assert::AreEqual(lambdaMin, lMin);

			scs.set_lambda(bad_lambdaMax);
			Assert::IsTrue(true);
			double lMax = scs.get_lambda();
			Assert::AreEqual(lambdaMax, lMax);
		}
		
		TMPr(LoadCheck, 2)
		{
			smooth_cubic_spline<double> scs;
			std::vector<double> x{ 3.4, 3.5, 3.6, 3.7, 3.8, 3.9 }; // sorted
			std::vector<double> x_bad{ 3.4, 3.5, 3.6, 3.7, 3.8 }; // sorted, but just 5 points
			std::vector<double> x_bad2{ 3.4, 3.5, 3.6, 3.7, 3.5, 3.9 }; // not sorted
			std::vector<double> y(6, 1.0);
			std::vector<double> y_bad(5, 6.7);

			try
			{
				scs.load(x, y); // correct data
				Assert::IsTrue(true);
				scs.load(x, y_bad); // x.size() != y_bad.size()
				Assert::IsTrue(false);
			}
			catch (std::exception& ex)
			{
				auto desc = ex.what();
				Assert::AreEqual("Wrong input data.", desc);
			}

			try
			{
				scs.load(x_bad, y_bad); // points number < 6
				Assert::IsTrue(false);
			}
			catch (std::exception& ex)
			{
				auto desc = ex.what();
				Assert::AreEqual("Not enough points.", desc);
			}

			try
			{
				scs.load(x_bad2, y); // not sorted
				Assert::IsTrue(false);
			}
			catch (std::exception& ex)
			{
				auto desc = ex.what();
				Assert::AreEqual("Incorrect data: x values must be sorted and distinct.", desc);
			}
		}

		TMPr(XCheck, 2)
		{
			smooth_cubic_spline<double> scs;
			std::vector<double> x{ 3.4, 3.5, 3.6, 3.7, 3.8, 3.9 }; // sorted
			std::vector<double> y(6, 1.0);
			scs.load(x, y); // correct data
			Assert::IsTrue(true);

			std::vector<double> x_res = scs.get_x();

			Assert::AreEqual((size_t)6, x_res.size());
			for (size_t i = 0; i < 6; i++)
				Assert::AreEqual(x.at(i), x_res.at(i)); // line, can check
		}

		TMPr(ValuesAtCheck, 2)
		{
			smooth_cubic_spline<double> scs;
			std::vector<double> x{ 3.4, 3.5, 3.6, 3.7, 3.8, 3.9 }; // sorted
			std::vector<double> y(6, 1.0);
			double y5;
			scs.load(x, y); // correct data
			Assert::IsTrue(true);

			try
			{
				y5 = scs.value_at(5);
				Assert::IsTrue(false);
			}
			catch (std::exception& ex)
			{
				auto desc = ex.what();
				Assert::AreEqual("Spline is not calculated.", desc);
			}

			scs.calculate();
			Assert::IsTrue(true);

			y5 = scs.value_at(5);
			
			Assert::AreEqual(1., y5); // line, can check
		}

		TMPr(FittedCheck, 2)
		{
			smooth_cubic_spline<double> scs;
			std::vector<double> x{ 3.4, 3.5, 3.6, 3.7, 3.8, 3.9 }; // sorted
			std::vector<double> y(6, 1.0);
			scs.load(x, y); // correct data
			Assert::IsTrue(true);

			std::vector<double> y_res = scs.fitted_values();

			Assert::AreEqual((size_t)0, y_res.size());

			scs.calculate();
			Assert::IsTrue(true);

			y_res = scs.fitted_values();

			Assert::AreEqual((size_t)6, y_res.size());
			for (size_t i = 0; i < 6; i++)
				Assert::AreEqual(1., y_res.at(i)); // line, can check
		}

		TMPr(CalcCheck, 2)
		{
			smooth_cubic_spline<double> scs;
			std::vector<double> x{ 3.4, 3.5, 3.6, 3.7, 3.8, 3.9 }; // sorted
			std::vector<double> y(6, 1.0);
			scs.load(x, y); // correct data
			Assert::IsTrue(true);

			scs.calculate();
			Assert::IsTrue(true);
		}

		TMPr(SplineVecCheck, 3)
		{
			smooth_cubic_spline<double> scs;
			std::vector<double> x{ 3.4, 3.5, 3.6, 3.7, 3.8, 3.9 }; // sorted
			std::vector<double> y(6, 1.0);

			std::vector<double> y_res = scs.spline_vec(x, y); // correct data

			Assert::AreEqual((size_t)6, y_res.size());
			for (size_t i = 0; i < 6; i++)
				Assert::AreEqual(1., y_res.at(i)); // line, can check
		}

	};

	TEST_CLASS(SmoothCubicSplineOtherTests)
	{
	public:

		TMPr(ReadFileCheck, 1)
		{
			std::vector<double> x;
			std::vector<double> y;

			try
			{
				read_file("BlaBlaBla.csv", x, y);
			}
			catch (std::exception& ex)
			{
				Assert::AreEqual("Can't open file.", ex.what());
			}

			read_file("input/testInput.txt", x, y);

			Assert::AreEqual((size_t)6, x.size());
			Assert::AreEqual((size_t)6, y.size());

			Assert::AreEqual(-3., x.at(0));
			Assert::AreEqual(4., y.at(0));
		}
		
		TMPr(ReadPrepareDataCheck, 2)
		{
			std::vector<double> x;
			std::vector<double> y;

			try
			{
				read_and_prepare_data("BlaBlaBla.csv", x, y);
			}
			catch (std::exception& ex)
			{
				Assert::AreEqual("Can't open file.", ex.what());
			}

			read_and_prepare_data("input/testInput.txt", x, y);

			Assert::AreEqual((size_t)6, x.size());
			Assert::AreEqual((size_t)6, y.size());

			Assert::AreEqual(-3., x.at(0));
			Assert::AreEqual(4., y.at(0));
		}

		TMPr(deltaCheck, 1) // simple check
		{
			std::vector<double> y{ 1.2 };
			std::vector<double> y_data;

			try
			{
				delta(y, y_data); // y.size() != y_data.size()
				Assert::IsTrue(false);
			}
			catch (std::exception& ex)
			{
				auto desc = ex.what();
				Assert::AreEqual("Wrong input data.", desc);
			}

			try
			{
				y.pop_back();
				delta(y, y_data); // points number < 1
				Assert::IsTrue(false);
			}
			catch (std::exception& ex)
			{
				auto desc = ex.what();
				Assert::AreEqual("Not enough points.", desc);
			}

			y.push_back(3.4);
			y_data.push_back(5.4);

			double d = delta(y, y_data);

			Assert::IsTrue(abs(2. - d) < 1e-7);
		}

		TMPr(EstimateRigidityCheck, 1) // simple check, just || line to Ox due to hard checking
		{
			std::vector<double> y{ 1.2 };

			try
			{
				estimate_rigidity(y); // y.size() < 2
				Assert::IsTrue(false);
			}
			catch (std::exception& ex)
			{
				auto desc = ex.what();
				Assert::AreEqual("Not enough points.", desc);
			}

			y.push_back(1.2);

			double l = estimate_rigidity(y);

			Assert::AreEqual(1., l);
		}

		TMPr(ExampleCheck, 3)
		{
			std::vector<double> x;
			std::vector<double> y;
			std::vector<double> y_fitted;

			try
			{
				spline_cubic_smooth_example<double>("BlaBlaBla.csv", x, y, y_fitted, 1.);
			}
			catch (std::exception& ex)
			{
				Assert::AreEqual("Can't open file.", ex.what());
			}

			spline_cubic_smooth_example<double>("input/testInput.txt", x, y, y_fitted, 1.);

			Assert::AreEqual((size_t)6, x.size());
			Assert::AreEqual((size_t)6, y.size());
			Assert::AreEqual((size_t)6, y_fitted.size());

			Assert::AreEqual(-3., x.at(0));
			Assert::AreEqual(4., y.at(0));
			Assert::IsTrue(abs(4. - y_fitted.at(0)) < 1e-5);
		}

	};
}