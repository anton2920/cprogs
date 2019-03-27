#include "Header_Calc.h"
#include "Combinatoric.h"

int Factorial(int count)
{
	int N = 1, res = 1;
	while (N <= count)
	{
		res *= N;
		N++;
	}
	return res;
}

int PlacementRepeat(int N, int K)
{
	int res = 1,count = 1;

	while (count <= K)
	{
		res *= N;
		count++;
	}

	return res;
}

int PlacementNoRepeat(int N, int K)
{
	int res;

	res = Factorial(N) / Factorial(N - K);

	return res;
}

int CombinationNoRepeat(int N, int K)
{
	int res;

	res = Factorial(N) / (Factorial(K)*Factorial(N - K));

	return res;
}

int CombinationRepeat(int N, int K) 
{
	int res;

	res = Factorial(N + K - 1) / (Factorial(K)*Factorial(N - 1));

	return res;
}

int RearrangementRepeat(int N, int K) 
{
	int arr[100];
	int res = 1;

	for (int i = 0; i < K; i++)
	{
		do
		{
			printf("How many items of type %d?\n", i+1);
			scanf("%d", &arr[i]);
		} while (arr[i] < 1);
		res *= Factorial(arr[i]);
	}
	res = Factorial(N) / (res);

	return res;
}

int RearrangementNoRepeat(int N)
{
	int res;

	res = Factorial(N);

	return res;
}
void IntputCombinatoric(int choice, int &N,int &K)
{
	do
	{
		printf("Enter the quantity of elements N: ");
		scanf("%d", &N);
	} while (N < 1);

	switch (choice)
	{
		case 1:
		{
			do
			{
				printf("Enter how many items to choose K: ");
				scanf("%d", &K);
			} while (K < 1);
			break;
		}
		case 2:
		{
			do
			{
				printf("Enter by how many positions to place K: ");
				scanf("%d", &K);
			} while ((K < 1)||(K>N));
		}
		break;
		case 3:
		{
			do
			{
				printf("Enter how many items to choose K: ");
				scanf("%d", &K);
			} while (K < 1);
			break;
		}
		case 4:
		{
			do
			{
				printf("Enter how many items to choose K: ");
				scanf("%d", &K);
			} while ((K < 1)||(K > N));
		}
		break;
		case 5:
		{
			do
			{
				printf("How many types of identical numbers?\n");
				scanf("%d", &K);
			} while (K < 1);
			break;
		}
		case 6:;
	}
}
void MenuCombinatoric()
{
	int choice, N, K, flag = 1;

	do
	{
		do
		{
			printf("\nSelect an action:\n0. Cancel\n1. Repetition placement\n2. Placement without repetition\n3. Combination with repetition\n4. Combination without repetition\n5. Permutation with repetition\n6. Permutation without repetitions\n");
			scanf("%d", &choice);
		} while ((choice < 0) || (choice > 6));

		switch (choice)
		{
		case 0: flag = 0; break;
		case 1:
		{
			IntputCombinatoric(choice, N, K);
			printf("Result:%d\n", PlacementRepeat(N, K));
			break;
		}
		case 2:
		{
			IntputCombinatoric(choice, N, K);
			printf("Result: %d\n", PlacementNoRepeat(N, K));
			break;
		}
		case 3:
		{
			IntputCombinatoric(choice, N, K);
			printf("Result: %d\n", CombinationRepeat(N, K));
			break;
		}
		case 4:
		{
			IntputCombinatoric(choice, N, K);
			printf("Result: %d\n",CombinationNoRepeat(N, K));
			break;
		}
		case 5:
		{
			IntputCombinatoric(choice, N, K);
			printf("Result: %d\n", RearrangementRepeat(N, K));			
			break;
		}
		case 6:
		{
			IntputCombinatoric(choice, N, K);
			printf("Result: %d\n", RearrangementNoRepeat(N));
			break;
		}
		}

		if (flag == 0)
			break;
	} while (flag == 1);
	
}
