#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "libs.h"
#include "/home/anton/C/home/STL2/src/STL.h"

int main() {

    /* Initializing variables */
    auto FILE *fin1 = fopen("input.txt", "r"), *fin2 = fopen("input2.txt", "r");
    auto FILE *fout = stdout;
    auto STL_List a, b, c;
    STL_List_init(&a);
    STL_List_init(&b);
    STL_List_init(&c);

    /* I/O flow */
    if (fin1 == NULL || fin2 == NULL) {
        return -1;
    }
    if (fin1 == stdin) {
        printf("----\t\tPolynomial #1\t\t----\n");
    }
    read_polynomials(&a, fin1);
    if (fin2 == stdin) {
        printf("----\t\tPolynomial #2\t\t----\n");
    }
    read_polynomials(&b, fin2);
    fflush(stdout);

    printf("----\t\tPolynomial #1\t\t----\n");
    print_polynomials(&a, fout);
    printf("----\t\tPolynomial #2\t\t----\n");
    print_polynomials(&b, fout);
    fflush(stdout);

    /* Main part */
    STL_List_clear(&c);
    add_polynomials(&c, &a, &b);
    printf("\n----\t\t#1 + #2\t\t----\n");
    print_polynomials(&c, fout);
    fflush(stdout);

    STL_List_clear(&c);
    multiply_polynomials(&c, &a, &b);
    printf("\n----\t\t#1 * #2\t\t----\n");
    print_polynomials(&c, fout);
    fflush(stdout);

    STL_List_delete(&a);

    /* Returning value */
    return 0;
}