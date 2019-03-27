#include "Matrix.h"
#include "Header_Calc.h"

void Matrix_menu()
{
	int choose_matrix;
	int Continue = 1;

	do
	{
		do
		{
			printf("\n");
			printf("0. Cancel\n");
			printf("1. Matrix addition\n");
			printf("2. Matrix subtraction\n");
			printf("3. Matrix multiplication\n");
			printf("4. Matrix multiplication by number\n");
			printf("5. Addition of a matrix with a number\n");
			printf("6. Matrix transposition\n");
			printf("7. Inverse matrix\n");
			printf("8. Determinant\n");
			printf("Select operation: ");
			scanf("%d", &choose_matrix);
			if ((choose_matrix < 0) || (choose_matrix > 8))
			{
				printf("Invalid value entered. Try again.\n");
			}
		} while ((choose_matrix < 0) || (choose_matrix > 8));

		switch (choose_matrix)
		{
		case 0: Continue = 0; break;
		case 1: Matrix_addition(); break;
		case 2: Matrix_subtraction(); break;
		case 3: Matrix_multiplication(); break;
		case 4: Matrix_multiplication_by_number(); break;
		case 5: Addition_of_a_matrix_with_a_number(); break;
		case 6: Matrix_transposition(); break;
		case 7: Inverse_matrix(); break;
		case 8: Determinant(); break;
		}

		if (Continue == 0)
			break;

	} while (Continue == 1);
}

void Matrix_addition()
{
	int line_1=0, column_1=0; //—Œ«ƒ¿Õ»≈ 1-… Ã¿“–»÷€
	double matrix_1[N][N] = {};
	printf("Enter array dimension.\n");
	do
	{
		printf("The number of lines must be less than 100.\n");
		printf("Number of lines: ");
		scanf("%d", &line_1);
		if ((line_1 < 1) || (line_1 > 100))
		{
			printf("Invalid value entered. Try again.\n");
		}
	} while ((line_1 < 1) || (line_1 > 100));
	do
	{
		printf("The number of columns must be less than 100.\n");
		printf("Number of columns: ");
		scanf("%d", &column_1);
		if ((column_1 < 1) || (column_1 > 100))
		{
			printf("Invalid value entered. Try again.\n");
		}
	} while ((column_1 < 1) || (column_1 > 100));

	printf("Enter numbers in the array\n");

	for (int i = 0; i < line_1; i++)
	{
		for (int j = 0; j < column_1; j++)
		{
			do 
			{
				scanf("%lf", &matrix_1[i][j]);
				if ((matrix_1[i][j] > INT_MAX) || (matrix_1[i][j] < INT_MIN)) printf("Invalid value. Try Again.\n");
			} while ((matrix_1[i][j] > INT_MAX) || (matrix_1[i][j] < INT_MIN));
		}
	}

	int line_2, column_2; //—Œ«ƒ¿Õ»≈ 2-… Ã¿“–»÷€
	double matrix_2[N][N] = {};
	printf("Enter array dimension. When adding matrices they must be the same size.\n");
	do
	{
		printf("The number of lines must be less than 100.\n");
		printf("Number of lines: ");
		scanf("%d", &line_2);
		if ((line_2 < 1) || (line_2 > 100)||(line_2!=line_1))
		{
			printf("Invalid value entered. Try again.\n");
		}
	} while ((line_2 < 1) || (line_2 > 100)||(line_2 != line_1));
	do
	{
		printf("The number of columns must be less than 100.\n");
		printf("Number of columns: ");
		scanf("%d", &column_2);
		if ((column_2 < 1) || (column_2 > 100)||(column_2!=column_1))
		{
			printf("Invalid value entered. Try again.\n");
		}
	} while ((column_2 < 1) || (column_2 > 100)||(column_2 != column_1));

	printf("Enter numbers in the array: \n");

	for (int i = 0; i < line_2; i++)
	{
		for (int j = 0; j < column_2; j++)
		{
			do
			{
				scanf("%lf", &matrix_2[i][j]);
				if ((matrix_2[i][j] > INT_MAX) || (matrix_2[i][j] < INT_MIN)) printf("Invalid value. Try Again.\n");
			} while ((matrix_2[i][j] > INT_MAX) || (matrix_2[i][j] < INT_MIN));
		}
	}

	int line_3=line_1, column_3=column_1; //—Œ«ƒ¿Õ»≈ 3-… Ã¿“–»÷€
	double matrix_3[N][N] = {};

	for (int i = 0; i < line_3; i++)
	{
		for (int j = 0; j < column_3; j++)
		{
			matrix_3[i][j] = matrix_1[i][j] + matrix_2[i][j];
		}
	}
	Matrix_output(matrix_3, &line_3, &column_3);
}

