#include "Header_Calc.h"
#include "Functional_Header.h"

double f(double x)
{
	return x * x * x;
}

void Functional_Menu()
{
	int type = -1;
	int output = 0;
	int Continue = 1;

	do
	{
		type = -1;
		printf("\nChoose your function type:\n"
			"0. Cancel\n"
			"1. Polynomial\n"
			"2. Power\n"
			"3. Exponential\n"
			"4. Logarithm\n"
			"5. Sinusoid\n"
			"6. Cosinusoid\n");
		while (!(0 <= type && type <= types_finish - types_start + 1))
		{
			printf("You choose: ");
			scanf("%i", &type);
		}
		type += (types_start - 1);

		if (type == 0)
			break;

		output = -1;
		printf("\nChoose your output type:\n"
			"0. Cancel\n"
			"1. Integral\n"
			"2. Graph\n"
			"3. Root\n"
			"4. Extremum\n"
			);
		while (!(0 <= output && output <= output_finish - output_start + 1))
		{
			printf("You choose: ");
			scanf("%i", &output);
		}
		output += (output_start - 1);

		if (output == 0)
			break;

		switch (output)
		{
		case integral:

			Functional_Integral(type);
			break;
		case graph:

			Functional_Graph(type);
			break;
		case root:

			Functional_Root(type);
			break;
		case extremum:

			extremum_functions(type);
			break;
		}
	} while (true);
}

inline double Functional_Absolute(double x)
{
	return (x < 0 ? -x : x);
}

double Functional_CalcPolynomial(double x, double a[MAX_LENGTH_ARRAY], double N)
{
	double sum = 0.0;
	double p = 1.0;

	for (int i = 0; i < N; i++)
	{
		sum += a[i] * p;
		p *= x;
	}

	return sum;
}
inline double Functional_CalcPower(double x, double a, double b, double c, double d)
{
	return a * pow(x, b) + c;
}
inline double Functional_CalcExponential(double x, double a, double b, double c, double d)
{
	return a * pow(b, c * x) + d;
}
inline double Functional_CalcLogarithm(double x, double a, double b, double c, double d)
{
	return a * log(b * x) + c;
}
inline double Functional_CalcSinusoid(double x, double a, double b, double c, double d)
{
	return a * sin(b * x + c) + d;
}
inline double Functional_CalcCosinusoid(double x, double a, double b, double c, double d)
{
	return a * cos(b * x + c) + d;
}

void Functional_InitArgs(int type, double params[MAX_VARIABLES], double polynoms[MAX_LENGTH_ARRAY])
{
	int amount = 0;

	switch (type)
	{
	case polynomial:

		while (!(0 <= params[0] && params[0] <= 100))
		{
			printf("Enter the maximum degree of the polyhomial: ");
			scanf("%lf", &params[0]);
		}
		params[0] += 1;
		for (int i = 0; i < params[0]; i++)
		{
			printf("Input x^%d of polynom: ", i);
			scanf("%lf", &polynoms[i]);
		}

		return;

	case power:
	case logarithm:

		printf("Input a, b, c: ");
		amount = 3;
		break;

	case exponential:
	case sinusoid:
	case cosinusoid:

		printf("Input a, b, c, d: ");
		amount = 4;
		break;
	}

	for (int i = 0; i < amount; i++)
		scanf("%lf", &params[i]);
}

