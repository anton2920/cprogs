#include "proj_folder/source.h"

int main(int argc, char *argv[]) {

    /* Initializing variables */
    struct SDL_Window *window = NULL;
    struct SDL_Renderer *renderer = NULL;
    union SDL_Event event;
    bool quit = false;


    /* VarCheck */
    if (check_args(argc, argv) == true) {
        if (SDL_Init_All(&window, &renderer) == true) {

            /* Initializing variables */
            struct _TTF_Font *my_font = TTF_OpenFont("../font/Font.ttf", 100);
            assert(my_font != NULL);
            struct SDL_Texture *textTexture;

            int k = 0, i;
            char text[10];
            sprintf(text, "%d", k);
            textTexture = get_text_texture(renderer, text, my_font);
            assert(textTexture != NULL);

            /* CPU|GPU parity issue */
            struct SDL_Rect balls[BALL_C];
            init_balls(balls, BALL_C);
            struct SDL_Surface *ballImage = IMG_Load("../pictures/purepng.png");
            assert(ballImage != NULL); /* Debugging sh*t */
            SDL_SetColorKey(ballImage, SDL_TRUE, SDL_MapRGB(ballImage->format, 255, 255, 255));
            struct SDL_Texture *ballTexture = SDL_CreateTextureFromSurface(renderer, ballImage);
            assert(ballTexture != NULL);
            SDL_FreeSurface(ballImage);

            /* Audio */
            struct SDL_AudioSpec wavSpec;
            Uint32 wavLength;
            Uint8 *wavBuffer;
            SDL_LoadWAV("../wav/Very_bad_piece.wav", &wavSpec, &wavBuffer, &wavLength);

            SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

            int success = -1;
            for (i = 0; i < 5; ++i) {
                success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
            }
            if (!success) {
                SDL_PauseAudioDevice(deviceId, 0);
            }

            /* Main part. SDL2 */
            if (**(argv + 1) == '1') {
                while (!quit) {
                    while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_QUIT) {
                            quit = true;
                        }
                        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                            for (i = 0; i < BALL_C; i++) {
                                if (is_ball_hit(balls + i, event.button.x, event.button.y)) {
                                    balls[i].w = balls[i].h = 0;
                                    k++;
                                    sprintf(text, "%d", k);
                                    SDL_DestroyTexture(textTexture);
                                    textTexture = get_text_texture(renderer, text,my_font);
                                }
                            }
                        }
                    }
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                    SDL_RenderClear(renderer);
                    draw_balls(renderer, balls, BALL_C, ballTexture);
                    draw_text(renderer, textTexture);
                    SDL_RenderPresent(renderer);
                }

                SDL_CloseAudioDevice(deviceId);
                SDL_FreeWAV(wavBuffer);
                SDL_DestroyTexture(textTexture);
                SDL_DestroyTexture(ballTexture);
                TTF_CloseFont(my_font);
                TTF_Quit();
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
            } else if (**(argv + 1) == '2') {

            } else if (**(argv + 1) == '3') {

            }
        } else {
            fprintf(stderr, "Error! Code: %s\n", SDL_GetError());
        }
    }


    /* Returning value */
    return 0;
}