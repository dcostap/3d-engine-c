#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>
#include "utils_3d.h"

typedef struct Color
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} Color;

extern SDL_Window *sdl_window;
extern SDL_Surface *screen_surface;
extern SDL_Renderer *renderer;
extern const int TARGET_FPS;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

int init_engine();
void dispose();
void draw_filled_triangle(Color, Triangle);