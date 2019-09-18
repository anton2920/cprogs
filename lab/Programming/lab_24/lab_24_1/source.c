#include "source.h"

bool check_args(int argc, char *argv[]) {

    /* VarCheck */
    if (argc == 2) {
        if (**(argv + 1) == '1' || **(argv + 1) == '2') {
            return true;
        } else {
            fprintf(stderr, "Error! No such argument!\n");
        }
    } else if (argc == 1) {
        fprintf(stderr, "Error! No arguments were found!\n");
        return false;
    } else {
        fprintf(stderr, "Error! Too many arguments!\n");
        return false;
    }
}

bool create_array(struct array *array1) {

    /* Initializing variables */
    int i;
    size_t n_bytes = (size_t) array1->rows * array1->columns * array1->size_of_elem;

    switch (array1->t) {
        case int_p:
            if ((array1->mas.i_p = (int *) malloc(n_bytes)) != NULL) {
                array1->t = int_p;
                return true;
            }
        case double_p:
            if ((array1->mas.d_p = (double *) malloc(n_bytes)) != NULL) {
                array1->t = double_p;
                return true;
            }
        case char_p:
            if ((array1->mas.c_p = (char *) malloc(n_bytes)) != NULL) {
                array1->t = char_p;
                return true;
            }
        case void_p:
            if ((array1->mas.vd_p = malloc(n_bytes)) != NULL) {
                array1->t = void_p;
                return true;
            }
        case int_pp:
            if ((array1->mas.i_pp = (int **) malloc(array1->rows * sizeof(int *))) != NULL) {
                for (i = 0; i < array1->rows; ++i) {
                    if ((array1->mas.i_pp[i] = (int *) malloc(array1->columns * sizeof(int))) == NULL) {
                        return false;
                    }
                }
            }
            return true;
        case double_pp:
            if ((array1->mas.d_pp = (double **) malloc(array1->rows * sizeof(double *))) != NULL) {
                for (i = 0; i < array1->rows; ++i) {
                    if ((array1->mas.d_pp[i] = (double *) malloc(array1->columns * sizeof(double))) == NULL) {
                        return false;
                    }
                }
            }
            return true;
        case char_pp:
            if ((array1->mas.c_pp = (char **) malloc(array1->rows * sizeof(char *))) != NULL) {
                for (i = 0; i < array1->rows; ++i) {
                    if ((array1->mas.c_pp[i] = (char *) malloc(array1->columns * sizeof(char))) == NULL) {
                        return false;
                    }
                }
            }
            return true;
        case void_pp:
            if ((array1->mas.vd_pp = (void **) malloc(array1->rows * sizeof(void *))) != NULL) {
                for (i = 0; i < array1->rows; ++i) {
                    if ((array1->mas.vd_pp[i] = malloc(array1->columns * array1->size_of_elem)) == NULL) {
                        return false;
                    }
                }
            }
            return true;
        default:
            break;
    }

    return false;

}

void set_ts(int t, struct array *array1, int way) {

    /* Main part */
    if (way == 1) {
        switch (t) {
            case 1:
                array1->t = int_p;
                array1->size_of_elem = sizeof(int);
                break;
            case 2:
                array1->t = double_p;
                array1->size_of_elem = sizeof(double);
                break;
            case 3:
                array1->t = char_p;
                array1->size_of_elem = sizeof(char);
                break;
            case 4:
                array1->t = void_p;
                break;
            default:
                break;
        }
    } else {
        switch (t) {
            case 1:
                array1->t = int_pp;
                array1->size_of_elem = sizeof(int);
                break;
            case 2:
                array1->t = double_p;
                array1->size_of_elem = sizeof(double);
                break;
            case 3:
                array1->t = char_p;
                array1->size_of_elem = sizeof(char);
                break;
            case 4:
                array1->t = void_p;
                break;
            default:
                break;
        }
    }
}