void Functional_Integral(int type)
{
	double params[MAX_VARIABLES] = { -1 };
	double polynoms[MAX_LENGTH_ARRAY];

	Functional_InitArgs(type, params, polynoms);

	// -1 = without polynomial
	double(*Functional_Functions[types_finish - types_start + 1 - 1])
		(double x, double a, double b, double c, double d) =
	{
		// without polynomial
		Functional_CalcPower,
		Functional_CalcExponential,
		Functional_CalcLogarithm,
		Functional_CalcSinusoid,
		Functional_CalcCosinusoid
	};
	type = type - 1 - 1;

	double Integral;
	double start;
	double finish;
	double parts;
	double growth = 0.1;

	printf("Enter the beginning of the segment: ");
	scanf("%lf", &start);

	finish = start - 1;
	while (finish < start)
	{
		printf("Enter the end of the segment: ");
		scanf("%lf", &finish);
	}

	parts = (finish - start) / growth;

	if (type + 1 + 1 == polynomial)
	{
		Integral = growth * (
			Functional_CalcPolynomial(start, polynoms, params[0]) +
			Functional_CalcPolynomial(finish, polynoms, params[0])) / 6.0;

		for (int i = 1; i <= parts; i++)
			Integral = Integral + 4.0 / 6.0 * growth *
			Functional_CalcPolynomial(start + growth * (i - 0.5), polynoms, params[0]);

		for (int i = 1; i <= parts - 1; i++)
			Integral = Integral + 2.0 / 6.0 * growth *
			Functional_CalcPolynomial(start + growth * i, polynoms, params[0]);
	}
	else
	{
		Integral = growth * (
			Functional_Functions[type](start, params[0], params[1], params[2], params[3]) +
			Functional_Functions[type](finish, params[0], params[1], params[2], params[3])) / 6.0;

		for (int i = 1; i <= parts; i++)
			Integral = Integral + 4.0 / 6.0 * growth *
			Functional_Functions[type](start + growth * (i - 0.5),
				params[0], params[1], params[2], params[3]);

		for (int i = 1; i <= parts - 1; i++)
			Integral = Integral + 2.0 / 6.0 * growth *
			Functional_Functions[type](start + growth * i,
				params[0], params[1], params[2], params[3]);
	}
	printf("Answer: %lf\n", Integral);
}

