#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main()
{
	double chislo;
	int a, b, i;
	do
	{
		i = 0;
		printf("Type a number: ");
		scanf("%lf", &chislo);
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

	return 0;
}
