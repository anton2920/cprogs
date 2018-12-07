#include <stdio.h>

int ameba(int h);

/* Ameba cells */
main() {

    /* Initializing variables */
    int counter;

    /* Main part */
    for (counter = 3; counter <= 24; counter = counter + 3) {
        printf("The number of cells in %d hours is %d\n", counter, ameba(counter));
    }
}

int ameba(int h) {
    
    if (h == 0) {
        return 1;
    } else {
        return ameba(h - 3) * 2;
    }
}