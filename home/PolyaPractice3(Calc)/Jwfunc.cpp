// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

//#define _CRT_SECURE_NO_WARNINGS
#include "head_jwfunc.h"
#include "Header_Calc.h"


int main_polinom()
{
	printf("Features of the polynomical calculator: \n1. Sum\n2. Difference\n3. Multiplication\n4. Multiply by number\n5. Derinative\n6. Division\n");
	int selection, tmp;
	while (true)
	{
		do
		{
			printf("\nEnter an action(1-6) or \"0\" to select a calculator: "); scanf("%d", &selection);
			if (selection < 0 || selection > 6)
			{
				printf("\n\tInvalid input\n");
			}
		} while (selection < 0 || selection > 6);
		
		switch (selection)
		{
		case 0:
		{
			return 0;
			break;
		}
		case 1:
		{
			while (true)
			{
				sum_polinoms();
				tmp = check_continue();
				if (tmp == 3)
				{
					return 0;
				}
				else if (tmp == 2)
				{
					break;
				}
			}
			break;
		}
		case 2:
		{
			while (true)
			{
				difference_polinoms();
				tmp = check_continue();
				if (tmp == 3)
				{
					return 0;
				}
				else if (tmp == 2)
				{
					break;
				}
			}
			break;
		}
		case 3:
		{
			while (true)
			{
				multiplication_polinoms();
				tmp = check_continue();
				if (tmp == 3)
				{
					return 0;
				}
				else if (tmp == 2)
				{
					break;
				}
			}
			break;
		}
		case 4:
		{
			while (true)
			{
				multiplication_polinom_by_number();
				tmp = check_continue();
				if (tmp == 3)
				{
					return 0;
				}
				else if (tmp == 2)
				{
					break;
				}
			}
			break;
		}
		case 5:
		{
			while (true)
			{
				derinative_polinom();
				tmp = check_continue();
				if (tmp == 3)
				{
					return 0;
				}
				else if (tmp == 2)
				{
					break;
				}
			}
			break;
		}
		case 6:
		{
			while (true)
			{
				division_polinom();
				tmp = check_continue();
				if (tmp == 3)
				{
					return 0;
				}
				else if (tmp == 2)
				{
					break;
				}
			}
			break;
		}
		}
	}
}

void sum_polinoms()
{
	polinom polm[3];
	filling_polinom(polm, 3);

	for (int i = 0; i < 2; i++)
	{
		for (int j = 10; j >= 0; j--)
		{
				polm[2].coef[j] += polm[i].coef[j];			
		}
	}	

	result_polinom(polm, 3);
}

void difference_polinoms()
{
	polinom polm[3];
	filling_polinom(polm, 3);

	for (int i = 10; i >= 0; i--)
	{
		polm[0].coef[i] -= polm[1].coef[i];
	}

	result_polinom(polm, 1);
}

void multiplication_polinoms()
{
	polinom polm[3];
	filling_polinom(polm, 3);
	float temp_polinom[21];

	for (int i = 20; i >= 0; i--)
	{
		temp_polinom[i] = 0;
	}
	
	for (int i = 10; i >= 0; i--)
	{
		for (int j = 10; j >= 0; j--)
		{
			temp_polinom[i + j] += polm[0].coef[i] * polm[1].coef[j];
		}
	}
	
	printf("\n\tResult:");
	for (int i = 20; i >= 0; i--)
	{
		if (temp_polinom[i] != 0 && i > 0)
		{
			printf("\nCoefficient before x^%d: %.2f;", i, temp_polinom[i]);
		}
		else if (temp_polinom[i] != 0 && i == 0)
		{
			printf("\nCoefficient before x^%d (free coefficient): %.2f;\n", i, temp_polinom[i]);
		}
	}
	printf("\n");
	
}

void multiplication_polinom_by_number()
{
	polinom polm[2];
	filling_polinom(polm, 2);
	float number_for_multiply;
	do
	{
		printf("Input number: ");
		scanf("%f", &number_for_multiply);
		if (number_for_multiply < -99999 || number_for_multiply > 99999)
		{
			printf("\nToo much value!\n\n");
		}
	} while (number_for_multiply < -99999 || number_for_multiply > 99999);
	for (int i = 10; i >= 0; i--)
	{
		polm[0].coef[i] *= number_for_multiply;
	}
	result_polinom(polm,1);
}

void derinative_polinom()
{
	polinom polm[2];
	filling_polinom(polm, 2);
	for (int i = 10; i > 0; i--)
	{
		polm[1].coef[i-1] = polm[0].coef[i] * i;
	}
	result_polinom(polm, 2);
}

