#ifndef PRO_HEADER
#define PRO_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#define WIDTH (800)
#define HEIGHT (800)
#define CENTER_X (WIDTH / 2)
#define CENTER_Y (HEIGHT / 2)
#define MULTIPLIER (4)

struct point {
    int x;
    int y;
};

struct diapazon {
    int left_x;
    int right_x;
};

/* tasks.c */
void sub_1(struct SDL_Renderer **);
void sub_2(struct SDL_Renderer **);
void sub_3(struct SDL_Renderer **, struct diapazon *, int, int);

/* routines.c */
int SDL_Init_All(struct SDL_Window **, struct SDL_Renderer **);
void rand_clr(int *, int *, int *);
int func(int, int, int);

#endif