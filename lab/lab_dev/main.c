#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAXSIZE 1024
#define NAME    21

/* Structure declaration */
struct goods {
    char name[NAME];
    int price;
};

/* Functions declarations */
void struct_init(struct goods *);
void prt_ln(void);
void no_cmd(void);
int quit_m(void);
int menu2(int *);
void menu2_5(int *);
void read_key(struct goods *, const int *);
int menu(int *);
int menu5(int *);
int rand_over(int *);
void read_rand(struct goods *, int *);
struct goods rand_goods(const int *, const int *, const int *);
int super_rand(const int *, const int *);
struct goods form_str(const char *, int);
void lstrcpy(const char *, char *);
int in_arr(const int *, const int *, const int *);
void init_arr(int *);
void read_file(struct goods *, int *);
int menu3(void);
struct goods min(const struct goods *, const int *);
struct goods max(const struct goods *, const int *);
void write_all_scr(const struct goods *, const int *);
void write_scr(const struct goods *, const struct goods *);
void write_file(const struct goods *, const struct goods *);
int menu4(void);

/* Structure: highest and lowest price */
int main() {

    /* Initializing variables */
    struct goods mas[MAXSIZE], min_g, max_g;
    int n;
    char func, func1, func2;
    srand((unsigned int) time(NULL));

    /* Main part */
    while (1) {
        struct_init(mas);
        func = 0;
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
                func = (!n) ? -2 : 0;
                break;
            default:
                break;
        }

        func2 = (!func) ? menu3() : func;

        /* Main part */
        min_g = min(mas, &n);
        max_g = max(mas, &n);

        /* Final output */
        switch (func2) {
            case -1:
                system("clear");
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
void struct_init(struct goods *mas) {

    /* Initializing variables */
    int i;

    /* Main part */
    for (i = 0; i < MAXSIZE; ++i, ++mas) {
        lstrcpy("", mas->name);
        mas->price = 0;
    }
}

void prt_ln(void) {

    /* Final output */
    printf(" ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
}

void no_cmd(void) {

    /* Final output */
    printf("| menu: no such command!                                     |\n");
}

int quit_m(void) {

    /* Initializing variables */
    int junk;

    /* Main part */
    if ((junk = getchar()) == 'u') {
        if ((junk = getchar()) == 'i') {
            if ((junk = getchar()) == 't') {
                if ((junk = getchar()) == '\n') {
                    return -1;
                } else {
                    no_cmd();
                    while ((junk = getchar()) != '\n')
                        ;
                    return 0;
                }
            } else {
                no_cmd();
                if (junk == '\n') {
                    return 0;
                } else {
                    while ((junk = getchar()) != '\n');
                    return 0;
                }
            }
        } else {
            no_cmd();
            if (junk == '\n') {
                return 0;
            } else {
                while ((junk = getchar()) != '\n');
                return 0;
            }
        }
    } else {
        no_cmd();
        if (junk == '\n') {
            return 0;
        } else {
            while ((junk = getchar()) != '\n');
            return 0;
        }
    }
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
                no_cmd();
                continue;
            }
            menu2_5(n);
            return func;
        } else if (func == 'q') {
            if (quit_m()) {
                return -1;
            } else {
                continue;
            }
        } else {
            no_cmd();
            while ((junk = getchar()) != '\n')
                ;
            continue;
        }
    }

}

void menu2_5(int *n) {

    /* I/O flow && VarCheck*/
    while (1) {
        printf("| Type the number of elements: ");
        scanf("%d", n);
        if (*n > MAXSIZE) {
            prt_ln();
            printf("| menu: error! The number of elements can't be greater than %d\n", MAXSIZE);
            prt_ln();
            continue;
        } else {
            break;
        }
    }
    while (getchar() != '\n')
        ;

    /* Final output */
    prt_ln();
}

void read_key(struct goods *mas, const int *n) {

    /* Initializing variables */
    int i;

    /* Main part */
    for (i = 1; i <= *n; ++i, ++mas) {
        printf("| >> %d%s product: ", i, (i == 1) ? "st" : (i == 2) ? "nd" : (i == 3) ? "rd" : "th");
        printf("Type name of a product: ");
        scanf("%s", mas->name);
        printf("| >> %d%s product: ", i, (i == 1) ? "st" : (i == 2) ? "nd" : (i == 3) ? "rd" : "th");
        printf("Type its price: ");
        scanf("%d", &mas->price);
        prt_ln();
    }
}

