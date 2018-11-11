#include <stdio.h>

/* Information amount converter (simplified version) */
main() {

	/* Initializing variables */
	float a;

	/* I/O flow */
	printf("Type a (amount of Information in bytes): ");
	scanf("%f", &a);

	/* Main part */
	printf("a = %.0f B", a);
	a = a / 1024.0;
	printf(", %.1f KiB", a);
	a = a / 1024.0;
	printf(", %.1f MiB", a);
	a = a / 1024.0;
	printf(", %.1f GiB\n", a);
}