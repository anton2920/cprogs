#include <stdio.h>


/* Previous day */
int main() {

    /* Initializing variables */
    int d, m;

    /* I/O flow */
    printf("Type the number of the day: ");
    scanf("%d", &d);
    printf("Type the number of the month: ");
    scanf("%d", &m);

    /* VarCheck */
    if (d <= 0) {
        printf("Wrong date!\n");
        return 0;
    } else {
        switch (m) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                if (d > 31) {
                    printf("Wrong date!\n");
                    return 0;
                } else {
                    break;
                }
            case 2:
                if (d > 28) {
                    printf("Wrong date!\n");
                    return 0;
                } else {
                    break;
                }
            case 4: case 6: case 9: case 11:
                if (d > 30) {
                    printf("Wrong date!\n");
                    return 0;
                } else {
                    break;
                }
            default:
                printf("Wrong month!\n");
                break;
        }
    }

    /* Main part */
    if (m == 1) {
        if (d == 1) {
            printf("Answer: 31.12\n");
        }
    } else {
        if (d == 1) {
            switch (m) {
                case 2: case 4: case 6: case 8: case 9: case 11:
                    printf("Answer: %d.%d\n", 31, m - 1);
                    break;
                case 3:
                    printf("Answer: %d.%d\n", 28, m - 1);
                    break;
                default:
                    printf("Answer: %d.%d\n", 30, m - 1);
                    break;
            }

        } else {
            printf("Answer: %d.%d\n", d - 1, m);
        }
    }

    return 0;
}