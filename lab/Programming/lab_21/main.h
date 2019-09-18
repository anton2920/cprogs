#ifndef MAIN_HEADER_LAB_21
#define MAIN_HEADER_LAB_21

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#define TITLE ("lab_21")
#define WIDTH (800)
#define HEIGHT (800)

#define DELAY (16)
#define ITER (500)
#define SIZE (200)

#define MAX_VEL_X (1)
#define MIN_VEL_X (0)
#define MAX_VEL_Y (6)
#define MIN_VEL_Y (4)

#define RECT_W (3)
#define RECT_H (3)

struct point {
    int x;
    int y;
    int multiplier;
    int x_vel;
    int y_vel;
};

struct dva_mas {
    struct point mas[SIZE];
    struct SDL_Rect snow[WIDTH];
};

/* routines.c */
int SDL_Init_All(struct SDL_Window **, struct SDL_Renderer **);
void set_coord(struct dva_mas *, int, int);

#endif
