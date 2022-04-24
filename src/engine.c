#include "engine.h"

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;
int TARGET_FPS = 60;

int current_FPS = 0;

SDL_Window* sdl_window;
SDL_Surface* screen_surface;
SDL_Renderer* renderer;
SDL_GLContext context;

static int on_window_resize_event(void* data, SDL_Event* event) {
    if (event->type == SDL_WINDOWEVENT &&
        event->window.event == SDL_WINDOWEVENT_RESIZED) {
        SDL_Window* win = SDL_GetWindowFromID(event->window.windowID);

        SDL_GetWindowSize(win, &SCREEN_WIDTH, &SCREEN_HEIGHT);
        if (win == (SDL_Window*)data) {
            printf("<Resize Event>\n");
        }
    }
    return 0;
}

int start_sdl_and_main_loop(bool (*main_loop)(float delta))
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetSwapInterval(1); // Use Vsync

    sdl_window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    SDL_SetWindowResizable(sdl_window, true);
    SDL_AddEventWatch(on_window_resize_event, sdl_window);

    context = SDL_GL_CreateContext(sdl_window);

    if (context == NULL)
    {
        fprintf(stderr, "Failed to create GL context\n");
        SDL_DestroyWindow(sdl_window);
        SDL_Quit();
        return 1;
    }

    bool quit = false;
    Uint64 last_time = 0;
    int last_current_FPS;

    while (!quit)
    {
        double elapsed = SDL_GetTicks() - last_time;

        while ((SDL_GetTicks() - last_time) < (1000.0f / TARGET_FPS))
        {
            SDL_Delay(1);
        }

        if (elapsed < 1000.0f / TARGET_FPS)
        {
            elapsed = 1000.0f / TARGET_FPS;
        }

        current_FPS = (int)(1 / (elapsed / 1000.0f));

        if (current_FPS != last_current_FPS)
        {
            printf("FPS: %d\n", current_FPS);
            fflush(stdout);
        }
        last_current_FPS = current_FPS;

        // clamp delta if program lags too much
        if (elapsed > 1000.0f / 25)
        {
            elapsed = 1000.0f / 25;
        }

        last_time = SDL_GetTicks();

        float delta = elapsed / 1000.0f;

        quit = main_loop(delta);
    }

    dispose();

    SDL_Quit();

    return 0;
}

void dispose()
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(sdl_window);
    sdl_window = NULL;
    screen_surface = NULL;
    renderer = NULL;
}
