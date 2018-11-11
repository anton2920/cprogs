#include <stdio.h>

/* Additional tasks (letter «a») */
main() {

	/* Initializing variables */
	float a;


	/* I/O flow */
	printf("Type a: ");
	scanf("%f", &a);

	/* Two operations --> a ^ 4 */
	a = a * a; /* ^ 2 */
	a = a * a; /* ^ 4 */

	/* Final printing */
	printf("a ^ 4 = %6.3f\n", a);
}