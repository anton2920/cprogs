#include <stdio.h>

main() {
	/* Initialising vars */
	float celsius, fahr;
	int min = 0, max = 500, step = 10;

	/* Printin header */
	printf("\nTemperature convertor (from Fahrenheiht to Celsius)\n\n");
	
	/* Cycle with main actions */
	fahr = min;
	while (fahr <= max) {
		celsius = 5.0 * (fahr - 32) / 9.0;
		printf("Fahr: %3.0f --> Cels: %4.2f\n", fahr, celsius);
		fahr = fahr + step;
	}
}
