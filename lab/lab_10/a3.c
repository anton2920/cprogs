#include <stdio.h>
#include <math.h>


/* Functions declaration */
void func1(float x, float y);
void func2(float x, float y);

/* Function displaying for different x's and y's */
main() {

	/* Initializing variables */
	int func;
	float x, y, leftx, rightx, lefty, righty, stepx, stepy;

	/* I/O flow && VarCheck */
	do {
		printf("Which function you want to work with [1/2]: ");
		scanf("%d", &func);
	} while (func != 1 && func != 2);
	printf("Type left border of X: ");
	scanf("%f", &leftx);
	do {
		printf("Type step: ");
		scanf("%f", &stepx);
	} while (stepx == 0);
	do {
		printf("Type right border of X: ");
		scanf("%f", &rightx);
	} while ((stepx > 0) ? rightx < leftx : leftx < rightx);
	printf("Type left border of Y: ");
	scanf("%f", &lefty);
	do {
		printf("Type step: ");
		scanf("%f", &stepy);
	} while (stepy == 0);
	do {
		printf("Type right border of Y: ");
		scanf("%f", &righty);
	} while ((stepy > 0) ? righty < lefty : lefty < righty);

	/* Main part */
	printf("–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
	printf("|\tx\t|\ty\t|\t\tf(x, y)\t\t|\n");
	printf("–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
	for (x = leftx; (stepx > 0) ? x <= rightx : x >= rightx; x += stepx) {
		for (y = lefty; (stepy > 0) ? y <= righty : y >= righty; y += stepy) {
			printf("|\t%.2f\t|\t%.2f\t|\t\t", x, y);
			(func == 1) ? func1(x, y) : func2(x, y);
			printf("\t\t|\n");
			printf("–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
		}
	}
}

void func1(float x, float y) {

	/* Main part */
	if (2 * x + 7 * y != 0) {
		printf("%.2f", (1 / 2 * x + 7 * y) + (x * x));
	} else {
		printf("——");
	}
}

void func2(float x, float y) {

	/* Main part */
	if (x * x - x + 6 >= 0) {
		printf("%.2f", sqrt(x * x - x + 6) * cos(y));
	} else {
		printf("——");
	}
}