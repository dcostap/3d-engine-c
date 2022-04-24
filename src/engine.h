#define SDL_MAIN_HANDLED
#include <SDL.h>
#define GL_GLEXT_PROTOTYPES 1
#include <SDL_opengl.h>
#include <stdio.h>
#include "math.h"

typedef struct Color
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} Color;

extern SDL_Window *sdl_window;
extern SDL_Renderer *renderer;

extern int current_FPS;
extern int TARGET_FPS;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

int start_sdl_and_main_loop();
void dispose();