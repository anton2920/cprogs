# ifndef Header_h
#define Header_h
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include "SDL.h"
#include "SDL_image.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>

const int N = 400;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

void loadmusic(Mix_Music * fon, int n);

void draw_record(SDL_Renderer *renderer, SDL_Texture* fon, SDL_Texture* fon_rec, SDL_Texture* text_logo, SDL_Texture* text_button[], SDL_Rect button[], int number, SDL_Texture* exit_texture); void draw_game(int i_menu, int lv, SDL_Renderer *renderer, SDL_Texture* fon, SDL_Texture* T_button, SDL_Texture* text_logo, SDL_Texture* text_button[], SDL_Rect button[], int number, SDL_Texture* exit_texture); void read_file(int lv, int a[], int index[], int emd, int count[]);
void init_text(SDL_Renderer *renderer, SDL_Texture* text_button[], int i_menu, TTF_Font* font, int theme);
int game_end(int count[], int red[], int lv);
void init_rect(SDL_Rect button[], int sign, int lv, int j);
void enter_file_winner(int lv, int emd, int winner_time[], char winner_name[5][12]);
void read_file_winner(int lv, int emd, int winner_time[], char winner_name[5][12]);
int time_win(int time, int winner_time[], int lv, int emd, char winner_name[5][12], char t_name[]);
int is_user_hit(SDL_Rect buttom, int x, int y);
void draw_name(SDL_Renderer *renderer, SDL_Texture* fon, SDL_Texture* text_logo, SDL_Texture* cell_fon, SDL_Texture* winner_text[], SDL_Rect winner_new_rect[], SDL_Texture* name_text[], SDL_Rect name_win[]);

SDL_Texture* init_cell_texture(SDL_Renderer* &renderer, char*text, TTF_Font *font);
SDL_Texture* get_text_texture(SDL_Renderer* &renderer, TTF_Font *font, int i, int k, int *red);
SDL_Texture* get_text_texture_text(SDL_Renderer* &renderer, TTF_Font *font, char *text, int theme);
#endif