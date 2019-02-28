#include <stdio.h>
#include <SDL2/SDL.h>

#define WIDTH (800)
#define HEIGHT (600)
#define DELAY (1000 * 5)

struct point {
    int x;
    int y;
};

int SDL_Init_All(struct SDL_Window **, struct SDL_Renderer **);
void sub_1(struct SDL_Renderer **renderer);

int main(int argc, const char *argv[]) {

    /* Initializing variables */
    struct SDL_Window *window = NULL;
    struct SDL_Renderer *renderer = NULL;

    /* SDL2 */
    if (!(SDL_Init_All(&window, &renderer))) {
        printf("Error! Code: %s\n", SDL_GetError());
    } else {

        sub_1(&renderer);

        SDL_Delay(DELAY);
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

void sub_1(struct SDL_Renderer **renderer) {

    /* Initializing variables */
    struct point pt1 = { 300, 400 };
    struct point pt2 = { 420, 125 };

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