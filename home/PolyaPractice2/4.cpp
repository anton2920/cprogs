#define _CRT_SECURE_NO_WARGINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string>

#define sizemass 100

void pere(int mass[], int lenght);
int check(int num_element, int mass_comp[], int lenght);
void randfull(int mass[], int lenght);
void userfull(int mass[], int lenght);
int check_mass(int mass[], int lenght);

int main()
{
	setlocale(0, "rus");
	int massive[sizemass], lenght, how, massiveres[sizemass];
	printf("Задание 4.\nПерестановка членов элементов массива.\n");
	do
	{
		printf("\nВведите количество элементов в массиве(2+): "); scanf_s("%d", &lenght);
		if (lenght < 2 || lenght>100)
			printf("\n\tВнимание! Вы ввели недопустимое значение для размера массива. \n\n\tПримечание: размерность в единицу так же недопустима, т.к. программа теряет какой-либо смысл.\n\tПопробуйте ещё раз...\n");
	} while (lenght < 2 || lenght>100);

	do
	{
		printf("\nКак заполнить массив? (1 - рандом, 2 - лично): "); scanf_s("%d", &how);
		if (how < 1 || how > 2)
			printf("\n\tВнимание! Вы ввели недопустимое значение для способа заполнения. \n\t Попробуйте ещё раз...\n");
	} while (how < 1 || how > 2);

	switch (how)
	{
	case 1: randfull(massiveres, lenght); break;
	case 2: userfull(massiveres, lenght); break;
	}

	printf("\n\n\t Массив: \n\n");
	for (int i = 0; i < lenght; i++)
	{
		printf(" %d ", massiveres[i]);
	}
	pere(massive, lenght);

	printf("\n\n\tРезультат после преобразования:\n\n");
	for (int i = 0; i < lenght; i++)
	{
		printf(" %d ", massiveres[massive[i]]);
	}
	printf("\n\n\n");
	system("pause");
	return 0;
}



// Сортировка
void pere(int mass[], int lenght)
{
	int temp, compare_mass[sizemass];
	memset(compare_mass, -111111, sizeof(compare_mass));
	for (int i = 0; i < lenght; i++)
	{
		srand(NULL);
		while (true)
		{
			if ((temp = rand() % lenght) != i && check(temp, compare_mass, lenght))
			{
				mass[i] = temp;
				compare_mass[i] = temp;
				break;
			}
		}
	}
}


// Проверка на отсутствие повторения при рандомной генерации
int check(int num_element, int mass_comp[], int lenght)
{
	for (int i = 0; i < lenght; i++)
	{
		if (num_element == mass_comp[i])
			return 0;
	}
	return 1;
}

//Заполнение ранд. числами массива
void randfull(int mass[], int lenght)
{
	for (int i = 0; i < lenght; i++)
	{
		mass[i] = rand() % 100 + 1;
	}
}

void userfull(int mass[], int lenght)
{
	while (true)
	{
		for (int i = 0; i < lenght; i++)
		{
			printf("Введите %d-й элемент массива: ", i); scanf_s("%d", &mass[i]);
		}
		if (check_mass(mass, lenght) == 0)
		{
		
			printf("\n\tВнимание! Недопустимо два и более одинаковых элемента массива. \n\tПопробуйте ещё раз...\n\n");
			continue;
		}
		break;
	}
}

int check_mass(int mass[], int lenght)
{
	for (int i = 0; i < lenght; i++)
	{
		if (mass[i] == mass[i + 1])
			return 0;
	}
	return 1;
}