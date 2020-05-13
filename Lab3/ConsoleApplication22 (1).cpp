#include <iostream>
#include <cmath>
#include <fstream>

void arrcpy(double *t1, double *t2,const int N)
{
	for (int i = 0; i < N; i++)
	{
		t1[i] = t2[i];
	}
}

void printarr(double *t1,const int N)
{
	for (int i = 0; i < N; i++)
	{
		std::cout << t1[i] << std::endl;
	}
}

void fprintarr(double *t1, int N, double h,const char* str)
{
	std::fstream file;
	file.open(str, std::ios::out);
	for (int i = 0; i < N; i++)
	{
		file << i * h << " " << t1[i] << std::endl;
	}
}


int main()
{

	const int N = 1000;
	int iter = 1000;
	// do wpisania do podpunktu a, b i c
	double omega = 0.8; //=0.8; =0.8
	double beta = 0; //=0.4; =0.4
	double F0 = 0; //=0; =0.1

	const char * file = "result.txt";
	double h =0.02,xs[N], xn[N], b[N];
	double d0[N],d1[N],d2[N];


	double a1 = 1;
	double a2 = (h*h) - 2 - beta * h;
	double a3 = 1 + beta * h;
	d1[0]=d2[0]= 0;
	d0[0]=b[0] = 1;
	d0[1] = 1;
	d1[1] = -1;
	d2[1] = 0;
	b[1] = 0;
	for (int i = 2; i < N - 1; i++)
	{
		d0[i] = a3;
		d1[i] = a2;
		d2[i] = a1;
		b[i] = h*h*F0*sin(omega*h*i);
	}
	for (int i = 0; i < N; i++)
	{
		xs[i] = 0;
		xn[i] = 0;
	}
	for(int j=0; j<iter; j++)
	{
		xn[0] = b[0]/d0[0];
		xn[1] = (b[1] - d1[1] * xs[0]) / d0[1];
			for(int i=2; i<N-1; i++)
			{
				xn[i] = (b[i]-d1[i]*xs[i-1]-d2[i]*xs[i-2])/d0[i];
			}
			for (int i = 0; i < N; i++)
			{
				xs[i]=xn[i];
			}
	}

	
	printarr(xn, N);
	fprintarr(xn, N, h, file);

	return 0;
}
