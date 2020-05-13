#include <stdio.h>
#include <math.h>
#include </usr/include/gsl/gsl_math.h>
#include </usr/include/gsl/gsl_linalg.h>

int main() 
{
	FILE *file;
	int signum,n=4,delta=2;
	float det_A=1,max=-1;
	
	gsl_matrix *A = gsl_matrix_calloc(n, n);
	gsl_matrix *A_copy = gsl_matrix_calloc(n, n);
	gsl_matrix *A_inv = gsl_matrix_calloc(n, n);
	gsl_matrix *C = gsl_matrix_calloc(n, n);
	gsl_vector *b = gsl_vector_calloc(n);
	gsl_vector *x1 = gsl_vector_calloc(n);
	gsl_vector *x2 = gsl_vector_calloc(n);
	gsl_vector *x3 = gsl_vector_calloc(n);
	gsl_vector *x4 = gsl_vector_calloc(n);
	gsl_permutation *p = gsl_permutation_alloc(n);
	
	
	file = fopen("wynik.txt", "w+");
	printf("A\n");
	fprintf(file, "A\n");
	
	for(int i = 0; i < n; i++) 
	{
		for(int j = 0; j < n; j++) 
		{
			gsl_matrix_set(A, i, j, 1.0/(i+j+delta));
			gsl_matrix_set(A_copy, i, j, gsl_matrix_get(A, i, j));
			fprintf(file, "%15f", gsl_matrix_get(A, i, j));
			printf("%15f", gsl_matrix_get(A, i, j));
		}
		printf("\n");
		fprintf(file, "\n");
	}
	
	printf("\n");
	fprintf(file, "\n");
	
	gsl_linalg_LU_decomp(A, p, &signum);
	printf("\nA after linalg_LU_decomp\n");
	
	for(int i = 0; i < n; i++) 
	{
		for(int j = 0; j < n; j++) 
		{
			printf("%15f", gsl_matrix_get(A, i, j));
		}
		printf("\n");
	}
	

	fprintf(file, "\nDiagonal\n");
	printf("\nDiagonal: ");
	for(int i = 0; i < n; i++) 
	{
		
				fprintf(file, "%f ", gsl_matrix_get(A, i, i));
				printf("%f ",gsl_matrix_get(A, i, i));
				det_A *= gsl_matrix_get(A, i, i);
	}
	det_A*=signum;
	printf("\nDet(A) = %g\n", det_A);
	fprintf(file, "\n\nDet(A) = %g\n", det_A);
	
	gsl_vector_set_zero(b);
	gsl_vector_set(b, 0, 1);
	gsl_linalg_LU_solve(A ,p, b, x1);
	
	gsl_vector_set_zero(b);
	gsl_vector_set(b, 1, 1);
	gsl_linalg_LU_solve(A ,p, b, x2);
	
	gsl_vector_set_zero(b);
	gsl_vector_set(b, 2, 1);
	gsl_linalg_LU_solve(A ,p, b, x3);
	
	gsl_vector_set_zero(b);
	gsl_vector_set(b, 3, 1);
	gsl_linalg_LU_solve(A ,p, b, x4);
	printf("\nA^-1:\n");
	fprintf(file, "\nA^-1\n");
	for(int i = 0; i < n; i++) 
	{
		printf("%15f", gsl_vector_get(x1, i));
		fprintf(file, "%15f", gsl_vector_get(x1, i));
		
		printf("%15f", gsl_vector_get(x2, i));
		fprintf(file, "%15f", gsl_vector_get(x2, i));
		
		printf("%15f", gsl_vector_get(x3, i));
		fprintf(file, "%15f", gsl_vector_get(x3, i));
		
		printf("%15f\n", gsl_vector_get(x4, i));
		fprintf(file, "%15f\n", gsl_vector_get(x4, i));
	}
	
	for(int i = 0; i < n; i++) 
	{
		gsl_matrix_set(A_inv, 0, i, gsl_vector_get(x1, i));
		gsl_matrix_set(A_inv, 1, i, gsl_vector_get(x2, i));
		gsl_matrix_set(A_inv, 2, i, gsl_vector_get(x3, i));
		gsl_matrix_set(A_inv, 3, i, gsl_vector_get(x4, i));
	}
	
	
	fprintf(file, "\nA * A^-1:\n");
	printf("\nA * A^-1:\n");
	
	
	for(int i = 0; i < n; i++) 
	{
		for(int j = 0; j < n; j++) 
		{
			for(int k = 0; k < n; k++) 
			{
				gsl_matrix_set(C, i, j, gsl_matrix_get(C, i, j) + gsl_matrix_get(A_copy, i, k) * gsl_matrix_get(A_inv, k, j));
			}
			fprintf(file, "%15g", gsl_matrix_get(C, i, j));
			printf("%15g", gsl_matrix_get(C, i, j));
		}
		printf("\n");
		fprintf(file, "\n");
	}
	
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(gsl_matrix_get(A, i, j)>0)
			{
				if(gsl_matrix_get(A, i, j)>max);
				max=gsl_matrix_get(A, i, j);
			}
			else
			{
				if(max>gsl_matrix_get(A, i, j));
				max=-gsl_matrix_get(A, i, j);
			}

			
			
		}
	}






	gsl_matrix_free(A);
	gsl_matrix_free(A_inv);
	gsl_vector_free(b);
	gsl_matrix_free(C);
	gsl_vector_free(x1);
	gsl_vector_free(x2);
	gsl_vector_free(x3);
	gsl_vector_free(x4);
	gsl_permutation_free(p);
	return 0;
}

