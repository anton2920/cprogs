#include <stdio.h>

/* Two states */
#define IN	1
#define OUT	0

/* Everything counter */
main() {
	
	int state;
	long c, nc = 0, wc = 0; /* c - char, nc - char counter, wc - word counter */ 
	
	/* getchar() put ONLY ONE char at a time to 'c' var. It doesn't matter whether we type one char or not. Using while, it will collect all of them but not simultaneously (char by char) */
	while ((c = getchar()) != EOF) {
		++nc;
		if (c == '\n' || c == ' ' || c == '\t') {
			state = OUT;
		} else if (state == OUT) { 
			state = IN;
			++wc;
		}
	}
	printf("The number of characters is: %ld\n", nc);
	printf("The number of words is: %ld\n", wc); 
}
