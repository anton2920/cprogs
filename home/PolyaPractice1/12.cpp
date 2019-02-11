#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale>

#define default_value 100

typedef struct
{
	int matrix[default_value][default_value];
	int M;
}massive;

void input(massive *mass);
void sorting_output(massive *mass);

int main()
{
	setlocale(0, "rus");
	massive mass[2];
	printf("Задание №12:");
	input(mass);
	sorting_output(mass);
	system("pause");
	return 1;
}

void input(massive *mass)
{
	do
	{
		printf("\n\t - Введите порядок матрицы: "); scanf("%d", &mass[1].M);
		if (mass[1].M < 1 || mass[1].M > 100)
			printf("\nВведены неккоректные значения, диапазон допустимых значений: 1-100.\n");
	} while (mass[1].M < 1 || mass[1].M > 100);
	srand(unsigned int(time(NULL)));

	for (int i = 0; i < mass[1].M; i++)
	{
		for (int j = 0; j < mass[1].M; j++)
		{
			mass[1].matrix[i][j] = (rand() % 99) + 1;
		}
	}
	for (int i = 0; i < mass[1].M; i++)
	{
		for (int j = 0; j < mass[1].M; j++)
		{
			printf("%d ", mass[1].matrix[i][j]);
		}
		printf("\n");
	}
}

void sorting_output(massive *mass)
{
	for (int i = mass[1].M - 1; i >= 0; i--)
	{
		for (int j = mass[1].M - 1; j >= 0; j--)
		{
			printf(" %d ", mass[1].matrix[j][i]);
		}
		printf("\n");
	}
}