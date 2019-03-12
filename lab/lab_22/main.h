#ifndef MAIN_H_LAB_22
#define MAIN_H_LAB_22

#include <stdio.h>
#include <SDL2/SDL.h>

#define TITLE ("lab_22")
#define WIDTH (800)
#define HEIGHT (800)

#define TRUE (1)
#define FALSE (0)

#define DELETE (0)
#define SMALL (1)
#define BIG (2)

#define SMALL_RECT (30)
#define BIG_RECT (80)

#define SIZE (100)
#define DELAY (10)

struct square {
    int size;
    struct SDL_Rect rect;
};

enum bool {
	false = FALSE,
    true = TRUE
};

/* routines.c */
int SDL_Init_All(struct SDL_Window **, struct SDL_Renderer **);
struct square *add_square(struct square *, int, int, int);
void draw_squares(struct SDL_Renderer *, struct square *, struct square *);
void delete_square_queue(struct square *, struct square *);
struct square *delete_square_stack(struct square *);
void delete_all(struct square *);
struct square *find_square(struct square *, struct square *, int, int);

#endif