#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#define WIDTH (800)
#define HEIGHT (800)
#define CENTER_X (WIDTH / 2)
#define CENTER_Y (HEIGHT / 2)
#define MULTIPLIER (15)

struct point {
    int x;
    int y;
};

struct diapazon {
    double left_x;
    double right_x;
};

int SDL_Init_All(struct SDL_Window **, struct SDL_Renderer **);
void sub_1(struct SDL_Renderer **);
void sub_2(struct SDL_Renderer **);
void rand_clr(int *, int *, int *);
void sub_3(struct SDL_Renderer **, struct diapazon *, double, double);
double func(double, double, double);

int main(int argc, const char *argv[]) {

    /* Initializing variables */
    double a, c;
    srand((unsigned int) time(NULL));
    Uint32 delay = 1000 * 5;
    struct SDL_Window *window = NULL;
    struct SDL_Renderer *renderer = NULL;
    struct diapazon dn1;

    if (argc == 1 || argc > 2) {
        printf("Error! Problem with arguments!\n");
        return 0;
    }

    if (**(argv + 1) == '3') {
        /* I/O flow && VarCheck */
        do {
            printf("Type left border: ");
            scanf("%lf", &dn1.left_x);
        } while (dn1.left_x < -10);

        do {
            printf("Type right border: ");
            scanf("%lf", &dn1.right_x);
        } while (dn1.right_x > 20);

        printf("Type A: ");
        scanf("%lf", &a);
        printf("Type C: ");
        scanf("%lf", &c);
    }

    /* SDL2 */
    if (!(SDL_Init_All(&window, &renderer))) {
        printf("Error! Code: %s\n", SDL_GetError());
    } else {
        switch (**(argv + 1)) {
            case '1':
                sub_1(&renderer);
                break;
            case '2':
                sub_2(&renderer);
                break;
            case '3':
                sub_3(&renderer, &dn1, a, c);
                break;
            default:
                printf("Error! Usage: name of sub-task\n");
                delay = 0;
        }

        SDL_Delay(delay);
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
    int i, r, g, b;
    struct point pt1 = { 0, 10 };
    struct point pt2 = { 10, 0 };

    /* SDL2 */
    SDL_SetRenderDrawColor(*renderer, 0xFF, 0xFF, 0xFF, 0);
    SDL_RenderClear(*renderer);

    for (i = 0; i <= 780; i += 20) {
        rand_clr(&r, &g, &b);
        SDL_SetRenderDrawColor(*renderer, r ,g, b, 0);
        SDL_RenderDrawLine(*renderer, pt1.x, pt1.y + i, pt2.x + i, pt2.y);
    }

    for (i = 0; i <= 780; i += 20) {
        rand_clr(&r, &g, &b);
        SDL_SetRenderDrawColor(*renderer, r ,g, b, 0);
        SDL_RenderDrawLine(*renderer, pt1.x + i, 800, 800, pt2.y + i);
    }

    SDL_Delay(500);
    SDL_RenderPresent(*renderer);
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
    for (x = dn1->left_x; x <= dn1->right_x; x += 0.01) {
        SDL_RenderDrawPoint(*renderer, CENTER_X + x * MULTIPLIER, CENTER_Y - func(x, a, c));
    }

    SDL_Delay(500);
    SDL_RenderPresent(*renderer);

}

double func(double x, double a, double c) {

    /* Returning value */
    return a * x * x * x + c;
}