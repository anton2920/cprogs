#include "Header.h"

int main() {

	/* Initializing variables */
	int n, counter = 0, C[10] = {0}, *A, **B, i, j;

	/* I/O flow && VarCheck */
	do {
		printf("Type the number of elements in the sequence: ");
		scanf("%d", &n);
	} while (n <= 0);

	A = (int *) malloc(n * sizeof(int));
	EnterRow(A, n);

	printf("\n");
	
	/* Main part */
	B = (int **) malloc(10 * sizeof(int *));

	for (i = 0; i < 10 ; ++i) {
		B[i] = (int *) malloc(n * sizeof(int));
	}

	for (i = 0; i < 10; ++i) {
		for (j = 0; j < n; ++j) {
			if ((*(A + j)) % 10 == i) {
				B[i][C[i]] = A[j];
				++C[i];
			}
		}
		B[i] = (int *) realloc(B[i], C[i] * sizeof(int));
	}

	for (i = 0; i < 10; i++) {
		printf("Ends with %d: ", i);

		for (j = 0; j < C[i]; j++) {
			printf("%d%s", B[i][j], (j == C[i] - 1) ? "" : ", ");
		}

		printf("\n");
	}
	for (int i = 0; i < 10; i++)
	{
		free(B[i]);
	}
	free(B);
	free(A);

	/* Returning value */
	return 0;
}

