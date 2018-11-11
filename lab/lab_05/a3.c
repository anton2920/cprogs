#include <stdio.h>
#include <math.h>

/* Dot and the area */
main() {

	/* Initializing variables */
	float x, y;

	/* I/O flow */
	printf("Type x of a dot: ");
	scanf("%f", &x);
	printf("Type y of a dot: ");
	scanf("%f", &y);

	/* Main part */
	if ((y < exp(x)) && y < exp(-x) && y > x * x) {
		printf("Dot is in the area\n");
	} else {
		printf("Dot is not in the area\n");
	}
}