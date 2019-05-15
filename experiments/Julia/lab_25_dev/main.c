#include <locale.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct array {
    int m;     // количество строк
    int **p; // указатель на вектор указателей строк
    int t; // терминальный символ
} Array;

Array CreateAndInputArray(void) {
    Array a;
    int i;
    printf("Введите терминальный символ: ");
    scanf("%d", &a.t);

    printf("Введите количество строк: ");
    scanf("%d", &a.m);

    a.p = (int **) malloc(a.m * sizeof(int *));
    for (i = 0; i < a.m; i++) {
        a.p[i] = (int *) malloc(sizeof(int));
        a.p[i][0] = a.t;
    }
    int k;
    for (i = 0; i < a.m; i++) {
        int j = 0;
        do {
            printf("Введите элемент [%d]-ой(ей) строки: ", i + 1);
            scanf("%d", &k);
            if (k != a.t) {
                a.p[i][j] = k;
                a.p[i] = (int *) realloc(a.p[i], sizeof(int) * (j + 1));
                j++;
            }
        } while (k != a.t);
        a.p[i][j] = a.t;
    }
    return a;
}

void PrintArray(Array const *a) {
    int i, j;

    for (i = 0; i < a->m; i++) {
        for (j = 0; a->p[i][j] != a->t; j++) {
            printf("[%d] = ", a->p[i][j]);
        }
        printf("\n");
    }
}

//Сохраняет введенный с клавиатуры массив в текстовый файл
int SaveDArrayInTF(Array a, char const file[]) {
//	FILE*ft;
//
//	if (fopen_s(&ft, file, "wt")) return -1;
//	fprintf_s(ft, "%d\n", a.m);
//	for (int i = 0; i < a.m; i++)
//	{
//		fprintf_s(ft, "%d ", a.p[i]);
//		for (int j = 0; j < a.p[i]; j++)
//		{
//			fprintf_s(ft, "%d ", a.p[i][j]);
//		}
//		fprintf_s(ft, "\n");
//	}
//
//
//	fclose(ft);
    return 0;
}

//Сохраняет введенный с клавиатуры массив в бинарный файл
int SaveDArrayInBF(Array a, char const file[]) {
//	FILE*fb;
//
//	if (fopen_s(&fb, file, "w+b")) \
//	{
//		return -1;
//	}
//	fwrite(&a.m, sizeof(int), 1, fb);
//	for (int i = 0; i < a.m; i++)
//	{
//		fwrite(&a.n[i], sizeof(int), 1, fb);
//		for (int j = 0; j < a.n[i]; j++)
//		{
//			fwrite(&a.p[i][j], sizeof(int), 1, fb);
//		}
//	}
//
//	fclose(fb);
    return 0;
}

//Считывает массив из текстового файла
/*Array LoadDArrayFromTF(char const file[])
{
Array b;
	int n;
	FILE*ft;

	fopen_s(&ft, file, "rt");
	fscanf_s(ft, "%d", &b.m);

	b.p = (int**)malloc(b.m * sizeof(int*));
	b.n = (int*)malloc(b.m * sizeof(int));

	for (int i = 0; i < b.m; i++)
	{
		fscanf_s(ft, "%d", &b.n[i]);
		b.p[i] = (int*)malloc(b.n[i] * sizeof(int));

		for (int j = 0; j < b.n[i]; j++)
		{
			fscanf_s(ft, "%d", &b.p[i][j]);
		}

	}

 fclose(ft);
 return b;
} */

//Считывает массив из бинарного файла
//Array LoadDArrayFromBF(char const fName[])
//{
//	int n;
//	FILE*fb;
//	Array b;
//
//	fopen_s(&fb, fName, "r+b");
//	fread(&b.m, sizeof(int), 1, fb);
//
//	b.p = (int**)malloc(b.m * sizeof(int*));
//	b.n = (int*)malloc(b.m * sizeof(int));
//
//	for (int i = 0; i < b.m; i++)
//	{
//		fread(&b.n[i], sizeof(int), 1, fb);
//		b.p[i] = (int*)malloc(b.n[i] * sizeof(int));
//
//		for (int j = 0; j < b.n[i]; j++)
//		{
//			fread(&b.p[i][j], sizeof(int), 1, fb);
//		}
//	}
//
//	fclose(fb);
//	return b;
//}

// обнуляет массив 
/* void FreeMemory(Array *a)
{

	for (int i = 0; i < a->m; i++)
	{
	free(a->p[i]);
	}
	free(a->n);
	free(a->p);

	a->n = NULL;
	a->p = NULL;
	a->m = 0;
}*/

int main() {
    setlocale(LC_ALL, "Russian");

    FILE *ft;
    FILE *fb;
    int choice1, choice2;

    do {
        printf("Выберете действие:\n1. Запись массива с клавиатуры\n2. Запись массива из текстового файла\n3. Запись массива из бинарного файла\nВыбор: ");
        scanf("%d", &choice1);
    } while ((choice1 != 1) && (choice1 != 2) && (choice1 != 3));

    switch (choice1) {
        case 1: {
            Array a;
            a = CreateAndInputArray();
            PrintArray(&a);
            //FreeMemory(&a);
            break;
        }

        case 2: {
            //Array t = LoadDArrayFromTF("array.txt");
            //PrintArray(&a);
            //FreeMemory(&t);
            break;
        }

        case 3: {
            //Array b = LoadDArrayFromBF("array.bin");
            //PrintArray(b);
            //FreeMemory(&b);
            break;
        }
    }
    getchar();
    return 0;
}