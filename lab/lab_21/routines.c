#include "main.h"

int SDL_Init_All(struct SDL_Window **window, struct SDL_Renderer **renderer) {

    /* SDL2 */
    SDL_Init(SDL_INIT_VIDEO);
    if ((*window = SDL_CreateWindow("lab_20", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)) < 0) {
        return 0;
    } else if (!(*renderer = SDL_CreateRenderer(*window, -1, 0))) {
        return 0;
    }

    /* Returning value */
    return 1;
}

void set_coord(struct point *mas, int init) {

    /* Initializing variables */
    int i;

    /* Main part */
    if (init) {
        for (i = 0; i < SIZE; ++i, ++mas) {
            mas->x = rand() % WIDTH + 1;
            mas->y = rand() % HEIGHT + 1;
            mas->multiplier = (rand() % 3) - 1;
            mas->x_vel = (rand() % (MAX_VEL_X - MIN_VEL_X + 1)) + MIN_VEL_X;
            mas->y_vel = (rand() % (MAX_VEL_Y - MIN_VEL_Y + 1)) + MIN_VEL_Y;
        }
    } else {
        for (i = 0; i < SIZE; ++i, ++mas) {
            mas->x += mas->x_vel * mas->multiplier;
            mas->y += mas->y_vel;

            if (mas->x > WIDTH) {
                mas->x -= WIDTH;
            } else if (mas->x < 0) {
                mas->x += WIDTH;
            }

            if (mas->y > HEIGHT) {
                mas->y -= HEIGHT;
            }
        }
    }
}