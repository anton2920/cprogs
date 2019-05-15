#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

/* Some macros */
#define __FALSE (0)
#define __TRUE (1)
#define TXT_EXT (".txt")
#define BIN_EXT (".bin")
#define ENDING(x) ((x == 1) ? "st" : (x == 2) ? "nd" : (x == 3) ? "rd" : "th")
#define FN_SIZE (20)

/* With C99 language standard "bool" type is already presented.
 * But I've used C89 (ANSI C) standard, so it's better to create your own data type.
 * As you see, I've implemented backward compatibility with further standards
 */
typedef enum {
    __false = __FALSE,
    __true = __TRUE
} __bool;

/* By task, you have to implement several ways of I/O an array. This enum makes it more handy */
typedef enum file_type {
    keyboard,
    text_f,
    bin_f,
    screen
} f_type;

/* Assume, that array elements are integers. It's possible to modify program to work with any data type.
 * It can be made using either unions or (void *)
 */
typedef struct array {
    int m; /* Number of rows */
    int **p; /* Pointer to rows vector */
    int t; /* Terminal "character" (integer value) */
} Array;

/* Some function declarations */
void prt_ln(void);
int menu_read(void);
int menu_write(void);
__bool menu_wwrite(void);
__bool create_array(struct array *);
void occ_input(struct array *);
__bool read_array(struct array *, enum file_type);
void write_array(const struct array *, enum file_type);
void delete_array(struct array *);
__bool continue_menu(void);

int main(void) {

    /* Initializing variables */
    auto int func;
    auto struct array mas = {};

    /* I/O flow */
    do {
        func = menu_read();
        switch (func) {
            case 1:
                if (read_array(&mas, keyboard) == __false) {
                    return -1;
                }
                break;
            case 2:
                if (read_array(&mas, text_f) == __false) {
                    return -2;
                }
                break;
            case 3:
                if (read_array(&mas, bin_f) == __false) {
                    return -3;
                }
            default:
                break;
        }

        func = menu_wwrite();
        if (func == __true) {
            func = menu_write();
            switch (func) {
                case 0:
                    write_array(&mas, screen);
                    break;
                case 1:
                    write_array(&mas, screen);
                    write_array(&mas, text_f);
                    break;
                case 2:
                    write_array(&mas, screen);
                    write_array(&mas, bin_f);
                    break;
                case 3:
                    write_array(&mas, screen);
                    write_array(&mas, text_f);
                    write_array(&mas, bin_f);
                default:
                    break;
            }
        }

        delete_array(&mas);

    } while (continue_menu() == __true);

    /* Final output */
    prt_ln();

    /* Returning value */
    return 0;
}

void prt_ln(void) {

    /* Final output */
    printf(" ------------------------------------------------------------\n");
}

int menu_read(void) {

    /* Initializing variables */
    auto int func;

    /* I/O flow */
    while (1) {
        printf(" ------------------------------------------------------------\n"
               "|                                                            |\n"
               "|                        >> Lab_25 <<                        |\n"
               "|                                                            |\n"
               "|    >> Read from...                                         |\n"
               "|                                                            |\n"
               "|       1) Keyboard                                          |\n"
               "|       2) Text file                                         |\n"
               "|       3) Binary file                                       |\n"
               "|                                                            |\n");
        printf("| Answer: ");
        func = getchar();
        prt_ln();
        if (func >= '1' && func <= '3') {
            return func - '0';
        } else if (func != 0xA) {
            while (getchar() != '\n')
                ;
        }
        printf("| menu: no such command!                                     |\n");
    }
}

int menu_write(void) {

    /* Initializing variables */
    auto int func;

    /* I/O flow */
    while (1) {
        printf(" ------------------------------------------------------------\n"
               "|                                                            |\n"
               "|                        >> Lab_25 <<                        |\n"
               "|                                                            |\n"
               "|    >> Occasional output...                                 |\n"
               "|                                                            |\n"
               "|       0) Screen only                                       |\n"
               "|       1) Text file                                         |\n"
               "|       2) Binary file                                       |\n"
               "|       3) Text and Binary files                             |\n"
               "|                                                            |\n");
        printf("| Answer: ");
        func = getchar();
        prt_ln();
        if (func >= '0' && func <= '3') {
            return func - '0';
        } else if (func != 0xA) {
            while (getchar() != '\n')
                ;
        }
        printf("| menu: no such command!                                     |\n");
    }
}

