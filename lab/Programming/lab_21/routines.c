#include "main.h"

int SDL_Init_All(struct SDL_Window **window, struct SDL_Renderer **renderer) {

    /* SDL2 */
    SDL_Init(SDL_INIT_VIDEO);
    if ((*window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)) < 0) {
        return 0;
    } else if (!(*renderer = SDL_CreateRenderer(*window, -1, 0))) {
        return 0;
    }

    /* Returning value */
    return 1;
}

void set_coord(struct dva_mas *dva, int init, int argc) {

    /* Initializing variables */
    int i;

    /* Main part */
    if (init) {
        for (i = 0; i < SIZE; ++i) {
            dva->mas[i].x = rand() % WIDTH + 1;
            dva->mas[i].y = rand() % HEIGHT + 1;
            dva->mas[i].multiplier = (rand() % 3) - 1;
            dva->mas[i].x_vel = (rand() % (MAX_VEL_X - MIN_VEL_X + 1)) + MIN_VEL_X;
            dva->mas[i].y_vel = (rand() % (MAX_VEL_Y - MIN_VEL_Y + 1)) + MIN_VEL_Y;
        }
    } else {
        for (i = 0; i < SIZE; ++i) {
            dva->mas[i].x += dva->mas[i].x_vel * dva->mas[i].multiplier;
            dva->mas[i].y += dva->mas[i].y_vel;

            if (dva->mas[i].x > WIDTH) {
                dva->mas[i].x -= WIDTH;
            } else if (dva->mas[i].x < 0) {
                dva->mas[i].x += WIDTH;
            }

            if (argc) {
                if (dva->mas[i].y > HEIGHT - dva->snow[dva->mas[i].x].h) {
                    dva->mas[i].y -= HEIGHT;

                    if (!dva->snow[dva->mas[i].x].y) {
                        dva->snow[dva->mas[i].x].x = dva->mas[i].x;
                        dva->snow[dva->mas[i].x].y = HEIGHT - RECT_H;
                        dva->snow[dva->mas[i].x].w = RECT_W;
                    } else {
                        dva->snow[dva->mas[i].x].y -= RECT_H;
                    }
                    dva->snow[dva->mas[i].x].h += RECT_H;
                }
            } else {
                if (dva->mas[i].y > HEIGHT) {
                    dva->mas[i].y -= HEIGHT;
                }
            }
        }
    }
}