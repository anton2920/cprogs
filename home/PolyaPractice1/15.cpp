#include <math.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <locale> 
#define M 50 
#define N 50 


void vvod_user(int num[M][N], int m, int n)
{
	int i, t;
	printf("Введите элементы матрицы:");
	for (i = 0; i < m; i++)
		for (t = 0; t < n; t++)
		{
			scanf("%d", &num[i][t]);
		}
}


void function(int num[M][N], int m, int n)
{
	setlocale(0, "Rus");
	int i, t;
	for (i = 0; i < m; i += 2)
		for (t = 0; t < n; t++)
		{
			for (int k = 0; k < n; k++)
				printf("%d", num[i][k]);
			printf("\n");
			t = n;
		}
}

int main()
{
	setlocale(0, "Rus");
	int m = 0, n = 0;
	int num[M][N];
	do
	{
		printf("Количество строк в матрице=");
		scanf("%d", &m);
	} while (m <= 0);
	do
	{
		printf("Количество столбцов в матрице=");
		scanf("%d", &n);
	} while (n <= 0);
	vvod_user(num, m, n);
	function(num, m, n);

	system("pause");
	return 0;
}
