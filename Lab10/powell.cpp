#include <iostream>
#include <cmath>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <fstream>
#include <tuple>
#include <utility>
#include <map>
#include <string>

const double h = 0.01;
const double e = 1e-8;

double fun1(double x)
{
	return std::log(pow(x, 5) + 3 * pow(x, 2) + x + 9);
}

double fun2(double x)
{
	return pow(x, 6);
}

double DiffQuot(std::function<double(double)> f, unsigned order, double x1, double x2, double x3 = 0)
{
	switch (order)
	{
	case 1:
		return (f(x2) - f(x1)) / (x2 - x1);
	case 2:
		return (DiffQuot(f, 1, x2, x3) - DiffQuot(f, 1, x1, x2)) / (x3 - x1);
	}
}

double MinApproximation(std::function<double(double)> f, double x1, double x2, double x3)
{
	return ((x2 + x1) / 2) - ((DiffQuot(f, 1, x1, x2)) / (2 * (DiffQuot(f, 2, x1, x2, x3))));
}

template<typename... Ts>
void Print2File(std::ofstream& file, std::tuple<Ts...> const& theTuple)
{
	std::apply
	(
		[&file](Ts const&... tupleArgs)
		{
			((file << std::setw(16) << tupleArgs), ...);
			file << std::endl;
		}, theTuple
	);
}

void Function2File()
{
	std::ofstream file("function.txt");
	for (double x = -1.5; x <= 1.; x += 0.01)
		Print2File(file, std::make_tuple(x, fun1(x)));
}

double nearest(double x1, double x2, double x3, double xm)
{
	if (fabs(xm - x1) < fabs(xm - x3))
		if (fabs(xm - x1) < fabs(xm - x2))
			return x1;
		else
			return x2;
	if (fabs(xm - x2) < fabs(xm - x3))
		return x2;
	return x3;
}

double& furthest(double& x1, double& x2, double& x3, double xm)
{
	if (fabs(xm - x1) > fabs(xm - x3))
		if (fabs(xm - x1) > fabs(xm - x2))
			return x1;
		else
			return x2;
	if (fabs(xm - x2) > fabs(xm - x3))
		return x2;
	return x3;
}

void PowellInterpolation(std::function<double(double)> f, double xMin, size_t iter, size_t result_number)
{
	std::ofstream file("result" + std::to_string(result_number) + ".txt");
	double x1 = xMin, x2 = xMin + h, x3 = xMin + 2 * h, xm = 0;

	if (f(x2) >= f(x1) || f(x3) >= f(x2) || f(x3) >= f(x1))
	{
		x2 = xMin - h;
		x3 = xMin - 2 * h;
	}

	for (size_t i = 0; i < iter; i++)
	{
		xm = MinApproximation(f, x1, x2, x3);
		Print2File(file, std::make_tuple(i + 1, x1, x2, x3, xm, DiffQuot(f, 1, x1, x2), DiffQuot(f, 2, x1, x2, x3)));
		if (fabs(xm - nearest(x1, x2, x3, xm)) < e)
		{
			file << std::endl;
			return;
		}
		std::swap(xm, furthest(x1, x2, x3, xm));
	}
	file << std::endl;
}


int main()
{
	PowellInterpolation(fun1, -0.5, 10, 1);
	PowellInterpolation(fun1, -0.9, 10, 2);
	PowellInterpolation(fun2, 1.5, 100, 3);

	Function2File();
}
