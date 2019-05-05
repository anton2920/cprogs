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

/* Miscellaneous routines */
void copy_arr(void *a, const void *b, int n, int nbytes) {

    /* Initializing variables */
    auto int i;

    /* Main part */
    for (i = 0; i < n; ++i) {
        COPY((a + i), (b + i), nbytes);
    }
}