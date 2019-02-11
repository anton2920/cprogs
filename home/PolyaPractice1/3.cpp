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
			do
			{
				printf("A[%d][%d] = ", i, j);
				scanf("%d", &A.arr[i][j]);
			} while (A.arr[i][j] < 0);
		}
	}
}
void sort(massiv& A)
{
	int tmp;
	for (int k = 0; k < A.M; k++)
	{
		for (int i = 0; i < A.N - 1; i++)
		{
			for (int j = A.N - 2; j >= i; j--)
			{
				if (A.arr[k][j] > A.arr[k][j + 1])
				{
					tmp = A.arr[k][j];
					A.arr[k][j] = A.arr[k][j + 1];
					A.arr[k][j + 1] = tmp;
				}
			}
		}
	}
}
int sravnenie(massiv& A)
{
	int n = 0, kol=0;
	
	for (int i = 1; i < A.M; i++)
	{
		for (int j = 0; j < A.N; j++)
		{
			if (A.arr[i][j] == A.arr[0][j]) n++; 
			else
			{
				n = 0;
				break;
			}
		}
		if (n != 0)
		{
			n = 0;
			kol++;
		}
	}
	return (kol);
}
int main()
{
	setlocale(LC_ALL, "Russian");

	massiv A;
	int vibor,res;

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
	res = sravnenie(A);

	printf("Кол-во строк равный 1-й равно %d\n", res);

	system("pause");
	return 0;
}