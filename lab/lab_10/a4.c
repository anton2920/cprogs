#include <stdio.h>

/* Number sequence */
main() {

	/* Initializing variables */
	int mem = 0, min1 = 0, min2, dist = 0, max_dist = 0, flag = 0, prev_mem = 0;

	/* Main part */
	do {
		prev_mem = mem;
		printf("Type a sequence member (zero for exit): ");
		scanf("%d", &mem);
		if (!flag)
			min1 = mem;
		if (mem > prev_mem && !flag) {
			flag = 1;
		} else if (mem < prev_mem && !flag) {
			flag = 2;
		} else if ((mem > prev_mem || mem < prev_mem) && flag) {
			flag = -1;
		}
		if (flag) {
			if (mem > prev_mem) {
				min1
			}
		}

	} while (mem != 0);

}