#include <stdio.h>

void swap(double *, double *);

main() {

	/* Initializing variables */
	double x, y;

	/* I/O flow */
	printf("Type x: ");
	scanf("%lf", &x);
	printf("Type y: ");
	scanf("%lf", &y);

	/* Main part */
	swap(&x, &y);

	/* Final output */
	printf("Swapped variables: x = %.2lf, y = %.2lf\n", x, y);
}

void swap(double *a, double *b) {

	/* Initializing variables */
	double temp;

	/* Main part */
	temp = *a;
	*a = *b;
	*b = temp;
}