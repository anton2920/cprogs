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

void rand_clr(int *red, int *green, int *blue) {

    /* Main part */
    *red = rand() % 256;
    *green = rand() % 256;
    *blue = rand() % 256;

    if (*red == 0xFF && *green == 0xFF && *blue == 0xFF) {
        rand_clr(red, green, blue);
    }
}

double func(double x, double a, double c) {

    /* Returning value */
    return a * x * x * x + c;
}