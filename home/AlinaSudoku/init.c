#define CLION /* Only for anton2920's workspace. Must be commented out or undefined at the end */

#ifdef CLION

#include "AlinaSudoku_dev/Header.h"

#else
#include "Header.h"
#endif

void loadmusic(Mix_Music *fon, int n) {
    switch (n) {
        case 0:
            fon = Mix_LoadMUS("m0.mp3");
            break;
        case 1:
            fon = Mix_LoadMUS("m1.mp3");
            break;
        case 2:
            fon = Mix_LoadMUS("m2.mp3");
            break;
        default:
            break;
    }
    Mix_PlayMusic(fon, -1);
}

void
draw_game(int i_menu, int lv, SDL_Renderer *renderer, SDL_Texture *fon, SDL_Texture *T_button, SDL_Texture *text_logo,
          SDL_Texture *text_button[], SDL_Rect button[], int number, SDL_Texture *exit_texture) {
    SDL_Rect fon_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Rect logo_rect = {250, 50, 300, 100};
    SDL_Rect ex = {700, 500, 75, 75};

    /* Variables from anton2920 */
    auto int i;

    SDL_RenderCopy(renderer, fon, NULL, &fon_rect);
    if (lv == 9) {
        logo_rect.y = 0;
    }
    SDL_RenderCopy(renderer, text_logo, NULL, &logo_rect);
    if (i_menu != 5) {
        for (i = 0; i < number; i++) {
            SDL_RenderCopy(renderer, T_button, NULL, &button[i]);
        }
    }
    for (i = 0; i < number; i++) {
        SDL_RenderCopy(renderer, text_button[i], NULL, &button[i]);
    }
    if (i_menu == 5) {
        SDL_RenderCopy(renderer, exit_texture, NULL, &ex);
    }
    SDL_RenderPresent(renderer);
}

void initField(int n, struct SDL_Texture *cell[]) {

    /* Initializing variables */
    auto int i;

    /* Main part */
    for (i = 0; i < n; ++i) {
        if (i < 257) {
            *cell++ = NULL;
        }
    }
}

void read_file(int lv, int a[], int index[], int emd, int count[]) {
    FILE *f = NULL;

    /* Variables from anton2920 */
    auto int i, j;

    if (lv == 4) {
        if (emd == 0) {
            f = fopen("40.txt", "r");
        }
        if (emd == 1) {
            f = fopen("41.txt", "r");
        }
        if (emd == 2) {
            f = fopen("42.txt", "r");
        }
    }
    if (lv == 9) {
        if (emd == 0) {
            f = fopen("90.txt", "r");
        }
        if (emd == 1) {
            f = fopen("91.txt", "r");
        }
        if (emd == 2) {
            f = fopen("92.txt", "r");
        }
    }
    if (lv == 16) {
        if (emd == 0) {
            f = fopen("160.txt", "r");
        }
        if (emd == 1) {
            f = fopen("161.txt", "r");
        }
        if (emd == 2) {
            f = fopen("162.txt", "r");
        }
    }

    for (i = 0; i < lv * lv; i++) {
        fscanf(f, "%d", &a[i]);
    }

    for (j = 0; j < lv * lv; j++) {
        fscanf(f, "%d", &index[j]);
        if (index[j] == 0)
            break;
        count[index[j]] = 1;
    }
    fclose(f);
}

