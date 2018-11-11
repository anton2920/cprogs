#include <stdio.h>

/* Number of hours from past day */
main() {

	/* Initializing variables */
	int n, a;

	/* I/O flow */
	printf("Type a number of seconds: ");
	scanf("%d", &n);

	/*Main part */

	/* Hint
	1 min = 60 sec
	1 hour = 60 min
	1 day = 24 hours
	1 week = 7 days */
	a = ((n / 60.0) / 60.0) / 24; /* To days */
	a = a * 24 * 60 * 60; /* To secs */
	n = n - a; /* Number of seconds from past day */

	/* Final output */
	printf("%4.2f hours passed\n", ((n / 60.0) / 60.0));
}