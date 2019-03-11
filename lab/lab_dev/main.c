#include <stdio.h>
#include <SDL2/SDL.h>

#define TITLE ("lab_22")
#define WIDTH (800)
#define HEIGHT (800)

#define TRUE (1)
#define FALSE (0)

#define DELETE (0)
#define SMALL (1)
#define BIG (2)

#define SMALL_RECT (30)
#define BIG_RECT (80)

#define SIZE (100)
#define DELAY (10)

struct square {
    int size;
    struct SDL_Rect rect;
};

enum bool {
    true = TRUE,
    false = FALSE
};

int SDL_Init_All(struct SDL_Window **, struct SDL_Renderer **);
struct square *add_square(struct square *, int, int, int);
void draw_squares(struct SDL_Renderer *, struct square *, struct square *);
void delete_square_queue(struct square *, struct square *);
struct square *delete_square_stack(struct square *);
void delete_all(struct square *);
struct square *find_square(struct square *, struct square *, int, int);

int main(int argc, const char *argv[]) {

    /* Initializing variables */
    struct SDL_Window *window = NULL;
    struct SDL_Renderer *renderer = NULL;
    union SDL_Event event;
    enum bool quit = false;
    struct square mas_small[SIZE] = {}, mas_big[SIZE] = {}, *last_small = mas_small, *last_big = mas_big, *item = NULL;
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
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT && i < SIZE - 1) {
                    last_small = add_square(mas_small + i++, event.button.x - SMALL_RECT / 2, event.button.y - SMALL_RECT / 2, SMALL);
                }

                if (event.button.button == SDL_BUTTON_RIGHT && j < SIZE - 1) {
                    last_big = add_square(mas_big + j++, event.button.x - BIG_RECT / 2, event.button.y - BIG_RECT / 2, BIG);
                }

                if (event.button.button == SDL_BUTTON_MIDDLE) {
                    item = find_square(mas_small, mas_big, event.button.x, event.button.y);
                    if (item != NULL) {
                        if (item->size == SMALL) {
                            delete_square_queue(item, last_small);
                            --i;
                            --last_small;
                        } else {
                            delete_square_queue(item, last_big);
                            --j;
                            --last_big;
                        }
                    }
                }
                event.type = 0;
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
                event.type = 0;
            }

            draw_squares(renderer, mas_small, mas_big);

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
    if ((*window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)) < 0) {
        return 0;
    } else if (!(*renderer = SDL_CreateRenderer(*window, -1, 0))) {
        return 0;
    }

    /* Returning value */
    return 1;
}

struct square *add_square(struct square *item, int x, int y, int size) {

    /* Initializing variables */
    item->size = size;
    item->rect.x = x;
    item->rect.y = y;

    /* Main part */
    switch (size) {
        case SMALL:
            item->rect.w = SMALL_RECT;
            item->rect.h = SMALL_RECT;
            break;
        case BIG:
            item->rect.w = BIG_RECT;
            item->rect.h = BIG_RECT;
            break;
        default:
            break;
    }

    /* Returning value */
    return item;

}

void draw_squares(struct SDL_Renderer *renderer, struct square *mas_small, struct square *mas_big) {

    /* Initializing variables */
    int i;

    /* Main part */
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    for (i = 0; i < SIZE; ++i, ++mas_small) {
        if (mas_small->size == SMALL) {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
            SDL_RenderFillRect(renderer, &mas_small->rect);
        } else {
            break;
        }
    }

    for (i = 0; i < SIZE; ++i, ++mas_big) {
        if (mas_big->size == BIG) {
            SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
            SDL_RenderFillRect(renderer, &mas_big->rect);
        } else {
            break;
        }
    }

    SDL_RenderPresent(renderer);
}

void delete_square_queue(struct square *item, struct square *last) {

    /* Main part */
    for ( ; last >= item; ++item) {
        *item = *(item + 1);
    }

}

struct square *delete_square_stack(struct square *item) {

    /* Initializing variables */
    item->size = DELETE;

    /* Returning value */
    return --item;
}

void delete_all(struct square *mas) {

    /* Initializing variables */
    int i;

    /* Main part */
    for (i = 0; i < SIZE || mas->size != DELETE; ++i, ++mas) {
        mas->size = DELETE;
    }
}

struct square *find_square(struct square *mas_small, struct square *mas_big, int x, int y) {

    /* Initializing variables */
    struct square *ans = NULL;

    /* Main part */
    for ( ; mas_big->size != DELETE && ans == NULL; ++mas_big) {
        if (x >= mas_big->rect.x && x <= mas_big->rect.x + BIG_RECT && y >= mas_big->rect.y && y <= mas_big->rect.y + BIG_RECT) {
            ans = mas_big;
        }
    }

    for ( ; mas_small->size != DELETE && ans == NULL; ++mas_small) {
        if (x >= mas_small->rect.x && x <= mas_small->rect.x + SMALL_RECT && y >= mas_small->rect.y && y <= mas_small->rect.y + SMALL_RECT) {
            ans = mas_small;
        }
    }

    /* Returning value */
    return ans;
}