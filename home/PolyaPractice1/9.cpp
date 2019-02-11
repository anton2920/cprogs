#include <math.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define size_XY 100

void Read(int MX[size_XY][size_XY], int M, int N)
{
	printf_s("Вводите матрицу: \n");

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			scanf_s("%d", &MX[i][j]);
		}
		printf_s("\n");
	}
}

void Alg(int MX[size_XY][size_XY], int M, int N, int &x, int &z)
{
	for (int i = 1; i < M; i++)
	{
		for (int j = i; j > 0; j--)
		{
			for (z = 0; z < N; z++)
			{
				if (MX[j][z] < MX[j - 1][z])
				{
					x = MX[j][z];
					MX[j][z] = MX[j - 1][z];
					MX[j - 1][z] = x;
				}
			}
		}
	}
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	int  M, N, MX[size_XY][size_XY], arr[size_XY], x, z;

	//printf_s("Дана целочисленная матрица размера ");//Вывести текст задания

	printf_s("Введите размерность матрицы(Max 100x100): \n");
	do {
		printf_s("M="); scanf_s("%d", &M);
	} while (M < 0);
	do {
		printf_s("N="); scanf_s("%d", &N);
	} while (N < 0);

	Read(MX, M, N);
	Alg(MX, M, N, x, z);

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf_s("%d ", MX[i][j]);
		}
		printf_s("\n");
	}

	system("pause");
	return 0;
}