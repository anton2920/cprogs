#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <locale>
#define M 100

void keyboard(double a[M][M], int m)
{
	printf("Введите числа в массиве\n");
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			scanf_s("%lf", &a[i][j]);
		}
	}
}

void output(double a[M][M], int m)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%5.2lf", a[i][j]);
		} printf("\n");
	} printf("\n");
}

void decision(double a[M][M], int m)
{
	double k, p, l;
	int counter = m - 1;
	for (int i = 0; i < m - 2; i++)
	{
		for (int j = i; j < counter; j++)
		{
			
			k = a[j][m - 1 - i]; 
			a[j][m - 1 - i] = a[i][j];
			p = a[m - 1 - i][m - 1 - j];
			a[m - 1 - i][m - 1 - j] = k;
			l = a[m - 1 - j][i];
			a[m - 1 - j][i] = p;
			a[i][j] = l;
		}
		counter = counter - 1;
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
	} while ((m > 100) || (m <= 0));

	double a[M][M] = {};

	keyboard(a, m);
	output(a, m);
	decision(a, m);
	output(a, m);

	system("pause");
	return 0;
}
