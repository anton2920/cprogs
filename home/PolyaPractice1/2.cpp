#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define M 100
#define N 100

void Write_Arr(int arr[M][N], int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%.3d\t", arr[i][j]);
		}
		printf("\n");
	}
}

void Read(int arr[M][N], int m, int n)
{
	printf("Enter the elements of array: ");
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			scanf("%d", &arr[i][j]);
	}
	Write_Arr(arr, m, n);
}

void Rand(int arr[M][N], int m, int n)
{
	srand(time(NULL));
	int x = 0, y = 1000;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			arr[i][j] = rand() % (y - x + 1) + x;
	}
	Write_Arr(arr, m, n);
}

int Zero(int arr[M][N], int m, int n)
{
	int j, cht = 0, s = 1;
	for (int i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (arr[i][j] % 2 != 0) break;
		}
		if (j == n) cht = i;
	}
	return cht;
}

int main()
{
	int arr[M][N] = { 0 };
	int a, m, n, cht = 0;
	
	do
	{
		printf("Enter the number of lines: ");
		scanf("%d", &m);
	} while (m > 100 || m < 1);
	
	do
	{
		printf("Enter the number of columns: ");
		scanf("%d", &n);
	} while (n > 100 || n < 1);
	
	printf("How are you want to enter the array?\n");
	printf("1. From keyboard;\n");
	printf("2. Enter the random elements. \n");

	scanf("%d", &a);
	while ((a < 1) || (a > 2))
	{
		printf("Was entered false value! Please, try again: ");
		scanf("%d", &a);
	}
	switch (a)
	{
	case 1: Read(arr, m, n); break;
	case 2: Rand(arr, m, n); break;
	default: break;
	}

	cht = Zero(arr, m, n);

	printf("The number of line with the only evens elements of massiv: %d\n", cht);

	system("pause");
	return 0;
}