#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printGraph(int *graph, int N) {

    /* Initializing variables */
    auto int i, j;

    /* Main part */
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            printf("%3d", *(graph + i * N + j));
        }
        printf("\n");
    }
}

main() {

    /* Initializing variables */
    auto int N;
    auto int i, j, ex;
    auto int *graph, *inverse_graph;
    auto char *zero;
    auto int *one;

    auto FILE *fp = fopen("input2.txt", "r");

    /* I/O flow */
    printf("Type N: ");
    fscanf(fp, "%d", &N);

    /* Main part */
    if ((graph = calloc(N * N, sizeof(int))) == NULL) {
        return EXIT_FAILURE;
    }

    if ((inverse_graph = calloc(N * N, sizeof(int))) == NULL) {
        return EXIT_FAILURE;
    }

    if ((zero = calloc(N, sizeof(int))) == NULL) {
        return EXIT_FAILURE;
    }

    if ((one = calloc(N - 1, sizeof(int))) == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < N - 1; ++i) {
        *(one + i) = 0x1;
    }

    printf("Indexes [%d, ..., %d]\nType 0 to finish\n", 1, N);
    do {
        fscanf(fp, "%d", &ex);
        if (!ex) {
            break;
        }
        fscanf(fp, "%d %d", &i, &j);
        *(graph + (i - 1) * N + (j - 1)) = 1;
        *(inverse_graph + (j - 1) * N + (i - 1)) = 1;
    } while (ex != 0);

    /*printGraph(graph, N);
    printf("\n");
    printGraph(inverse_graph, N);
*/
    for (i = 0; i < N; ++i) {
        if (!memcmp(graph + i * N, zero, N * sizeof(int))) {
            if (!memcmp(inverse_graph + i * N, one, (N - 1) * sizeof(int))) {
                printf("Vertex %d is a drain\n", i + 1);

                free(graph);
                free(zero);
                return EXIT_SUCCESS;
            }
        }
    }

    free(graph);
    free(zero);

    /* Final output */
    printf("There's no drains\n");
}