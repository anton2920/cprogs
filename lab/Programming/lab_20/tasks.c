#include "main.h"

void sub_1(struct SDL_Renderer **renderer) {

    /* Initializing variables */
    struct point pt1 = { 250, 500 };
    struct point pt2 = { pt1.x + 120, pt1.y - 275 };

    /* SDL2 */
    SDL_SetRenderDrawColor(*renderer, 0xFF, 0xFF, 0xFF, 0);
    SDL_RenderClear(*renderer);

    SDL_SetRenderDrawColor(*renderer, 0x01, 0x01, 0x01, 0x00);
    SDL_RenderDrawLine(*renderer, pt1.x, pt1.y, pt1.x + 200, pt1.y);
    SDL_RenderDrawLine(*renderer, pt1.x, pt1.y, pt1.x + 60, pt1.y - 100);
    SDL_RenderDrawLine(*renderer, pt1.x + 60, pt1.y - 100, pt1.x + 260, pt1.y - 100);
    SDL_RenderDrawLine(*renderer, pt1.x + 200, pt1.y, pt1.x + 260, pt1.y - 100);

    SDL_SetRenderDrawColor(*renderer, 0x00, 0x00, 0xFF, 0x00);
    SDL_RenderDrawLine(*renderer, pt1.x, pt1.y, pt2.x, pt2.y);

    SDL_SetRenderDrawColor(*renderer, 0x00, 0xFF, 0x00, 0x00);
    SDL_RenderDrawLine(*renderer, pt1.x + 60, pt1.y - 100, pt2.x, pt2.y);

    SDL_SetRenderDrawColor(*renderer, 0xFF, 0x55, 0x00, 0x00);
    SDL_RenderDrawLine(*renderer, pt1.x + 200, pt1.y, pt2.x, pt2.y);

    SDL_SetRenderDrawColor(*renderer, 0xFF, 0x00, 0x00, 0x00);
    SDL_RenderDrawLine(*renderer, pt1.x + 260, pt1.y - 100, pt2.x, pt2.y);

    SDL_Delay(500);
    SDL_RenderPresent(*renderer);
}

void sub_2(struct SDL_Renderer **renderer) {

    /* Initializing variables */
    int i, r, g, b, j;
    struct point pt1 = { 0, 10 };
    struct point pt2 = { 10, 0 };

    /* SDL2 */
    SDL_SetRenderDrawColor(*renderer, 0xFF, 0xFF, 0xFF, 0);
    SDL_RenderClear(*renderer);

    for (i = 0, j = 0; i <= 780; i += 20, j += 2) {
        rand_clr(&r, &g, &b);
        SDL_SetRenderDrawColor(*renderer, r ,g, b, 0);
        SDL_RenderDrawLine(*renderer, pt1.x, pt1.y + i, pt2.x + i, pt2.y);
    	SDL_Delay(100 + j);
	    SDL_RenderPresent(*renderer);
    }

    for (i = 10; i <= 780; i += 20) {
        rand_clr(&r, &g, &b);
        SDL_SetRenderDrawColor(*renderer, r ,g, b, 0);
        SDL_RenderDrawLine(*renderer, pt1.x + i, 800, 800, pt2.y + i);
    	SDL_Delay(200);
	    SDL_RenderPresent(*renderer);
    }

}

void sub_3(struct SDL_Renderer **renderer, struct diapazon *dn1, double a, double c) {

    /* Initializing variables */
    int i;
    double x;

    /* SDL2 */
    SDL_SetRenderDrawColor(*renderer, 0xFF, 0xFF, 0xFF, 0);
    SDL_RenderClear(*renderer);

    /* Axis */
    SDL_SetRenderDrawColor(*renderer, 0x01, 0x01, 0x01, 0x00);
    SDL_RenderDrawLine(*renderer, WIDTH / 2, 0, WIDTH / 2, HEIGHT);
    SDL_RenderDrawLine(*renderer, 0, HEIGHT / 2, WIDTH, HEIGHT / 2);

    SDL_RenderDrawLine(*renderer, CENTER_X, 0, CENTER_X - 10, 10);
    SDL_RenderDrawLine(*renderer, CENTER_X, 0, CENTER_X + 10, 10);
    SDL_RenderDrawLine(*renderer, WIDTH, CENTER_Y, WIDTH - 10, CENTER_Y - 10);
    SDL_RenderDrawLine(*renderer, WIDTH, CENTER_Y, WIDTH - 10, CENTER_Y + 10);

    SDL_SetRenderDrawColor(*renderer, 0x01, 0x01, 0x01, 200);
    for (i = 0; i * MULTIPLIER < WIDTH - 10; ++i) {
        SDL_RenderDrawLine(*renderer, i * MULTIPLIER, CENTER_Y + 3, i * MULTIPLIER, CENTER_Y - 3);
    }

    SDL_SetRenderDrawColor(*renderer, 0xFF, 0x00, 0x00, 0);
    for (x = dn1->left_x; x <= dn1->right_x; x += 0.001) {
        SDL_RenderDrawPoint(*renderer, CENTER_X + x * MULTIPLIER, CENTER_Y - func(x, a, c));
    }

    SDL_Delay(500);
    SDL_RenderPresent(*renderer);

}
