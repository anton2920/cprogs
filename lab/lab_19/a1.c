#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <assert.h>

#define WIDTH (1200)
#define HEIGHT (1200)
#define DELAY (1000 * 5)

main(int argc, const char *argv[]) {

    /* Initializing variables */
    struct SDL_Window *fortochka = NULL;
    struct SDL_Surface *screenSurface = NULL;
    struct SDL_Surface *picture = IMG_Load("vegetables.png");
    assert(picture != NULL);
    struct SDL_Rect dest;
    dest.x = 0;
    dest.y = 0;

    /* SDL2 */
    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        printf("Error! %s\n", SDL_GetError());
    } else {
        fortochka = SDL_CreateWindow("Pavlovsky", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if (fortochka == NULL) {
            printf("Error #2! %s\n", SDL_GetError());
        } else {
            screenSurface = SDL_GetWindowSurface(fortochka); /* Getting surface */
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xA9, 0xD1, 0x8E));

            SDL_BlitSurface(picture, NULL, screenSurface, &dest);
            SDL_SetColorKey(picture, SDL_TRUE, SDL_MapRGB(picture->format, 0xFF, 0xFF, 0xFF));

			SDL_Delay(200);
            SDL_UpdateWindowSurface(fortochka);
            SDL_Delay(DELAY);
        }
    }

    SDL_DestroyWindow(fortochka);

    SDL_Quit();
}
