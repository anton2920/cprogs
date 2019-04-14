#include <cstdlib>
#include <stdio.h>
#include <malloc.h>
#include "Header.h"

void EnterRow(int *A, int n) {

	/* I/O flow */
	for (int i = 0; i < n; i++)
	{
		printf("A[%d]= ", i);
		scanf("%d", (A + i));
	}

	printf("\nInitial array: ");
	for (int i = 0; i < n; i++) {
		printf("%d ", *(A + i));
	}

	/* Final output */
	printf("\n");
}