#include <iostream>
#include <cmath>
#include <iomanip>
#include <gsl/gsl_matrix.h>

void print_matrix(gsl_matrix* M, const int n)
{
	for (int i = 0; i < n; i++)
	{
		std::cout << i << "   ";
		for (int j = 0; j < n; j++)
		{
			std::cout << std::scientific << std::setprecision(5) << gsl_matrix_get(M, i, j) << "   ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}
void fill_matrix(gsl_matrix* M, const int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			gsl_matrix_set(M, i, j, 1. / (sqrt(2. + abs(i - j))));
		}
	}
}
void fill_matrix_with_matrix(gsl_matrix* M, gsl_matrix* N, const int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			gsl_matrix_set(M, i, j, gsl_matrix_get(N, i, j));
		}
	}
}
void multiply_matrix_vector(gsl_vector* result, gsl_vector* V, gsl_matrix* M, const int n)
{
	gsl_vector_set_zero(result);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			gsl_vector_set(result, i, (gsl_vector_get(result, i) + (gsl_matrix_get(M, i, j) * gsl_vector_get(V, j))));
		}
	}
}
void multiply_matrix_matrix(gsl_matrix* result, gsl_matrix* M, gsl_matrix* N, const int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			double a = 0.;
			for (int k = 0; k < n; k++)
			{
				a += gsl_matrix_get(result, i, j) + (gsl_matrix_get(M, i, k) * gsl_matrix_get(N, k, j));
			}
			gsl_matrix_set(result, i, j, a);
		}
	}
}
double multiply_vector_vector(gsl_vector* V1, gsl_vector* V2, const int n)
{
	double result = 0.;
	for (int i = 0; i < n; i++)
	{
		result += gsl_vector_get(V1, i) * gsl_vector_get(V2, i);
	}
	return result;
}
void tensor_product(gsl_matrix* M, gsl_vector* lambda, gsl_vector* x, int k, const int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			gsl_matrix_set(M, i, j, gsl_matrix_get(M, i, j) - gsl_vector_get(lambda, k) * gsl_vector_get(x, i) * gsl_vector_get(x, j));
		}
	}
}
void print_eigen_approx(gsl_matrix* p, const int IT_MAX, const int n)
{
	for (int i = 0; i < IT_MAX; i++)
	{
		std::cout << i << "   ";
		for (int j = 0; j < n; j++)
		{
			std::cout << std::scientific << std::setprecision(10) << gsl_matrix_get(p, i, j) << "   ";
		}
		std::cout << "\n";
	}
}

int main()
{
	const int n = 7;
	const int K = 7;
	const int IT_MAX = 20;
	
	gsl_matrix* A = gsl_matrix_calloc(n, n);
	gsl_matrix* W = gsl_matrix_calloc(n, n);
	gsl_matrix* X = gsl_matrix_calloc(n, n);
	gsl_matrix* p = gsl_matrix_calloc(IT_MAX, IT_MAX);

	gsl_matrix* temp = gsl_matrix_calloc(n, n);
	gsl_matrix* temp2 = gsl_matrix_calloc(n, n);
	gsl_matrix* X_t = gsl_matrix_calloc(n, n);

	gsl_vector* x_v = gsl_vector_calloc(n);
	gsl_vector* x_v2 = gsl_vector_calloc(n);
	gsl_vector* lambda = gsl_vector_calloc(n);

	fill_matrix(A, n);
	fill_matrix_with_matrix(W, A, n);

	for (int k = 0; k < n; k++)
	{
		gsl_vector_set_all(x_v, 1.);
		for (int i = 0; i < IT_MAX; i++)
		{
			multiply_matrix_vector(x_v2, x_v, W, n);
			gsl_vector_set(lambda, k, multiply_vector_vector(x_v2, x_v, n) / multiply_vector_vector(x_v, x_v, n));
			gsl_matrix_set(p, i, k, gsl_vector_get(lambda, k));
			for (int j = 0; j < n; j++)
			{
				gsl_vector_set(x_v, j, gsl_vector_get(x_v2, j) / sqrt(multiply_vector_vector(x_v2, x_v2, n)));
			}
		}
		tensor_product(W, lambda, x_v, k, n);
		for (int i = 0; i < n; i++)
		{
			gsl_matrix_set(X, i, k, gsl_vector_get(x_v, i));
		}
	}
	fill_matrix_with_matrix(X_t, X, n);
	gsl_matrix_transpose(X);
	multiply_matrix_matrix(temp2, A, X_t, n);
	multiply_matrix_matrix(temp, X, temp2, n);

	print_matrix(temp, n);
	print_eigen_approx(p, IT_MAX, n);

	gsl_matrix_free(A);
	gsl_matrix_free(W);
	gsl_matrix_free(X);
	gsl_matrix_free(p);
	gsl_matrix_free(temp);
	gsl_matrix_free(temp2);
	gsl_matrix_free(X_t);

	gsl_vector_free(x_v);
	gsl_vector_free(x_v2);
	gsl_vector_free(lambda);
}