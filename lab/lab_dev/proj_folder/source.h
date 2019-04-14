#ifndef LAB_DEV_SOURCE_H
#define LAB_DEV_SOURCE_H

/* Header inclusion */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/* Macros */
#define TITLE ("lab_23")
#define WIDTH (800)
#define HEIGHT (800)
#define BALL_C (5)

/* Types */
typedef enum {
    false,
    true
} bool;

/* source.c */
bool check_args(int, char *[]);
bool SDL_Init_All(struct SDL_Window **, struct SDL_Renderer **);
struct SDL_Texture *get_text_texture(struct SDL_Renderer *renderer, char *text, struct _TTF_Font *font);
void draw_text(struct SDL_Renderer *, struct SDL_Texture *);
void init_balls(struct SDL_Rect *balls, int count);
void draw_balls(struct SDL_Renderer *, struct SDL_Rect *, int, struct SDL_Texture *);
bool is_ball_hit(struct SDL_Rect *, int, int);

#endif //LAB_DEV_SOURCE_H
