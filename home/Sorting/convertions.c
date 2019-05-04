#include "sorting.h"

/* String to ... */
double atof(const char *n) {

    /* Initializing variables */
    auto int a = 0, b = 0, sign = 1;
    auto bool comma = false;

    /* Main part */
    while (*n) {
        if (*n == '-') {
            sign = -1;
        } else if (*n == '+') {
            sign = 1;
        } else if (*n == '.') {
            comma = true;
        }
        if (isdigit(*n)) {
            if (comma) {
                b *= 10;
                b += *n - '0';
            } else {
                a *= 10;
                a += *n - '0';
            }
        }
        ++n;
    }

    a *= sign;

    /* Returning value */
    return (b == 0) ? (double) a : (double) a / (double) b;
}

int atoi(const char *n) {

    /* Initializing variables */
    auto int a = 0, sign = 1;

    /* Main part */
    while (*n) {
        if (*n == '-') {
            sign = -1;
            continue;
        } else if (*n == '+') {
            sign = 1;
            continue;
        }

        if (isdigit(*n)) {
            a *= 10;
            a += *n - '0';
            ++n;
        } else {
            break;
        }
    }

    /* Returning value */
    return a * sign;
}