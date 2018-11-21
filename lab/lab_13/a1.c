#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXSIZ 100

/* Array: arithmetic mean of even odd-positioned numbers */
main() {

    /* Initializing variables */
    int mas[MAXSIZ], i, func, n, a, b, func2, sum = 0, count = 0;
    float ar_mean = 0;
    char name[21];
    FILE *inputs, *outputs;
    srand(time(NULL));

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
            for (i = 0; i < n; ++i) {
                printf("Type %d%s element: ", i, (i == 1) ? "st" : (i == 2) ? "nd" : (i == 3) ? "rd" : "th");
                scanf("%d", mas + i);
            }
            break;
        case 2:
            printf("Type «left» border of generation: ");
            scanf("%d", &a);
            printf("Type «right» border of generation: ");
            scanf("%d", &b);
            for (i = 0; i < n; ++i) {
                mas[i] = (rand() % (b - a + 1)) + a;
            }
            break;
        case 3:
            do {
                printf("Type the name of a text file: ");
                scanf("%s", name);
            } while ((inputs = fopen(name, "r")) == NULL);
            for (i = 0; i < n; ++i) {
                fscanf(inputs, "%d", mas + i);
            }
            fclose(inputs);
            break;
        case 4:
            do {
                printf("Type the name of a binary file: ");
                scanf("%s", name);
            } while ((inputs = fopen(name, "rb")) == NULL);
            for (i = 0; i < n; ++i) {
                fread(mas + i, sizeof(int), n, inputs);
            }
            fclose(inputs);
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
    for (i = 0; i < n; i += 2) {
        if (*(mas + i) % 2 == 0) {
            sum += *(mas + i);
            ++count;
        }
    }

    if (count == 0) {
        func2 = 0;
    } else {
        ar_mean = sum * 1.0 / count * 1.0;
    }

    /* Final output */

    switch (func2) {
        case 1:
            printf("Arithmetic mean: %.2f\n", ar_mean);
            printf("Array: ");
            for (i = 0; i < n; i += 2) {
                if (*(mas + i) > ar_mean && *(mas + i) % 2 == 0) {
                    printf("%d ", *(mas + i));
                }
            }
            printf("\n");
            break;
        case 2:
            outputs = fopen("a1out.txt", "w");
            fprintf(outputs, "%.2f\n", ar_mean);
            for (i = 0; i < n; i += 2) {
                if (*(mas + i) > ar_mean && *(mas + i) % 2 == 0) {
                    fprintf(outputs, "%d ", *(mas + i));
                }
            }
            break;
        case 3:
            outputs = fopen("a1out.bin", "wb");
            fwrite(&ar_mean, sizeof(float), 1, outputs);
            /* fwrite("\n", sizeof(char), 1, outputs); */
            for (i = 0; i < n; i += 2) {
                if (*(mas + i) > ar_mean && *(mas + i) % 2 == 0) {
                    fwrite(mas + i, sizeof(int), 1, outputs);
                }
            }
            break;
        default:
            break;
    }
}