void input_param(struct array *array1, int way) {
    
    /* Initializing variables */
    int answer;
    
    /* I/O flow && VarCheck */
    do {
        printf("Type the number of rows: ");
        scanf("%d", &array1->rows);
    } while (array1->rows <= 0);

    do {
        printf("Type the number of columns: ");
        scanf("%d", &array1->columns);
    } while (array1->columns <= 0);

    do {
        printf("Choose an array type: \n"
                       "\t1) Integer\n"
                       "\t2) Double-precision floating-point\n"
                       "\t3) Characters\n"
                       "\t4) Unknown (raw bytes)\n");
        printf("Answer: ");
        scanf("%d", &answer);
    } while (answer > 4 || answer < 1);

    if (answer == 4) {
        do {
            printf("Type the size of an array element: ");
            scanf("%d", &array1->size_of_elem);
        } while (array1->size_of_elem <= 0);
    }
    set_ts(answer, array1, way);
}

void input_array(struct array *array1) {

    /* Initializing variables */
    register int i, j;

    /* I/O flow */
    putchar(0xA);
    for (i = 0; i < array1->rows; ++i) {
        for (j = 0; j < array1->columns; ++j) {
            printf("Type %d%s element in the %d%s row: ", j,
                   (j == 1) ? "st" : (j == 2) ? "nd" : (j == 3) ? "rd" : "th", i,
                   (i == 1) ? "st" : (i == 2) ? "nd" : (i == 3) ? "rd" : "th");
            switch (array1->t) {
                case int_p:
                    scanf("%d", &array1->mas.i_p[i * array1->columns + j]);
                    break;
                case double_p:
                    scanf("%lf", &array1->mas.d_p[i * array1->columns + j]);
                    break;
                case char_p:
                    getchar();
                    scanf("%c", &array1->mas.c_p[i * array1->columns + j]);
                    break;
                case void_p:
                    do {
                        getchar();
                    } while (!fread(array1->mas.vd_p + (i * array1->columns + j) * array1->size_of_elem, array1->size_of_elem, 1, stdin));
                    break;
                case int_pp:
                    scanf("%d", &array1->mas.i_pp[i][j]);
                    break;
                case double_pp:
                    scanf("%lf", &array1->mas.d_pp[i][j]);
                    break;
                case char_pp:
                    getchar();
                    scanf("%c", &array1->mas.c_pp[i][j]);
                    break;
                case void_pp:
                    do {
                        getchar();
                    } while (!fread(array1->mas.vd_pp[i] + j * array1->size_of_elem, array1->size_of_elem, 1, stdin));
                    break;
                default:
                    break;
            }
        }
        printf("\n");
    }
}

void print_array(struct array *array1) {

    /* Initializing variables */
    register int i, j;
    char sp = '\t';
    auto size_t temp;

    /* I/O flow */
    printf("Array: \n");
    for (i = 0; i < array1->rows; ++i) {
        for (j = 0; j < array1->columns; ++j) {
            switch (array1->t) {
                case int_p:
                    printf("%d\t", array1->mas.i_p[i * array1->columns + j]);
                    break;
                case double_p:
                    printf("%.2lf\t", array1->mas.d_p[i * array1->columns + j]);
                    break;
                case char_p:
                    printf("\'%c\'\t", array1->mas.c_p[i * array1->columns + j]);
                    break;
                case void_p:
                    do {
                        temp = fwrite(array1->mas.vd_p + (i * array1->columns + j) * array1->size_of_elem, array1->size_of_elem, 1, stdout);
                        fwrite(&sp, sizeof(char), 1, stdout);
                    } while (!temp);
                    break;
                case int_pp:
                    printf("%d\t", array1->mas.i_pp[i][j]);
                    break;
                case double_pp:
                   printf("%.2lf\t", array1->mas.d_pp[i][j]);
                    break;
                case char_pp:
                    printf("\'%c\'\t", array1->mas.c_pp[i][j]);
                    break;
                case void_pp:
                    do {
                        temp = fwrite(array1->mas.vd_pp[i] + j * array1->size_of_elem, array1->size_of_elem, 1, stdout);
                        fwrite(&sp, sizeof(char), 1, stdout);
                    } while (!temp);
                    break;
                default:
                    break;
            }
        }
        printf("\n");
    }
}

