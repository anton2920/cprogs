#include <stdio.h>
#include <stdlib.h>
#include <locale>
#include <time.h>

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Rus");
	int chislo = 0, diff, k, i;
	printf("Правила: Игра начинается с числа 0. За ход можно прибавлять к имеющемуся числу любое число от 1 до 10. Выигрывает получивший число 100.\n");

	do
	{
		do
		{
			k = 0;
			printf("Пользователь выбрал число = ");
			scanf_s("%d", &diff);
			if ((diff > 10) || (diff < 1))
			{
				k = 1;
				printf("Неправильное число. Введите число ещё раз.\n");
			}
			else
			{
				chislo += diff;
				printf("Получившееся число = %d\n", chislo);
			}
			i = 0;
		} while (k == 1);	

		if (chislo < 90)
		{
			diff = 1 + rand() % (10);
			printf("Компьютер выбрал число = %d\n", diff);
			chislo += diff;
			printf("Получившееся число = %d\n", chislo);
		}
		else
		{
			if (chislo < 100)
			{
				diff = 100 - chislo;
				printf("Компьютер выбрал число = %d\n", diff);
				chislo += diff;
				printf("Получившееся число равно = %d\n", chislo);
				i = 1;
			}
		}
	} while (chislo < 100);

	if (chislo == 100)
	{
		if (i == 0)
		{
			printf("Поздравляю! Вы выиграли\n");
		}
		else
		{
			printf("Вы проиграли. Компьютер молодец\n");
		}
	}
	else
	{
		printf("Вы проиграли (прочтите правила игры)\n");
	}

	system("pause");
	return 0;
}