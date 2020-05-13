#include <iostream>
#include <vector>
#include <complex>
#include <iomanip>
#include <fstream>
using namespace std::complex_literals;

std::ostream& operator<<(std::ostream& os, const std::complex<double>& a)
{
	os << ((fabs(a.real()) < 0.00000000001) ? 0.000 : a.real()) << " " << ((fabs(a.imag()) < 0.00000000001) ? 0.000 : a.imag());
	return os;
}

std::complex<double> modulo(const std::vector <std::complex<double>>& vec1, std::vector <std::complex<double>>& vec2, const int l, std::complex<double> zj, int k, const int n)
{

	if (k < 0)
	{
		std::complex<double> temp = vec1[0] + (zj * vec2[0]);
		return temp;
	}
	else if (k == n)
	{
		vec2[n] = 0.;
	}
	else
	{
		vec2[k] = vec1[k + 1] + zj * vec2[k + 1];
	}
	modulo(vec1, vec2, l, zj, --k, n);

}

void findzero(const int n, const int IT_MAX, std::complex<double> z0, std::vector <std::complex<double>> vec1, std::vector <std::complex<double>> vec2, std::vector <std::complex<double>> vec3, std::ofstream& result)
{
	std::complex<double> zj = 0., Rj = 0., Rjprim = 0.;

	for (int l = n; l >= 1; l--)
	{
		zj = z0;
		std::cout << std::setprecision(5) << std::setw(9) << std::fixed << zj << std::endl;
		result << std::setprecision(5) << std::setw(9) << std::fixed << zj << std::endl;

		for (int j = 1; j <= IT_MAX; j++)
		{
			Rj = modulo(vec1, vec2, l, zj, n, n);
			Rjprim = modulo(vec2, vec3, l - 1, zj, n - 1, n - 1);
			zj -= Rj / Rjprim;
			std::cout << std::setprecision(5) << std::setw(9) << std::fixed << zj << std::endl;
			result << std::setprecision(5) << std::setw(9) << std::fixed << zj << std::endl;
		}
		for (int i = 0; i < n + 1; i++)
		{
			vec1[i] = vec2[i];
		}
		std::cout << std::endl;
	}
}

int main()
{
	const int n = 4;
	const int IT_MAX = 20;
	std::complex<double> z0 = 0.;
	std::ofstream output1, output2;
	output1.open("output_part1.txt");
	output2.open("output_part2.txt");

	std::vector <std::complex<double>> a = { 16. + 8.i, -20. + 14.i, 4. - 8.i, -4. + 1.i, 1. };
	std::vector <std::complex<double>> b = { 0., 0., 0., 0., 0. };
	std::vector <std::complex<double>> c = { 0., 0., 0., 0. };

	findzero(n, IT_MAX, z0, a, b, c, output1);

	std::cout << std::endl << std::endl << std::endl << std::endl;

	z0 = -10. - 10.i;
	findzero(n, IT_MAX, z0, a, b, c, output2);

	output1.close();
	output2.close();
}

