#include "main.h"

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