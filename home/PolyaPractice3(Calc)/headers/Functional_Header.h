#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include <SDL2/SDL.h>
#include <string.h>

#define SCREEN_WIDTH		800
#define SCREEN_HEIGTH		640

#define MAX_LENGTH_ARRAY	100
#define MAX_VARIABLES		5

// sqrt(SCREEN_WIDTH * SCREEN_WIDTH / 4 + SCREEN_HEIGTH * SCREEN_HEIGTH / 4) = 512.24994...
#define MAX_POINTS		512

typedef struct
{
	double coef[11], params[4], from, to, extrem[101];
} Function;

enum
{
	cancel,

	types_start,
	polynomial = types_start,
	power,
	exponential,
	logarithm,
	sinusoid,
	cosinusoid,
	types_finish = cosinusoid,

	output_start,
	integral = output_start,
	graph,
	root,
	extremum,
	output_finish = extremum
};

void Functional_Menu();

void Functional_Integral(int type);
void Functional_Graph(int type);
void Functional_Root(int type);
//void Functional_Extremum(int type);
void extremum_functions(int type);
void input_values(Function * func, int type);

#endif // !FUNCTIONAL_H
