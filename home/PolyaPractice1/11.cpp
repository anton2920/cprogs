#include <math.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define size_XY 100

void zeroing(int MX[size_XY][size_XY], int M)
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			scanf_s("%d", &MX[i][j]);
			if ((i + j < (M - 1)) && (i < j)) MX[i][j] = 0;

		}
	}
}

void output(int MX[size_XY][size_XY], int M)
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			printf_s("%d ", MX[i][j]);
		}
		printf_s("\n");
	}

}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	int  M, MX[size_XY][size_XY], x, z, i, j;

	do
	{
		printf_s("¬ведите размерность матрицы(Max 100x100): \n");

		printf_s("M="); scanf_s("%d", &M);
	} while ((M > 100) || (M < 0));
	printf_s("¬водите матрицу: \n");

	zeroing(MX, M);
	output(MX, M);

	system("pause");
	return 0;
}