#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXSIZ 100

/* Functions declaration */
void read_key(int *, int *);
void read_rand(int *, int *);
void read_file(int *, int *);
void read_bfile(int *, int *);
float a_mean (int *, int *, int *);
void write_scr(int *, int *, float *);
void write_file(int *, int *, float *);
void write_bfile(int *, int *, float *);

/* Array: arithmetic mean of even odd-positioned numbers */
main() {

    /* Initializing variables */
    int mas[MAXSIZ], func, n, func2;
    srand(time(NULL));
    float ar_mean;

    /* I/O flow */
    do {
        printf("Type the number of elements: ");
        scanf("%d", &n);
    } while (n > MAXSIZ);
    do {
        printf("Fill array with… [1 — keyboard-typed numbers, 2 — pseudo-random generated numbers, 3 — text file, 4 — binary file]: ");
        scanf("%d", &func);
    } while (func <= 0 || func >= 5);

    switch (func) {
        case 1:
            read_key(mas, &n);
            break;
        case 2:
            read_rand(mas, &n);
            break;
        case 3:
            read_file(mas, &n);
            break;
        case 4:
            read_bfile(mas, &n);
            break;
        default:
            break;
    }

    printf("\n");
    do {
        printf("Output answer with… [1 — screen, 2 — text file, 3 — binary file]: ");
        scanf("%d", &func2);
    } while (func2 <= 0 || func2 >= 4);

    /* Main part */
    ar_mean = a_mean(mas, &n, &func2);

    /* Final output */
    switch (func2) {
        case 1:
            write_scr(mas, &n, &ar_mean);
            break;
        case 2:
            write_file(mas, &n, &ar_mean);
            break;
        case 3:
            write_bfile(mas, &n, &ar_mean);
            break;
        default:
            break;
    }
}

/* Functions defenitions */
void read_key(int *mas, int *n) {

    /* Initializing variables */
    int i;

    /* Main part */
    for (i = 0; i < *n; ++i) {
        printf("Type %d%s element: ", i, (i == 1) ? "st" : (i == 2) ? "nd" : (i == 3) ? "rd" : "th");
        scanf("%d", mas + i);
    }
}

void read_rand(int *mas, int *n) {

    /* Initializing variables */
    int i, a, b, temp;

    /* Main part */
    printf("Type «left» border of generation: ");
    scanf("%d", &a);
    printf("Type «right» border of generation: ");
    scanf("%d", &b);
    if (a > b) {
        temp = b;
        b = a;
        a = temp;
    }
    for (i = 0; i < *n; ++i) {
        mas[i] = (rand() % (b - a + 1)) + a;
    }
}

void read_file(int *mas, int *n) {

    /* Initializing variables */
    int i;
    FILE *inputs;
    char name[21];

    /* Main part */
    do {
        printf("Type the name of a text file: ");
        scanf("%s", name);
    } while ((inputs = fopen(name, "r")) == NULL);
    for (i = 0; i < *n; ++i) {
        fscanf(inputs, "%d", mas + i);
    }
    fclose(inputs);
}

void read_bfile(int *mas, int *n) {

    /* Initializing variables */
    int i;
    FILE *inputs;
    char name[21];

    /* Main part */
    do {
        printf("Type the name of a binary file: ");
        scanf("%s", name);
    } while ((inputs = fopen(name, "rb")) == NULL);
    for (i = 0; i < *n; ++i) {
        fread(mas + i, sizeof(int), (size_t) *n, inputs);
    }
    fclose(inputs);
}

float a_mean(int *mas, int *n, int *func) {

    /* Intializing variables */
    int i, sum = 0, count = 0;
    float ar_mean = 0;

    /* Main part */
    for (i = 0; i < *n; i += 2) {
        if (*(mas + i) % 2 == 0) {
            sum += *(mas + i);
            ++count;
        }
    }

    if (count == 0) {
        *func = 0;
    } else {
        ar_mean = sum * 1.0 / count * 1.0;
    }

    /* Returning value */
    return ar_mean;

}

void write_scr(int *mas, int *n, float *ar_mean) {

    /* Initializing varialbes */
    int i;

    /* Main part */
    printf("Arithmetic mean: %.2f\n", *ar_mean);
    printf("Array: ");
    for (i = 0; i < *n; i += 2) {
        if (*(mas + i) > *ar_mean && *(mas + i) % 2 == 0) {
            printf("%d ", *(mas + i));
        }
    }
    printf("\n");
}

void write_file(int *mas, int *n, float *ar_mean) {

    /* Initializing variables */
    int i;
    FILE *outputs;

    /* Main part */
    outputs = fopen("a1out.txt", "w");
    fprintf(outputs, "%.2f\n", *ar_mean);
    for (i = 0; i < *n; i += 2) {
        if (*(mas + i) > *ar_mean && *(mas + i) % 2 == 0) {
            fprintf(outputs, "%d ", *(mas + i));
        }
    }
}

void write_bfile(int *mas, int *n, float *ar_mean) {

    /* Initializing varialbes */
    int i;
    FILE *outputs;

    /* Main part */
    outputs = fopen("a1out.bin", "wb");
    fwrite(&ar_mean, sizeof(float), 1, outputs);
    /* fwrite("\n", sizeof(char), 1, outputs); */
    for (i = 0; i < *n; i += 2) {
        if (*(mas + i) > *ar_mean && *(mas + i) % 2 == 0) {
            fwrite(mas + i, sizeof(int), 1, outputs);
        }
    }
}