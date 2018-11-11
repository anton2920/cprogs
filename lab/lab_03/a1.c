#include <stdio.h>

/* Yuriy annual income */
main() {

	/* Initializing vasriables */
	float x;

	/* I/O flow */
	printf("Type x (Yuriy's amount of money per week for candies): ");
	scanf("%f", &x);

	/* Answer */
	printf("Yuriy's annual income equals to %6.3f\n", 208 * x);
}