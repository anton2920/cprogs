#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

int main() {
	setlocale(LC_ALL, "Russian");
	int a, b = 1, i, max = -1;

	printf("Введите a: ");
	scanf_s("%d", &a);

	a = (a >= 0) ? a : -a;

	for (i = 0; b < a; ++i) {
		b *= 2;
		if (b > max && a % b == 0) {
			max = i;
		}
	}

	printf("Max: %d\n", ++max);

	system("pause");

return 0;
}