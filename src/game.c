#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int arc, char ** argv) {

    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        printf(SDL_GetError());
    } else {

        SDL_CreateWindow(
            "SDL2 Demo",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
        );

        SDL_Delay(2000);
    }

    return 0;
}