#include "main.h"

int main(int argc, const char *argv[]) {

    /* Initializing variables */
    int iter, i, j;
    srand((unsigned int) time(NULL));
    struct SDL_Window *window = NULL;
    struct SDL_Renderer *renderer = NULL;
    struct point *mas_p;
    struct dva_mas dva = {};
    struct SDL_Rect rect;
    set_coord(&dva, 1, argc - 1);

    /* VarCheck */
    if (argc > 2 || (argc == 2 && **(argv + 1) != '1')) {
        printf("Error! Problems with arguments!\n");
        return 0;
    }

    /* SDL2 */
    if (!(SDL_Init_All(&window, &renderer))) {
        printf("Error! Code: %s\n", SDL_GetError());
    } else {
        for (iter = 0; iter < ITER; ++iter) {

            /* Background */
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderClear(renderer);

            /* Flakes */
            set_coord(&dva, 0, argc - 1);
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            for (i = 0, mas_p = dva.mas; i < SIZE; ++i, ++mas_p) {
                rect.x = mas_p->x;
                rect.y = mas_p->y;
                rect.h = RECT_H;
                rect.w = RECT_W;
                SDL_RenderFillRect(renderer, &rect);
                if (argc == 2 && **(argv + 1) == '1') {
                    for (j = 0; j < WIDTH; ++j) {
                        if (dva.snow[j].y) {
                            SDL_RenderFillRect(renderer, &dva.snow[j]);
                        }
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