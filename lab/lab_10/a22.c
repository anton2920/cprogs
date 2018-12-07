#include <stdio.h>

/* Logo (loop version #2) */
main() {

    /* Initializing variables */
    int i, j;

    /* Main part */
    for (i = 0; i < 18; ++i) {
        for (j = 0; j < 46; ++j) {
            if ((j == 0) || ((!i || i == 17) && (j >= 1 && j < 15)) || ((i >= 4 && i <= 13) && j == 6) || ((i == 3 || i == 14) && (j > 6 && j <= 13))) {
                printf("[");
            } else if (j == 45) {
                printf("]\n");
            } else if (((i != 0 && i != 17) && (j < 6 || j > 39)) || (((i >= 1 && i <= 2) || (i >= 15 && i <= 16)) && ((j >= 6 && j <= 13) || (j > 31 && j <= 39))) || ((i == 3 || i == 14) && (j == 6 || j == 39)) || (((i >= 1 && i <= 3) || (i >= 14 && i <= 16)) && (j == 14 || j == 31))) {
                printf(":");
            } else if (((i >= 4 && i <= 13) && j == 39) || ((i == 3 || i == 14) && (j > 31 && j < 39)) || ((!i || i == 17) && (j >= 31 && j <= 44))) {
                printf("]");
            } else if (i == 7 && j == 21) {
                printf("BSTU");
                j += 3;
            } else if (i == 8 && j == 20) {
                printf("18-SWE");
                j += 5;
            } else if (i == 9 && j == 10) {
                printf("Pavlovsky Anton Evgenevich");
                j += 25;
            } else {
                printf(" ");
            }
        }
    }
}