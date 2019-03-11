#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#define WIDTH (800)
#define HEIGHT (800)
#define DELAY (10)
#define SIZE (200)
#define MAX_VEL_X (1)
#define MIN_VEL_X (0)
#define MAX_VEL_Y (7)
#define MIN_VEL_Y (5)
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

struct point2 {
    int is_on;
};

int SDL_Init_All(struct SDL_Window **, struct SDL_Renderer **);
void set_coord(struct dva_mas *, int);

int main(int argc, const char *argv[]) {

    /* Initializing variables */
    int iter, i, j;
    srand((unsigned int) time(NULL));
    struct SDL_Window *window = NULL;
    struct SDL_Renderer *renderer = NULL;
    struct point *mas_p;
    struct dva_mas dva = {};
    struct SDL_Rect rect;
    set_coord(&dva, 1);

    /* SDL2 */
    if (!(SDL_Init_All(&window, &renderer))) {
        printf("Error! Code: %s\n", SDL_GetError());
    } else {
        for (iter = 0; iter < 100000000; ++iter) {

            /* Background */
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderClear(renderer);

            /* Flakes */
            set_coord(&dva, 0);
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            for (i = 0, mas_p = dva.mas; i < SIZE; ++i, ++mas_p) {
                rect.x = mas_p->x;
                rect.y = mas_p->y;
                rect.h = RECT_H;
                rect.w = RECT_W;
                SDL_RenderFillRect(renderer, &rect);
                for (j = 0; j < WIDTH; ++j) {
                    if (dva.snow[j].y) {
                        SDL_RenderFillRect(renderer, &dva.snow[j]);
                    }
                }
                /* SDL_RenderDrawPoint(renderer, mas_p->x, mas_p->y); */
            }

            /* Ending */
            SDL_RenderPresent(renderer);
            SDL_Delay(DELAY);
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }

    SDL_Quit();

    /* Returning value */
    return 0;

}

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

void set_coord(struct dva_mas *dva, int init) {

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

            if (dva->mas[i].y > HEIGHT - dva->snow[dva->mas[i].x].h) {
                dva->mas[i].y -= HEIGHT - RECT_H;

                if (!dva->snow[dva->mas[i].x].y) {
                    dva->snow[dva->mas[i].x].x = dva->mas[i].x;
                    dva->snow[dva->mas[i].x].y = HEIGHT - RECT_H;
                    dva->snow[dva->mas[i].x].w = RECT_W;
                } else {
                    dva->snow[dva->mas[i].x].y -= RECT_H;
                }
                dva->snow[dva->mas[i].x].h += RECT_H;
            }
        }
    }
}