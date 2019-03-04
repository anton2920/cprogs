//7. Построить множество, которое состоит из дружных чисел на интервале от 1 до 255. 
//Дружными числами называется такая пара натуральных чисел М и N, 
//для которых сумма всех делителей числа М(кроме самого М) равняется числу N, 
//а сумма всех делителей числа N(кроме самого числа N) равняется числу М.

#pragma warning (disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#define N 255

void write(int *B, int deg)
{
	for (int k = 0; k < deg; k++)
		printf("%d ", B[k]);
	printf("\n");
}

void mass(int *m, int *n, int *B, int a, int b, int c, int d, int j, int &deg)
{
	while (a < N + 1)
	{
		j = 0;
		for (int i = 1; i < N + 1; i++)
		{
			if (a % i == 0 && i < a)
			{
				m[j] = i;
				j++;
			}
		}
		while (b < N + 1)
		{
			j = 0;
			for (int i = 1; i < N + 1; i++)
			{
				if (b % i == 0 && i < b)
				{
					n[j] = i;
					j++;
				}
			}
			for (int k = 0; k < N; k++)
			{
				c += m[k];
				d += n[k];
			}
			if (c == b && d == a/* && a != b*/)
			{

				B[deg] = a;
				B[deg + 1] = b;
				deg += 2;
			}
			c = 0;
			d = 0;
			for (int k = 0; k < N; k++)
				n[k] = 0;
			b++;
		}
		a++;
		b = 1;
		for (int k = 0; k < N; k++)
			m[k] = 0;
	}
}

int main()
{
	int B[N] = {};
	int m[N] = {}, n[N] = {};
	int a = 1, b = 1, c = 0, d = 0, j = 0, deg = 0;

	mass(m, n, B, a, b, c, d, j, deg);
	write(B, deg);

	system("pause");
	return 0;
}