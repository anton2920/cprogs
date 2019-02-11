#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define M 100
#define N 100

void Read(int arr[M][N], int m, int n)
{
	printf("Enter the elements of array: ");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			scanf("%d", &arr[i][j]);
	}
}

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

void Rand(int arr[M][N], int m, int n)
{
	srand(time(NULL));
	int x = 0, y = 1000;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			arr[i][j] = rand() % (y - x + 1) + x;
	}
	Write_Arr(arr, m, n);
}

int Min(int arr[M][N], int m, int n)
{
	int k = 0;


}

int main()
{
	int arr[M][N] = { 0 };
	int a, m, n;

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



	system("pause");
	return 0;
}