#include <stdio.h>
#include <math.h>

/* f(x) = 1 + pow((2 * x * x) * (x - 6)), 1 / 3) (simplified version) */
main() {

	/* Initializing vasriables */
	float x;

	/* I/O flow */
	printf("Type x: ");
	scanf("%f", &x);

	/* Main part */
	printf("f(x) = %6.3f\n", 1 + pow((2 * x * x) * (x - 6), 1.0 / 3.0));
}