void Matrix_subtraction()
{
	int line_1 = 0, column_1 = 0; //—Œ«ƒ¿Õ»≈ 1-… Ã¿“–»÷€
	double matrix_1[N][N] = {};
	printf("Enter array dimension.\n");
	do
	{
		printf("The number of lines must be less than 100.\n");
		printf("Number of lines: ");
		scanf("%d", &line_1);
		if ((line_1 < 1) || (line_1 > 100))
		{
			printf("Invalid value entered. Try again.\n");
		}
	} while ((line_1 < 1) || (line_1 > 100));
	do
	{
		printf("The number of columns must be less than 100.\n");
		printf("Number of columns: ");
		scanf("%d", &column_1);
		if ((column_1 < 1) || (column_1 > 100))
		{
			printf("Invalid value entered. Try again.\n");
		}
	} while ((column_1 < 1) || (column_1 > 100));

	printf("Enter numbers in the array: \n");

	for (int i = 0; i < line_1; i++)
	{
		for (int j = 0; j < column_1; j++)
		{
			do
			{
				scanf("%lf", &matrix_1[i][j]);
				if ((matrix_1[i][j] > INT_MAX) || (matrix_1[i][j] < INT_MIN)) printf("Invalid value. Try Again.\n");
			} while ((matrix_1[i][j] > INT_MAX) || (matrix_1[i][j] < INT_MIN));
		}
	}

	int line_2, column_2; //—Œ«ƒ¿Õ»≈ 2-… Ã¿“–»÷€
	double matrix_2[N][N] = {};
	printf("Enter array dimension. When adding matrices they must be the same size.\n");
	do
	{
		printf("The number of lines must be less than 100.\n");
		printf("Number of lines: ");
		scanf("%d", &line_2);
		if ((line_2 < 1) || (line_2 > 100) || (line_2 != line_1))
		{
			printf("Invalid value entered. Try again.\n");
		}
	} while ((line_2 < 1) || (line_2 > 100) || (line_2 != line_1));
	do
	{
		printf("The number of columns must be less than 100.\n");
		printf("Number of columns: ");
		scanf("%d", &column_2);
		if ((column_2 < 1) || (column_2 > 100) || (column_2 != column_1))
		{
			printf("Invalid value entered. Try again.\n");
		}
	} while ((column_2 < 1) || (column_2 > 100) || (column_2 != column_1));

	printf("Enter numbers in the array: \n");

	for (int i = 0; i < line_2; i++)
	{
		for (int j = 0; j < column_2; j++)
		{
			do
			{
				scanf("%lf", &matrix_2[i][j]);
				if ((matrix_2[i][j] > INT_MAX) || (matrix_2[i][j] < INT_MIN)) printf("Invalid value. Try Again.\n");
			} while ((matrix_2[i][j] > INT_MAX) || (matrix_2[i][j] < INT_MIN));
		}
	}

	int line_3 = line_1, column_3 = column_1; //—Œ«ƒ¿Õ»≈ 3-… Ã¿“–»÷€
	double matrix_3[N][N] = {};

	for (int i = 0; i < line_3; i++)
	{
		for (int j = 0; j < column_3; j++)
		{
			matrix_3[i][j] = matrix_1[i][j] - matrix_2[i][j];
		}
	}
	Matrix_output(matrix_3, &line_3, &column_3);
}

