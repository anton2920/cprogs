#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <locale>
#define M 100
#define N 100
void replacemen(double a[M][N], int m, int n, int starting_position);

void keyboard(double a[M][N], int m, int n)
{
	printf("Введите числа в массиве\n");
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf_s("%lf", &a[i][j]);
		}
	}
}

void output(double a[M][N], int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%5.2lf", a[i][j]);
		} printf("\n");
	} printf("\n");
}

void decision(double a[M][N], int m, int n, int starting_position)
{
	int counter = 0;
	for (int j = 0; j < n; j++)
	{
		for (int i = 0; i < m; i++)
		{
			if (a[i][j] > 0)
			{
				counter += 1;
			}
		}
		if (counter == m)
		{
			starting_position = j;
			if(starting_position == 0)
			{
				break;
			}
			replacemen(a, m, n, starting_position); break;
		}
		counter = 0;
		printf("\n");
	} printf("\n");
}

void replacemen(double a[M][N], int m, int n, int starting_position)
{
	for (int i = 0; i < m; i++)
	{
		a[i][starting_position - 1] = 1;
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	int m, n, starting_position = 0;

	do
	{
		printf("Введите М\n");
		scanf_s("%d", &m);
	} while ((m > 100)||(m <= 0));
	do
	{
		printf("Введите N\n");
		scanf_s("%d", &n);
	} while ((n > 100)||(n <= 0));

	double a[M][N] = {};
	keyboard(a, m, n);
	output(a, m, n);
	decision(a, m, n, starting_position);
	output(a, m, n);
	system("pause");
	return 0;
}