void init_text(SDL_Renderer *renderer, SDL_Texture *text_button[], int i_menu, TTF_Font *font) {

    /* Variables from anton2920 */
    auto int j;

    switch (i_menu) {
        case 1: {
            for (j = 0; j < 3; j++) {
                if (j == 0) {
                    char text[] = "DRAGONS";
                    text_button[0] = get_text_texture_text(renderer, font, text);
                }
                if (j == 1) {
                    char text[] = "BTS";
                    text_button[1] = get_text_texture_text(renderer, font, text);
                }
                if (j == 2) {
                    char text[] = "CLASSIC";
                    text_button[2] = get_text_texture_text(renderer, font, text);
                }
            }
        }
            break;
        case 2: // main menu
        {
            for (j = 0; j < 3; j++) {
                if (j == 0) {
                    char text[] = "PLAY";
                    text_button[0] = get_text_texture_text(renderer, font, text);
                }
                if (j == 1) {
                    char text[] = "RECORDS";
                    text_button[1] = get_text_texture_text(renderer, font, text);
                }
                if (j == 2) {
                    char text[] = "EXIT";
                    text_button[2] = get_text_texture_text(renderer, font, text);
                }
            }
        }
            break;
        case 3: // level
        {
            for (j = 0; j < 3; j++) {
                if (j == 0) {
                    char text[] = "4 X 4";
                    text_button[0] = get_text_texture_text(renderer, font, text);
                }
                if (j == 1) {
                    char text[] = "9 X 9";
                    text_button[1] = get_text_texture_text(renderer, font, text);
                }
                if (j == 2) {
                    char text[] = "16 X 16";
                    text_button[2] = get_text_texture_text(renderer, font, text);
                }
            }
        }
            break;
        case 4: // сложность
        {
            for (j = 0; j < 3; j++) {
                if (j == 0) {
                    char text[] = "EASY";
                    text_button[0] = get_text_texture_text(renderer, font, text);
                }
                if (j == 1) {
                    char text[] = "MEDIUM";
                    text_button[1] = get_text_texture_text(renderer, font, text);
                }
                if (j == 2) {
                    char text[] = "HARD";
                    text_button[2] = get_text_texture_text(renderer, font, text);
                }
            }
        }
            break;
        case 5: // ВРЕМЯ
        {
            for (j = 0; j < 2; j++) {
                if (j == 0) {
                    char text[] = "WITH TIME";
                    text_button[0] = get_text_texture_text(renderer, font, text);
                }
                if (j == 1) {
                    char text[] = "CLASSIC";
                    text_button[1] = get_text_texture_text(renderer, font, text);
                }
            }
        }
            break;
        case 6: // record
            break;
        case 7: // win
        {
            for (j = 0; j < 2; j++) {
                if (j == 0) {
                    char text[] = "YOU WIN!";
                    text_button[0] = get_text_texture_text(renderer, font, text);
                }
                if (j == 1) {
                    char text[] = "NEW RECORD!";
                    text_button[1] = get_text_texture_text(renderer, font, text);
                }
            }
        }
            break;
        case 8: // winner name
        {
            for (j = 0; j < 2; j++) {
                if (j == 0) {
                    char text[] = "Enter your name:";
                    text_button[0] = get_text_texture_text(renderer, font, text);
                }
                if (j == 1) {
                    char text[] = "OK";
                    text_button[1] = get_text_texture_text(renderer, font, text);
                }
            }
        }
            break;
        default:
            break;
    }
}

void draw_record(SDL_Renderer *renderer, SDL_Texture *fon, SDL_Texture *fon_rec, SDL_Texture *text_logo,
                 SDL_Texture *text_button[], SDL_Rect button[], int number, SDL_Texture *exit_texture) {

    /* Variables from anton2920 */
    auto int i;

    SDL_Rect fon_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Rect logo_rect = {250, 50, 300, 100};
    SDL_Rect ex = {700, 500, 75, 75};
    SDL_Rect rec = {100, 175, 600, 300};
    SDL_RenderCopy(renderer, fon, NULL, &fon_rect);
    SDL_RenderCopy(renderer, fon_rec, NULL, &rec);
    SDL_RenderCopy(renderer, text_logo, NULL, &logo_rect);

    for (i = 0; i < number; i++) {
        SDL_RenderCopy(renderer, text_button[i], NULL, &button[i]);
    }

    SDL_RenderCopy(renderer, exit_texture, NULL, &ex);
    SDL_RenderPresent(renderer);
}

int game_end(int count[], int red[], int lv) {

    /* Variables from anton2920 */
    auto int i, j;

    int c = 0;
    for (j = 0; j < lv * lv; j++) {
        if (count[j] == 0) {
            c = 1;
        }
    }
    if (c == 0) {
        int r = 0;
        for (i = 0; i < lv * lv; i++) {
            if (red[i] == 1) {
                r = 1;
            }
        }

        if (r == 0) {
            return 2;
            /* draw_game(0, renderer, fon, cell_fon, text_logo, cell_text, cell, lv*lv, exit_texture); */
        }
    }
    return 1;
}