void Matrix_multiplication() 
{
	int line_1 = 0, column_1 = 0; //—Œ«ƒ¿Õ»≈ 1-… Ã¿“–»÷€
	double matrix_1[N][N] = {};
	printf("Enter array dimension.\n");
	do
	{
		printf("The number of lines must be less than 100.\n");
		printf("Number of lines: ");
		scanf("%d", &line_1);
		if ((line_1 < 1) || (line_1 > 100))
		{
			printf("Invalid value entered. Try again.\n");
		}
	} while ((line_1 < 1) || (line_1 > 100));
	do
	{
		printf("The number of columns must be less than 100.\n");
		printf("Number of columns: ");
		scanf("%d", &column_1);
		if ((column_1 < 1) || (column_1 > 100))
		{
			printf("Invalid value entered. Try again.\n");
		}
	} while ((column_1 < 1) || (column_1 > 100));

	printf("Enter numbers in the array: \n");

	for (int i = 0; i < line_1; i++)
	{
		for (int j = 0; j < column_1; j++)
		{
			do
			{
				scanf("%lf", &matrix_1[i][j]);
				if ((matrix_1[i][j] > INT_MAX) || (matrix_1[i][j] < INT_MIN)) printf("Invalid value. Try Again.\n");
			} while ((matrix_1[i][j] > INT_MAX) || (matrix_1[i][j] < INT_MIN));
		}
	} 

	int line_2, column_2; //—Œ«ƒ¿Õ»≈ 2-… Ã¿“–»÷€
	double matrix_2[N][N] = {};
	printf("Enter array dimension. The lines of the second matrix must match the columns of the first matrix.\n");
	do
	{
		printf("The number of lines must be less than 100.\n");
		printf("Number of lines: ");
		scanf("%d", &line_2);
		if ((line_2 < 1) || (line_2 > 100) || (line_2 != column_1))
		{
			printf("Invalid value entered. Try again.\n");
		}
	} while ((line_2 < 1) || (line_2 > 100) || (line_2 != column_1));
	do
	{
		printf("The number of columns must be less than 100.\n");
		printf("Number of columns: ");
		scanf("%d", &column_2);
		if ((column_2 < 1) || (column_2 > 100))
		{
			printf("Invalid value entered. Try again.\n");
		}
	} while ((column_2 < 1) || (column_2 > 100));

	printf("Enter numbers in the array: \n");

	for (int i = 0; i < line_2; i++)
	{
		for (int j = 0; j < column_2; j++)
		{
			do
			{
				scanf("%lf", &matrix_2[i][j]);
				if ((matrix_2[i][j] > INT_MAX) || (matrix_2[i][j] < INT_MIN)) printf("Invalid value. Try Again.\n");
			} while ((matrix_2[i][j] > INT_MAX) || (matrix_2[i][j] < INT_MIN));
		}
	} 

	int line_3 = line_1, column_3 = column_2; //—Œ«ƒ¿Õ»≈ 3-… Ã¿“–»÷€
	double matrix_3[N][N] = {0};

	for (int i = 0; i < line_3; i++)
	{
		for (int j = 0; j < column_3; j++)
		{
			int p = 0, q = 0;
			do
			{
				matrix_3[i][j] = matrix_3[i][j] + matrix_1[i][q] * matrix_2[p][j];
				p += 1; q += 1;
			} while (p<=column_3);
		}
	}
	Matrix_output(matrix_3, &line_3, &column_3);
}

void Matrix_multiplication_by_number()
{
	int line_1 = 0, column_1 = 0; //—Œ«ƒ¿Õ»≈ 1-… Ã¿“–»÷€
	double matrix_1[N][N] = {};
	printf("Enter array dimension.\n");
	do
	{
		printf("The number of lines must be less than 100.\n");
		printf("Number of lines: ");
		scanf("%d", &line_1);
		if ((line_1 < 1) || (line_1 > 100))
		{
			printf("Invalid value entered. Try again.\n");
		}
	} while ((line_1 < 1) || (line_1 > 100));
	do
	{
		printf("The number of columns must be less than 100.\n");
		printf("Number of columns: ");
		scanf("%d", &column_1);
		if ((column_1 < 1) || (column_1 > 100))
		{
			printf("Invalid value entered. Try again.\n");
		}
	} while ((column_1 < 1) || (column_1 > 100));

	printf("Enter numbers in the array: \n");

	for (int i = 0; i < line_1; i++)
	{
		for (int j = 0; j < column_1; j++)
		{
			do
			{
				scanf("%lf", &matrix_1[i][j]);
				if ((matrix_1[i][j] > INT_MAX) || (matrix_1[i][j] < INT_MIN)) printf("Invalid value. Try Again.\n");
			} while ((matrix_1[i][j] > INT_MAX) || (matrix_1[i][j] < INT_MIN));
		}
	} 

	double number=0;
	printf("Enter the number: ");
	do
	{
		scanf("%lf", &number);
		if ((number > INT_MAX) || (number < INT_MIN)) printf("Invalid value. Try Again.\n Enter the number = ");
	} while ((number > INT_MAX) || (number < INT_MIN));

	int line_3 = line_1, column_3 = column_1; //—Œ«ƒ¿Õ»≈ 3-… Ã¿“–»÷€
	double matrix_3[N][N] = { 0 };

	for (int i = 0; i < line_3; i++)
	{
		for (int j = 0; j < column_3; j++)
		{
			matrix_3[i][j] = matrix_1[i][j] * number;
		}
	}
	Matrix_output(matrix_3, &line_3, &column_3);
}

