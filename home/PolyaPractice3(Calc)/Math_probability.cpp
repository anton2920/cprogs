#include "Header_Calc.h"
#include "Math_probability.h" 

void probability()
{
	double m, n;

	printf("\nProbability m/n: \nEnter n: ");
	scanf("%lf", &n);

	while (n <= 0)
	{
		printf("Error! Enter n again: ");
		scanf("%lf", &n);
	}

	printf("Enter m: ");
	scanf("%lf", &m);

	while (m <= 0 || m > n)
	{
		printf("Error! Enter m again: ");
		scanf("%lf", &m);
	}

	m = m / n;

	printf("Probability m/n: %lf\n", m);
}

void table_entry(double x[100], double p[100], int s)
{
	printf("Enter value(xi) and probability (pi, 0 < pi <= 1): ");

	for (int i = 1; i <= s; i++)
	{
		printf("\n x%d: ", i);
		scanf("%lf",&x[i]);
		printf("p%d: ", i);
		scanf("%lf", &p[i]);
		while (p[i] <= 0 || p[i] > 1)
		{
			printf("\nError!\np%d=", i);
			scanf("%lf", &p[i]);
		}

	}
}

double math_dispertion(double x[100], double p[100], int s, double rr)
{
	double sum = 0;

	for (int i = 1; i <= s; i++)
		sum += p[i]*x[i]*x[i];

	sum -= rr * rr;

	return sum;
}

double math_expectation(double x[100], double p[100], int s)
{
	double sum = 0;
	for (int i = 1; i <= s; i++)
		sum += x[i] * p[i];

	return sum;
}

void math_probability_menu()
{
	int a, n;
	double p[100], x[100], r, r1;

	a = 0;

	do
	{
		printf("\n0. Output\n1. Mathematical probability\n2. Mathematical dispertion and expectation\n\nEnter task number: ");
		scanf("%d", &a);

		while (a < 0 || a > 2)
		{
			printf("Error! Enter task number again: ");
			scanf("%d", &a);
		}

		switch (a)
		{
		case 1:probability(); break;
		case 2:
		{
			printf("Enter the number of measurements (0 < n <= 100): ");
			scanf("%d", &n);

			while (n < 0 || n> 100)
			{
				printf("\nError! Enter the number of measurements (0 < n <= 100) again: ");
				scanf("%d", &n);
			}

			table_entry(x, p, n);
			r = math_expectation(x, p, n);
			r1 = math_dispertion(x, p, n, r);
			printf("\nMathematical expectation: %lf\nMathematical dispertion: %lf\n", r, r1);
		}
		; break;
		}

	} while (a != 0);
}