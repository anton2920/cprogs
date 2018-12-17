#include "../headers/lab.h"

void read_key(struct arr *mas) {

    /* Initializing variables */
    int i, j;

    /* I/O flow */
    for (i = 0; i < mas->n; ++i) {
        for (j = 0; j < mas->m; ++j) {
            printf("| Type %d%s element of %d%s row: ", j + 1, (j + 1 == 1) ? "st" : (j + 1 == 2) ? "nd" : (j + 1 == 3) ? "rd" : "th", i + 1, (i + 1 == 1) ? "st" : (i + 1 == 2) ? "nd" : (i + 1 == 3) ? "rd" : "th");
            scanf("%d", &mas->array[i][j]);
        }
    }

    /* Final output */
    prt_ln();
}

void read_rand(struct arr *mas) {

    /* Initializing variables */
    int i, a, b, temp, j;

    /* I/O flow */
    printf("| Type «left» border: ");
    scanf("%d", &a);
    printf("| Type «right» border: ");
    scanf("%d", &b);
    if (a > b) {
        temp = a;
        a = b;
        b = temp;
    }
    prt_ln();

    /* Main part */
    for (i = 0; i < mas->n; ++i) {
        for (j = 0; j < mas->m; ++j) {
            mas->array[i][j] = (rand() % (b - a + 1)) + a;
        }
    }
}

void read_file(struct arr *mas) {

    /* Initializing variables */
    int i, junk, j;
    FILE *inputs;
    char name[NAME];

    /* Main part */
    do {
        printf("| Type the name of a text file: ");
        scanf("%s", name);
        prt_ln();
    } while (!(inputs = fopen(name, "r")));
    for (i = 0; i < mas->n && !feof(inputs); ++i) {
        for (j = 0; j < mas->m && !feof(inputs); ++j) {
            fscanf(inputs, "%d", &mas->array[i][j]);
        }
    }
    fclose(inputs);

    if (i == 1 && j == 1) {
        printf("| txt: fatal! No elements were found!                        |\n");
        mas->n = 0;
        mas->m = 0;
        prt_ln();
        while ((junk = getchar()) != '\n')
            ;
        return;
    } else if (i != mas->n || j != mas->m) {
        printf("| txt: can't resolve more than %d values!\n", i * j);
        mas->n = i;
        mas->m = j;
        printf("| txt: the number of elements is %d now\n", mas->n * mas->m);
        prt_ln();
        return;
    }
}

void read_formula(struct arr *mas) {

    /* Initializing variables */
    int i, j;

    /* Main part */
    for (i = 0; i < mas->n; ++i) {
        for (j = 0; j < mas->m; ++j) {
            mas->array[i][j] = (i == j) ? i * j : (i > j) ? i - 2 * j : 3 * i + j;
        }
    }

    /* Final output */
    ungetc('\n', stdin);
}

void write_scr(const struct arr *mas) {

    /* Initializing variables */
    int i, j;

    /* I/O flow */
    for (i = 0; i < mas->n; ++i) {
        printf("| ");
        for (j = 0; j < mas->m; ++j) {
            printf("%6d", mas->array[i][j]);
        }
        printf("\n");
    }

    /* Final output */
    prt_ln();
}

void write_file(const struct arr *mas) {

    /* Initializing variables */
    int i, j;
    FILE *outputs;

    /* Main part */
    outputs = fopen("a1out.txt", "w");
    if (outputs == NULL) {
        printf("| txt: error, couldn't open file!                            |\n");
        prt_ln();
        return;
    }

    for (i = 0; i < mas->n && !feof(outputs); ++i) {
        for (j = 0; j < mas->m && !feof(outputs); ++j) {
            fprintf(outputs, "%6d", mas->array[i][j]);
        }
        fprintf(outputs, "\n");
    }

    fclose(outputs);

    /* Final output */
    printf("| txt: the information was stored successfully!              |\n");
    prt_ln();
}