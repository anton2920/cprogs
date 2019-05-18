#ifndef LAB_DEV_SOURCE_H
#define LAB_DEV_SOURCE_H

/* Header inclusion */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <time.h>
#include <math.h>

/* Macros */
#define TITLE ("lab_23")
#define WIDTH (800)
#define HEIGHT (800)
#define BALL_C (10)
#define RND_COST (10)
#define RED_COEFF (2)
#define DELAY (30)
#define TEXTURE_SIZE (40)
#define MINES_TOTAL (14)
#define LIFES_TOTAL (3)

#define CLION (1)

#if (CLION == 1)
#define FONT_PATH ("../font/Font.ttf")
#define MUS_PATH ("../wav/Very_bad_piece.wav")
#define SND_PATH ("../wav/snd.wav")
#define PIC_PATH ("../pictures/purepng.png")
#define BLUE_PIC_PATH ("../pictures/purepng_copy.png")
#define GRASS_PATH ("../pictures/Grass.jpg")
#define CONCRETE_PATH ("../pictures/Concrete.jpg")
#define MINE_PATH ("../pictures/mine.png")
#define TRAP_PATH ("../pictures/trap.png")
#define CHAR_PATH ("../pictures/game-sprite.phg")
#else
#define FONT_PATH ("Font.ttf")
#define MUS_PATH ("Very_bad_piece.wav")
#define SND_PATH ("snd.wav")
#define PIC_PATH ("purepng.png")
#define BLUE_PIC_PATH ("purepng_copy.png")
#define GRASS_PATH ("Grass.jpg")
#define CONCRETE_PATH ("Concrete.jpg")
#define MINE_PATH ("mine.png")
#define TRAP_PATH ("trap.png")
#define CHAR_PATH ("game-sprite.phg")
#endif

/* Types */
typedef enum {
    false,
    true
} bool;

enum texttype {
    shaded,
    solid
};

enum control_speed {
    up_speed = 10,
    down_speed = 10,
    left_speed = 10,
    right_speed = 10
};

enum directions {
    y_pos = -1,
    y_neg = 1,
    x_pos = 1,
    x_neg = -1
};

enum speed_limits {
    x_max_spd = 5,
    x_min_spd = 2,
    y_max_spd = 5,
    y_min_spd = 2
};

struct pro_balls {
    struct SDL_Rect *ball;
    enum directions x_d;
    enum directions y_d;
    int x_spd;
    int y_spd;
};

/* source.c */
bool check_args(int, char *[]);
bool SDL_Init_All(struct SDL_Window **, struct SDL_Renderer **, bool);
struct SDL_Texture *get_text_texture(struct SDL_Renderer *renderer, char *text, struct _TTF_Font *font,
                                     struct SDL_Color *, struct SDL_Color *, enum texttype);
void draw_text(struct SDL_Renderer *, struct SDL_Texture *, struct SDL_Rect *);
void init_balls(struct pro_balls *, struct SDL_Rect *, int *);
void draw_balls(struct SDL_Renderer *, struct SDL_Rect *, int, struct SDL_Texture *, struct SDL_Texture *,
                int *, struct _TTF_Font *my_font, struct SDL_Rect *);
bool is_ball_hit(struct SDL_Rect *, int, int);
void loadmusic(Mix_Music *);
void sound(struct Mix_Chunk *, char *);
bool is_ball_collapse(struct SDL_Rect *, struct SDL_Rect *);
void move_ball(struct pro_balls *);
void ball_touch_another_ball(struct pro_balls *, struct SDL_Rect *);
void balls_touch_wall(struct pro_balls *, struct SDL_Rect *);

/* Game */
void draw_field(struct SDL_Renderer *);
void spawn_mines(struct SDL_Renderer *);
void set_traps(struct SDL_Renderer *);
void print_info(int, int, struct SDL_Renderer *, struct _TTF_Font *);

#endif