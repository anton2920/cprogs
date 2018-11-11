#include <stdio.h>

/* «Angling» hours and minutes */
main() {

	/* Initializing variables */
	int a;

	/* I/O flow */
	printf("Type the number of degrees: ");
	scanf("%d", &a);

	/* Main part */
	printf("The time is %dh:%dm\nThe angle between minute hand and the ray (center of a clock and the 12h point) equals to %d°\n", (a / 30) % 12, (a * 2) % 60, (a * 12) % 360);
}