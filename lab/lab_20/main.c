#include "main.h"

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