#include <stdio.h>
#include <math.h>

/* f(x) = 1 + pow((2 * x * x) * (x - 6)), 1 / 3) */
main() {

	/* Initializing vasriables */
	float x;

	/* I/O flow */
	printf("Type x: ");
	scanf("%f", &x);

	/* Main part */
	if ((2 * x * x) * (x - 6) > 0) {
		printf("f(x) = %6.3f\n", 1 + pow((2 * x * x) * (x - 6), 1.0 / 3.0));
	} else if ((2 * x * x) * (x - 6) < 0) {
		printf("f(x) = %6.3f\n", 1 - pow(-((2 * x * x) * (x - 6)), 1.0 / 3.0));
	}
}