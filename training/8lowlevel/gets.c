#include "gets.h"

int lgets(char *str) {

	/* Initializing variables */
	int n;

	/* I/O flow */
	n = read(0, str, SIZE_BUF_GETS);
	*(str + (n - 1)) = '\0';

	/* Returning value */
	return n;
}