__bool menu_wwrite(void) {

    /* Initializing variables */
    auto int func;

    /* I/O flow */
    while (getchar() != '\n')
        ;

    printf("| Would you like to output your array? [y/N]: ");
    func = getchar();

    if (func == 0xA) {
        return __false;
    }

    while (getchar() != '\n')
        ;

    if (func == 'y' || func == 'Y') {
        return __true;
    } else if (func == 'n' || func == 'N') {
        return __false;
    }

    /* Final output */
    prt_ln();
}

__bool create_array(struct array *mas) {

    /* Main part */
    if ((mas->p = (int **) malloc(mas->m * sizeof(int *))) != NULL) {
        return __true;
    }
    return __false;
}

void occ_input(struct array *mas) {

    /* I/O flow */
    do {
        printf("| Type the number of rows: ");
        scanf("%d", &mas->m);
    } while (mas->m <= 0 || mas->m >= INT_MAX);

    printf("| Type the \"terminal\" character: ");
    scanf("%d", &mas->t);
}

__bool read_array(struct array *mas, enum file_type t) {

    /* Initializing variables */
    auto FILE *fp;
    register int i, j;
    auto char fn[FN_SIZE];
    auto __bool ext_ch;
    auto int len;

    /* Main part */
    switch (t) {
        case keyboard:
            occ_input(mas);
            prt_ln();

            create_array(mas);
            for (i = 0; i < mas->m; ++i) {
                if ((mas->p[i] = (int *) malloc(INT_MAX)) == NULL) {
                    return __false;
                }
                j = -1;
                do {
                    ++j;
                    printf("| Type %d%s element of %d%s row: ", j, ENDING(j), i, ENDING(i));
                    scanf("%d", &mas->p[i][j]);
                } while (mas->p[i][j] != mas->t);
                if ((mas->p[i] = (int *) realloc(mas->p[i], j * sizeof(int))) == NULL) {
                    return __false;
                }
                prt_ln();
            }
            break;
        case text_f:
            do {
                printf("| Type name of the text file (must be ended with \".txt\"): ");
                scanf("%s", fn);
                prt_ln();
                len = strlen(fn);
                if (!strcmp(fn + (len - 4), TXT_EXT)) {
                    ext_ch = __true;
                } else {
                    ext_ch = __false;
                    continue;
                }

                if ((fp = fopen(fn, "r")) == NULL) {
                    printf("| txt: couldn't open file                                    |\n");
                    prt_ln();
                    ext_ch = __false;
                }
            } while (ext_ch == __false);


            fscanf(fp, "%d %d", &mas->m, &mas->t);

            create_array(mas);

            for (i = 0; i < mas->m; ++i) {
                if ((mas->p[i] = (int *) malloc(INT_MAX)) == NULL) {
                    return __false;
                }
                j = -1;
                do {
                    ++j;
                    fscanf(fp, "%d", &mas->p[i][j]);
                } while (mas->p[i][j] != mas->t);
                if ((mas->p[i] = (int *) realloc(mas->p[i], j * sizeof(int))) == NULL) {
                    return __false;
                }
            }

            fclose(fp);

            printf("| txt: array was read successfully                           |\n");
            prt_ln();
            break;

        case bin_f:
            do {
                printf("| Type name of the text file (must be ended with \".bin\"): ");
                scanf("%s", fn);
                prt_ln();
                len = strlen(fn);
                if (!strcmp(fn + (len - 4), BIN_EXT)) {
                    ext_ch = __true;
                } else {
                    ext_ch = __false;
                    continue;
                }

                if ((fp = fopen(fn, "rb")) == NULL) {
                    printf("| bin: couldn't open file                                    |\n");
                    prt_ln();
                    ext_ch = __false;
                }
            } while (ext_ch == __false);

            fread((void *) &mas->m, sizeof(int), 1, fp);
            fread((void *) &mas->t, sizeof(int), 1, fp);

            create_array(mas);

            for (i = 0; i < mas->m; ++i) {
                if ((mas->p[i] = (int *) malloc(INT_MAX)) == NULL) {
                    return __false;
                }
                j = -1;
                do {
                    ++j;
                    fread((void *) &mas->p[i][j], sizeof(int), 1, fp);
                } while (mas->p[i][j] != mas->t);
                if ((mas->p[i] = (int *) realloc(mas->p[i], j * sizeof(int))) == NULL) {
                    return __false;
                }
            }

            fclose(fp);

            printf("| bin: array was read successfully                           |\n");
            prt_ln();
            break;
        default:
            break;
    }

    /* Returning value */
    return __true;
}

