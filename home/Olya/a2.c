#include <stdio.h>
#include <math.h>

main() {

	/* Initializing variables */
	auto double a, b, c;

	/* I/O flow */
	printf("Type a: ");
	scanf("%lf", &a);

	printf("Type b: ");
	scanf("%lf", &b);

	/* Main part */
	if (a <= 0 || b <= 0) {
		return -1;
	}

	c = sqrt(a * a + b * b);

	/* Final output */
	printf("Perimetr: %.2lf, Area: %.2lf\n", a + b + c, a * b / 2);
}