void sum_of_row(struct array *array1) {

    /* Initializing variables */
    register int i, j;
    union sum res[array1->rows], max_res;

    /* Main part */
    switch (array1->t) {
        case int_p: case int_pp:
            for (i = 0; i < array1->rows; ++i) {
                res[i].i_sum = 0;
            }
            break;
        case double_p: case double_pp:
            for (i = 0; i < array1->rows; ++i) {
                res[i].d_sum = 0;
            }
            break;
        case char_p: case char_pp:
            for (i = 0; i < array1->rows; ++i) {
                res[i].c_sum = 0;
            }
            break;
        default:
            return;
    }
    putchar(0xA);

    for (i = 0; i < array1->rows; ++i) {
        for (j = 0; j < array1->columns; ++j) {
            switch (array1->t) {
                case int_p:
                    res[i].i_sum += array1->mas.i_p[i * array1->columns + j];
                    break;
                case double_p:
                    res[i].d_sum += array1->mas.d_p[i * array1->columns + j];
                    break;
                case char_p:
                    res[i].c_sum += (int) array1->mas.c_p[i * array1->columns + j];
                    break;
                case int_pp:
                    res[i].i_sum += array1->mas.i_pp[i][j];
                    break;
                case double_pp:
                    res[i].d_sum += array1->mas.d_pp[i][j];
                    break;
                case char_pp:
                    res[i].c_sum += (int) array1->mas.c_pp[i][j];
                    break;
                default:
                    break;
            }
        }

        switch (array1->t) {
            case int_p: case int_pp:
                max_res.i_sum = (max_res.i_sum > res[i].i_sum) ? max_res.i_sum : res[i].i_sum;
                printf("Sum of %d%s row: %d\n", i, (i == 1) ? "st" : (i == 2) ? "nd" : (i == 3) ? "rd" : "th",
                       res[i].i_sum);
                break;
            case double_p: case double_pp:
                max_res.d_sum = (max_res.d_sum > res[i].d_sum) ? max_res.d_sum : res[i].d_sum;
                printf("Sum of %d%s row: %.2lf\n", i, (i == 1) ? "st" : (i == 2) ? "nd" : (i == 3) ? "rd" : "th",
                       res[i].d_sum);
                break;
            case char_p: case char_pp:
                max_res.c_sum = (max_res.c_sum > res[i].c_sum) ? max_res.c_sum : res[i].c_sum;
                printf("Sum of %d%s row: %d\n", i, (i == 1) ? "st" : (i == 2) ? "nd" : (i == 3) ? "rd" : "th",
                       res[i].c_sum);
                break;
            default:
                break;
        }
    }

    switch (array1->t) {
        case int_p: case int_pp:
            printf("Max sum: %d\n", max_res.i_sum);
            break;
        case double_p: case double_pp:
            printf("Max sum: %.2lf\n", max_res.d_sum);
            break;
        case char_p: case char_pp:
            printf("Max sum: %d\n", max_res.c_sum);
            break;
        default:
            break;
    }
}

void delete_array(struct array *array1) {

    /* Initializing variables */
    register int i;

    /* Main part */
    switch (array1->t) {
        case int_p:
            free(array1->mas.i_p);
            break;
        case double_p:
            free(array1->mas.d_p);
            break;
        case char_p:
            free(array1->mas.c_p);
            break;
        case void_p:
            free(array1->mas.vd_p);
            break;
        case int_pp:
            for (i = 0; i < array1->columns; ++i) {
                free(array1->mas.i_pp[i]);
            }
            free(array1->mas.i_pp);
            break;
        case double_pp:
            for (i = 0; i < array1->columns; ++i) {
                free(array1->mas.d_pp[i]);
            }
            free(array1->mas.d_pp);
            break;
        case char_pp:
            for (i = 0; i < array1->columns; ++i) {
                free(array1->mas.d_pp[i]);
            }
            free(array1->mas.c_pp);
            break;
        case void_pp:
            for (i = 0; i < array1->columns; ++i) {
                free(array1->mas.vd_pp[i]);
            }
            free(array1->mas.vs_pp);
            break;
        default:
            break;
    }
}

void arr_err(void) {

    /* Final output */
    fprintf(stderr, "Error with allocating memory!\n");
}