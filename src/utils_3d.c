#include "utils_3d.h"

void swap(int *x, int *y)
{
    int t = *x;
    *x = *y;
    *y = t;
}

float to_radians(float degrees)
{
    return degrees * PI / 180.0f;
}

float cos_deg(float degrees)
{
    return cosf(to_radians(degrees));
}

float sin_deg(float degrees)
{
    return sinf(to_radians(degrees));
}

void rotate_vector(Vector *vector, float rotation_x, float rotation_y, float rotation_z)
{
    float cosa = cos_deg(rotation_z);
    float sina = sin_deg(rotation_z);

    float cosb = cos_deg(rotation_y);
    float sinb = sin_deg(rotation_y);

    float cosc = cos_deg(rotation_x);
    float sinc = sin_deg(rotation_x);

    float Axx = cosa * cosb;
    float Axy = cosa * sinb * sinc - sina * cosc;
    float Axz = cosa * sinb * cosc + sina * sinc;

    float Ayx = sina * cosb;
    float Ayy = sina * sinb * sinc + cosa * cosc;
    float Ayz = sina * sinb * cosc - cosa * sinc;

    float Azx = -sinb;
    float Azy = cosb * sinc;
    float Azz = cosb * cosc;

    float orig_x = vector->x;
    float orig_y = vector->y;
    float orig_z = vector->z;

    vector->x = Axx * orig_x + Axy * orig_y + Axz * orig_z;
    vector->y = Ayx * orig_x + Ayy * orig_y + Ayz * orig_z;
    vector->z = Azx * orig_x + Azy * orig_y + Azz * orig_z;
}


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