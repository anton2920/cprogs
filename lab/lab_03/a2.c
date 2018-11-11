#include <stdio.h>
#include <math.h>

/* Additional procedure for printing measuring units */
void pechat(int x);

/* Information amount converter */
main() {

	/* Initializing variables */
	float a;
	int i;
	i = 0;

	/* I/O flow */
	printf("Type a (amount of information in bytes): ");
	scanf("%f", &a);
	printf("a = %.0f B", a);

	/* Main cycle */
	do {
		++i;
		a = a / 1024.0;
		printf(", %.1f ", a);
		pechat(i);
	} while (round(a) / 1024 != 0);

	/* Final printing */
	printf("\n");
}

void pechat(int x) {
	switch (x) {
		case 1: printf("kiB"); break;
		case 2: printf("MiB"); break;
		case 3: printf("GiB"); break;
		case 4: printf("TiB"); break;
		case 5: printf("PiB"); break;
		case 6: printf("EiB"); break;
		case 7: printf("ZiB"); break;
		case 8: printf("YiB"); break;
		default: printf("XXX"); break;
	}
}