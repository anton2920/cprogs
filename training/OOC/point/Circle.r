#ifndef CIRCLE_R
#define CIRCLE_R

/* Header inclusion */
#include <stdio.h>
#include "Point.r"

/* Type definition */
struct Circle {
	const struct Point _;
	int rad;
};

#endif