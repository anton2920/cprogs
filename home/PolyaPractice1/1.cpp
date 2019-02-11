#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH	100

void FillArray(int array[MAX_LENGTH][MAX_LENGTH], int length)
{
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {

			printf("Input a[%i][%i]: ", i, j);
			scanf("%i", &array[i][j]);
		}
	}
}

int main(void)
{
	int array[MAX_LENGTH][MAX_LENGTH];
	int length;

	printf("Enter the number of length (odd): ");
	do scanf("%i", &length);
	while (!(0 < length && length <= MAX_LENGTH && length % 2));

	FillArray(array, length);

	int offset_i = 0;
	int offset_j = 0;
	int center = length / 2;

	while ((offset_i != center && offset_j != center))
	{
		for (int i = 0 + offset_i; i < length - 1 - offset_i; i++)
			printf("%i ", array[i][offset_j]);

		for (int j = 0 + offset_j; j < length - 1 - offset_j; j++)
			printf("%i ", array[length - offset_i - 1][j]);

		for (int i = length - offset_i - 1; i > 0 + offset_i; i--)
			printf("%i ", array[i][length - offset_j - 1]);

		for (int j = length - offset_j - 1; j > 0 + offset_j; j--)
			printf("%i ", array[offset_i][j]);

		offset_j++;
		offset_i++;
	}
	printf("%i", array[center][center]);

	system("pause");
	return 0;
}