#include <stdio.h>
#include "shoulders.h"

int getint(char *num) {

	/* Initializing variables */
	int i, sign, c;
	if (!lisdigit(c = getchar()) && c != '-' && c != '+') {
		return -1;
	}
	sign = (c == '-') ? -1 : 1;
	for (i = 0; (c = getchar()) != '\n'; ++i) {
		*num += *num * 10 + (c - '0');
	}
	*num *= sign;
	
	/* Return */
	return i;
}

int lisdigit(char dig) {
	return (dig >= '0' && dig <= '9') ? 1 : 0;
}