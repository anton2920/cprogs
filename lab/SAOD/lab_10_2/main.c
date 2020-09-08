#include <stdio.h>
#include <stdlib.h>

#include "libs.h"

main() {

    /* Initializing variables */
    auto FILE *fp = fopen("input.txt", "r");
    auto struct DataItem d;

    /* VarCheck */
    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    /* Main part */
    for ( ; !feof(fp); ) {
        fscanf(fp, "%s %lu", d.data, &d.key);
        insert(d.key, d.data);
    }

    printf("Type a phone number: ");
    scanf("%lu", &d.key);

    d = *search(d.key);

    /* Final output */
    printf("Number corresponds to %s\n", d.data);
}