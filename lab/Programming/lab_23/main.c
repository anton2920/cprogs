#include "source.h"

int main(int argc, char *argv[]) {

    /* Initializing variables */
    struct SDL_Window *window = NULL;
    struct SDL_Renderer *renderer = NULL;
    union SDL_Event event;
    bool quit = false;
    srand((unsigned int) time(NULL) / 2);

    /* VarCheck */
    if (check_args(argc, argv) == true) {
        if (SDL_Init_All(&window, &renderer, (**(argv + 1) == '3') ? true : false) == true) {

            /* Initializing variables */
            struct _TTF_Font *my_font = TTF_OpenFont(FONT_PATH, 100);
            assert(my_font != NULL);
            struct SDL_Texture *textTexture;
            struct SDL_Rect main_rect = {0, 0, 70, 200};
            struct SDL_Rect *curr_ball = NULL;

            struct SDL_Color fore_color = {130, 140, 50, 0};
            /* struct SDL_Color back_color = { 188, 155, 166, 0 }; */
            struct SDL_Color back_color = {0, 0, 0, 0};

            int k = 0, i, check = 0;
            char text[10];
            sprintf(text, "%d", k);
            textTexture = get_text_texture(renderer, text, my_font, &fore_color, &back_color, shaded);
            assert(textTexture != NULL);

            /* Balls */
            struct SDL_Rect balls[BALL_C];
            struct pro_balls p_b[BALL_C];
            int ball_cost[BALL_C];
            init_balls(p_b, balls, ball_cost);

            /* CPU/GPU parity issue */
            struct SDL_Surface *ballImage = IMG_Load(PIC_PATH);
            assert(ballImage != NULL); /* Debugging sh*t */
            SDL_SetColorKey(ballImage, SDL_TRUE, SDL_MapRGB(ballImage->format, 255, 255, 255));
            struct SDL_Texture *ballTexture = SDL_CreateTextureFromSurface(renderer, ballImage);
            assert(ballTexture != NULL);
            SDL_FreeSurface(ballImage);

            struct SDL_Surface *ballImage1 = IMG_Load(BLUE_PIC_PATH);
            assert(ballImage1 != NULL); /* Debugging sh*t */
            SDL_SetColorKey(ballImage1, SDL_TRUE, SDL_MapRGB(ballImage1->format, 255, 255, 255));
            struct SDL_Texture *ballTexture1 = SDL_CreateTextureFromSurface(renderer, ballImage1);
            assert(ballTexture1 != NULL);
            SDL_FreeSurface(ballImage1);

            /* Audio */
            /*struct SDL_AudioSpec wavSpec;
            Uint32 wavLength;
            Uint8 *wavBuffer;
            SDL_LoadWAV(MUS_PATH, &wavSpec, &wavBuffer, &wavLength);

            SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

            int success = -1;
            for (i = 0; i < 5; ++i) {
                success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
            }
            if (!success) {
                SDL_PauseAudioDevice(deviceId, 0);
            }*/

            /* Audio. SDL_Mixer approach */
            struct Mix_Chunk *Sound = NULL;
            Mix_Music *fon = NULL;
            Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);

            /* Game */
            auto int mleft = MINES_TOTAL;
            auto int lleft = LIFES_TOTAL;

            /* Main part. SDL2 */
            /*loadmusic(fon);*/
            if (**(argv + 1) != '3') {
                while (!quit) {
                    while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_QUIT) {
                            quit = true;
                        }
                        if (**(argv + 1) == '1') {
                            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                                for (i = 0; i < BALL_C; i++) {
                                    if (is_ball_hit(balls + i, event.button.x, event.button.y)) {
                                        balls[i].w = balls[i].h = 0;
                                        sound(Sound, SND_PATH);
                                        k += ball_cost[i];
                                        sprintf(text, "%d", k);
                                        SDL_DestroyTexture(textTexture);
                                        textTexture = get_text_texture(renderer, text, my_font, &fore_color,
                                                                       &back_color, shaded);
                                    }
                                }
                            }
                        } else {
                            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                                for (i = 0; i < BALL_C && event.type == SDL_MOUSEBUTTONDOWN; i++) {
                                    if (is_ball_hit(balls + i, event.button.x, event.button.y) && balls + i != curr_ball) {
                                        curr_ball = (balls + i);
                                        event.type = 0;
                                        break;
                                    } else if (is_ball_hit(balls + i, event.button.x, event.button.y) && balls + i == curr_ball) {
                                        curr_ball = NULL;
                                        event.type = 0;
                                        break;
                                    }
                                }
                            } else if (event.type == SDL_KEYDOWN && curr_ball != NULL) {
                                if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) {
                                    curr_ball->y -= up_speed;
                                    check = 1;
                                } else if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
                                    curr_ball->y += down_speed;
                                    check = 1;
                                } else if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a) {
                                    curr_ball->x -= left_speed;
                                    check = 1;
                                } else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
                                    curr_ball->x += right_speed;
                                    check = 1;
                                }

                                if (check) {
                                    for (i = 0; i < BALL_C; ++i) {
                                        if (is_ball_collapse(balls + i, curr_ball) == true && balls + i != curr_ball && (balls + i)->w != 0) {
                                            balls[i].w = balls[i].h = 0;
                                            sound(Sound, SND_PATH);
                                            k += ball_cost[i];
                                            sprintf(text, "%d", k);
                                            SDL_DestroyTexture(textTexture);
                                            textTexture = get_text_texture(renderer, text, my_font, &fore_color,
                                                                           &back_color, shaded);
                                        }
                                    }

                                    check = 0;
                                }
                            }
                        }
                    }
                    if (curr_ball != NULL) {
                        for (i = 0; i < BALL_C; ++i) {
                            if (balls + i == curr_ball || (balls + i)->w == 0) {
                                continue;
                            }
                            move_ball(p_b + i);
                            if (is_ball_collapse(balls + i, curr_ball) == true && balls + i != curr_ball && (balls + i)->w != 0) {
                                balls[i].w = balls[i].h = 0;
                                sound(Sound, SND_PATH);
                                k += ball_cost[i];
                                sprintf(text, "%d", k);
                                SDL_DestroyTexture(textTexture);
                                textTexture = get_text_texture(renderer, text, my_font, &fore_color,
                                                               &back_color, shaded);
                            }

                        }
                        /* Check for collision && Fix 'em all */
                        ball_touch_another_ball(p_b, curr_ball);
                        balls_touch_wall(p_b, curr_ball);
                    }
                    /* Other stuff */
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                    SDL_RenderClear(renderer);
                    draw_text(renderer, textTexture, &main_rect);
                    draw_balls(renderer, balls, BALL_C, ballTexture, ballTexture1, ball_cost, my_font, curr_ball);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(DELAY);
                }

                /*SDL_CloseAudioDevice(deviceId);
                SDL_FreeWAV(wavBuffer);*/
                Mix_FreeMusic(fon);
                Mix_FreeChunk(Sound);
                Mix_CloseAudio();
                SDL_DestroyTexture(textTexture);
                SDL_DestroyTexture(ballTexture);
                TTF_CloseFont(my_font);
                TTF_Quit();
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
            } else {

                /* F**cking game. Mines, traps, score, lives */
                while (!quit) {
                    while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_QUIT) {
                            quit = true;
                        }
                        SDL_RenderClear(renderer);

                        draw_field(renderer); /* Drawing field */
                        spawn_mines(renderer); /* Spawning mines */
                        set_traps(renderer); /* Setting traps */
                        print_info(mleft, lleft, renderer, my_font); /* Printing mines information */

                        SDL_RenderPresent(renderer);
                    }
                }
            }
        } else {
            fprintf(stderr, "Error! Code: %s\n", SDL_GetError());
        }
    }


    /* Returning value */
    return 0;
}