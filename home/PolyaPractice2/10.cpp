#include <stdio.h>
#include <stdlib.h>
#include <locale>

int main()
{
	setlocale(LC_ALL, "Rus");
	double chislo;
	int a, b, i;
	do
	{
		i = 0;
		printf("¬ведите число = ");
		scanf_s("%lf", &chislo);
		if (chislo - int(chislo) != 0) i = 1;
	} while ((chislo < 2)||(i==1)||(chislo>INT_MAX));

	for (int i = 1; i<=int(chislo / 2); i++)
	{
		a = i;
		b = chislo - i;
		printf("%d", a);
		printf("+");
		printf("%d\n", b);
	}

	system("pause");
	return 0;
}