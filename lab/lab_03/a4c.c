#include <stdio.h>

/* Additional tasks (letter «c») */
main() {

	/* Initializing variables */
	float a, b;


	/* I/O flow */
	printf("Type a: ");
	scanf("%f", &a);

	/* Three operations --> a ^ 6 */
	a = a * a; /* ^ 2 */
    b = a * a; /* ^ 4 */
    a = a * b; /* ^ 6 */


	/* Final printing */
	printf("a ^ 6 = %6.3f\n", a);
}