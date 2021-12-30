#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

typedef bool (*Main_loop)(void);

typedef struct Color
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} Color;

void close();
void draw_filled_triangle(Color color, int x1, int y1, int x2, int y2, int x3, int y3);
SDL_Window *window;
SDL_Surface *screen_surface;
SDL_Renderer *renderer;
const int TARGET_FPS;
const int SCREEN_WIDTH;
const int SCREEN_HEIGHT;