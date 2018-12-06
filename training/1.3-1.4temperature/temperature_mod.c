#include <stdio.h>

/* Symbolic constants */
#define LOW	0	/* Lower limit*/
#define UP	300	/* Upper limit */
#define STEP	20	/* Step */

main() {
	
	/* Variables */
	int fahr;

	/* Printing header */
	printf("\n-- The inverse temperature converter --\n");
	
	/* The FOR loop */
	for (fahr = UP; fahr >= LOW; fahr = fahr - STEP) {
		printf("Fahrenheiht: %3i --> Celsius: %4.2f\n", fahr, 5.0 * (fahr - 32) / 9.0);
	}

}
