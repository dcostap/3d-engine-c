#include "engine.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int TARGET_FPS = 60;

int current_FPS = 0;

SDL_Window *sdl_window;
SDL_Surface *screen_surface;
SDL_Renderer *renderer;

float *depth_buffer;

int init_engine(bool (*main_loop)(float delta))
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf(SDL_GetError());
    }
    else
    {
        sdl_window = SDL_CreateWindow(
            "SDL2 Demo",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);

        if (!sdl_window)
        {
            printf("Window could not be created!\n"
                   "SDL_Error: %s\n",
                   SDL_GetError());
        }
        else
        {
            depth_buffer = malloc(sizeof(float) * SCREEN_WIDTH * SCREEN_HEIGHT);
            screen_surface = SDL_GetWindowSurface(sdl_window);
            renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);

            bool quit = false;
            Uint64 last_time = 0;
            int last_current_FPS;

            while (!quit)
            {
                double elapsed = SDL_GetTicks64() - last_time;

                while ((SDL_GetTicks64() - last_time) < (1000.0f / TARGET_FPS))
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

                last_time = SDL_GetTicks64();

                quit = main_loop((float)(elapsed / 1000.0f));
            }
            dispose();
        }

        SDL_Quit();
    }

    return 0;
}

void dispose()
{
    SDL_DestroyWindow(sdl_window);
    sdl_window = NULL;
    screen_surface = NULL;
    renderer = NULL;
}

void set_pixel(int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_Surface *surface = screen_surface;
    Uint32 pixel = SDL_MapRGB(surface->format, r, g, b);
    Uint32 *const target_pixel = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel);
    *target_pixel = pixel;
}

void swap(int *x, int *y)
{
    int t = *x;
    *x = *y;
    *y = t;
}

