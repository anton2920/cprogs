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
    Mix_Init(0);

    /* Returning value */
    return true;
}

struct SDL_Texture *get_text_texture(struct SDL_Renderer *renderer, char *text, struct _TTF_Font *font,
                                     struct SDL_Color *fore_color, struct SDL_Color *back_color, enum texttype t) {

    /* Initializing variables */
    struct SDL_Surface *textSurface = NULL;

    struct SDL_Texture *texture = NULL;

    /* Main part */
    if (t == shaded) {
        textSurface = TTF_RenderText_Shaded(font, text, *fore_color, *back_color);
    } else if (t == solid) {
        textSurface = TTF_RenderText_Solid(font, text, *fore_color);
    }
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    /* Returning value */
    return texture;
}

void draw_text(struct SDL_Renderer *renderer, struct SDL_Texture *texture, struct SDL_Rect *rect) {

    /* Main part */
    SDL_RenderCopy(renderer, texture, NULL, rect);
}

void init_balls(SDL_Rect *balls, int count, int *ball_cost) {

    /* Initializing variables */
    int i, j;
    int cX, cX_C;
    int cY, cY_C;
    int r, r_C;

    /* Main part */
    for (i = 0; i < count; i++) {
        /* (balls + i)->x = i * 100 + 110;
         * (balls + i)->y = i * 100 + 10;
         * (balls + i)->w = 50 + 10 * i;
         * (balls + i)->h = 50 + 10 * i;
         */

        (balls + i)->x = (rand() % (700 - 110 + 1)) + 110;
        (balls + i)->y = (rand() & (700 - 10 + 1)) + 10;
        (balls + i)->w = (rand() % (150 - 50 + 1)) + 50;
        (balls + i)->h = (balls + i)->w;

        cX = (balls + i)->x + (balls + i)->w / 2;
        cY = (balls + i)->y + (balls + i)->h / 2;
        r = (balls + i)->w / 2;

        *(ball_cost + i) = (balls + i)->w / RND_COST;
        for (j = 0; j < i; ++j) {
            cX_C = (balls + j)->x + (balls + j)->w / 2;
            cY_C = (balls + j)->y + (balls + j)->h / 2;
            r_C = (balls + j)->w / 2;
            if (sqrt((cX_C - cX) * (cX_C - cX) + (cY_C - cY) * (cY_C - cY)) <= r + r_C) {
                --i;
                continue;
            }
        }
    }
}

void draw_balls(struct SDL_Renderer *renderer, struct SDL_Rect *balls, int count,
                struct SDL_Texture *texture, struct SDL_Texture *texture_blue,
                int *ball_cost, struct _TTF_Font *my_font, struct SDL_Rect *curr_ball) {

    /* Initializing variables */
    int i;
    char text[10];
    struct SDL_Color fore_color = { 0, 0, 255, 0 };
    struct SDL_Color back_color2 = {};
    assert(my_font != NULL);
    struct SDL_Texture *textTexture;
    struct SDL_Rect font_rect = {};

    /* Main part */
    for (i = 0; i < count; i++) {
        if (balls[i].w == 0) {
            continue;
        }
        font_rect.x = balls[i].x + (balls[i].w / RED_COEFF / 2);
        font_rect.y = balls[i].y + (balls[i].w / RED_COEFF / 2);
        font_rect.w = balls[i].w - (balls[i].w / RED_COEFF);
        font_rect.h = balls[i].w - (balls[i].w / RED_COEFF);
        if (balls + i == curr_ball) {
            SDL_RenderCopy(renderer, texture_blue, NULL, &balls[i]);
        } else {
            SDL_RenderCopy(renderer, texture, NULL, &balls[i]);
            sprintf(text, "%d", ball_cost[i]);
            textTexture = get_text_texture(renderer, text, my_font, &fore_color, &back_color2, solid);
            draw_text(renderer, textTexture, &font_rect);
            SDL_DestroyTexture(textTexture);
        }
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

void loadmusic(Mix_Music *fon) {

    /* Initializing variables */
    fon = Mix_LoadMUS("../wav/Very_bad_piece.wav");
    assert(fon != NULL);

    /* Main part */
    Mix_PlayMusic(fon, -1);

}

void sound(struct Mix_Chunk *Sound, char *name) {

    /* Initializing variables */
    Sound = Mix_LoadWAV(name);

    /* Main part */
    Mix_PlayChannel(-1, Sound, 0);
}