void Functional_Graph(int type)
{
	double params[MAX_VARIABLES] = { -1 };
	double polynoms[MAX_LENGTH_ARRAY];

	Functional_InitArgs(type, params, polynoms);

	// -1 = without polynomial
	double(*Functional_Functions[types_finish - types_start + 1 - 1])
		(double x, double a, double b, double c, double d) =
	{
		// without polynomial
		Functional_CalcPower,
		Functional_CalcExponential,
		Functional_CalcLogarithm,
		Functional_CalcSinusoid,
		Functional_CalcCosinusoid
	};
	type = type - 1 - 1;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	window = SDL_CreateWindow("Graphic",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGTH, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, SDL_GetError());
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, SDL_GetError());
		return;
	}

	SDL_SetRenderDrawColor(renderer, 66, 66, 66, 0);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

	// Rendering axis
	SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGTH / 2, SCREEN_WIDTH, SCREEN_HEIGTH / 2);			// oX
	SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGTH);			// oY

	// Rendering arrays
	SDL_RenderDrawLine(renderer, SCREEN_WIDTH - 15, SCREEN_HEIGTH / 2 - 5, SCREEN_WIDTH, SCREEN_HEIGTH / 2);// oX
	SDL_RenderDrawLine(renderer, SCREEN_WIDTH - 15, SCREEN_HEIGTH / 2 + 5, SCREEN_WIDTH, SCREEN_HEIGTH / 2);// oX
	SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2 - 5, 15, SCREEN_WIDTH / 2, 0);				// oY
	SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2 + 5, 15, SCREEN_WIDTH / 2, 0);				// oY

	for (int i = 0; i < SCREEN_WIDTH / 10; i++)
	{
		SDL_RenderDrawPoint(renderer, 10 * i, SCREEN_HEIGTH / 2 + 1);					// oX
	}
	for (int i = 0; i < SCREEN_HEIGTH / 10; i++)
	{
		SDL_RenderDrawPoint(renderer, SCREEN_WIDTH / 2 - 1, 10 * i);					// oX
	}

	SDL_Point last = { SCREEN_WIDTH, -1 };
	SDL_Point current = { SCREEN_WIDTH, -1 };

	if (type == polynomial - 1 - 1)
	{
		for (double x = -SCREEN_WIDTH; x < SCREEN_WIDTH; x++)
		{
			for (double y = -SCREEN_HEIGTH; y < SCREEN_HEIGTH; y++)
			{
				if (Functional_Absolute(Functional_CalcPolynomial(x / 10, polynoms, params[0]) - y / 10) <= 0.01 * params[0])
				{
					if (last.x == SCREEN_WIDTH)
					{
						last.x = SCREEN_WIDTH / 2 + (int)x;
						last.y = SCREEN_HEIGTH / 2 - (int)y;
					}
					else if (current.x == SCREEN_WIDTH)
					{
						current.x = SCREEN_WIDTH / 2 + (int)x;
						current.y = SCREEN_HEIGTH / 2 - (int)y;
					}

					else
					{
						SDL_RenderDrawLine(renderer, last.x, last.y, current.x, current.y);

						last = current;
						current.x = SCREEN_WIDTH / 2 + (int)x;
						current.y = SCREEN_HEIGTH / 2 - (int)y;
					}
				}
			}
		}
	}
	else
	{
		for (double x = -SCREEN_WIDTH; x < SCREEN_WIDTH; x++)
		{
			for (double y = -SCREEN_HEIGTH; y < SCREEN_HEIGTH; y++)
			{
				if (Functional_Absolute(Functional_Functions[type]
				(x / 10, params[0], params[1], params[2], params[3]) - y / 10) <= 0.01 * params[1])
				{
					if (last.x == SCREEN_WIDTH)
					{
						last.x = SCREEN_WIDTH / 2 + (int)x;
						last.y = SCREEN_HEIGTH / 2 - (int)y;
					}
					else if (current.x == SCREEN_WIDTH)
					{
						current.x = SCREEN_WIDTH / 2 + (int)x;
						current.y = SCREEN_HEIGTH / 2 - (int)y;
					}

					else
					{
						SDL_RenderDrawLine(renderer, last.x, last.y, current.x, current.y);

						last = current;
						current.x = SCREEN_WIDTH / 2 + (int)x;
						current.y = SCREEN_HEIGTH / 2 - (int)y;
					}
				}
			}
		}
	}


	SDL_RenderPresent(renderer);

	while (1)
	{
		SDL_Event e;
		SDL_PollEvent(&e);

		if (e.type == SDL_QUIT)
			break;
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

void Functional_Root(int type)
{
	double params[MAX_VARIABLES] = { -1 };
	double polynoms[MAX_LENGTH_ARRAY];

	Functional_InitArgs(type, params, polynoms);

	// -1 = without polynomial
	double(*Functional_Functions[types_finish - types_start + 1 - 1])
		(double x, double a, double b, double c, double d) =
	{
		// without polynomial
		Functional_CalcPower,
		Functional_CalcExponential,
		Functional_CalcLogarithm,
		Functional_CalcSinusoid,
		Functional_CalcCosinusoid
	};
	type = type - 1 - 1;

	double start;
	double finish;
	double growth = 0.01;

	int isFound = 0;

	printf("Enter the beginning of the segment: ");
	scanf("%lf", &start);

	finish = start - 1;
	while (finish < start)
	{
		printf("Enter the end of the segment: ");
		scanf("%lf", &finish);
	}

	// x = start + growth * N .. finish
	if (type + 1 + 1 == polynomial)
	{
		while (start <= finish)
		{
			double y = Functional_CalcPolynomial(start, polynoms, params[0]);

			if (Functional_Absolute(y) <= growth * 3)
			{
				printf("When x = %lf, the function is %lf\n", start, y);
				isFound = 1;
			}

			start += growth;
		}
	}
	else
	{
		while (start <= finish)
		{
			double y = Functional_Functions[type]
			(start, params[0], params[1], params[2], params[3]);

			if (Functional_Absolute(y) <= growth * 3)
			{
				printf("When x = %lf, the function is %lf\n", start, y);
				isFound = 1;
			}

			start += growth;
		}
	}

	if (!isFound)
	{
		printf("There are no roots in this segment.\n");
	}
}

void extremum_functions(int type)
{
	int amount_temp = 0;
	double comp1 = 0, comp2 = 0, derivative[11];
	Function func;
	for (int i = 100; i >= 0; i--)
	{
		func.extrem[i] = 10000;
		if (i < 11)
		{
			derivative[i] = 0;
			func.coef[i] = 0;
			if (i < 4)
			{
				func.params[i] = 0;
			}
		}
	}

	switch (type)
	{
	case 1:

		input_values(&func, 1);


		for (int i = 10; i > 0; i--)
		{
			derivative[i - 1] = func.coef[i] * i;

		}

		for (double i = func.from; i < func.to; i += 0.01)
		{
			comp1 = (derivative[9] * pow(i, 9) + derivative[8] * pow(i, 8) + derivative[7] * pow(i, 7) + derivative[6] * pow(i, 6) + derivative[5] * pow(i, 5) + derivative[4] * pow(i, 4) + derivative[3] * pow(i, 3) + derivative[2] * pow(i, 2) + derivative[1] * pow(i, 1) + derivative[0]);
			comp2 = (derivative[9] * pow(i + i, 9) + derivative[8] * pow(i + i, 8) + derivative[7] * pow(i + i, 7) + derivative[6] * pow(i + i, 6) + derivative[5] * pow(i + i, 5) + derivative[4] * pow(i + i, 4) + derivative[3] * pow(i + i, 3) + derivative[2] * pow(i + i, 2) + derivative[1] * pow(i + i, 1) + derivative[0]);
			if (comp1*comp2 < 0)
			{
				func.extrem[amount_temp] = i;
				amount_temp++;
				i += 0.5;
			}
		}

		break;

	case 2: // a*x^b+c
		input_values(&func, 2);


		derivative[0] = func.params[0] * func.params[1];
		derivative[1] = func.params[1] - 1;
		if ((int)derivative[1] % 2 != 0 && derivative[0] != 0)
		{
			func.extrem[0] = 0;
			amount_temp++;
		}
		break;

	case 3: // a*b^(c*x)+d
		input_values(&func, 3);


		derivative[0] = func.params[0] * func.params[1] * func.params[2];
		for (double i = func.from; i < func.to; i += 0.05)
		{
			comp1 = pow(derivative[0], (func.params[2] * i) - 1);
			comp2 = pow(derivative[0], (func.params[2] * i + i) - 1);
			if (comp1*comp2 < 0)
			{
				func.extrem[amount_temp] = i;
				amount_temp++;
				i++;
			}
		}
		break;

	case 4: // a*ln(b*x)+c
		input_values(&func, 4);
		for (double i = func.from; i < func.to; i += 0.01)
		{
			comp1 = (func.params[0]) / (i);
			comp2 = (func.params[0]) / (i + i);
			if (comp1*comp2 < 0)
			{
				func.extrem[amount_temp] = i;
				amount_temp++;
				i += 0.1;
			}
		}
		break;

	case 5: // a*sin(b*x+c)+d
		input_values(&func, 5);
		for (double i = func.from; i < func.to; i += 0.0001)
		{
			comp1 = (func.params[0] * func.params[1]) * cos(func.params[1] * i + func.params[2]);
			comp2 = comp1 + 0.01;
			if (comp1*comp2 < 0)
			{
				func.extrem[amount_temp] = i;
				amount_temp++;
				i += 0.1;
			}
		}
		break;

	case 6: // a*cos(b*x+c)+d
		input_values(&func, 6);
		for (double i = func.from; i < func.to; i += 0.0001)
		{
			comp1 = (func.params[0] * func.params[1]) * (-sin(func.params[1] * i + func.params[2]));
			comp2 = comp1 + 0.01;
			if (comp1*comp2 < 0)
			{
				func.extrem[amount_temp] = i;
				amount_temp++;
				i += 0.1;
			}
		}
		break;
	}

	printf("\nExtremums of function(approximately):");
	if (amount_temp == 0)
	{
		printf("\nNo critical points\n");
	}
	else
	{
		for (int i = 100; i >= 0; i--)
		{
			if (func.extrem[i] != 10000)
			{
				printf("\nx = %.2lf;", func.extrem[i]);
			}
		}
	}

}

void input_values(Function * func, int type)
{
	int tmp;
	switch (type)
	{
	case 1:

		do
		{
			printf("\nEnter the maximal degree of the polynomial: ");
			scanf("%d", &tmp);
		} while (tmp < 0 || tmp>10);

		for (int i = tmp; i >= 0; i--)
		{
			printf("\nCoeficient before x^%d: ", i);
			scanf("%lf", &func->coef[i]);
		}
		break;

	case 2:
	case 4:

		printf("Input a, b, c: ");
		tmp = 3;
		for (int i = 0; i < tmp; i++)
		{
			scanf("%lf", &func->params[i]);
		}
		break;

	case 3:
	case 5:
	case 6:

		printf("Input a, b, c, d: ");
		tmp = 4;
		for (int i = 0; i < tmp; i++)
		{
			scanf("%lf", &func->params[i]);
		}
		break;
	}
	while (true)
	{
		printf("Enter the beginning of the segment: ");
		scanf("%lf", &func->from);
		printf("Enter the end of the segment: ");
		scanf("%lf", &func->to);
		if (func->from > func->to)
		{
			double temp = func->from;
			func->from = func->to;
			func->to = temp;
		}
		if (fabs(func->from) + fabs(func->to) < 99)
		{
			break;
		}
		printf("\nToo much\n\n");
	}
}