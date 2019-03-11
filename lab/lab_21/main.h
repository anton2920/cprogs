#ifndef MAIN_HEADER_LAB_21
#define MAIN_HEADER_LAB_21

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#define WIDTH (800)
#define HEIGHT (800)
#define DELAY (20)
#define SIZE (200)
#define MAX_VEL_X (5)
#define MIN_VEL_X (0)
#define MAX_VEL_Y (15)
#define MIN_VEL_Y (10)
#define RECT_W (4)
#define RECT_H (4)

struct point {
    int x;
    int y;
    int multiplier;
    int x_vel;
    int y_vel;
};

/* routines.c */
int SDL_Init_All(struct SDL_Window **, struct SDL_Renderer **);
void set_coord(struct point *, int);

#endif
