#pragma once

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL_render.h>

#define PI		3.14159265358979323846

typedef struct Vec3
{
    float x;
    float y;
    float z;
} Vec3;

typedef float Mat4[16];

enum RotationAxis {
    X_AXIS,
    Y_AXIS,
    Z_AXIS
};

float to_radians(float degrees);
float cos_deg(float degrees);
float sin_deg(float degrees);

// Search-select function definitions
// ^\w+ \w+\(.+(?=\))\)

void rotate_vector(Vec3* vector, float rotation_x, float rotation_y, float rotation_z);
float vec3_dot_product(Vec3 v1, Vec3 v2);
float vec3_get_length(Vec3 v);
void vec3_set_unit(Vec3 *v);
void vec3_copy_to(Vec3 src, Vec3 *dest);
void vec3_set(Vec3 *dest, float x, float y, float z);
void vec3_add(Vec3 *dest, Vec3 a);
void vec3_sub(Vec3 *dest, Vec3 a);
void vec3_cross(Vec3 *dest, Vec3 a, Vec3 b);
void mat4_scale_by_vec3(Mat4* mtx, Vec3 vec);
void mat4_rotate_around_vec3(Mat4* mtx, struct Vec3* vec);
void mat4_set_identity(Mat4* mtx);
void mat4_copy_to(const Mat4* src, Mat4* dst);
void mat4_rotate_around_axis(Mat4* mtx, enum RotationAxis axis, float angle_degrees);
void mat4_mul(Mat4* mA, const Mat4* mB);
void mat4_set_to_rotation_matrix(Mat4* mtx, Vec3 axis, float angle_degrees);
void mat4_translate_by_vec3(Mat4* mtx, Vec3 vec);
void vec3_transform_by_mat4(Vec3 *vec, Mat4 *mtx);