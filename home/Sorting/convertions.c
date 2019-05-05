/*
Sorting library — free shared library, that contains a few general-purpose sorting algorithms
Copyright © Pavlovsky Anton, 2019

This file is part of Sorting library.

Sorting library is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Sorting library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Sorting library. If not, see <https://www.gnu.org/licenses/>.
*/

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