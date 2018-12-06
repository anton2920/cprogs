#include "a1.h"

/* Functions definitions */
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