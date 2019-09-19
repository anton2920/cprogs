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

bool SDL_Init_All(struct SDL_Window **window, struct SDL_Renderer **renderer, bool task_3) {

    /* SDL2 */
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if (task_3 == true) {
        #undef WIDTH
        #undef HEIGHT
        #define WIDTH (850)
        #define HEIGHT (640)
    }
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

void init_balls(struct pro_balls *p_b, SDL_Rect *balls, int *ball_cost) {

    /* Initializing variables */
    int i, j;
    int cX, cX_C;
    int cY, cY_C;
    int r, r_C;
    auto int rnd;

    /* Main part */
    for (i = 0; i < BALL_C; i++) {
        /* (balls + i)->x = i * 100 + 110;
         * (balls + i)->y = i * 100 + 10;
         * (balls + i)->w = 50 + 10 * i;
         * (balls + i)->h = 50 + 10 * i;
         */
        (p_b + i)->ball = balls + i;
        (balls + i)->x = (rand() % (700 - 110 + 1)) + 110;
        (balls + i)->y = (rand() & (700 - 10 + 1)) + 10;
        (balls + i)->w = (rand() % (150 - 50 + 1)) + 50;
        (balls + i)->h = (balls + i)->w;
        rnd = rand() % 4;
        switch (rnd) {
            case 0:
                (p_b + i)->x_d = x_neg;
                (p_b + i)->y_d = y_neg;
                break;
            case 1:
                (p_b + i)->x_d = x_neg;
                (p_b + i)->y_d = y_pos;
                break;
            case 2:
                (p_b + i)->x_d = x_pos;
                (p_b + i)->y_d = y_neg;
                break;
            case 3:
                (p_b + i)->x_d = x_pos;
                (p_b + i)->y_d = y_pos;
                break;
            default:
                break;

        }
        (p_b + i)->x_spd = (rand() % (x_max_spd - x_min_spd + 1)) + x_min_spd;
        (p_b + i)->y_spd = (rand() % (y_max_spd - y_min_spd + 1)) + y_min_spd;

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
    return (sqrt((centerX - x) * (centerX - x) + (centerY - y) * (centerY - y)) < radius) ? true : false;
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

bool is_ball_collapse(struct SDL_Rect *ball1, struct SDL_Rect *ball2) {

    /* Initializing variables */
    auto int cX = ball1->x + ball1->w / 2, cX_C = ball2->x + ball2->w / 2;
    auto int cY = ball1->y + ball1->h / 2, cY_C = ball2->y + ball2->h / 2;
    auto int r = ball1->w / 2, r_C = ball2->w / 2;

    /* Returning value */
    return (sqrt((cX_C - cX) * (cX_C - cX) + (cY_C - cY) * (cY_C - cY)) <= r + r_C) ? true : false;
}

void move_ball(struct pro_balls *ball) {

    /* Initializing variables */
    ball->ball->x += ball->x_spd * ball->x_d;
    ball->ball->y += ball->y_spd * ball->y_d;

}

void ball_touch_another_ball(struct pro_balls *all, struct SDL_Rect *curr_ball) {

    /* Initializing variables */
    register int i, j;
    enum directions dir;
    struct pro_balls *base, *an;
    auto int cX_base, cX_an, cY_base, cY_an, r_base, r_an;
    auto int base_x_spd, an_x_spd, base_y_spd, an_y_spd, base_mass, an_mass;

    /* Main part */
    for (i = 0; i < BALL_C; ++i) {
        for (j = i; j < BALL_C; ++j) {
            if (j == i || (all + i)->ball == curr_ball || (all + j)->ball == curr_ball) {
                continue;
            }
            if (is_ball_collapse((all + i)->ball, (all + j)->ball) == true && (all + i)->ball->w != 0 && (all + j)->ball->w != 0) {

                /* Bogdan's simple approach */
                /*dir = (all + i)->x_d;
                (all + i)->x_d = (all + j)->x_d;
                (all + j)->x_d = dir;

                dir = (all + i)->y_d;
                (all + i)->y_d = (all + j)->y_d;
                (all + j)->y_d = dir;*/


                /* My original approach */
                /*(all + i)->x_d = ((all + i)->x_d == x_pos) ? x_neg : x_pos;
                (all + i)->y_d = ((all + i)->y_d == y_pos) ? y_neg : y_pos;

                (all + j)->x_d = ((all + j)->x_d == x_pos) ? x_neg : x_pos;
                (all + j)->y_d = ((all + j)->y_d == y_pos) ? y_neg : y_pos;*/

                base = all + i;
                an = all + j;

                /* Wall-corner approach */
                r_base = (base->ball->w / 2 > an->ball->h / 2) ? base->ball->w / 2 : an->ball->h / 2;

                if (r_base == base->ball->w) {
                    cX_base = base->ball->x + base->ball->w / 2;
                    cX_an = an->ball->x + an->ball->w / 2;
                    cY_base = base->ball->y + base->ball->h / 2;
                    cY_an = an->ball->y + an->ball->h / 2;
                    r_an = an->ball->h / 2;
                } else {
                    cX_an = base->ball->x + base->ball->w / 2;
                    cX_base = an->ball->x + an->ball->w / 2;
                    cY_an = base->ball->y + base->ball->h / 2;
                    cY_base = an->ball->y + an->ball->h / 2;
                    r_base = base->ball->h / 2;
                }

                if (cX_an < cX_base && cY_an >= cY_base - r_base && cY_an <= cY_base + r_base) { /* Small to left wall */
                    if (base->x_d != an->x_d) {
                        base->x_d = (base->x_d == x_pos) ? x_neg : x_pos;
                    }
                    an->x_d = (an->x_d == x_pos) ? x_neg : x_pos;
                } else if (cX_an > cX_base && cY_an >= cY_base - r_base && cY_an <= cY_base + r_base) { /* Small to right wall */
                    if (base->x_d != an->x_d) {
                        base->x_d = (base->x_d == x_pos) ? x_neg : x_pos;
                    }
                    an->x_d = (an->x_d == x_pos) ? x_neg : x_pos;
                } else if (cY_an < cY_base && cX_an >= cX_base - r_base && cX_an <= cX_base + r_base) { /* Small to topper wall */
                    if (base->y_d != an->y_d) {
                        base->y_d = (base->y_d == y_pos) ? y_neg : y_pos;
                    }
                    an->y_d = (an->y_d == y_pos) ? y_neg : y_pos;
                } else if (cY_an > cY_base && cX_an >= cX_base - r_base && cX_an <= cX_base + r_base) { /* Small to lower wall */
                    if (base->y_d != an->y_d) {
                        base->y_d = (base->y_d == y_pos) ? y_neg : y_pos;
                    }
                    an->y_d = (an->y_d == y_pos) ? y_neg : y_pos;
                } else {
                    /*dir = base->x_d;
                    base->x_d = an->x_d;
                    an->x_d = dir;

                    dir = base->y_d;
                    base->y_d = an->y_d;
                    an->y_d = dir;*/

                    (all + i)->x_d = ((all + i)->x_d == x_pos) ? x_neg : x_pos;
                    (all + i)->y_d = ((all + i)->y_d == y_pos) ? y_neg : y_pos;

                    (all + j)->x_d = ((all + j)->x_d == x_pos) ? x_neg : x_pos;
                    (all + j)->y_d = ((all + j)->y_d == y_pos) ? y_neg : y_pos;
                }

                /*} else if () {  Small to left topper corner

                } else if () {  Small to left lower corner

                } else if () {  Small to right topper corner

                } else if () {  Small to right lower corner

                }*/

                /* New physics approach */
                /*base_mass = base->ball->w;
                an_mass = an->ball->w;
                base_x_spd = (base->x_spd * (base_mass - an_mass) + 2 * an_mass * an->x_spd) /
                        (base_mass + an_mass);
                an_x_spd = (an->x_spd * (an_mass - base_mass) + 2 * base_mass * base->x_spd) /
                        (base_mass + an_mass);
                if (base_x_spd < 0) {
                    base->x_d = (base->x_d == x_pos) ? x_neg : x_pos;
                }
                if (an_x_spd < 0) {
                    an->x_d = (an->x_d == x_pos) ? x_neg : x_pos;
                }

                base_y_spd = (base->y_spd * (base_mass - an_mass) + 2 * an_mass * an->y_spd) /
                             (base_mass + an_mass);
                an_y_spd = (an->y_spd * (an_mass - base_mass) + 2 * base_mass * base->y_spd) /
                           (base_mass + an_mass);
                if (base_y_spd < 0) {
                    base->y_d = (base->y_d == y_pos) ? y_neg : y_pos;
                }
                if (an_y_spd < 0) {
                    an->y_d = (an->y_d == y_pos) ? y_neg : y_pos;
                }*/

                move_ball(base);
                move_ball(an);
            }
        }
    }
}

void balls_touch_wall(struct pro_balls *all, struct SDL_Rect *curr_ball) {

    /* Initializing variables */
    register int i;

    /* Main part */
    for (i = 0; i < BALL_C; ++i) {
        if ((all + i)->ball == curr_ball || (all + i)->ball->w == 0) {
            continue;
        }
        if ((all + i)->ball->x < 0 && (all + i)->ball->y > 0 && ((all + i)->ball->y + (all + i)->ball->h) < HEIGHT) { /* Left wall */
            (all + i)->x_d = ((all + i)->x_d == x_pos) ? x_neg : x_pos;
        } else if (((all + i)->ball->x + (all + i)->ball->w) > WIDTH && (all + i)->ball->y > 0 && ((all + i)->ball->y + (all + i)->ball->h) < HEIGHT) { /* Right wall */
            (all + i)->x_d = ((all + i)->x_d == x_pos) ? x_neg : x_pos;
        } else if ((all + i)->ball->y < 0 && (all + i)->ball->x > 0 && ((all + i)->ball->x + (all + i)->ball->w) < WIDTH) { /* Topper wall */
            (all + i)->y_d = ((all + i)->y_d == y_pos) ? y_neg : y_pos;
        } else if (((all + i)->ball->y + (all + i)->ball->h) > HEIGHT && (all + i)->ball->x > 0 && ((all + i)->ball->x + (all + i)->ball->w) < WIDTH) { /* Lower wall */
            (all + i)->y_d = ((all + i)->y_d == y_pos) ? y_neg : y_pos;
        } else if ((all + i)->ball->x < 0 && (all + i)->ball->y < 0) { /* Left topper corner */
            (all + i)->x_d = ((all + i)->x_d == x_pos) ? x_neg : x_pos;
            (all + i)->y_d = ((all + i)->y_d == y_pos) ? y_neg : y_pos;
        } else if (((all + i)->ball->x < 0) && ((all + i)->ball->y + (all + i)->ball->h) > HEIGHT) { /* Left lower corner */
            (all + i)->x_d = ((all + i)->x_d == x_pos) ? x_neg : x_pos;
            (all + i)->y_d = ((all + i)->y_d == y_pos) ? y_neg : y_pos;
        }  else if (((all + i)->ball->y < 0) && ((all + i)->ball->x + (all + i)->ball->w) > WIDTH) { /* Right topper corner */
            (all + i)->x_d = ((all + i)->x_d == x_pos) ? x_neg : x_pos;
            (all + i)->y_d = ((all + i)->y_d == y_pos) ? y_neg : y_pos;
        } else if (((all + i)->ball->x + (all + i)->ball->w) > WIDTH && ((all + i)->ball->y + (all + i)->ball->h) > HEIGHT) { /* Right lower corner */
            (all + i)->x_d = ((all + i)->x_d == x_pos) ? x_neg : x_pos;
            (all + i)->y_d = ((all + i)->y_d == y_pos) ? y_neg : y_pos;
        }

        move_ball(all + i);
    }
}

/* Game */
void draw_field(struct SDL_Renderer *renderer) {

    /* Initializing variables */
    register int i, j;

    auto struct SDL_Surface *grassImage = IMG_Load(GRASS_PATH);
    assert(grassImage != NULL); /* Debugging sh*t */
    SDL_SetColorKey(grassImage, SDL_TRUE, SDL_MapRGB(grassImage->format, 255, 255, 255));
    auto struct SDL_Texture *grassTexture = SDL_CreateTextureFromSurface(renderer, grassImage);
    assert(grassTexture != NULL);
    SDL_FreeSurface(grassImage);

    auto struct SDL_Surface *concImage = IMG_Load(CONCRETE_PATH);
    assert(concImage != NULL); /* Debugging sh*t */
    SDL_SetColorKey(concImage, SDL_TRUE, SDL_MapRGB(concImage->format, 255, 255, 255));
    auto struct SDL_Texture *concTexture = SDL_CreateTextureFromSurface(renderer, concImage);
    assert(concTexture != NULL);
    SDL_FreeSurface(concImage);

    auto struct SDL_Rect text_rect = {};

    /* Main part */

    /* Field:                      */
    /* 0 * * * * * * * * * * * * * * * *
       1 * - - - - × - - - - - - - - - *
       2 * - - - # - - - - # - - × - - *
       3 * * * * * * * * * - - - - - - *
       4 * - - # - - - - * - - - # - - *
       5 * - - - - - × - - - × - - - × *
       6 * - × - - - - - - - - - - - - *
       7 * - - - # - - - * - - - # - - *
       8 * - - - - - × - * * * * * * * *
       9 * * * * * * - - # - - - - - - *
      10 * - - - × # - - - - - - × - - *
      11 * - - - - - - - - × - - - - - *
      12 * * * * * * * * * * * * - - × *
      13 * - - × - - - # - - - × - - - *
      14 * - # - - - × - - - - - # - - *
      15 * * * * * * * * * * * * * * * *
         0 1 2 3 4 5 6 7 8 9 A B C D E F */

    for (i = 0; i < 16; ++i) {
        for (j = 0; j < 16; ++j) {
            text_rect.x = j * TEXTURE_SIZE;
            text_rect.y = i * TEXTURE_SIZE;
            text_rect.w = TEXTURE_SIZE;
            text_rect.h = text_rect.w;
            if (!i || i == 15 || !j || j == 15 || (i == 3 && j <= 8) ||
                    (i == 4 && j == 8) || (i == 7 && j == 8) || (i == 8 && j >= 8) ||
                    (i == 9 && j <= 5) || (i == 12 && j <= 11)) {
                SDL_RenderCopy(renderer, concTexture, NULL, &text_rect);
            } else {
                SDL_RenderCopy(renderer, grassTexture, NULL, &text_rect);
            }
        }
    }
}

void spawn_mines(struct SDL_Renderer *renderer) {

    /* Initializing variables */
    register int i, j;

    auto struct SDL_Surface *mineImage = IMG_Load(MINE_PATH);
    assert(mineImage != NULL); /* Debugging sh*t */
    SDL_SetColorKey(mineImage, SDL_TRUE, SDL_MapRGB(mineImage->format, 255, 255, 255));
    auto struct SDL_Texture *mineTexture = SDL_CreateTextureFromSurface(renderer, mineImage);
    assert(mineTexture != NULL);
    SDL_FreeSurface(mineImage);

    auto struct SDL_Rect text_rect = {};

    /* Main part */
    for (i = 0; i < 15; ++i) {
        for (j = 0; j < 15; ++j) {
            if ((i == 1 && j == 5) || (i == 2 && j == 12) || (i == 5 && j == 6) ||
                    (i == 5 && j == 10) || (i == 5 && j == 14) || (i == 6 && j == 2) ||
                    (i == 8 && j == 6) || (i == 10 && j == 4) || (i == 10 && j == 12) ||
                    (i == 11 && j == 9) || (i == 12 && j == 14) || (i == 13 && j == 3) ||
                    (i == 13 && j == 11) || (i == 14 && j == 6)) {
                text_rect.w = TEXTURE_SIZE / 2;
                text_rect.h = text_rect.w;
                text_rect.x = j * TEXTURE_SIZE + text_rect.w / 2;
                text_rect.y = i * TEXTURE_SIZE + text_rect.h / 2;
                SDL_RenderCopy(renderer, mineTexture, NULL, &text_rect);
            }
        }
    }
}

void set_traps(struct SDL_Renderer *renderer) {

    /* Initializing variables */
    register int i, j;

    auto struct SDL_Surface *trapImage = IMG_Load(TRAP_PATH);
    assert(trapImage != NULL); /* Debugging sh*t */
    SDL_SetColorKey(trapImage, SDL_TRUE, SDL_MapRGB(trapImage->format, 255, 255, 255));
    auto struct SDL_Texture *trapTexture = SDL_CreateTextureFromSurface(renderer, trapImage);
    assert(trapTexture != NULL);
    SDL_FreeSurface(trapImage);

    auto struct SDL_Rect text_rect = {};

    /* Main part */
    for (i = 0; i < 15; ++i) {
        for (j = 0; j < 15; ++j) {
            if ((i == 2 && j == 4) || (i == 2 && j == 9) || (i == 4 && j == 3) ||
                    (i == 4 && j == 12) || (i == 7 && j == 4) || (i == 7 && j == 12) ||
                    (i == 9 && j == 8) || (i == 10 && j == 5) || (i == 13 && j == 7) ||
                    (i == 14 && j == 2) || (i == 14 && j == 12)) {
                text_rect.w = TEXTURE_SIZE;
                text_rect.h = text_rect.w;
                text_rect.x = j * TEXTURE_SIZE;
                text_rect.y = i * TEXTURE_SIZE;
                SDL_RenderCopy(renderer, trapTexture, NULL, &text_rect);
            }
        }
    }
}

void print_info(int mleft, int lleft, struct SDL_Renderer *renderer, struct _TTF_Font *fnt) {

    /* Initializing variables */
    auto char text[20];
    auto struct SDL_Color clr = {0xFF, 0x55, 0x00, 0x00};

    /* Main part */
    sprintf(text, "Mines left: %d", mleft);
    auto struct SDL_Texture *text_t = get_text_texture(renderer, text, fnt, &clr, NULL, solid);
    assert(text_t != NULL);
    auto struct SDL_Rect rect = {680, 40, 120, 40};
    SDL_RenderCopy(renderer, text_t, NULL, &rect);

    sprintf(text, "Lives left: %d", lleft);
    text_t = get_text_texture(renderer, text, fnt, &clr, NULL, solid);
    assert(text_t != NULL);
    rect.x = 680;
    rect.y = 80;
    rect.w = 120;
    rect.h = 40;
    SDL_RenderCopy(renderer, text_t, NULL, &rect);
}

void spawn_character(struct SDL_Rect *pl_rect, struct SDL_Renderer *renderer) {

    /* Initializing variables */
    auto struct SDL_Surface *trapImage = IMG_Load(CHAR_PATH);
    assert(trapImage != NULL); /* Debugging sh*t */
    SDL_SetColorKey(trapImage, SDL_TRUE, SDL_MapRGB(trapImage->format, 255, 255, 255));
    auto struct SDL_Texture *trapTexture = SDL_CreateTextureFromSurface(renderer, trapImage);
    assert(trapTexture != NULL);
    SDL_FreeSurface(trapImage);

    /* Main part */

}