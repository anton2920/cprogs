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

#ifndef SORTING_LIBRARY_H
#define SORTING_LIBRARY_H

/* Macros */
#define isdigit(n) ((n >= '0' && n <= '9') ? 1 : 0)
#define GREATER (1)
#define LESS (-1)
#define EQUALS (0)
#ifndef NULL
    #define NULL (0)
#endif

#define SWAP(a, b, size)                \
    do {                                \
        int __size = (size);            \
        char *__a = (a), *__b = (b);    \
        do {                            \
            char __tmp = *__a;          \
            *__a++ = *__b;              \
            *__b++ = __tmp;             \
        } while (--__size > 0);         \
    } while (0)

#define COPY(a, b, size)                \
    do {                                \
      int __size = (size);              \
      char *__a = (a), *__b = (b);      \
      do {                              \
          *__a++ = *__b++;              \
      } while (--__size > 0);           \
    } while (0)

#define MIN(a, b) (((a) < (b)) ? a : b)

/* Types */
typedef enum {
    false = 0,
    true = 1
} bool;

/* String to ... */
double atof(const char *); /* ...double */
int atoi(const char *); /* ...integer */

/* Basic functions for compare */
int strcmp(const char *, const char *); /* Compares strings lexicographically */
int numcmp(const char *, const char *); /* Compares strings numerically */
int inumcmp(const void *, const void *); /* Compares integers */
int dnumcmp(const void *, const void *); /* Compares doubles */

/* Miscellaneous routines */


/* Basic sorting algorithms */
void bubble_sort(void *pbase, int n, int nbytes, int (*cmp)(const void *, const void *));
void selection_sort(void *pbase, int n, int nbytes, int (*cmp)(const void *, const void *));
void insertion_sort(void *pbase, int n, int nbytes, int (*cmp)(const void *, const void *));

/* Advanced sorting algorithms */
void quick_sort(void *pbase, int n, int nbytes, int (*cmp)(const void *, const void *));
void merge_sort(void *pbase, int n, int nbytes, int (*cmp)(const void *, const void *));

#endif