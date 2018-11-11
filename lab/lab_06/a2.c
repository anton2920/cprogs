#include <stdio.h>
#include <math.h>

#define M_PI 3.1415923535897932384626433832795

/* Functions headers */
float square (float radius);
float big (float a1, float a2, float a3);


/* Circle radiuses */
main() {

	/* Initializing variables */
	float r1, r2, r3;

	/* I/O flow */
	printf("Type first radius: ");
	scanf("%f", &r1);
	printf("Type second radius: ");
	scanf("%f", &r2);
	printf("Type third radius: ");
	scanf("%f", &r3);

	/* VarCheck */
	if (r1 <= 0 || r2 <= 0 || r3 <= 0) {
		printf("Wrong radius!\n");
	} else {
		/* Final output */
		printf("Answer: %f\n", square(big(r1, r2, r3)));
	}
}


/* Custom function for circle square */
float square (float radius) {

	return radius * radius * M_PI;
}


float big (float a1, float a2, float a3) {

	if (a1 > a2 && a1 > a3) {
		return a1;
	} else if (a2 > a1 && a2 > a3) {
		return a2;
	} else {
		return a3;
	}
}