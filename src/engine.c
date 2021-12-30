#include "setup.h"

typedef struct Vector
{
    float x;
    float y;
    float z;
} Vector;

typedef struct Triangle {
    Vector v1;
    Vector v2;
    Vector v3;

    Vector trans_v1;
    Vector trans_v2;
    Vector trans_v3;

    Vector normal;
    Vector trans_normal;

    bool is_drawn;
} Triangle;

void plane_to_triangles(Vector v1, Vector v2, Vector v3, Vector v4, Triangle *triangles) {
    
}

float vec_dot_product(Vector v1, Vector v2);
void vec_cross_product(Vector v1, Vector v2, Vector *result);
void vec_sub(Vector v1, Vector v2, Vector *result);
void vec_set_unit(Vector *v);
float get_length(Vector v);

float vec_dot_product(Vector v1, Vector v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

void vec_cross_product(Vector v1, Vector v2, Vector *result)
{
    result->x = v1.y * v2.z - v1.z * v2.y;
    result->y = v1.z * v2.x - v1.x * v2.z;
    result->z = v1.x * v2.y - v1.y * v2.x;
}

void vec_sub(Vector v1, Vector v2, Vector *result)
{
    result->x = v1.x - v2.x;
    result->y = v1.y - v2.y;
    result->z = v1.z - v2.z;
}

float get_length(Vector v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

void vec_set_unit(Vector *v)
{
    float length = get_length(*v);
    v->x = v->x / length;
    v->y = v->y / length;
    v->z = v->z / length;
}

bool loop()
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

int main(int arc, char **argv)
{
    return start(loop);
}