#include <stdio.h>

float func1 (float x, float y);
float func2 (float x, float y);

main() {

    /* Initializing variables */
    int func;
    float x, y, leftx, rightx, lefty, righty, stepx, stepy;

    /* I/O flow && VarCheck */
    do {
        printf("Which function you want to work with [1/2]: ");
        scanf("%d", &func);
    } while (func != 1 || func != 2);
    printf("Type left border of X: ");
    scanf("%f", &leftx);
    do {
        printf("Type step: ");
        scanf("&f", &stepx);
    } while (stepx == 0);
    do {
        printf("Type right border of X: ");
        scanf("%f", &rightx);
    } while ((stepx > 0) ? rightx < leftx : leftx < rightx);
    printf("Type left border of Y: ");
    scanf("%f", &lefty);
    do {
        printf("Type step: ");
        scanf("&f", &stepy);
    } while (stepx == 0);
    do {
        printf("Type right border of Y: ");
        scanf("%f", &righty);
    } while ((stepy > 0) ? righty < lefty : lefty < righty);

    /* Main part */

}

void func1 (float x, float y) {

    printf("%.0f%s", (2 * x + 7 * y) > 0 ? 1 / (2 * x + 7 * y) + 3 * y * y, "" : "—");
}