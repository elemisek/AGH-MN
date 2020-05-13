// sklejki.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include "gsl/gsl_linalg.h"


const unsigned int N = 14;
const double xMax = 5.;
const double xMin = -5;
const double h = (xMax - xMin) / (N - 1.);
const double x0 = -5.;
const double dx = 0.01;



enum class typeOfFunction
{
	cosinus,
	rational
};

double fun(double x, typeOfFunction tof)
{
	if (tof == typeOfFunction::cosinus)
	{
		return std::cos(2 * x);
	}

	if (tof == typeOfFunction::rational)
	{
		return 1 / (1 + x * x);
	}
}

double xi(int i)
{
	return x0 + i * h;
}

double xi2(int i)
{
	return x0 + (i - 1) * h;
}

double phi(double x, unsigned int i)
{
	if (x >= xi2(i - 2) && x < xi2(i - 1))
		return (pow(x - xi2(i - 2), 3)) / (pow(h, 3));

	if (x >= xi2(i - 1) && x < (xi2(i)))
		return (pow(h, 3) + 3 * pow(h, 2) * (x - xi2(i - 1)) + 3 * h * pow((x - xi2(i - 1)), 2) - 3 * pow((x - xi2(i - 1)), 3)) / pow(h, 3);

	if (x >= xi2(i) && x < (xi2(i + 1)))
		return (pow(h, 3) + 3 * pow(h, 2) * (xi2(i + 1) - x) + 3 * h * pow((xi2(i + 1) - x), 2) - 3 * pow((xi2(i + 1) - x), 3)) / pow(h, 3);

	if (x >= xi2(i + 1) && x < (xi2(i + 2)))
		return (pow(xi2(i + 2) - x, 3)) / (pow(h, 3));

	return 0;
}

void fill_A(gsl_matrix* A)
{
	for (size_t i = 0; i < N - 1; i++)
	{
		gsl_matrix_set(A, i, i, 4);
		gsl_matrix_set(A, i, i + 1, 1);
		gsl_matrix_set(A, i + 1, i, 1);
	}

	gsl_matrix_set(A, N - 1, N - 1, 4);

	gsl_matrix_set(A, 0, 1, 2);

	gsl_matrix_set(A, N - 1, N - 2, 2);
}

void fill_B(gsl_vector* B, typeOfFunction tof)
{
	for (size_t i = 1; i < N - 1; i++)
	{
		gsl_vector_set(B, i, fun(xi(i), tof));
	}

	gsl_vector_set(B, 0, fun(x0, tof) + h / 3 * (fun(x0 + dx, tof) - fun(x0 - dx, tof)) / (2 * dx));

	gsl_vector_set(B, N - 1, fun(xi(N - 1), tof) - h / 3 * (fun(xi(N - 1) + dx, tof) - fun(xi(N - 1) - dx, tof)) / (2 * dx));
}

void print_A(gsl_matrix* A)
{
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < N; j++)
			std::cout << gsl_matrix_get(A, i, j) << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void print_B(gsl_vector* B, const int n)
{
	for (size_t i = 0; i < n; i++)
		std::cout << gsl_vector_get(B, i) << " ";
	std::cout << std::endl;
}

void BtoBplus2(gsl_vector* B, gsl_vector* Bplus2, typeOfFunction tof)
{
	for (size_t i = 0; i < N; i++)
	{
		gsl_vector_set(Bplus2, i + 1, gsl_vector_get(B, i));
	}
	gsl_vector_set(Bplus2, 0, gsl_vector_get(Bplus2, 2) - (h / 3.0) * (fun(x0 + dx, tof) - fun(x0 - dx, tof)) / (2 * dx)); //we wskazówkach jest na to inny wzór, ale brakuje mu pochodnej
	gsl_vector_set(Bplus2, N + 1, gsl_vector_get(Bplus2, N - 1) + (h / 3.0) * (fun(xi(N - 1) + dx, tof) - fun(xi(N - 1) - dx, tof)) / (2 * dx)); //jw.
}

void interpolatio(gsl_vector* Bplus2, std::ofstream& file, typeOfFunction tof)
{
	double s;
	for (double x = xMin; x <= xMax; x += 0.01)
	{
		s = 0.0;
		for (size_t i = 0; i < N + 2; i++)
		{
			s += gsl_vector_get(Bplus2, i) * phi(x, i);
		}
		file << x << "   " << s << "   " << fun(x, tof) <<std::endl;
	}
}


int main()
{
	gsl_matrix* A = gsl_matrix_calloc(N, N);
	gsl_vector* B = gsl_vector_calloc(N);
	gsl_vector* Bplus2 = gsl_vector_calloc(N + 2);

	std::ofstream file;
	file.open("Wyniki_cos_14.txt");
	std::ofstream file2;
	file2.open("Wyniki_wezly_cos_14.txt");

	fill_A(A);
	fill_B(B, typeOfFunction::cosinus);

	print_A(A);
	print_B(B, N);

	gsl_linalg_HH_svx(A, B);
	print_B(B, N);

	BtoBplus2(B, Bplus2, typeOfFunction::cosinus);
	print_B(Bplus2, N + 2);

	if (file.good())
	{
		interpolatio(Bplus2, file, typeOfFunction::cosinus);
	}
	if (file2.good())
	{
		for (double i = xMin; i <= xMax; i+=h)
		{
			file2 << i << "  " << fun(i, typeOfFunction::cosinus) << std::endl;
		}
	}

	file.close();
	file2.close();
	gsl_matrix_free(A);
	gsl_vector_free(B);

	return 0;
}
