#include <math.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define size_XY 100

void read(int a[size_XY][size_XY], int M, int N)
{
	printf_s("Вводите матрицу: \n");

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			scanf_s("%d", &a[i][j]);
		}
		printf_s("\n");
	}
}

void Arr(int a[size_XY][size_XY], int M, int N, int &max_i, int &max_j, int &x)
{
	int max = INT_MIN;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (a[i][j] > max)
			{
				max = a[i][j]; max_i = i; max_j = j;
			}
		}
		for (int s = 0; s < N; s++)
		{
			if (max < a[s][max_j]) x++;
		}
		max = INT_MIN;
		if ((x + 1) % N == 0) { x = 1; break; }
	}
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	int M, N, max_i, max_j, MX[size_XY][size_XY], x = 0;

	//printf_s("Дана целочисленная матрица размера ");//Вывести текст задания

	do
	{
		printf_s("Введите размерность матрицы(Max 100x100): \n");
		printf_s("M="); scanf_s("%d", &M);
	} while ((M > 100) || (M <= 0));
	do
	{
		printf_s("N="); scanf_s("%d", &N);
	} while ((N > 100) || (N <= 0));
	
	read(MX, M, N);
	Arr(MX, M, N, max_i, max_j, x);

	if (x == 0) printf_s("0\n");
	else printf_s("Элемент MX[%d][%d] матрицы максимальный в своей строке и минимальный в своём столбце\n", max_i, max_j);

	system("pause");
	return 0;
}