#include "main.h"

int main(int argc, const char *argv[]) {

    /* Initializing variables */
    struct SDL_Window *window = NULL;
    struct SDL_Renderer *renderer = NULL;
    union SDL_Event event;
    enum bool quit = false;
    struct square mas_small[SIZE] = {}, mas_big[SIZE] = {}, *last_small = mas_small, *last_big = mas_big;
    int i = 0, j = 0;

    /* SDL2 */
    if (!(SDL_Init_All(&window, &renderer))) {
        printf("Error! Code: %s\n", SDL_GetError());
    } else {
        while (!quit) {
            SDL_PollEvent(&event);
            if (event.type == SDL_QUIT) {
                quit = true;
                continue;
            }
            if (i + j < SIZE - 1) {
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        last_small = add_square(mas_small + i++, event.button.x - SMALL_RECT / 2, event.button.y - SMALL_RECT / 2, SMALL);
                    }

                    if (event.button.button == SDL_BUTTON_RIGHT) {
                        last_big = add_square(mas_big + j++, event.button.x - BIG_RECT / 2, event.button.y - BIG_RECT / 2, BIG);
                    }
                }
            }

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_q && last_small >= mas_small) {
                    delete_square_queue(mas_small, last_small);
                    --last_small;
                    --i;
                }

                if (event.key.keysym.sym == SDLK_a && last_small >= mas_small) {
                    last_small = delete_square_stack(last_small);
                    --i;
                }

                if (event.key.keysym.sym == SDLK_e && last_big >= mas_big) {
                    delete_square_queue(mas_big, last_big);
                    --last_big;
                    --j;
                }

                if (event.key.keysym.sym == SDLK_d && last_big >= mas_big) {
                    last_big = delete_square_stack(last_big);
                    --j;
                }

                if (event.key.keysym.sym == SDLK_x) {
                    delete_all(mas_small);
                    delete_all(mas_big);
                    last_small = mas_small;
                    last_big = mas_big;
                    i = 0;
                    j = 0;
                }
            }

            draw_squares(renderer, mas_small, mas_big);
            event.type = 0;
            SDL_Delay(DELAY);
        }
        
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }

    SDL_Quit();

    /* Returning value */
    return 0;

}