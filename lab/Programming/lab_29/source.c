#include "source.h"

bool create_string(char **a) {

    /* Main part */
     if ((*a = (char *) malloc(INT_MAX))) {
        return true;
     }

    /* Returning value */
    return false;
}

void str_err(void) {

    /* Final output */
    fprintf(stderr, "Error! Allocation problems!\n");
}

void read_text(struct string *a) {

    /* Initializing variables */
    register int i;

    /* I/O flow */
    puts("Type text [Ctrl + D (i.e EOF) to finish]: ");
    for (i = 0; (a->str[i] = (char) getchar()) != EOF; ++i)
        ;

    /* Main part */
    a->str[i] = '\0';
    if ((a->str = realloc(a->str, (i + 1) * sizeof(char))) == NULL) {
        exit(1);
    }

}

char read_letter(void) {

    /* Initializing variables */
    char letter;

    /* I/O flow && VarCheck */
    putchar(10);
    do {
        printf("Type letter: ");
        scanf("%c", &letter);
    } while (!isalpha(letter));

    /* Returning value */
    return letter;
}

void find_letter(char letter, struct string *a) {

    /* Initializing variables */
    register int i;

    /* Main part */
    for (i = 0; i < strlen(a->str); ++i) {
        if (a->str[i] == letter) {
            ++a->let_num;
        }
    }
}

void print_let_num(char letter, int num) {

    /* Final output */
    printf("\nThe number of occurrences of \'%c\' = %d\n", letter, num);
}

void delete_string(char *a) {

    /* Main part */
    free(a);
}