int menu(int *n) {
    /* Initializing variables */
    int func, junk;

    /* I/O flow */
    while (1) {
        printf(" ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n"
"|                                                            |\n"
"|                      >> Lab_15 #16 <<                      |\n"
"|                                                            |\n"
"|  >> Type of pseudo-random:                                 |\n"
"|                                                            |\n"
"|       1) Pseudo-random price                               |\n"
"|       2) Everything is random (up to 20 goods)             |\n"
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
                no_cmd();
                continue;
            }
            if (func == 2 && *n > NAME - 1) {
                if (!rand_over(n)) {
                    continue;
                }
            }
            return func;
        } else if (func == 'q') {
            if (quit_m()) {
                return -1;
            } else {
                continue;
            }
        } else {
            no_cmd();
            while ((junk = getchar()) != '\n')
                ;
            continue;
        }
    }

}

int menu5(int *n) {

    /* Initializing variables */
    int func, junk;

    /* Main part */
    while (1) {
        printf("| Do you want to change the number of elements? [Y/n]: ");
        switch ((func = getchar())) {
            case 'y': case 'Y': case '\n':
                if (func == 'y' || func == 'Y') {
                    if ((junk = getchar()) != '\n') {
                        while ((junk = getchar()) != '\n')
                            ;
                        prt_ln();
                        continue;
                    }
                }
                prt_ln();
                return 1;
            case 'n': case 'N':
                if ((junk = getchar()) != '\n') {
                    while ((junk = getchar()) != '\n')
                        ;
                    prt_ln();
                    continue;
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

int rand_over(int *n) {

    /* Initializing variables */
    int junk;

    /* Main part */
    while (1) {
        printf("| random: can't handle more than 20 goods                    |\n");
        prt_ln();
        if ((junk = menu5(n))) {
            menu2_5(n);
            if (*n > NAME - 1) {
                continue;
            } else {
                break;
            }
        } else {
            printf("| random: error! No way to handle more than 20 goods         |\n");
            prt_ln();
            return 0;
        }
    }

    return 1;
}

void read_rand(struct goods *mas, int *n) {

    /* Initializing variables */
    int i, a, b, temp;
    char func, name[NAME];

    /* I/O flow */
    if ((func = menu(n)) == -1) {
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
            printf("| >> %d%s product: ", i + 1, (i == 0) ? "st" : (i == 1) ? "nd" : (i == 2) ? "rd" : "th");
            printf("Type name of a product: ");
            scanf("%s", name);
            *mas = form_str(name, super_rand(&a, &b));
            printf("| >> %d%s product: ", i + 1, (i == 0) ? "st" : (i == 1) ? "nd" : (i == 2) ? "rd" : "th");
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
    char *name[NAME] = { "", "TV", "Phone", "Computer", "Fridge", "Oven", "Heater", "Shirt", "Calendar",
                         "Calculator", "Laptop", "Camera", "Toy", "Blanket", "Pillow", "VHS", "Shelf",
                         "Jacket", "Vase", "Glass", "PVC"};

    /* Main part */
    if (!*i) {
        init_arr(arr);
    }
    while (1) {
        rand_ch = (rand() % (20)) + 1;
        if (!in_arr(arr, &rand_ch, i)) {
            *(arr + *i) = rand_ch;
            break;
        }
    }

    temp = form_str(*(name + rand_ch), super_rand(a ,b));

    /* Returning value */
    return temp;

}

int super_rand(const int *a, const int *b) {

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

void read_file(struct goods *mas, int *n) {

    /* Initializing variables */
    int i, junk;
    FILE *inputs;
    char name[NAME];

    /* Main part */
    do {
        printf("| Type the name of a text file: ");
        scanf("%s", name);
        prt_ln();
    } while (!(inputs = fopen(name, "r")));
    for (i = 0; i < *n && !feof(inputs); ++i, ++mas) {
        fscanf(inputs, "%s %i", mas->name, &mas->price);
    }
    fclose(inputs);

    if (i == 1 && (--mas)->price == 0) {
        printf("| txt: fatal! No elements were found!                        |\n");
        *n = 0;
        prt_ln();
        while ((junk = getchar()) != '\n')
            ;
        return;
    } else if (i != *n) {
        printf("| txt: can't resolve more than %d values!\n", i);
        *n = i;
        printf("| txt: the number of elements is %d now\n", *n);
        prt_ln();
        return;
    }
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
                while ((junk = getchar()) != '\n')
                    ;
                no_cmd();
                continue;
            }
            return func;
        } else if (func == 'q') {
            if (quit_m()) {
                return -1;
            } else {
                continue;
            }
        } else {
            no_cmd();
            while ((junk = getchar()) != '\n')
                ;
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
    printf("| Full structure [{ Name, Price }]: ");
    for (i = 0; i < *n; ++i, ++mas) {
        printf("{ %s, %d }%s ", mas->name, mas->price, (i == *n - 1) ? "" : ";");
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
    FILE *outputs;

    /* Main part */
    outputs = fopen("a1out.txt", "w");
    if (outputs == NULL) {
        printf("| txt: error, couldn't open file!                            |\n");
        prt_ln();
        return;
    }
    fprintf(outputs, "%s %d\n", min->name, min->price);
    fprintf(outputs, "%s %d", max->name, max->price);
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