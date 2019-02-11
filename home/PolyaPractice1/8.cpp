#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<ctime>

struct massiv
{
	int arr[100][100];
	int M, N;
};
void random_vvod(massiv& A)
{
	srand(time(NULL));
	for (int i = 0; i < A.M; i++)
	{
		for (int j = 0; j < A.N; j++)
		{
			A.arr[i][j] = rand() % (101);
			printf("A[%d][%d]=%d\n", i, j, A.arr[i][j]);
		}
	}
}
void vvod_klav(massiv& A)
{
	for (int i = 0; i < A.M; i++)
	{
		for (int j = 0; j < A.N; j++)
		{
			printf("A[%d][%d] = ", i, j);
			scanf("%d", &A.arr[i][j]);
		}
	}
}
void sort(massiv& A)
{
	int tmp;
	
	for (int j = 0; j < A.N; j++)
	{
		for (int k = 0; k < A.M - 1; k++)
		{
			for (int i = A.M-2; i>=k; i--)
			{
				if (A.arr[i][j] < A.arr[i + 1][j])
				{
					tmp = A.arr[i][j];
					A.arr[i][j] = A.arr[i + 1][j];
					A.arr[i + 1][j] = tmp;
				}
			}
		}
	}

	for (int i = 0; i < A.N - 1; i++)
	{
		if (A.arr[0][i] > A.arr[0][i + 1])
		{
			tmp = A.arr[0][i];
			A.arr[0][i] = A.arr[0][i + 1];
			A.arr[0][i + 1] = tmp;
		}
	}
}
void vivod(massiv& A)
{
	for (int i = 0; i < A.M; i++)
	{
		for (int j = 0; j < A.N; j++)
			printf("A[%d][%d]=%d\n", i,j,A.arr[i][j]);
	}
}
int main()
{
	setlocale(LC_ALL, "Russian");

	massiv A;
	int vibor;

	do
	{
		printf("Выберете способ ввода матрицы\n1)С клавиатуры\n2)Радномно\n");
		scanf("%d", &vibor);
	} while ((vibor < 1) || (vibor > 2));

	do
	{
		printf("Кол-во строк M=");
		scanf("%d", &A.M);
		printf("Кол-во столбцов N=");
		scanf("%d", &A.N);
	} while ((A.M > 100) || (A.M < 1) || (A.N > 100) || (A.M < 1));

	switch (vibor)
	{
	case 1:
	{
		vvod_klav(A);
		break;
	}
	case 2:
	{
		random_vvod(A);
		break;
	}
	}

	sort(A);
	vivod(A);

	system("pause");
	return 0;
}