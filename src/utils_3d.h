#ifndef UTILS_3D_H
#define UTILS_3D_H

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL_render.h>

#define PI		3.14159265358979323846

typedef struct Vector
{
    float x;
    float y;
    float z;
} Vector;

float vec_dot_product(Vector v1, Vector v2);
void vec_cross_product(Vector v1, Vector v2, Vector *result);
void vec_sub(Vector v1, Vector v2, Vector *result);
void vec_set_unit(Vector *v);
float get_length(Vector v);

float to_radians(float degrees);
void swap(int *x, int *y);
float cos_deg(float degrees);
float sin_deg(float degrees);

#endif