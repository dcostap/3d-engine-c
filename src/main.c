#include "engine.h"

bool main_loop();
int main(void);

int main(void)
{
    return init_engine(main_loop);
}

bool main_loop()
{
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

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // set_pixel(10, 10, 255, 255, 255);

    Color color;

    color.r = 50;
    color.g = 50;
    color.b = 255;

    draw_filled_triangle(color, 0, 0, 30, 40, 100, 20);

    SDL_RenderPresent(renderer);

    return false;
}