#include <stdio.h>

#define ABS(X) ((X < 0) ? (-X) : (X))

void dig_sum_mul(int *, int *, int); 

main() {

	/* Initializing variables */
	int a, b, c, sum = 0, prod = 1;

	/* I/O flow */
	printf("Type a: ");
	scanf("%d", &a);
	printf("Type b: ");
	scanf("%d", &b);
	printf("Type c: ");
	scanf("%d", &c);

	/* Main part */

	dig_sum_mul(&sum, &prod, ABS(a));
	printf("a: Sum of digits = %d, Product of digits = %d\n", sum, prod);
	sum = 0;
	prod = 1;
	dig_sum_mul(&sum, &prod, ABS(b));
	printf("b: Sum of digits = %d, Product of digits = %d\n", sum, prod);
	sum = 0;
	prod = 1;
	dig_sum_mul(&sum, &prod, ABS(c));
	printf("c: Sum of digits = %d, Product of digits = %d\n", sum, prod);
}

void dig_sum_mul(int *sum, int *prod, int num) {

	/* Initializing variables */
	int dig;

	/* Main part */
	for ( ; num; ) {
		dig = num % 10;
		*sum += dig;
		*prod *= dig;
		num /= 10;
	}
}