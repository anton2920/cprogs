#include "source.h"

bool check_args(int argc, char *argv[]) {

    /* VarCheck */
    if (argc == 2) {
        if (**(argv + 1) == '1' || **(argv + 1) == '2' || **(argv + 1) == '3') {
            return true;
        }
    }

    /* Final output */
    fprintf(stderr, "Error! Arguments problem!\n");

    /* Returning value */
    return false;
}

bool SDL_Init_All(struct SDL_Window **window, struct SDL_Renderer **renderer) {

    /* SDL2 */
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if ((*window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)) < 0) {
        return false;
    } else if (!(*renderer = SDL_CreateRenderer(*window, -1, 0))) {
        return false;
    }

    TTF_Init();

    /* Returning value */
    return true;
}

struct SDL_Texture *get_text_texture(struct SDL_Renderer *renderer, char *text, struct _TTF_Font *font) {

    /* Initializing variables */
    struct SDL_Surface *textSurface = NULL;
    struct SDL_Color fore_color = { 130, 140, 50 };
    struct SDL_Color back_color = { 188, 155, 166 };
    struct SDL_Texture *texture = NULL;

    /* Main part */
    textSurface = TTF_RenderText_Shaded(font, text, fore_color, back_color);
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    /* Returning value */
    return texture;
}

void draw_text(struct SDL_Renderer *renderer, struct SDL_Texture *texture) {

    /* Initializing variables */
    SDL_Rect rect = { 0, 0, 70, 200 };

    /* Main part */
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void init_balls(SDL_Rect *balls, int count) {

    /* Initializing variables */
    int i;

    /* Main part */
    for (i = 0; i < count; i++) {
        (balls + i)->x = i * 100 + 110;
        (balls + i)->y = i * 100 + 10;
        (balls + i)->w = 50 + 10 * i;
        (balls + i)->h = 50 + 10 * i;
    }
}

void draw_balls(struct SDL_Renderer *renderer, struct SDL_Rect *balls, int count, struct SDL_Texture *texture) {

    /* Initializing variables */
    int i;

    /* Main part */
    for (i = 0; i < count; i++) {
        if (balls[i].w == 0) {
            continue;
        }

    SDL_RenderCopy(renderer, texture, NULL, &balls[i]);
    }
}

bool is_ball_hit(struct SDL_Rect *ball, int x, int y) {

    /* Initializing variables */
    int centerX = ball->x + ball->w / 2;
    int centerY = ball->y + ball->h / 2;
    int radius = ball->w / 2;

    /* Main part */
    if (ball->w == 0) {
        return false;
    }

    /* Returning value */
    return (sqrt((centerX - x)*(centerX - x) + (centerY - y)*(centerY - y)) < radius) ? true : false;
}