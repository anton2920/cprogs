#include <iostream>
#include <stdio.h>

int const M = 100;
int const N = 100;

void vvod1(int A[100][100], int m, int n)
{
	int i, j;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
		{
			printf("\nВведите %d.%d элемент массива: ", i + 1, j + 1);
			scanf_s("%d", &A[i][j]);
		}
}

/*void vvod2(int A[100][100], int m, int n)
{
	int i, j;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
		{
			A[i][j] = rand() % 10 - 5;
		}
}
*/
void matr(int A[100][100], int m, int n)
{
	int i, j;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
			printf("%6.0d", A[i][j]);
		printf("\n");
	}
}

int serch_otr_sb(int A[100][100], int m, int n)
{
	int i, j, k = 0;
	for (i = 0; i < n; i++)
	{
		k = 0;
		for (j = 0; j < m; j++)
		{
			if (A[j][i] >= 0)
				k = -1;
		}
		if (k == 0)
		{
			k = i;
			break;
		}
	}
	//printf("\nk=%d", k);
	return k;
}

void zam_sb(int A[100][100], int m, int n, int x)
{
	int i, j, t;
	for (i = 0; i < m; i++)
	{
		t = A[i][n - 1];
		A[i][n - 1] = A[i][x];
		A[i][x] = t;
	}
	printf("\n");
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
			printf("%6.0d", A[i][j]);
		printf("\n");
	}
}

void vivod(int A[100][100], int m, int n)
{
	int i, j;
	printf("\n");
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
			printf("%6.0d", A[i][j]);
		printf("\n");
	}
}

int main()
{
	setlocale(LC_ALL, "RUS");


	int A[M][N];

	int m, n;  //m-кол-во строк, n-кол-во столбцов.
	do
	{
		printf_s("Введите кол-во строк: ");
		scanf_s("%d", &m);
		printf_s("\nВведите кол-во столбцов: ");
		scanf_s("%d", &n);
	} while (m <= 0 || n <= 0 || m >= 100 || n >= 100);

	int vvod;
	//printf_s("\nВыберете вариант ввода: 1)с клавиатуры 2)рандомом: ");
	//scanf_s("%d", &vvod);

	//if (vvod == 1)
	vvod1(A, m, n);
	//if (vvod == 2)
		//vvod2(A,m,n);

	matr(A, m, n);

	int x;
	x = serch_otr_sb(A, m, n);

	if (x != -1)
		zam_sb(A, m, n, x);
	else
		vivod(A, m, n);

	system("pause");
	return 0;
}

