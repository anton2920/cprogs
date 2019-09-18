#include <stdio.h>

/* City population */
main() {

	/* Initializing variables */
	float a; /* Rate in per cents */
	long int b, n1, n2, i, b2, flag = 0, flag2 = 0, res; /* Basic population, «start» year, «end» year, iterator, old population */

	/* I/O flow && VarCheck */
	printf("Type rate (in %%): ");
	scanf("%f", &a);
	do {
		printf("Type basic city population: ");
		scanf("%ld", &b);
	} while (b <= 1);
	do {
		printf("Type the «start» year: ");
		scanf("%ld", &n1);
	} while (n1 < 0);
	do {
		printf("Type the «end» year: ");
		scanf("%ld", &n2);
	} while (n2 < 0 || n2 <= n1);

	/* Main part */
	b2 = b;
	printf("The population in year %ld equals to %ld\n", n1, b);
	for (i = n1 + 1; i <= n2; ++i) {
		b2 += b2 * (a / 100);
		printf("The population in year %ld equals to %ld\n", i, b2);
		if (b2 / b == 3 && flag == 0) {
			flag = 1;
			res = i - n1;
		}
		if (b2 == 0) {
			flag2 = 1;
			printf("The city has been extinguished ×_×\n");
			break;
		}
	}
	if (!flag && !flag2) {
		for ( ; !flag || b2 == 0; ++i) {
			b2 += b2 * (a / 100);
			if (b2 / b == 3 && flag == 0) {
				flag = 1;
				res = i - n1;
			}
		}
		if (!flag) {
			printf("The population will never be triple as many as original\n");
		} else {
			printf("The population will be triple as many as original in %ld years\n", res);
		}
	} else {
		printf("The population will be triple as many as original in %ld years\n", res);
	}
}