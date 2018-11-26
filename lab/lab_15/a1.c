#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAXSIZE 10
#define NAME    21

/* Structure declaration */
struct goods {
    char name[NAME];
    int price;
};

/* Functions declarations */
void prt_ln(void);
int menu2(int *);
void menu2_5(int *);
void read_key(struct goods *, const int *);
void read_rand(struct goods *, const int *);
int menu(void);
struct goods rand_goods(const int *, const int *, const int *);
int super_rand(int *, int *);
struct goods form_str(const char *, int);
void lstrcpy(const char *, char *);
int in_arr(const int *, const int *, const int *);
void init_arr(int *);
void read_file(struct goods *, const int *);
int menu3(void);
struct goods min(const struct goods *, const int *);
struct goods max(const struct goods *, const int *);
void write_all_scr(const struct goods *, const int *);
void write_scr(const struct goods *, const struct goods *);
void write_file(const struct goods *, const struct goods *);
int menu4(void);

/* Struct: highest and lowest price */
int main() {

    /* Initializing variables */
    struct goods mas[MAXSIZE], min_g, max_g;
    int n;
    char func, func1, func2;
    srand(time(NULL));

    /* Main part */
    while (1) {
        switch (func1 = menu2(&n)) {
            case -1:
                system("clear");
                return 0;
            case 1:
                read_key(mas, &n);
                break;
            case 2:
                read_rand(mas, &n);
                break;
            case 3:
                read_file(mas, &n);
                break;
            default:
                break;
        }

        func2 = menu3();

        /* Main part */
        min_g = min(mas, &n);
        max_g = max(mas, &n);

        /* Final output */
        switch (func2) {
            case -1:
                return 0;
            case 0:
                write_all_scr(mas, &n);
                write_scr(&min_g, &max_g);
                break;
            case 1:
                write_all_scr(mas, &n);
                write_scr(&min_g, &max_g);
                write_file(&min_g, &max_g);
                break;
            default:
                break;
        }
        if (menu4()) {
            continue;
        } else {
            system("clear");
            return 0;
        }
   }
}

