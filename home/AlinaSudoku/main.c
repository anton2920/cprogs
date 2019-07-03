#define CLION /* Only for anton2920's workspace. Must be commented out or undefined at the end */

#ifdef CLION

#include <mines.h>
#include "AlinaSudoku_dev/Header.h"

#else
#include "Header.h"
#endif

#ifdef _WIN32
#pragma comment (lib, "SDL2_mixer.lib")
#undef main
#endif

int main(int argc, char **argv) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Sudoku", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                          SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    TTF_Init();
    TTF_Font *font = TTF_OpenFont("3.ttf", 100);

    Mix_Init(0);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024); // звук
    Mix_Music *fon_m = NULL;
    loadmusic(fon_m, 0);

    int a[N]; // массив цифр
    int lv = 0; // уровень
    int emd = 0; // сложность
    int index[N]; // массив цифр на поле

    SDL_Rect button[3], cell[N] = {}; // структура для кнопок, структура для клеток поля
    SDL_Texture *fon = NULL, *fon_rec = NULL, *text_logo = NULL, *exit_texture = NULL; // текстура фона, текстура рекордов, текстура лого, текстура кнопки выход
    SDL_Texture *texture_button = NULL, *button_text[3] = {}, *winner_text[2] = {}, *cell_text[257] = {}, *game_sudoku = NULL, *cell_fon = NULL;
    // текстура фона кнопки, текстура текста на кнопке, текстура если победа, текстура для цифр, текстура ?, текстура фона клетки
    SDL_Event event;
    bool quit = false;
    int sign = 0, play = 0;
    // номер экрана

    init_rect(button, 1, 0, 0); // инициализация первого экрана

    SDL_Surface *fonImage = IMG_Load("theme.bmp");
    SDL_SetColorKey(fonImage, SDL_TRUE, SDL_MapRGB(fonImage->format, 0, 0, 0));
    texture_button = SDL_CreateTextureFromSurface(renderer, fonImage);
    char t[] = "SUDOKU";
    text_logo = get_text_texture_text(renderer, font, t);
    fonImage = IMG_Load("fon_0.bmp");
    fon = SDL_CreateTextureFromSurface(renderer, fonImage);
    fonImage = IMG_Load("fon_record.bmp");
    fon_rec = SDL_CreateTextureFromSurface(renderer, fonImage);
    fonImage = IMG_Load("exit.bmp");
    SDL_SetColorKey(fonImage, SDL_TRUE, SDL_MapRGB(fonImage->format, 255, 255, 255));
    exit_texture = SDL_CreateTextureFromSurface(renderer, fonImage);
    fonImage = IMG_Load("cell.bmp");
    cell_fon = SDL_CreateTextureFromSurface(renderer, fonImage);
    SDL_FreeSurface(fonImage);

    init_text(renderer, button_text, 1, font); // получаем текстуры текста для первого экрана
    draw_game(0, lv, renderer, fon, texture_button, text_logo, button_text, button, 3,
              exit_texture); // отрисовка первого экрана

    int i_help = -5;
    char winner_name[5][12] = {};
    int count[N] = {};
    int start = 0; // гл. меню
    int l = 0; //  индексы
    int red[N] = {};
    int z = 0; // для ввода двузначных цифр
    int time = 0;
    int new_record = 0;
    int start_time = 0, end_time = 0; // время
    int winner_time[5] = {100, 100, 100, 100, 100};
    char t_name[12] = {};
    int stop = -1; // рекорды
    int winner = 0;
    SDL_Rect ex_rect = {700, 500, 75, 75};
    SDL_Texture *name_text[13] = {};
    SDL_Texture *record_texture[10] = {};
    SDL_Rect name_win[13];
    SDL_Rect record_rect[10] = {};
    SDL_Rect winner_new_rect[2];
    int key = -1;

    /* Variables from anton2920 */
    auto int i, j;

    /* winner_new_rect[0] = { 275, 250, 250, 75 }; */
    winner_new_rect[0].x = 275;
    winner_new_rect[0].y = 250;
    winner_new_rect[0].w = 250;
    winner_new_rect[0].h = 75;

    /* winner_new_rect[1] = { 275, 350, 250, 75 }; */
    winner_new_rect[1].x = 275;
    winner_new_rect[1].y = 350;
    winner_new_rect[1].w = 250;
    winner_new_rect[1].h = 75;

    for (i = 0; i < 12; i++) {
        /* name_win[i] = { 100 + i * 50, 300, 50, 50 }; */
        name_win[i].x = 100 + i * 50;
        name_win[i].y = 300;
        name_win[i].w = 50;
        name_win[i].h = 50;
    }
    int ex = 1;

    /* name_win[12] = { 375, 400, 50, 50 }; */
    name_win[12].x = 375;
    name_win[12].y = 400;
    name_win[12].w = 50;
    name_win[12].h = 50;

    int in_time = 0;
    while (!quit) {
        SDL_PollEvent(&event);

        if (event.type == SDL_QUIT)
            quit = true;

        if ((ex == 0) && (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) &&
            (is_user_hit(ex_rect, event.button.x, event.button.y))) // переход от таблицы рекордов в главное меню
        {
            ex = 1;
            sign = 1;
            init_text(renderer, button_text, 2, font);
            draw_game(0, lv, renderer, fon, texture_button, text_logo, button_text, button, 3, exit_texture);
        }
        if ((event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) && (start == 0) &&
            (winner == 2) && (sign == 1)) {
            draw_game(0, lv, renderer, fon, texture_button, text_logo, button_text, button, 3, exit_texture);
        }
        if ((event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) && (start == 0)) {
            for (i = 0; i < 3; i++) {
                if (is_user_hit(button[i], event.button.x, event.button.y)) {
                    event.type = NO_EVENT;
                    switch (sign) {
                        case 0: // экран 1. выбор темы
                        {
                            loadmusic(fon_m, i);
                            SDL_Surface *fonImage1 = NULL;
                            switch (i) {
                                case 0: {
                                    fonImage1 = IMG_Load("key_0.bmp");
                                    break;
                                }
                                case 1: {
                                    fonImage1 = IMG_Load("key_1.bmp");
                                    break;
                                }
                                case 2: {
                                    fonImage1 = IMG_Load("key_2.bmp");
                                    break;
                                }
                                default:
                                    break;
                            }

                            SDL_SetColorKey(fonImage1, SDL_TRUE, SDL_MapRGB(fonImage1->format, 0, 0, 0));
                            texture_button = SDL_CreateTextureFromSurface(renderer, fonImage1);
                            switch (i) {
                                case 0: {
                                    fonImage1 = IMG_Load("fon_3.bmp");
                                    break;
                                }
                                case 1: {
                                    fonImage1 = IMG_Load("fon_1.bmp");
                                    break;
                                }
                                case 2: {
                                    fonImage1 = IMG_Load("fon_2.bmp");
                                    break;
                                }
                                default:
                                    break;
                            }
                            fon = SDL_CreateTextureFromSurface(renderer, fonImage1);
                            SDL_FreeSurface(fonImage1);

                            sign = 1;
                            init_text(renderer, button_text, 2, font);
                            draw_game(0, lv, renderer, fon, texture_button, text_logo, button_text, button, 3,
                                      exit_texture);
                        }
                            break;
                        case 1: // экран 2. главное меню
                        {
                            if (i == 0) // игра
                            {
                                sign = 2;
                                play = 0;
                                init_text(renderer, button_text, 5, font);
                                draw_game(0, lv, renderer, fon, texture_button, text_logo, button_text, button, 2,
                                          exit_texture);
                            }
                            if (i == 1) // рекорды
                            {
                                sign = 3;
                                init_text(renderer, button_text, 4, font);
                                draw_game(0, lv, renderer, fon, texture_button, text_logo, button_text, button, 3,
                                          exit_texture);
                                stop = 0;
                            }
                            if (i == 2) // выход
                            {
                                quit = true;
                            }
                        }
                            break;
                        case 2: {
                            switch (play) // выбор уровня, сложности и режима игры
                            {
                                case 0: // режим
                                {
                                    init_text(renderer, button_text, 3, font);
                                    draw_game(0, lv, renderer, fon, texture_button, text_logo, button_text, button, 3,
                                              exit_texture);
                                    in_time = i;
                                    play = 1;
                                    break;
                                }
                                case 1: // уровень
                                {
                                    lv = i;
                                    if (lv == 0) {
                                        lv = 4;
                                    } else if (lv == 1) {
                                        lv = 9;
                                    } else if (lv == 2) {
                                        lv = 16;
                                    }
                                    init_text(renderer, button_text, 4, font);
                                    draw_game(0, lv, renderer, fon, texture_button, text_logo, button_text, button, 3,
                                              exit_texture);
                                    play = 2;
                                    break;
                                }
                                case 2: // сложность и отрисовка поля
                                {
                                    emd = i;
                                    init_rect(cell, 2, lv, 0); // координаты клеток
                                    initField(N, cell_text);
                                    read_file(lv, a, index, emd, count); // цифры
                                    for (l = 0, j = 0; j < lv * lv; j++) {
                                        if (index[l] == 0)
                                            break;
                                        else {
                                            cell_text[index[l]] = get_text_texture(renderer, font, a[index[l]],
                                                                                   a[index[l]], &red[l]);
                                            l++;
                                        }
                                    }
                                    draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv * lv,
                                              exit_texture);
                                    start = 1;
                                    play = 0;
                                    start_time = clock(); // начинаем отсчет времени
                                    break;
                                }
                                default:
                                    break;
                            }
                            break;
                        }
                        case 3: // таблица рекордов
                        {
                            switch (stop) {
                                case 0: // выбор уровня
                                {
                                    init_text(renderer, button_text, 3, font);
                                    draw_game(0, lv, renderer, fon, texture_button, text_logo, button_text, button, 3,
                                              exit_texture);
                                    lv = i;
                                    if (lv == 0) {
                                        lv = 4;
                                    }
                                    if (lv == 1) {
                                        lv = 9;
                                    }
                                    if (lv == 2) {
                                        lv = 16;
                                    }
                                    stop = 1;
                                    break;
                                }
                                case 1: // выбор сложности
                                {
                                    emd = i;
                                    read_file_winner(lv, emd, winner_time, winner_name);
                                    for (j = 5; j < 10; j++) {
                                        if (winner_time[j - 5] < 10) {
                                            init_rect(record_rect, 3, 1, j);
                                        } else if (winner_time[j - 5] < 100) {
                                            init_rect(record_rect, 3, 2, j);
                                        } else if (winner_time[j - 5] < 1000) {
                                            init_rect(record_rect, 3, 3, j);
                                        } else if (winner_time[j - 5] < 10000) {
                                            init_rect(record_rect, 3, 4, j);
                                        } else {
                                            init_rect(record_rect, 3, 5, j);
                                        }
                                    }
                                    for (j = 0; j < 5; j++) {
                                        init_rect(record_rect, 4, strlen(winner_name[j]), j);
                                    }

                                    for (j = 0; j < 5; j++) // текстура со временем( в секундах)
                                    {
                                        record_texture[j + 5] = get_text_texture(renderer, font, winner_time[j],
                                                                                 winner_time[j], &in_time);
                                    }
                                    for (j = 0; j < 5; j++) // текстура с именем
                                    {
                                        record_texture[j] = get_text_texture_text(renderer, font, winner_name[j]);
                                    }
                                    draw_record(renderer, fon, fon_rec, text_logo, record_texture, record_rect, 10,
                                                exit_texture);
                                    ex = 0;
                                    break;
                                }
                                default:
                                    break;
                            }
                        }
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        if ((event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) &&
            (start == 1)) // игровой процесс (узнаем значение какой клетки хочет поменять пользователь)
        {
            for (i = 0; i < lv * lv; i++) {
                if (is_user_hit(cell[i], event.button.x, event.button.y) == 1) {
                    play = i;
                }
            }
        }
        if ((event.type == SDL_KEYDOWN) && (play == i_help)) // для вывода цифр от 10 до 16(для уровня 16х16)
        {
            switch (event.key.keysym.sym) {
                case SDLK_1:
                case SDLK_KP_1: {
                    cell_text[play] = get_text_texture(renderer, font, 11, a[play], &red[play]);
                    count[play] = 1;
                    draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv * lv, exit_texture);
                    start = game_end(count, red, lv);
                    i_help = -5;
                    z = 1;
                    break;
                }
                case SDLK_2:
                case SDLK_KP_2: {
                    cell_text[play] = get_text_texture(renderer, font, 12, a[play], &red[play]);
                    count[play] = 1;
                    draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv * lv, exit_texture);
                    start = game_end(count, red, lv);
                    i_help = -5;
                    z = 1;
                    break;
                }
                case SDLK_3:
                case SDLK_KP_3: {
                    cell_text[play] = get_text_texture(renderer, font, 13, a[play], &red[play]);
                    count[play] = 1;
                    draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv * lv, exit_texture);
                    start = game_end(count, red, lv);
                    i_help = -5;
                    z = 1;
                }
                    break;
                case SDLK_4:
                case SDLK_KP_4: {
                    cell_text[play] = get_text_texture(renderer, font, 14, a[play], &red[play]);
                    count[play] = 1;
                    draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv * lv, exit_texture);
                    start = game_end(count, red, lv);
                    i_help = -5;
                    z = 1;
                    break;
                }
                case SDLK_5:
                case SDLK_KP_5: {
                    cell_text[play] = get_text_texture(renderer, font, 15, a[play], &red[play]);
                    count[play] = 1;
                    draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv * lv, exit_texture);
                    start = game_end(count, red, lv);
                    i_help = -5;
                    z = 1;

                    break;
                }
                case SDLK_6:
                case SDLK_KP_6: {
                    cell_text[play] = get_text_texture(renderer, font, 16, a[play], &red[play]);
                    count[play] = 1;
                    draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv * lv, exit_texture);
                    start = game_end(count, red, lv);
                    i_help = -5;
                    z = 1;
                    break;
                }
                case SDLK_0:
                case SDLK_KP_0: {
                    cell_text[play] = get_text_texture(renderer, font, 10, a[play], &red[play]);
                    count[play] = 1;
                    draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv * lv, exit_texture);
                    start = game_end(count, red, lv);
                    i_help = -5;
                    z = 1;
                }
                    break;
                case SDLK_7:
                case SDLK_KP_7: {
                    if (lv > 4) {
                        cell_text[play] = get_text_texture(renderer, font, 7, a[play], &red[play]);
                        count[play] = 1;
                        draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv * lv, exit_texture);
                        start = game_end(count, red, lv);
                        i_help = -5;
                        z = 1;
                    }
                    break;
                }
                case SDLK_8:
                case SDLK_KP_8: {
                    if (lv > 4) {
                        cell_text[play] = get_text_texture(renderer, font, 8, a[play], &red[play]);
                        count[play] = 1;
                        draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv * lv, exit_texture);
                        start = game_end(count, red, lv);
                        i_help = -5;
                        z = 1;
                    }
                    break;
                }
                case SDLK_9:
                case SDLK_KP_9: {
                    if (lv > 4) {
                        cell_text[play] = get_text_texture(renderer, font, 9, a[play], &red[play]);
                        count[play] = 1;
                        draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv * lv, exit_texture);
                        start = game_end(count, red, lv);
                        i_help = -5;
                        z = 1;
                    }
                    break;
                }
                default:
                    break;
            }
        }
        if ((event.type == SDL_KEYDOWN) && (play >= 0) && (play != i_help)) // ввод цифр пользователем
        {
            switch (event.key.keysym.sym) {
                case SDLK_1:
                case SDLK_KP_1: {
                    if ((lv == 16) && (z != 1)) {
                        i_help = play;
                    }
                    if (z != 1) {

                        cell_text[play] = get_text_texture(renderer, font, 1, a[play], &red[play]);
                        count[play] = 1;
                        draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv * lv, exit_texture);
                        start = game_end(count, red, lv);
                    }
                    break;
                }
                case SDLK_2:
                case SDLK_KP_2: {
                    if (z != 1) {

                        cell_text[play] = get_text_texture(renderer, font, 2, a[play], &red[play]);
                        count[play] = 1;
                        draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv * lv, exit_texture);
                        start = game_end(count, red, lv);
                    }
                    break;
                }
                case SDLK_3:
                case SDLK_KP_3: {
                    if (z != 1) {
                        cell_text[play] = get_text_texture(renderer, font, 3, a[play], &red[play]);
                        count[play] = 1;
                        draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv * lv, exit_texture);
                        start = game_end(count, red, lv);
                    }
                    break;
                }
                case SDLK_4:
                case SDLK_KP_4: {
                    if (z != 1) {
                        cell_text[play] = get_text_texture(renderer, font, 4, a[play], &red[play]);
                        count[play] = 1;
                        draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv * lv, exit_texture);
                        start = game_end(count, red, lv);
                    }
                    break;
                }
                case SDLK_5:
                case SDLK_KP_5: {
                    if (lv > 4) {
                        if (z != 1) {
                            cell_text[play] = get_text_texture(renderer, font, 5, a[play], &red[play]);
                            count[play] = 1;
                            draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv * lv,
                                      exit_texture);
                            start = game_end(count, red, lv);
                        }
                    }
                    break;
                }
                case SDLK_6:
                case SDLK_KP_6: {
                    if (lv > 4) {
                        if (z != 1) {
                            cell_text[play] = get_text_texture(renderer, font, 6, a[play], &red[play]);
                            count[play] = 1;
                            draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv * lv,
                                      exit_texture);
                            start = game_end(count, red, lv);
                        }
                    }
                    break;
                }
                case SDLK_7:
                case SDLK_KP_7: {
                    if (lv > 4) {
                        cell_text[play] = get_text_texture(renderer, font, 7, a[play], &red[play]);
                        count[play] = 1;
                        draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv * lv, exit_texture);
                        start = game_end(count, red, lv);
                    }
                    break;
                }
                case SDLK_8:
                case SDLK_KP_8: {
                    if (lv > 4) {
                        cell_text[play] = get_text_texture(renderer, font, 8, a[play], &red[play]);
                        count[play] = 1;
                        draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv * lv, exit_texture);
                        start = game_end(count, red, lv);
                    }
                    break;
                }
                case SDLK_9:
                case SDLK_KP_9: {
                    if (lv > 4) {
                        cell_text[play] = get_text_texture(renderer, font, 9, a[play], &red[play]);
                        count[play] = 1;
                        draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv * lv, exit_texture);
                        start = game_end(count, red, lv);
                    }
                    break;
                }
                default:
                    break;
            }
        }
        z = 0;
        if ((winner == 3) && (event.type == SDL_MOUSEBUTTONDOWN &&
                              event.button.button == SDL_BUTTON_LEFT)) // возврат в главное меню после игры?
        {
            event.type = NO_EVENT;
            start = 0;
            sign = 1;
            init_text(renderer, button_text, 2, font);
            draw_game(0, lv, renderer, fon, texture_button, text_logo, button_text, button, 3, exit_texture);
        }
        if (new_record == 1) // пользователь вводит свое имя
        {
            draw_name(renderer, fon, text_logo, cell_fon, winner_text, winner_new_rect, name_text, name_win);
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                for (i = 0; i < 13; i++) {
                    if (is_user_hit(name_win[i], event.button.x, event.button.y) == 1) {
                        if (i == 12) {
                            time_win(time, winner_time, lv, emd, winner_name, t_name); // запись в файл
                            start = 0;
                            init_text(renderer, button_text, 2, font);
                            draw_game(0, lv, renderer, fon, texture_button, text_logo, button_text, button, 3,
                                      exit_texture);
                            new_record = 0;
                            sign = 1;
                        } else {
                            key = i;
                        }
                    }
                }
            }
        }
        if (winner == 1) // время - рекорд
        {
            draw_game(0, lv, renderer, fon, NULL, text_logo, winner_text, winner_new_rect, 2, exit_texture);
            init_text(renderer, winner_text, 8, font);

            /* winner_new_rect[0] = { 275, 250, 250, 75 }; */
            winner_new_rect[0].x = 275;
            winner_new_rect[0].y = 250;
            winner_new_rect[0].w = 250;
            winner_new_rect[0].h = 50;

            /* winner_new_rect[1] = { 275, 350, 250, 75 }; */
            winner_new_rect[1].x = 375;
            winner_new_rect[1].y = 400;
            winner_new_rect[1].w = 50;
            winner_new_rect[1].h = 50;

            new_record = 1;
            winner = 2;
        }
        if (start == 2) // пользователь победил
        {
            end_time = clock(); // время окончания игры
            time = (end_time - start_time) / CLOCKS_PER_SEC; // время игры в секундах

            init_text(renderer, winner_text, 7, font);
            start = 3;
            play = -1;
            if (in_time == 0) // проверяем новое время( если новое время рекорд, то просим пользователя ввести имя)
            {
                for (i = 0; i < 5; i++) {
                    for (j = 0; j < 5; j++) {
                        if (time < winner_time[j]) {
                            winner = 1;
                            draw_game(0, lv, renderer, fon, NULL, text_logo, &winner_text[0], &winner_new_rect[0], 1,
                                      exit_texture);
                        }
                    }
                }
            } else {
                /* if (winner != 1) { */
                    draw_game(0, lv, renderer, fon, NULL, text_logo, &winner_text[0], &winner_new_rect[0], 1,
                              exit_texture);
                    winner = 3;
                /* } */
            }
        }
        if ((event.type == SDL_KEYDOWN) && (key >= 0)) { /* ввод имени */
            t_name[key] = event.key.keysym.sym;
            name_text[key] = get_text_texture_text(renderer, font, (char *) &event.key.keysym.sym);
        }

    }

    for (i = 0; i < 2; i++) {
        SDL_DestroyTexture(winner_text[i]);
    }
    for (i = 0; i < 3; i++) {
        SDL_DestroyTexture(button_text[i]);
    }
    SDL_DestroyTexture(texture_button);
    SDL_DestroyTexture(game_sudoku);
    SDL_DestroyTexture(fon);
    SDL_DestroyTexture(text_logo);

    TTF_CloseFont(font);
    TTF_Quit();
    Mix_FreeMusic(fon_m);
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}