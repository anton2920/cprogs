#include <stdio.h>

/* Everything counter */
main() {
	
	long c, nc = 0, lc = 0, bc = 0, tc = 0; /* c - string, nc - chars counter, lc - lines counter, bc - blanks counter, tc - tabs counter */
	
	/* getchar() put ONLY ONE char at a time to 'c' var. It doesn't matter whether we type one char or not. Using while, it will collect all of them but not simultaneously (char by char) */
	while ((c = getchar()) != EOF) {
		++nc;
		if (c == '\n') {
			++lc;
		}
		if (c == ' ') {
			++bc;
		}
		if (c == '\t') {
			++tc;
		}
	}
	printf("The number of characters is: %ld\n", nc - (lc + bc + tc));
	printf("The number of lines is: %ld\n", lc);
	printf("The number of blanks is: %ld\n", bc);
	printf("The number of tabs is: %ld\n", tc);
}
