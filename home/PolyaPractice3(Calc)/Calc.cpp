#include "Header_Calc.h"
#include "head_jwfunc.h"
#include "Header_fraction.h"
#include "Combinatoric.h"
#include "Math_probability.h" 
#include "Matrix.h"
#include "Functional_Header.h"

#undef main

int main ()
{
	int Vyborcalc;
	int Continue = 1;

	do
	{
		printf("Select the mode of the calculator: \n");
		printf("1. Matrix calculator \n");
		printf("2. Fraction calculator \n");
		printf("3. Combinatorics calculator \n");
		printf("4. Polynomial calculator \n");
		printf("5. Probability calculator \n");
		printf("6. Function calculator \n");
		printf("7. Exit \n");
		printf("\n");
		do
		{
			printf("You choose: ");
			scanf("%d",&Vyborcalc);
		}
		while ( Vyborcalc < 1 || Vyborcalc > 7 );

		switch (Vyborcalc)
		{
		case 1:
		{
			Matrix_menu();
		}break;
		case 2:
		{
			menu_fraction();
		}break;
		case 3:
		{
			MenuCombinatoric();
		}break;
		case 4:
		{
			main_polinom();
		}break;
		case 5:
		{
			math_probability_menu();
		}break;
		case 6:
		{
			Functional_Menu();
		}break;
		case 7: Continue = 0; break;
		}

		if (Continue == 0)
			break;

		printf("\n");
	}
	while ( Continue == 1 );

	return 0;
}
