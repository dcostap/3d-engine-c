#include "engine.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int TARGET_FPS = 60;

int current_FPS = 0;

SDL_Window *sdl_window;
SDL_Surface *screen_surface;
SDL_Renderer *renderer;
SDL_GLContext context;

float random_float(const float min, const float max)
{
    if (max == min)
        return min;
    else if (min < max)
        return (max - min) * ((float)rand() / RAND_MAX) + min;

    return 0;
}

int init_engine(bool (*main_loop)(float delta))
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetSwapInterval(1);

    sdl_window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    context = SDL_GL_CreateContext(sdl_window);

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

        // quit = main_loop((float)(elapsed / 1000.0f));

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                return true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    return true;
                }
            }
        }

        glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        glClearColor(0.3f, 0.2f, 0.5f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_POLYGON);
        glColor3f(1, 0, 0);
        glVertex3f(-0.6, -0.75, 0.5);
        glColor3f(0, 1, 0);
        glVertex3f(0.6, -0.75, 0);
        glColor3f(0, 0, 1);
        glVertex3f(0, 0.75, 0);
        glEnd();

        SDL_GL_SwapWindow(sdl_window);
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
