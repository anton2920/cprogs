#pragma warning (disable : 4996)
#include<iostream>
#include<ctime>

void turn_user(int *coin)
{
	int choice, choice_1, choice_2, kol,kol_pair=0;
	for (int i = 0; i < 24; i++)
	{
		if ((coin[i] == 1) && (coin[i + 1] == 1)) kol_pair++;
	}
	for (int i = 0; i < 25; i++)
	{
		printf("%d(%d) ", coin[i], i);
	}
	printf("\n");
	do
	{
		printf("Сколько монет вы хотите взять?\n");
		scanf("%d", &kol);
	} while (((kol > 2) || (kol < 1))||((kol == 2) && (kol_pair == 0)));
	if (kol == 1)//пользователь берет 1 монету
	{
		do
		{
			printf("Выберете какую монету взять\n");
			scanf("%d", &choice);
		} while (coin[choice] == 0);
		for (int i = 0; i < 25; i++)
		{
			coin[choice] = 0;
		}
	}
	else//пользователь берет 2 монеты
	{
		do
		{
			printf("Выберете какие монеты взять\n");
			scanf("%d", &choice_1);
			scanf("%d", &choice_2);
		} while ((coin[choice_1] == 0) || (coin[choice_2] == 0) || (abs(choice_1 - choice_2) != 1));
		for (int i = 0; i < 25; i++)
		{
			coin[choice_1] = 0;
			coin[choice_2] = 0;
		}
	}
}
void turn_computer(int *coin)
{
	int choice, choice_1, choice_2, kol,kol_pair=0;
	for (int i = 0; i < 24; i++)
	{
		if ((coin[i] == 1) && (coin[i + 1] == 1)) kol_pair++;
	}
	do
	{
		kol = rand() % 2 + 1;
	} while (((kol > 2) || (kol < 1)) || ((kol == 2) && (kol_pair == 0)));
	if (kol == 1)//компьютер берет 1 монету
	{
		do
		{
			choice = rand() % 25;
		} while (coin[choice] == 0);
		for (int i = 0; i < 25; i++)
		{
			coin[choice] = 0;
		}
	}
	else//компьютер берет 2 монеты
	{
		do
		{
			choice_1 = rand() % 25;
			choice_2 = rand() % 25;
		} while ((coin[choice_1] == 0) || (coin[choice_2] == 0) || (abs(choice_1 - choice_2) != 1));
		for (int i = 0; i < 25; i++)
		{
			coin[choice_1] = 0;
			coin[choice_2] = 0;
		}
	}
}
int summa(int *coin)
{
	int sum=0;
	for (int i = 0; i < 25; i++)
	{
		sum += coin[i];
	}
	return sum;
}
int main()
{
	setlocale(LC_ALL, "russian");

	int coin[25] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	int first;
	srand(time(NULL));
	first = rand() % 2 ;
	printf("Правила игры:\nКаждый ход будет выводиться ряд монет, если 1, то монету можно брать, если 0, то ее нельзя выбрать.\nЗа ход можно взять одну или две рядом лежащие монеты.\nЧтобы взять монету или монеты нужно ввести ее или их номера, которые указаны в скобках.\nПроигрывает тот кому нечего брать.\nТого, кто первый ходит определяет рандом\n");

	if (first == 0)//первым ходит пользователь 
	{
		printf("Вы ходите первым\n");
		do
		{
			turn_user(coin);
			if (summa(coin) == 0)
			{
				printf("Вы победили!!!\n");
			}
			turn_computer(coin);
			if (summa(coin) == 0)
			{
				printf("Вы програли(\n");
			}
		} while (summa(coin) > 0);
	}
	else//первым ходит компьютер
	{
		printf("Первым ходит компьютер\n");
		do
		{
			turn_computer(coin);
			if (summa(coin) == 0)
			{
				printf("Вы програли(\n");
				break;
			}
			turn_user(coin);
			if (summa(coin) == 0)
			{
				printf("Вы победили!!!\n");
				break;
			}
		} while (summa(coin) > 0);
	}
	system("pause");
	return 0;
}