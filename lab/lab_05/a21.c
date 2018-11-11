#include <stdio.h>
#include <math.h>

/* Segment function */
main() {

	/* Initializing variables */
	float x;

	/* I/O flow */
	printf("Type x («independant» variable): ");
	scanf("%f", &x);

	/* Main part */
	if (x <= 0) {
		printf("Answer: 5\n");
	}
	if ((x > 0) && (x <= 1)) {
		printf("Answer: %6.3f\n", (x*x*x + 1) / (2 * x + 3));
	}
	if (x > 1) {
		printf("Answer: %6.3f\n", 5 * log(x));
	}
}