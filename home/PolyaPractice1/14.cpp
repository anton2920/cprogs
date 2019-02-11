#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#define M 100
#define N 100

void read(int a[M][N], int m, int n)
{
	for (i = 0; i < m; ++i)
	{
		printf("%d | \n", i + 1);
		for (j = 0; j < n; ++j)
		{
			printf("%d | ", j + 1);
			scanf("%d", &a[i][j]);
		}
	}
}

void Alg(int a[M][N], int m, int n, int i, int j)
{
	for (i = 0; i < m; ++i)
	{
		for (j = 0; j < n; ++j)
		{
			if (j % 2 == 0)
			{
				printf(" | %d | ", a[i][j]);
			}
			else
			{
				printf(" | %d | ", a[n - i - 1][j]);
			}
		}
		printf("\n");
	}
}

int main(void)
{
	int a[M][N];
	int m, n;
	int i, j;
	
	do 
	{
		printf("Vvedite kolichestvo strok\n");
		scanf("%d", &m);
	} while ((m > 100) && (m < 0));
	
	do
	{
		printf("Vvedite kolichestvo stolbcov\n");
		scanf("%d", &n);
	} while ((n > 100) && (n < 0));
	
	read(a, m, n);
	Alg(a[M][N], m, n, i, j);
	
	system("pause");
	return 0;
}