void write_array(const struct array *mas, enum file_type t) {

    /* Initializing variables */
    register int i, j;
    auto FILE *fp;
    auto char fn[FN_SIZE];
    auto int len;
    auto __bool ext_ch;

    /* Main part */
    switch (t) {
        case screen:
            printf("| Array:                                                     |\n");
            prt_ln();
            for (i = 0; i < mas->m; ++i) {
                j = -1;
                putchar('|');
                do {
                    ++j;
                    printf("%3d", mas->p[i][j]);
                } while (mas->p[i][j] != mas->t);

                putchar(0xA);
            }

            prt_ln();
            break;
        case text_f:
            do {
                printf("| Type name of the text file (must be ended with \".txt\"): ");
                scanf("%s", fn);
                prt_ln();
                len = strlen(fn);
                if (!strcmp(fn + (len - 4), TXT_EXT)) {
                    ext_ch = __true;
                } else {
                    ext_ch = __false;
                    continue;
                }

                if ((fp = fopen(fn, "w")) == NULL) {
                    printf("| txt: couldn't open file                                    |\n");
                    prt_ln();
                    ext_ch = __false;
                }
            } while (ext_ch == __false);

            fprintf(fp, "%d %d\n", mas->m, mas->t);

            for (i = 0; i < mas->m; ++i) {
                j = -1;
                do {
                    ++j;
                    fprintf(fp, "%d ", mas->p[i][j]);
                } while (mas->p[i][j] != mas->t);

                putc(0xA, fp);
            }

            printf("| txt: array was written successfully                        |\n");
            prt_ln();
            break;

        case bin_f:
            do {
                printf("| Type name of the text file (must be ended with \".bin\"): ");
                scanf("%s", fn);
                prt_ln();
                len = strlen(fn);
                if (!strcmp(fn + (len - 4), BIN_EXT)) {
                    ext_ch = __true;
                } else {
                    ext_ch = __false;
                    continue;
                }

                if ((fp = fopen(fn, "wb")) == NULL) {
                    printf("| bin: couldn't open file                                    |\n");
                    prt_ln();
                    ext_ch = __false;
                }
            } while (ext_ch == __false);

            fwrite((const void *) &mas->m, sizeof(int), 1, fp);
            fwrite((const void *) &mas->t, sizeof(int), 1, fp);

            for (i = 0; i < mas->m; ++i) {
                j = -1;
                do {
                    ++j;
                    fwrite((const void *) &mas->p[i][j], sizeof(int), 1, fp);
                } while (mas->p[i][j] != mas->t);
            }

            printf("| bin: array was written successfully                        |\n");
            prt_ln();
            break;
        default:
            break;
    }

}

void delete_array(struct array *mas) {

    /* Initializing variables */
    register int i;

    /* Main part */
    for (i = 0; i < mas->m; ++i) {
        free(mas->p[i]);
    }

    free(mas->p);
}

__bool continue_menu(void) {

    /* Initializing variables */
    auto int func;

    /* I/O flow */
    while (getchar() != '\n')
        ;

    printf("| Continue? [y/N]: ");
    func = getchar();

    if (func == 0xA) {
        return __false;
    }

    while (getchar() != '\n')
        ;

    if (func == 'y' || func == 'Y') {
        return __true;
    } else if (func == 'n' || func == 'N') {
        return __false;
    }

    /* Final output */
    prt_ln();
}