void draw_hor_line(Color color, int start_x, int end_x, int y, float z)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    if (start_x < 0) start_x = 0;
    if (start_x >= SCREEN_WIDTH) start_x = SCREEN_WIDTH - 1;
    if (end_x >= SCREEN_WIDTH) end_x = SCREEN_WIDTH - 1;
    if (y < 0) y = 0;
    if (y >= SCREEN_HEIGHT) y = SCREEN_HEIGHT - 1;

    for (int x = start_x; x < end_x; x++)
    {
        int pixel_pos = (x % SCREEN_WIDTH) + y * SCREEN_WIDTH;
        if (depth_buffer[pixel_pos] == 0 || depth_buffer[pixel_pos] < z)
        {
            depth_buffer[pixel_pos] = z;
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}

void draw_filled_triangle(Color color, Triangle t)
{
    int x1 = t.trans_v1.x;
    int x2 = t.trans_v2.x;
    int x3 = t.trans_v3.x;

    int y1 = t.trans_v1.y;
    int y2 = t.trans_v2.y;
    int y3 = t.trans_v3.y;

    float z_avg = (t.trans_v1.z + t.trans_v2.z + t.trans_v3.z) / 3;

    int t1x, t2x, y, minx, maxx, t1xp, t2xp;
    bool changed1 = false;
    bool changed2 = false;
    int signx1, signx2, dx1, dy1, dx2, dy2;
    int e1, e2;
    // Sort vertices
    if (y1 > y2)
    {
        swap(&y1, &y2);
        swap(&x1, &x2);
    }
    if (y1 > y3)
    {
        swap(&y1, &y3);
        swap(&x1, &x3);
    }
    if (y2 > y3)
    {
        swap(&y2, &y3);
        swap(&x2, &x3);
    }

    t1x = t2x = x1;
    y = y1; // Starting points
    dx1 = (int)(x2 - x1);
    if (dx1 < 0)
    {
        dx1 = -dx1;
        signx1 = -1;
    }
    else
        signx1 = 1;
    dy1 = (int)(y2 - y1);

    dx2 = (int)(x3 - x1);
    if (dx2 < 0)
    {
        dx2 = -dx2;
        signx2 = -1;
    }
    else
        signx2 = 1;
    dy2 = (int)(y3 - y1);

    if (dy1 > dx1)
    {
        swap(&dx1, &dy1);
        changed1 = true;
    }
    if (dy2 > dx2)
    {
        swap(&dy2, &dx2);
        changed2 = true;
    }

    e2 = (int)(dx2 >> 1);
    // Flat top, just process the second half
    if (y1 == y2)
        goto next;
    e1 = (int)(dx1 >> 1);

    for (int i = 0; i < dx1;)
    {
        t1xp = 0;
        t2xp = 0;
        if (t1x < t2x)
        {
            minx = t1x;
            maxx = t2x;
        }
        else
        {
            minx = t2x;
            maxx = t1x;
        }
        // process first line until y value is about to change
        while (i < dx1)
        {
            i++;
            e1 += dy1;
            while (e1 >= dx1)
            {
                e1 -= dx1;
                if (changed1)
                    t1xp = signx1; // t1x += signx1;
                else
                    goto next1;
            }
            if (changed1)
                break;
            else
                t1x += signx1;
        }
        // Move line
    next1:
        // process second line until y value is about to change
        while (1)
        {
            e2 += dy2;
            while (e2 >= dx2)
            {
                e2 -= dx2;
                if (changed2)
                    t2xp = signx2; // t2x += signx2;
                else
                    goto next2;
            }
            if (changed2)
                break;
            else
                t2x += signx2;
        }
    next2:
        if (minx > t1x)
            minx = t1x;
        if (minx > t2x)
            minx = t2x;
        if (maxx < t1x)
            maxx = t1x;
        if (maxx < t2x)
            maxx = t2x;
        draw_hor_line(color, minx, maxx, y, z_avg); // Draw line from min to max points found on the y
                                                    // Now increase y
        if (!changed1)
            t1x += signx1;
        t1x += t1xp;
        if (!changed2)
            t2x += signx2;
        t2x += t2xp;
        y += 1;
        if (y == y2)
            break;
    }
next:
    // Second half
    dx1 = (int)(x3 - x2);
    if (dx1 < 0)
    {
        dx1 = -dx1;
        signx1 = -1;
    }
    else
        signx1 = 1;
    dy1 = (int)(y3 - y2);
    t1x = x2;

    if (dy1 > dx1)
    {
        swap(&dy1, &dx1);
        changed1 = true;
    }
    else
        changed1 = false;

    e1 = (int)(dx1 >> 1);

    for (int i = 0; i <= dx1; i++)
    {
        t1xp = 0;
        t2xp = 0;
        if (t1x < t2x)
        {
            minx = t1x;
            maxx = t2x;
        }
        else
        {
            minx = t2x;
            maxx = t1x;
        }
        // process first line until y value is about to change
        while (i < dx1)
        {
            e1 += dy1;
            while (e1 >= dx1)
            {
                e1 -= dx1;
                if (changed1)
                {
                    t1xp = signx1;
                    break;
                } // t1x += signx1;
                else
                    goto next3;
            }
            if (changed1)
                break;
            else
                t1x += signx1;
            if (i < dx1)
                i++;
        }
    next3:
        // process second line until y value is about to change
        while (t2x != x3)
        {
            e2 += dy2;
            while (e2 >= dx2)
            {
                e2 -= dx2;
                if (changed2)
                    t2xp = signx2;
                else
                    goto next4;
            }
            if (changed2)
                break;
            else
                t2x += signx2;
        }
    next4:

        if (minx > t1x)
            minx = t1x;
        if (minx > t2x)
            minx = t2x;
        if (maxx < t1x)
            maxx = t1x;
        if (maxx < t2x)
            maxx = t2x;
        draw_hor_line(color, minx, maxx, y, z_avg);
        if (!changed1)
            t1x += signx1;
        t1x += t1xp;
        if (!changed2)
            t2x += signx2;
        t2x += t2xp;
        y += 1;
        if (y > y3)
            return;
    }
}