/* Functions definitions */
void prt_ln(void) {

    /* Final output */
    printf(" ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
}

int menu2(int *n) {

    /* Initializing variables */
    int func, junk;

    /* I/O flow */
    while (1) {
        printf(" ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n"
"|                                                            |\n"
"|                      >> Lab_15 #16 <<                      |\n"
"|                                                            |\n"
"|  >> Fill in an array of structures with:                   |\n"
"|                                                            |\n"
"|       1) Keyboard-typed goods                              |\n"
"|       2) Pseudo-randomly generated goods                   |\n"
"|       3) Containment of a text file                        |\n"
"|                                                            |\n"
"|       >> Type \"quit\" to terminate this program <<          |\n"
"|                                                            |\n");
        printf("| Answer: ");
        func = getchar();
        prt_ln();
        if (isdigit(func) && func >= '1' && func <= '3') {
            func -= '0';
            if ((junk = getchar()) != '\n') {
                while ((junk = getchar()) != '\n')
                    ;
                printf("| menu: no such command!                                     |\n");
                continue;
            }
            menu2_5(n);
            return func;
        } else if (func == 'q') {
            if ((junk = getchar()) == 'u') {
                if ((junk = getchar()) == 'i') {
                    if ((junk = getchar()) == 't') {
                        if ((junk = getchar()) == '\n') {
                            return -1;
                        } else {
                            printf("| menu: no such command!                                     |\n");
                            while ((junk = getchar()) != '\n')
                                ;
                            continue;
                        }
                    } else {
                        printf("| menu: no such command!                                     |\n");
                        if (junk == '\n') {
                            continue;
                        } else {
                            while ((junk = getchar()) != '\n');
                            continue;
                        }
                    }
                } else {
                    printf("| menu: no such command!                                     |\n");
                    if (junk == '\n') {
                        continue;
                    } else {
                        while ((junk = getchar()) != '\n');
                        continue;
                    }
                }
            } else {
                printf("| menu: no such command!                                     |\n");
                if (junk == '\n') {
                    continue;
                } else {
                    while ((junk = getchar()) != '\n');
                    continue;
                }
            }
        } else {
            printf("| menu: no such command!                                     |\n");
            while ((junk = getchar()) != '\n')
                ;
            continue;
        }
    }

}

void menu2_5(int *n) {

    /* I/O flow */
    printf("| Type the number of elements: ");
    scanf("%d", n);
    prt_ln();
}

void read_key(struct goods *mas, const int *n) {

    /* Initializing variables */
    int i;

    /* Main part */
    for (i = 0; i < *n; ++i, ++mas) {
        printf("| >> %d%s product: ", i, (i == 1) ? "st" : (i == 2) ? "nd" : (i == 3) ? "rd" : "th");
        printf("Type name of a product: ");
        scanf("%s", mas->name);
        printf("| >> %d%s product: ", i, (i == 1) ? "st" : (i == 2) ? "nd" : (i == 3) ? "rd" : "th");
        printf("Type its price: ");
        scanf("%d", &mas->price);
        prt_ln();
    }
}

int menu(void) {
    /* Initializing variables */
    int func, junk;

    /* I/O flow */
    while ((junk = getchar()) != '\n')
        ;
    while (1) {
        printf(" ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n"
"|                                                            |\n"
"|                      >> Lab_15 #16 <<                      |\n"
"|                                                            |\n"
"|  >> Type of pseudo-random:                                 |\n"
"|                                                            |\n"
"|       1) Pseudo-random price                               |\n"
"|       2) Everything is random (up to ten goods)            |\n"
"|                                                            |\n"
"|       >> Type \"quit\" to terminate this program <<          |\n"
"|                                                            |\n");
        printf("| Answer: ");
        func = getchar();
        prt_ln();
        if (isdigit(func) && func >= '1' && func <= '2') {
            func -= '0';
            if ((junk = getchar()) != '\n') {
                while ((junk = getchar()) != '\n')
                    ;
                printf("| menu: no such command!                                     |\n");
                continue;
            }
            return func;
        } else if (func == 'q') {
            if ((junk = getchar()) == 'u') {
                if ((junk = getchar()) == 'i') {
                    if ((junk = getchar()) == 't') {
                        if ((junk = getchar()) == '\n') {
                            return -1;
                        } else {
                            printf("| menu: no such command!                                     |\n");
                            while ((junk = getchar()) != '\n')
                                ;
                            continue;
                        }
                    } else {
                        printf("| menu: no such command!                                     |\n");
                        if (junk == '\n') {
                            continue;
                        } else {
                            while ((junk = getchar()) != '\n');
                            continue;
                        }
                    }
                } else {
                    printf("| menu: no such command!                                     |\n");
                    if (junk == '\n') {
                        continue;
                    } else {
                        while ((junk = getchar()) != '\n');
                        continue;
                    }
                }
            } else {
                printf("| menu: no such command!                                     |\n");
                if (junk == '\n') {
                    continue;
                } else {
                    while ((junk = getchar()) != '\n');
                    continue;
                }
            }
        } else {
            printf("| menu: no such command!                                     |\n");
            while ((junk = getchar()) != '\n')
                ;
            continue;
        }
    }

}

void read_rand(struct goods *mas, const int *n) {

    /* Initializing variables */
    int i, a, b, temp;
    char func, name[NAME];

    /* I/O flow */
    if ((func = menu()) == -1) {
        system("clear");
        exit(0);
    }
    printf("| >> Price range: ");
    printf("Type «left» border: ");
    scanf("%d", &a);
    printf("| >> Price range: ");
    printf("Type «right» border: ");
    scanf("%d", &b);
    if (a > b) {
        temp = a;
        a = b;
        b = temp;
    }
    prt_ln();

    /* Main part */
    if (func == 2) {
        for (i = 0; i < *n; ++i, ++mas) {
            *mas = rand_goods(&i, &a, &b);
        }
    } else if (func == 1) {
        for (i = 0; i < *n; ++i, ++mas) {
            printf("| >> %d%s product: ", i, (i == 1) ? "st" : (i == 2) ? "nd" : (i == 3) ? "rd" : "th");
            printf("Type name of a product: ");
            scanf("%s", name);
            *mas = form_str(name, super_rand(&a, &b));
            printf("| >> %d%s product: ", i, (i == 1) ? "st" : (i == 2) ? "nd" : (i == 3) ? "rd" : "th");
            printf("Its price: %d\n", mas->price);
            prt_ln();
        }
    }
}

struct goods rand_goods(const int *i, const int *a, const int *b) {

    /* Initializing variables */
    struct goods temp;
    int rand_ch;
    static int arr[10];
    char *name;

    /* Main part */
    if (!*i) {
        init_arr(arr);
    }
    while (1) {
        rand_ch = (rand() % (10)) + 1;
        if (!in_arr(arr, &rand_ch, i)) {
            *(arr + *i) = rand_ch;
            break;
        }
    }
    switch (rand_ch) {
        case 1:
            name = "TV";
            break;
        case 2:
            name = "Phone";
            break;
        case 3:
            name = "Computer";
            break;
        case 4:
            name = "Fridge";
            break;
        case 5:
            name = "Oven";
            break;
        case 6:
            name = "Heater";
            break;
        case 7:
            name = "Shirt";
            break;
        case 8:
            name = "Calendar";
            break;
        case 9:
            name = "Calculator";
            break;
        case 10:
            name = "Laptop";
            break;
        default:
            break;
    }

    temp = form_str(name, super_rand(a ,b));

    /* Returning value */
    return temp;

}

int super_rand(int *a, int *b) {

    /* Initializing variables */
    int num;

    /* Main part */
    num = (rand() % (*b - *a + 1)) + *a;
    num /= 10;
    num -= 1;
    num = (num >= 0) ? num : -num;
    num *= 10;
    num += 9;

    /* Returning value */
    return num;
}

struct goods form_str(const char *name, int price) {

    /* Initializing variables */
    struct goods temp;

    /* Main part */
    lstrcpy(name, temp.name);
    temp.price = price;

    /* Returning value */
    return temp;
}

void lstrcpy(const char *s, char *t) {

    /* Copies from s to t */

    /* Main part */
    while ((*t++ = *s++))
        ;
}

int in_arr(const int *arr, const int *rand_ch, const int *i) {

    /* Initializing variables */
    int j;

    /* Main part */
    for (j = 0; j < *i; ++j) {
        if (*rand_ch == *(arr + j)) {
            return 1;
        }
    }

    /* Returning value */
    return 0;
}

void init_arr(int *arr) {

    /* Initializing variables */
    int i;

    /* Main part */
    for (i = 0; i < 10; ++i) {
        *(arr + i) = 0;
    }
}

void read_file(struct goods *mas, const int *n) {

    /* Initializing variables */
    int i;
    FILE *inputs;
    char name[NAME];

    /* Main part */
    do {
        printf("| Type the name of a text file: ");
        scanf("%s", name);
    } while (!(inputs = fopen(name, "r")));
    for (i = 0; i < *n; ++i, ++mas) {
        fscanf(inputs, "%s %i", mas->name, &mas->price);
    }
    fclose(inputs);

    /* Final output */
    prt_ln();
}

int menu3(void) {

    /* Initializing variables*/
    int func, junk;

    /* I/O flow */
    while ((junk = getchar()) != '\n')
        ;
    while (1) {
        printf(" ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n"
"|                                                            |\n"
"|                      >> Lab_15 #16 <<                      |\n"
"|                                                            |\n"
"|  >> Occasional output?                                     |\n"
"|                                                            |\n"
"|       0) Screen only                                       |\n"
"|       1) To the text file                                  |\n"
"|                                                            |\n"
"|       >> Type \"quit\" to terminate this program <<          |\n"
"|                                                            |\n");
        printf("| Answer: ");
        func = getchar();
        prt_ln();
        if (isdigit(func) && func >= '0' && func <= '1') {
            func -= '0';
            if ((junk = getchar()) != '\n') {
                while ((junk = getchar()) != '\n');
                printf("| menu: no such command!                                     |\n");
                continue;
            }
            return func;
        } else if (func == 'q') {
            if ((junk = getchar()) == 'u') {
                if ((junk = getchar()) == 'i') {
                    if ((junk = getchar()) == 't') {
                        if ((junk = getchar()) == '\n') {
                            return -1;
                        } else {
                            printf("| menu: no such command!                                     |\n");
                            while ((junk = getchar()) != '\n')
                                ;
                            continue;
                        }
                    } else {
                        printf("| menu: no such command!                                     |\n");
                        if (junk == '\n') {
                            continue;
                        } else {
                            while ((junk = getchar()) != '\n');
                            continue;
                        }
                    }
                } else {
                    printf("| menu: no such command!                                     |\n");
                    if (junk == '\n') {
                        continue;
                    } else {
                        while ((junk = getchar()) != '\n');
                        continue;
                    }
                }
            } else {
                printf("| menu: no such command!                                     |\n");
                if (junk == '\n') {
                    continue;
                } else {
                    while ((junk = getchar()) != '\n');
                    continue;
                }
            }
        } else {
            printf("| menu: no such command!                                     |\n");
            while ((junk = getchar()) != '\n');
            continue;
        }
    }
}

struct goods min(const struct goods *mas, const int *n) {

    /* Initializing variables */
    int i;
    struct goods min = *mas++;

    /* Main part */
    for (i = 1; i < *n; ++i, ++mas) {
        if (mas->price < min.price) {
            min = *mas;
        }
    }

    /* Returning value */
    return min;
}

struct goods max(const struct goods *mas, const int *n) {

    /* Initializing variables */
    int i;
    struct goods max = *mas;

    /* Main part */
    for (i = 0; i < *n; ++i, ++mas) {
        if (mas->price > max.price) {
            max = *mas;
        }
    }

    /* Returning value */
    return max;
}

void write_all_scr(const struct goods *mas, const int *n) {

    /* Initializing variables */
    int i;

    /* I/O flow */
    printf("| Full structure: ");
    for (i = 0; i < *n; ++i, ++mas) {
        printf("{ %s, %d } ", mas->name, mas->price);
    }

    /* Final output */
    printf("\n");
    prt_ln();
}

void write_scr(const struct goods *min, const struct goods *max) {

    /* I/O flow */
    printf("| The lowest price: { %s, %d }\n", min->name, min->price);
    printf("| The highest price: { %s, %d }\n", max->name, max->price);

    /* Final output */
    prt_ln();
}

void write_file(const struct goods *min, const struct goods *max) {

    /* Initializing variables */
    int i;
    FILE *outputs;

    /* Main part */
    outputs = fopen("a1out.txt", "w");
    if (outputs == NULL) {
        printf("| txt: error, couldn't open file!                            |\n");
        prt_ln();
        return;
    }
    fprintf(outputs, "%s\t%d\n", min->name, min->price);
    fprintf(outputs, "%s\t%d", max->name, max->price);
    fclose(outputs);

    /* Final output */
    printf("| txt: the information was stored successfully!              |\n");
    prt_ln();
}

int menu4(void) {

    /* Initializing variables */
    int func, junk;

    /* I/O flow */
    while (1) {
        printf("| Continue? [y/N]: ");
        switch ((func = getchar())) {
            case 'y': case 'Y':
                if ((junk = getchar()) != '\n') {
                    while ((junk = getchar()) != '\n')
                        ;
                    prt_ln();
                    continue;
                }
                prt_ln();
                return 1;
            case 'n': case 'N': case '\n':
                if (func == 'n' || func == 'N') {
                    if ((junk = getchar()) != '\n') {
                        while ((junk = getchar()) != '\n')
                            ;
                        prt_ln();
                        continue;
                    }
                }
                prt_ln();
                return 0;
            default:
                while ((junk = getchar()) != '\n')
                    ;
                prt_ln();
                continue;
        }
    }
}