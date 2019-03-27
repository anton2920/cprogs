//#define _CRT_SECURE_NO_WARNINGS

#include "Header_fraction.h"
#include "Header_Calc.h"


#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void sum_fraction(int *numerator, int *denominator, int n) //сумма
{
	float sum = 0;

	for (int i = 0; i < n; i++)
	{
		sum = sum + ((float)(numerator[i]) / denominator[i]);
	}

	printf("Sum = %f\n", sum);
}

void difference_fraction(int *numerator, int *denominator, int n) //разность
{
	float dif = (float)(numerator[0]) / denominator[0];

	for (int i = 1; i < n; i++)
	{
		dif = dif - ((float)(numerator[i]) / denominator[i]);
	}

	printf("Difference = %f\n", dif);
}

void multiplication_fraction(int *numerator, int *denominator, int n) //умножение
{
	float mul = 1;

	for (int i = 0; i < n; i++)
	{
		mul = mul * ((float)(numerator[i]) / denominator[i]);
	}

	printf("Mutiplication = %f\n", mul);
}

void division_fraction(int *numerator, int *denominator, int n) //деление
{
	float div = (float)(numerator[0]) / denominator[0];

	for (int i = 1; i < n; i++)
	{
		div = div / ((float)(numerator[i]) / denominator[i]);
	}

	printf("Division = %f\n", div);
}

void comparison_fraction(int *numerator, int *denominator, int n) //сравнение
{
	if (((float)(numerator[0]) / denominator[0])>((float)(numerator[1]) / denominator[1]))
		printf("%d/%d > %d/%d\n", numerator[0], denominator[0], numerator[1], denominator[1]);
	else if (((float)(numerator[0]) / denominator[0])<((float)(numerator[1]) / denominator[1]))
		printf("%d/%d < %d/%d\n", numerator[0], denominator[0], numerator[1], denominator[1]);
	else if (((float)(numerator[0]) / denominator[0]) == ((float)(numerator[1]) / denominator[1]))
		printf("%d/%d = %d/%d\n", numerator[0], denominator[0], numerator[1], denominator[1]);
}

void reduction_fraction(int *numerator, int *denominator, int n) //сокращение
{
	int red;
	int num1 = numerator[0];
	int denom1 = denominator[0];
	while (num1 != 0 && denom1 != 0)
	{
		if (num1>denom1)
			num1 = num1 % denom1;
		else
			denom1 = denom1 % num1;
	}
	red = num1 + denom1;

	int num = numerator[0] / red;
	int denom = denominator[0] / red;

	printf("Reduced fraction: %d/%d\n", num, denom);
}

void in_decimal_fraction(int *numerator, int *denominator, int n)	//представление в виде десятичной дроби
{
	float dec;
	dec = (float)(numerator[0]) / denominator[0];
	printf("Decimal representation: %f\n", dec);
}


void menu_fraction()
{
	int no = 1;
	while (no == 1)
	{

		int op;

		printf("\n");
		printf("What function do you want to perform? \n");
		printf("0. Cancel \n");
		printf("1. The sum of the fractions \n");
		printf("2. The difference of the fractions \n");
		printf("3. The multiplying of the fractions \n");
		printf("4. The division of the fractions \n");
		printf("5. The comparison of the fractions \n");
		printf("6. The reduction of the fractions \n");
		printf("7. The decimal representation of the fractions \n");

		do
		{
			printf("Choose the variant of function:");
			scanf("%d", &op);
		} while ((op > 7) || (op < 0));

		int n;

		if (op == 1 || op == 2 || op == 3 || op == 4)
		{
			do
			{
				printf("Enter the number of fractions: ");
				scanf("%d", &n);
			} while (n < 2 || n >= 100);
		}
		else if (op == 5)
		{
			do
			{
				printf("Enter the number of fractions: ");
				scanf("%d", &n);
			} while (n != 2);
		}
		else if (op == 6 || op == 7)
		{
			do
			{
				printf("Enter the number of fractions: ");
				scanf("%d", &n);
			} while (n != 1);
		}

		int numerator[n1], denominator[n1];

		if (op != 4 && op != 0)
			for (int i = 0; i < n; i++)
			{
				do
				{
					printf("Enter the numerator of %d fraction: ", i + 1);
					scanf("%d", &numerator[i]);
				} while (numerator[i] < -214748648 || numerator[i] > 2147483647);
				do
				{
					printf("Enter the denominator of %d fraction: ", i + 1);
					scanf("%d", &denominator[i]);
				} while(denominator[i] < -214748648 || denominator[i] == 0 || denominator [i] > 2147483647);
			}
		else if (op == 4)
			for (int i = 0; i < n; i++)
			{
				if (i == 0)
				{
					do
					{
						printf("Enter the numerator of %d fraction: ", i + 1);
						scanf("%d", &numerator[i]);
					} while (numerator[i] < -214748648 || numerator[i] > 2147483647);
				}

				if (i == 1)
					do
					{
						printf("Enter the numerator of %d fraction: ", i + 1);
						scanf("%d", &numerator[i]);
					} while (numerator[i] < -214748648 || numerator[i] > 2147483647 || numerator[i] == 0);

					do
					{
						printf("Enter the denominator of %d fraction: ", i + 1);
						scanf("%d", &denominator[i]);
					} while (denominator[i] < -214748648 || denominator[i] == 0 || denominator[i] > 2147483647);
			}

		switch (op)
		{
		case 0: no = 0; break;
		case 1: sum_fraction(numerator, denominator, n); break;
		case 2: difference_fraction(numerator, denominator, n); break;
		case 3: multiplication_fraction(numerator, denominator, n); break;
		case 4: division_fraction(numerator, denominator, n); break;
		case 5: comparison_fraction(numerator, denominator, n); break;
		case 6: reduction_fraction(numerator, denominator, n); break;
		case 7: in_decimal_fraction(numerator, denominator, n); break;
		};

		if (no == 0)
			break;
	} 
}