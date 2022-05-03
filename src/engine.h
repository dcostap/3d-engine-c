#pragma once

#define SDL_MAIN_HANDLED
#include <SDL.h>
#define GL_GLEXT_PROTOTYPES 1
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include <math.h>
#include "math.h"
#include "utils.h"
#include "graphics.h"

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
extern int target_FPS;
extern float delta;

extern int screen_width;
extern int screen_height;

int start_sdl_and_main_loop(bool (*main_loop)());
int on_window_resize_event(void *data, SDL_Event *event);
void dispose();
void exit_app();