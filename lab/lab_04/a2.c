#include <stdio.h>

/* Changing positions of second and fifth digits */
main() {

	/* Initializing variables */
	int a, a1, a2, a3, a4, a5, an; /* Number itsefl, first, second, third, fourth and fifth digits */

	/* I/O flow */
	printf("Type a five digit number: ");
	scanf("%d", &a);

	/* Digits deassebly */
	a5 = abs(a % 10);
	a4 = abs((a / 10) % 10);
	a3 = abs((a / 100) % 10);
	a2 = abs((a / 1000) % 10);
	a1 = a / 10000;

	/* Reverse */
	an = a1 * 10000 + a5 * 1000 + a3 * 100 + a4 * 10 + a2;

	/* Main output */
	printf("Answer: %d%d%d%d%d\n", a1, a5, a3, a4, a2);
	printf("Answer2: %d\n", an);
}