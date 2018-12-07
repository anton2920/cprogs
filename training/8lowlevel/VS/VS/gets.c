#include "gets.h"

int lgets(char *str) {

	/* Initializing variables */
	int n;

	/* I/O flow */
	#ifdef _WIN32
		n = _read(0, str, SIZE_BUF_GETS);
	#endif // _WIN32
	#ifdef __unix__
		n = read(0, str, SIZE_BUF_GETS);
	#endif // __unix__

	*(str + (n - 1)) = '\0';

	/* Returning value */
	return n;
}