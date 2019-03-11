#include "main.h"

int main(int argc, const char *argv[]) {

    /* Initializing variables */
    int iter, i;
    srand((unsigned int) time(NULL));
    struct SDL_Window *window = NULL;
    struct SDL_Renderer *renderer = NULL;
    struct point mas[SIZE], *mas_p;
	struct SDL_Rect rect;
    set_coord(mas, 1);

    /* SDL2 */
    if (!(SDL_Init_All(&window, &renderer))) {
        printf("Error! Code: %s\n", SDL_GetError());
    } else {
        for (iter = 0; iter < 100000000; ++iter) {

            /* Background */
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderClear(renderer);

            /* Flakes */
            set_coord(mas, 0);
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			for (i = 0, mas_p = mas; i < SIZE; ++i, ++mas_p) {
			    rect.x = mas_p->x;
				rect.y = mas_p->y;
				rect.h = RECT_H;
				rect.w = RECT_W;
				SDL_RenderFillRect(renderer, &rect);
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
