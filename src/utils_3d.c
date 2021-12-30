#include "utils_3d.h"

void plane_to_triangles(Vector v1, Vector v2, Vector v3, Vector v4, Triangle *triangles) {

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