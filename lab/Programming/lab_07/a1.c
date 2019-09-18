#include <stdio.h>

/* Member of a number set (cycled version) */
main() {

	/* Initializing variables */
	float a, b, c;

	/* I/O flow */
	printf("Type the element a: ");
	scanf("%f", &a);
	printf("Type the step b: ");
	scanf("%f", &b);
	printf("Type the first element c: ");
	scanf("%f", &c);

	/* Main part */
	while (c < a) {
		c = c + b;
	}

	/* Final output */
	printf("The «a» element is %s in the number set\n", (a == 0) ? "" : "not");
}