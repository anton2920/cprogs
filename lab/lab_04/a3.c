#include <stdio.h>

/* Number of the day of the week */
main() {
	
	/* Initializing variables */
	int k, n;

	/* I/O flow */
	printf("Type N (the day of the week of the first day of the year) [0..6]: ");
	scanf("%d", &n);
	printf("Type K (the number of the exact day) [0..365]: ");
	scanf("%d", &k);

	/* Main part */
	printf("The day of the week is: %d\n", (k + n) % 7);
}