void Addition_of_a_matrix_with_a_number()
{
	int line_1 = 0, column_1 = 0; //—Œ«ƒ¿Õ»≈ 1-… Ã¿“–»÷€
	double matrix_1[N][N] = {};
	printf("Enter array dimension.\n");
	do
	{
		printf("The number of lines must be less than 100.\n");
		printf("Number of lines: ");
		scanf("%d", &line_1);
		if ((line_1 < 1) || (line_1 > 100))
		{
			printf("Invalid value entered. Try again.\n");
		}
	} while ((line_1 < 1) || (line_1 > 100));
	do
	{
		printf("The number of columns must be less than 100.\n");
		printf("Number of columns: ");
		scanf("%d", &column_1);
		if ((column_1 < 1) || (column_1 > 100))
		{
			printf("Invalid value entered. Try again.\n");
		}
	} while ((column_1 < 1) || (column_1 > 100));

	printf("Enter numbers in the array: \n");

	for (int i = 0; i < line_1; i++)
	{
		for (int j = 0; j < column_1; j++)
		{
			do
			{
				scanf("%lf", &matrix_1[i][j]);
				if ((matrix_1[i][j] > INT_MAX) || (matrix_1[i][j] < INT_MIN)) printf("Invalid value. Try Again.\n");
			} while ((matrix_1[i][j] > INT_MAX) || (matrix_1[i][j] < INT_MIN));
		}
	}

	double number;
	printf("Enter the number: ");
	do
	{
		scanf("%lf", &number);
		if ((number > INT_MAX) || (number < INT_MIN)) printf("Invalid value. Try Again.\n Enter the number = ");
	} while ((number > INT_MAX) || (number < INT_MIN));

	int line_3 = line_1, column_3 = column_1; //—Œ«ƒ¿Õ»≈ 3-… Ã¿“–»÷€
	double matrix_3[N][N] = { 0 };

	for (int i = 0; i < line_3; i++)
	{
		for (int j = 0; j < column_3; j++)
		{
			matrix_3[i][j] = matrix_1[i][j] + number;
		}
	}
	Matrix_output(matrix_3, &line_3, &column_3);
}

void Matrix_transposition()
{
	int line_1 = 0, column_1 = 0; //—Œ«ƒ¿Õ»≈ 1-… Ã¿“–»÷€
	double matrix_1[N][N] = {};
	printf("Enter array dimension.\n");
	do
	{
		printf("The number of lines must be less than 100.\n");
		printf("Number of lines: ");
		scanf("%d", &line_1);
		if ((line_1 < 1) || (line_1 > 100))
		{
			printf("Invalid value entered. Try again.\n");
		}
	} while ((line_1 < 1) || (line_1 > 100));
	do
	{
		printf("The number of columns must be less than 100.\n");
		printf("Number of columns: ");
		scanf("%d", &column_1);
		if ((column_1 < 1) || (column_1 > 100))
		{
			printf("Invalid value entered. Try again.\n");
		}
	} while ((column_1 < 1) || (column_1 > 100));

	printf("Enter numbers in the array: \n");

	for (int i = 0; i < line_1; i++)
	{
		for (int j = 0; j < column_1; j++)
		{
			do
			{
				scanf("%lf", &matrix_1[i][j]);
				if ((matrix_1[i][j] > INT_MAX) || (matrix_1[i][j] < INT_MIN)) printf("Invalid value. Try Again.\n");
			} while ((matrix_1[i][j] > INT_MAX) || (matrix_1[i][j] < INT_MIN));
		}
	}

	int line_3 = column_1, column_3 = line_1; //—Œ«ƒ¿Õ»≈ 3-… Ã¿“–»÷€
	double matrix_3[N][N] = { 0 };
	for (int i = 0; i < line_3; i++)
	{
		for (int j = 0; j < column_3; j++)
		{
			matrix_3[i][j] = matrix_1[j][i];
		}
	}
	Matrix_output(matrix_3, &line_3, &column_3);
}

