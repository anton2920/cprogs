#include <stdio.h> 

/* Digital clock */
main() {
	
	/* Initializing variables */
	int m, n, k, p, q, r; /* m — hours, n — mins, k — secs, p — add. hours, q — add. mins and r — add. secs */

	/* I/O flow */
	printf("Type the number of hours: ");
	scanf("%d", &m);
	printf("Type the number of minutes: ");
	scanf("%d", &n);
	printf("Type the number of seconds: ");
	scanf("%d", &k);
	printf("———————————————\n");
	printf("Type the number of additional hours: ");
	scanf("%d", &p);
	printf("Type the number of additional minutes: ");
	scanf("%d", &q);
	printf("Type the number of additional seconds: ");
	scanf("%d", &r);

	/* Main part */
	k = k + r;
	n = n + q + (k / 60);
	m = m + p + (n / 60);

	k = k % 60;
	n = n % 60;
	m = m % 24;

	/* Final output */
	printf("The time is %d:%d:%d\n", m, n, k);
}