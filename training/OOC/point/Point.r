#ifndef POINT_R
#define POINT_R

/* Header inclusion */
#include <stdio.h>

/* Type definition */
struct Point {
	const void *class;
	int x;
	int y;
};

/* Macro definitions */
#define x(p) (((const struct Point *)(p))-> x)
#define y(p) (((const struct Point *)(p))-> y)

#endif