#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

const SDL_Color COLOR_TRANSPARENT   = {0};
const SDL_Color COLOR_BLACK         = {0, 0, 0, 255};
const SDL_Color COLOR_WHITE         = {255, 255, 255, 255};
const SDL_Color COLOR_GRAY          = {100, 100, 100, 255};
const SDL_Color COLOR_DARK_GRAY     = {30, 30, 30, 255};
const SDL_Color COLOR_LIGHT_GRAY    = {200, 200, 200, 255};
const SDL_Color COLOR_RED           = {255, 0, 0, 255};
const SDL_Color COLOR_GREEN         = {0, 255, 0, 255};
const SDL_Color COLOR_BLUE          = {0, 0, 255, 255};
const SDL_Color COLOR_YELLOW        = {255, 255, 0, 255};
const SDL_Color COLOR_ORANGE        = {255, 133, 0, 255};
const SDL_Color COLOR_PINK          = {255, 0, 206, 255};
const SDL_Color COLOR_VIOLET        = {145, 0, 255, 255};

void Utils_setBackgroundColor(SDL_Renderer *renderer, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Renderer *renderer;

int main(int arc, char **argv)
{
    printf("Waddup\n");
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf(SDL_GetError());
    }
    else
    {

        SDL_Window *window = SDL_CreateWindow(
            "SDL2 Demo",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);

        if (!window)
        {
            printf(stderr, "Window could not be created!\n"
                           "SDL_Error: %s\n",
                   SDL_GetError());
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (!renderer)
            {
                printf(stderr, "Renderer could not be created!\n"
                               "SDL_Error: %s\n",
                       SDL_GetError());
            }
            else
            {
                main_loop();
                SDL_DestroyRenderer(renderer);
            }

            SDL_DestroyWindow(window);
        }

        SDL_Quit();
    }

    return 0;
}

void main_loop()
{
    bool quit = false;

    while (!quit)
    {
        SDL_Event e;

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
                break;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                }
            }
        }

        // Set background color
        Utils_setBackgroundColor(renderer, COLOR_DARK_GRAY);

        // Update screen
        SDL_RenderPresent(renderer);
    }
}