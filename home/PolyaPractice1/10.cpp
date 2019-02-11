#include <math.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define size_XY 100

void Read(int MX[size_XY][size_XY], int M)
{
	printf_s("¬ведите матрицу:");

	for ( int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			printf_s("MX[%d][%d]=", i, j);
			scanf_s("%d", &MX[i][j]);
		}
	}
}

void Alg(int MX[size_XY][size_XY], int M, int &x1, int &x2, int &z, double A[size_XY * 2])
{
	int i = 0;
	int j = 0;

	for (z = 0; z < M; z++)
	{
		do
		{
			x1 += MX[i + z][j];
			x2 += MX[j][i + z];
			i++;
			j++;
		} while (i < (M - z) || j < (M - z));
		A[M - z] = double(x1) / double(M - z);
		A[M + z] = double(x2) / double(M - z);
		x1 = 0;
		x2 = 0;
		i = 0;
		j = 0;
	}
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	double A[size_XY * 2];
	int MX[size_XY][size_XY], x1, x2;
	int i, z, M;
	x1 = 0;
	x2 = 0;

	printf_s("¬ведите размерность матрицы(Max 100x100): \n");
	do
	{
		printf_s("M="); scanf_s("%d", &M);
	} while (M < 0);

	Read(MX, M);
	Alg(MX, M, x1, x2, z, A);

	for (i = 1; i < M * 2; i++)
	{
		printf_s("%lf\n", A[i]);
	}

	system("pause");
	return 0;
}