void init_rect(SDL_Rect button[], int sign, int lv, int j) {

    /* Variables from anton2920 */
    auto int i;

    if (sign == 1) // для меню
    {
        /* button[0] = { 125, 250, 200, 100 }; */
        button[0].x = 125;
        button[0].y = 250;
        button[0].w = 200;
        button[0].h = 100;

        /* button[1] = { 475, 250, 200, 100 }; */
        button[1].x = 475;
        button[1].y = 250;
        button[1].w = 200;
        button[1].h = 100;

        /* button[2] = { 300, 425, 200, 100 }; */
        button[2].x = 300;
        button[2].y = 425;
        button[2].w = 200;
        button[2].h = 100;
    }
    if (sign == 2) // для игры
    {
        for (i = 0; i < lv * lv; i++) {
            if (lv == 4) {
                /* button[i] = { 300 + (i%lv) * 50, 200 + (i / lv) * 50, 50, 50 }; */
                button[i].x = 300 + (i % lv) * 50;
                button[i].y = 200 + (i / lv) * 50;
                button[i].w = 50;
                button[i].h = 50;
            } else if (lv == 9) {
                /* button[i] = { 175 + (i%lv) * 50, 100 + (i / lv) * 50, 50, 50 }; */
                button[i].x = 175 + (i % lv) * 50;
                button[i].y = 100 + (i / lv) * 50;
                button[i].w = 50;
                button[i].h = 50;
            } else {
                /* button[i] = { 200 + (i%lv) * 25, 150 + (i / lv) * 25, 25, 25 }; */
                button[i].x = 200 + (i % lv) * 25;
                button[i].y = 150 + (i / lv) * 25;
                button[i].w = 25;
                button[i].h = 25;
            }
        }
    }
    if (sign == 3) // рекорды. время
    {
        /* button[j] = { 200, 200 + (j - 5) * 51, lv * 30, 50 }; */
        button[j].x = 200;
        button[j].y = 200 + (j - 5) * 51;
        button[j].w = lv * 30;
        button[j].h = 50;
    }
    if (sign == 4) // рекорды. имя
    {
        /* button[j] = { 450, 200 + j * 51, lv * 25, 50 }; */
        button[j].x = 450;
        button[j].y = 200 + j * 51;
        button[j].w = lv * 25;
        button[j].h = 50;
    }
}

void enter_file_winner(int lv, int emd, int winner_time[], char winner_name[5][12]) {

    /* Variables from anton2920 */
    auto int j;

    FILE *f = NULL;
    if (lv == 4) {
        if (emd == 0) {
            f = fopen("40_win.txt", "w+b");
        }
        if (emd == 1) {
            f = fopen("41_win.txt", "w+b");
        }
        if (emd == 2) {
            f = fopen("42_win.txt", "w+b");
        }
    }
    if (lv == 9) {
        if (emd == 0) {
            f = fopen("90_win.txt", "w+b");
        }
        if (emd == 1) {
            f = fopen("91_win.txt", "w+b");
        }
        if (emd == 2) {
            f = fopen("92_win.txt", "w+b");
        }
    }
    if (lv == 16) {
        if (emd == 0) {
            f = fopen("160_win.txt", "w+b");
        }
        if (emd == 1) {
            f = fopen("161_win.txt", "w+b");
        }
        if (emd == 2) {
            f = fopen("162_win.txt", "w+b");
        }
    }
    for (j = 0; j < 5; j++) {
        fprintf(f, "%d ", winner_time[j]);
    }
    for (j = 0; j < 5; j++) {
        fprintf(f, "%s", winner_name[j]);
        fprintf(f, " ");
    }
    fclose(f);
}

void read_file_winner(int lv, int emd, int winner_time[], char winner_name[5][12]) {

    /* Variables from anton2920 */
    auto int j;

    FILE *f = NULL;

    if (lv == 4) {
        if (emd == 0) {
            f = fopen("40_win.txt", "rb");
        }
        if (emd == 1) {
            f = fopen("41_win.txt", "rb");
        }
        if (emd == 2) {
            f = fopen("42_win.txt", "rb");
        }
    }
    if (lv == 9) {
        if (emd == 0) {
            f = fopen("90_win.txt", "rb");
        }
        if (emd == 1) {
            f = fopen("91_win.txt", "rb");
        }
        if (emd == 2) {
            f = fopen("92_win.txt", "rb");
        }
    }
    if (lv == 16) {
        if (emd == 0) {
            f = fopen("160_win.txt", "rb");
        }
        if (emd == 1) {
            f = fopen("161_win.txt", "rb");
        }
        if (emd == 2) {
            f = fopen("162_win.txt", "rb");
        }
    }

    for (j = 0; j < 5; j++) {
        fscanf(f, "%d", &winner_time[j]);
    }
    for (j = 0; j < 5; j++) {
        fscanf(f, "%s", winner_name[j]);
    }
    fclose(f);
}

