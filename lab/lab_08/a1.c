#include <stdio.h>
#include <math.h>

/* Geometric mean */
main() {

	/* Initializing variables */
	float res, a, counter;
	res = 1;
	a = 1;
	counter = 0;

	/* Main part */
	do {
		res = res * a;
		++counter;
		printf("Type a positive number: ");
		scanf("%f", &a);
	} while (a > 0);

	/* Final output */
	printf("Answer: %f\n", pow(res, 1.0 / (counter - 1)));
}