void Determinant()
{
	int line_1 = 0, column_1 = 0; //—Œ«ƒ¿Õ»≈ 1-… Ã¿“–»÷€
	double matrix_1[N][N] = {};
	printf("Enter array dimension.\n");
	do
	{
		printf("The number of lines must be less than 100.\n");
		printf("Number of lines: ");
		scanf("%d", &line_1);
		if ((line_1 < 1) || (line_1 > 100))
		{
			printf("Invalid value entered. Try again.\n");
		}
	} while ((line_1 < 1) || (line_1 > 100));
	do
	{
		printf("The number of columns must be less than 100.\n");
		printf("Number of columns: ");
		scanf("%d", &column_1);
		if ((column_1 < 1) || (column_1 > 100)||(column_1!=line_1))
		{
			printf("Invalid value entered. Try again.\n");
		}
	} while ((column_1 < 1) || (column_1 > 100) || (column_1 != line_1));

	printf("Enter numbers in the array: \n");

	for (int i = 0; i < line_1; i++)
	{
		for (int j = 0; j < column_1; j++)
		{
			do
			{
				scanf("%lf", &matrix_1[i][j]);
				if ((matrix_1[i][j] > INT_MAX) || (matrix_1[i][j] < INT_MIN)) printf("Invalid value. Try Again.\n");
			} while ((matrix_1[i][j] > INT_MAX) || (matrix_1[i][j] < INT_MIN));
		}
	}

	int p = 0;
	double kst;
	for (int i = 0; i < line_1 - 1; i++)
	{
		int t = 1;
		while (matrix_1[i][i] == 0)
		{
			for (int j = 0; j < line_1; j++)
			{
				matrix_1[i][j] = kst;
				matrix_1[i][j] = matrix_1[i + t][j];
				matrix_1[i + t][j] = kst;
			}
			p++;
			t++;
		}
		for (int k = i + 1; k < line_1; k++)
		{
			kst = matrix_1[k][i] / matrix_1[i][i];
			for (int j = 0; j < line_1; j++) matrix_1[k][j] -= matrix_1[i][j] * kst;
		}
	}
	kst = pow(-1, p);
	for (int i = 0; i < line_1; i++) kst *= matrix_1[i][i];
	if (kst == -0) kst = 0;
	printf("Determinant: %lf\n", kst);
}

void Inverse_matrix()
{
	int line_3 = 0, column_3 = 0; //—Œ«ƒ¿Õ»≈ 1-… Ã¿“–»÷€
	double matrix_3[N][N] = {};
	printf("Enter array dimension.\n");
	do
	{
		printf("The number of lines must be less than 100.\n");
		printf("Number of lines: ");
		scanf("%d", &line_3);
		if ((line_3 < 1) || (line_3 > 100))
		{
			printf("Invalid value entered. Try again.\n");
		}
	} while ((line_3 < 1) || (line_3 > 100));
	do
	{
		printf("The number of columns must be less than 100.\n");
		printf("Number of columns: ");
		scanf("%d", &column_3);
		if ((column_3 < 1) || (column_3 > 100) || (column_3 != line_3))
		{
			printf("Invalid value entered. Try again.\n");
		}
	} while ((column_3 < 1) || (column_3 > 100) || (column_3 != line_3));

	printf("Enter numbers in the array: \n");

	for (int i = 0; i < line_3; i++)
	{
		for (int j = 0; j < column_3; j++)
		{
			do
			{
				scanf("%lf", &matrix_3[i][j]);
				if ((matrix_3[i][j] > INT_MAX) || (matrix_3[i][j] < INT_MIN)) printf("Invalid value. Try Again.\n");
			} while ((matrix_3[i][j] > INT_MAX) || (matrix_3[i][j] < INT_MIN));
		}
	}

	double temp;
	double matrix_2[N][N] = {};

	for (int i = 0; i < line_3; i++)
		for (int j = 0; j < line_3; j++)
		{
			matrix_2[i][j] = 0.0;

			if (i == j)
				matrix_2[i][j] = 1.0;
		}

	for (int k = 0; k < line_3; k++)
	{
		temp = matrix_3[k][k];

		for (int j = 0; j < line_3; j++)
		{
			matrix_3[k][j] /= temp;
			matrix_2[k][j] /= temp;
		}

		for (int i = k + 1; i < line_3; i++)
		{
			temp = matrix_3[i][k];

			for (int j = 0; j < line_3; j++)
			{
				matrix_3[i][j] -= matrix_3[k][j] * temp;
				matrix_2[i][j] -= matrix_2[k][j] * temp;
			}
		}
	}

	for (int k = line_3 - 1; k > 0; k--)
	{
		for (int i = k - 1; i >= 0; i--)
		{
			temp = matrix_3[i][k];

			for (int j = 0; j < line_3; j++)
			{
				matrix_3[i][j] -= matrix_3[k][j] * temp;
				matrix_2[i][j] -= matrix_2[k][j] * temp;
			}
		}
	}

	for (int i = 0; i < line_3; i++)
	{
		for (int j = 0; j < line_3; j++)
		{
			matrix_3[i][j] = matrix_2[i][j];
		}
	}
	
	Matrix_output(matrix_3, &line_3, &column_3);
}

void Matrix_output(double matrix_3[][N], int *line_3, int *column_3)
{
	for (int i = 0; i < *line_3; i++)
	{
		for (int j = 0; j < *column_3; j++)
		{
			printf("%10.3lf ", matrix_3[i][j]);
		}
		printf("\n");
	}
}