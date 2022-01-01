#ifndef UTILS_3D_H
#define UTILS_3D_H

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define PI		3.14159265358979323846

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

typedef struct
{
    Triangle triangles[1000];
    int triangles_pos;
    Vector rotation;
    Vector position;
} Mesh;

void update_triangle_normal(Triangle *triangle);

float vec_dot_product(Vector v1, Vector v2);
void vec_cross_product(Vector v1, Vector v2, Vector *result);
void vec_sub(Vector v1, Vector v2, Vector *result);
void vec_set_unit(Vector *v);
float get_length(Vector v);

#endif