int time_win(int time, int winner_time[], int lv, int emd, char winner_name[5][12], char t_name[]) {

    /* Variables from anton2920 */
    auto int i, j;

    int winner = 0;
    read_file_winner(lv, emd, winner_time, winner_name);

    for (i = 0; i < 5; i++) { // сортируем массив в секундах
        for (j = 0; j < 5; j++) {
            if (winner_time[i] < winner_time[j]) {
                int t = winner_time[i];
                winner_time[i] = winner_time[j];
                winner_time[j] = t;
                char k[12] = {};
                strcpy(k, winner_name[i]);
                strcpy(winner_name[i], winner_name[j]);
                strcpy(winner_name[j], k);
            }
        }
    }


    for (i = 0; i < 5; i++) // проверяем новое время
    {
        for (j = 0; j < 5; j++) {
            if (time < winner_time[j]) {
                int t = time;
                time = winner_time[j];
                winner_time[j] = t;
                char k[12] = {};
                strcpy(k, t_name);
                strcpy(t_name, winner_name[j]);
                strcpy(winner_name[j], k);
            }
        }
    }
    enter_file_winner(lv, emd, winner_time, winner_name);
    return winner;
}

int is_user_hit(SDL_Rect button, int x, int y) {
    if ((x > button.x) && (x < (button.x + button.w)) && (y > button.y) && (y < (button.y + button.h))) return 1;
    else return 0;
}

void draw_name(SDL_Renderer *renderer, SDL_Texture *fon, SDL_Texture *text_logo, SDL_Texture *cell_fon,
               SDL_Texture *winner_text[], SDL_Rect winner_new_rect[], SDL_Texture *name_text[], SDL_Rect name_win[]) {

    /* Variables from anton2920 */
    auto int i;

    SDL_Rect fon_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Rect logo_rect = {250, 50, 300, 100};

    SDL_RenderCopy(renderer, fon, NULL, &fon_rect);
    SDL_RenderCopy(renderer, text_logo, NULL, &logo_rect);

    for (i = 0; i < 2; i++) {
        SDL_RenderCopy(renderer, winner_text[i], NULL, &winner_new_rect[i]);
    }
    for (i = 0; i < 12; i++) {
        SDL_RenderCopy(renderer, cell_fon, NULL, &name_win[i]);
    }
    for (i = 0; i < 13; i++) {
        SDL_RenderCopy(renderer, name_text[i], NULL, &name_win[i]);
    }
    SDL_RenderPresent(renderer);
}

SDL_Texture *get_text_texture(SDL_Renderer *renderer, TTF_Font *font, int i, int k, int *red) {
    char text[10];
    SDL_Surface *textSurface = NULL;
    SDL_Color fore_color = {};
    SDL_Color back_color = {20, 20, 20};
    if (i != k) {
        *red = 1;
        /* fore_color = { 128,0,0 }; */
        fore_color.r = 128;
        fore_color.g = 0;
        fore_color.b = 0;
        fore_color.a = 0;
    } else {
        *red = 0;
    }

    /* _itoa_s(i, text, 10); */
    sprintf(text, "%d", i);

    textSurface = TTF_RenderText_Shaded(font, text, fore_color, back_color);
    SDL_SetColorKey(textSurface, SDL_TRUE, SDL_MapRGB(textSurface->format, 20, 20, 20));
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    return texture;
}

SDL_Texture *get_text_texture_text(SDL_Renderer *renderer, TTF_Font *font, char *text) {
    SDL_Surface *textSurface = NULL;

    SDL_Color fore_color = {};
    SDL_Color back_color = {20, 20, 20};
    textSurface = TTF_RenderText_Shaded(font, text, fore_color, back_color);
    SDL_SetColorKey(textSurface, SDL_TRUE, SDL_MapRGB(textSurface->format, 20, 20, 20));
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    return texture;
}