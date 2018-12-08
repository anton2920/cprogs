#include <stdio.h>
#include "headers/project.h"

main() {

    /* Initializing variables */
    int func;
    char a[NAME], b[NAME], c[NAME];

    /* I/O flow */
    func = set_sets(a, b, c);
	printf("%d", func);
}
