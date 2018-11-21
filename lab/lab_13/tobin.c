#include <stdio.h>

/* Quick text-to-bin converter */
main() {

	/* Initializing variables */
	int n, num, i;
	FILE *inputs, *outputs;
	char name[21];

	/* I/O flow */
	printf("Type the number of elements: ");
	scanf("%d", &n);
	do {
		printf("Type the name of a text file: ");
		scanf("%s", name);
	} while ((inputs = fopen(name, "r")) == NULL);
	do {
		printf("Type the name of a binary file: ");
		scanf("%s", name);
	} while ((outputs = fopen(name, "wb")) == NULL);

	/* Main part */
	for (i = 0; i < n; ++i) {
		fscanf(inputs, "%d", &num);
		fwrite(&num, sizeof(int), 1, outputs);
	}

	fclose(inputs);
	fclose(outputs);
}