void division_polinom()
{
	polinom polm[3], polm_ost, polm_otvet;
	float tmp, tmp_for_exit;
	filling_polinom(&polm_ost, 1);
	filling_polinom(&polm_otvet, 1);
	do
	{
		filling_polinom(polm, 3);
		for (int i = 10; i >= 0; i--)
		{
			if (polm[0].coef[i] == 0 && polm[1].coef[i] != 0)
			{
				printf("\nIt is unacceptable that the leading degree of the second polynomial be higher than that of the first polynomial.\n\n");
				tmp = 1;
				break;
			}
			else if ((polm[0].coef[i] != 0 && polm[1].coef[i] == 0) || (polm[0].coef[i] != 0 && polm[1].coef[i] != 0))
			{
				tmp = 0; 
				break;
			}
		}
	} while (tmp);

	tmp = 1;

	while (tmp)
	{
		for (int i = 10; i >= 0; i--)
		{
			polm[2].coef[i]= 0;
			polm_ost.coef[i] = 0;
		}

		tmp_for_exit = 0;
		for (int i = 10; i >= 0; i--)
		{
			for (int j = 10; j >= 0; j--)
			{
				if (polm[0].coef[i] != 0 && polm[1].coef[j] != 0 && i>=j)
				{
					polm_ost.coef[i - j] = polm[0].coef[i] / polm[1].coef[j];
					polm_otvet.coef[i - j] += polm_ost.coef[i - j];
					tmp_for_exit = 1;
					break;
				}
			}
			if (tmp_for_exit)
			{
				break;
			}
		}

		for (int i = 10; i >= 0; i--)
		{
			for (int j = 10; j >= 0; j--)
			{
				polm[2].coef[i + j] += polm[1].coef[j] * polm_ost.coef[i];
			}
		}
		
		for (int i = 10; i >= 0; i--)
		{
			polm[0].coef[i] -= polm[2].coef[i];
		}
		

		for (int i = 10; i >= 0; i--)
		{
			if (polm[0].coef[i] == 0 && polm[1].coef[i] != 0)
			{
				tmp = 0;
			}
		}
	}

	printf("\tThe result of dividing a polynomial by a polynomial is: divisor * quotient + remainder.\n");
	
	for (int j = 0; j < 3; j++)
	{
		if (j == 0)
		{
			printf("\nCoefficient`s divisor:");
		}
		else if (j == 1)
		{
			printf("\nCoefficient`s quotient:");
		}
		else
		{
			printf("\nCoefficient`s remainder:");
		}
		for (int i = 10; i >= 0; i--)
		{
			if (j == 0 && polm[1].coef[i])
			{
				printf("\nx^%d: %.2f;", i, polm[1].coef[i]);
			}
			else if (j == 1 && polm_otvet.coef[i])
			{
				printf("\nx^%d: %.2f;", i, polm_otvet.coef[i]);
			}
			else if( j == 2&& polm[0].coef[i])
			{
				printf("\nx^%d: %.2f;", i, polm[0].coef[i]);
			}
		}
		printf("\n");
	}
}

void filling_polinom(polinom *polm, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 10; j >= 0; j--)
		{
			polm[i].coef[j] = 0;
		}
	}

	int max_deg[2];
	for (int i = 0; i < n-1; i++)
	{
		do
		{
			printf("Input max degree %d polinom(max 10): ", i+1);
			scanf("%d", &max_deg[i]);
		} while (max_deg[i]<0||max_deg[i]>10);
	}
	for (int i = 0; i < n-1; i++)
	{
		for (int j = max_deg[i]; j >= 0; j--)
		{
			do
			{
				if (j > 0)
				{
					printf("Input a coefficient before x^%d, %d polinom: ", j, i + 1);
					scanf("%f", &polm[i].coef[j]);
				}
				else
				{
				
					printf("Input a free coefficient %d polinom: ", i + 1);
					scanf("%f", &polm[i].coef[j]);
				}
				if (polm[i].coef[j] < -99999 || polm[i].coef[j] > 99999)
				{
					printf("\n\tToo much value!\n\n");
				}
			} while (polm[i].coef[j] < -99999 || polm[i].coef[j] > 99999);
		}
		printf("\n");
	}	
}

void result_polinom(polinom *polm, int n)
{
	printf("\n\tResult:");
	for (int i = 10; i >= 0; i--)
	{
		if (polm[n-1].coef[i] != 0 && i>0)
		{
			printf("\nCoefficient before x^%d: %.2f;", i, polm[n-1].coef[i]);
		}
		else if( polm[n-1].coef[i] != 0 && i==0)
		{
			printf("\nCoefficient before x^%d(Free coefficient): %.2f;\n\n",i, polm[n-1].coef[i]);
		}
	}
}

int check_continue()
{
	int tmp;
	printf("\n1. Again.\n2. Change action.\n3. Exit.\n\n Enter: ");
	do
	{
		scanf("%d", &tmp);
	} while (tmp < 1 || tmp>3);
	return tmp;
}