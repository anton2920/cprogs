// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#ifndef DEBUG
#define DEBUG

typedef struct
{
	float coef[11];
}polinom;

int main_polinom(); // 
void sum_polinoms(); // completed
void difference_polinoms(); // completed
void multiplication_polinoms(); // completed
void multiplication_polinom_by_number(); // completed
void derinative_polinom();// completed
void division_polinom();
void filling_polinom(polinom *polm, int n); //completed
void result_polinom(polinom *polm, int n); //completed
int check_continue(); // completed

#endif