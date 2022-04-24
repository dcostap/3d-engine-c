#include "math.h"

float random_float(const float min, const float max)
{
    if (max == min)
        return min;
    else if (min < max)
        return (max - min) * ((float)rand() / RAND_MAX) + min;

    return 0;
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

#pragma region VECTORS

void rotate_vector(Vec3* vector, float rotation_x, float rotation_y, float rotation_z)
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

float vec3_dot_product(Vec3 v1, Vec3 v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

float vec3_get_length(Vec3 v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

void vec3_set_unit(Vec3 *v)
{
    float length = vec3_get_length(*v);

    if (length != 0.0f) {
        v->x = v->x / length;
        v->y = v->y / length;
        v->z = v->z / length;
    }
}

void vec3_copy_to(Vec3 src, Vec3 *dest) {
    dest->x = src.x;
    dest->y = src.y;
    dest->z = src.z;
}

void vec3_set(Vec3 *dest, float x, float y, float z) {
    dest->x = x;
    dest->y = y;
    dest->z = z;
}

void vec3_add(Vec3 *dest, Vec3 a) {
    dest->x += a.x;
    dest->y += a.y;
    dest->z += a.z;
}

void vec3_sub(Vec3 *dest, Vec3 a) {
    dest->x -= a.x;
    dest->y -= a.y;
    dest->z -= a.z;
}

void vec3_cross(Vec3 *dest, Vec3 a, Vec3 b) {
    dest->x = a.y * b.z - b.y * a.z;
    dest->y = a.z * b.x - b.z * a.x;
    dest->z = a.x * b.y - b.x * a.y;
}

#pragma endregion

#pragma region MATRICES

void print_matrix(Mat4 mtx) {
    for (int i = 0; i < 4; i++) {
        printf("[");
        for (int j = 0; j < 4; j++) {
            printf("%f, ", mtx[j + 4 * i]);
        }
        printf("]\n");
    }
    printf("\n");
}

void set_projection_matrix(Mat4 *mtx, float fov, float near, float far, int width, int height) {
    mat4_set_identity(mtx);

    float aspect_ratio = (float) width / (float) height;

    float y_scale = (1.0f / tanf(to_radians(fov / 2.0f))) * aspect_ratio;
    float x_scale = y_scale / aspect_ratio;
    float frustrum_length = far - near;

    //    [column + row * 4]
    (*mtx)[0 + 0 * 4] = x_scale;
    (*mtx)[1 + 1 * 4] = y_scale;
    (*mtx)[2 + 2 * 4] = -(far + near) / frustrum_length;
    (*mtx)[3 + 2 * 4] = -1.0f;
    (*mtx)[2 + 3 * 4] = -(2 * far * near) / frustrum_length;
    (*mtx)[3 + 3 * 4] = 0.0f;
}

void mat4_scale_by_vec3(Mat4* mtx, Vec3 vec) {
    //    [column + row * 4]
    (*mtx)[0 + 4 * 0] *= vec.x;
    (*mtx)[1 + 4 * 0] *= vec.x;
    (*mtx)[2 + 4 * 0] *= vec.x;
    (*mtx)[0 + 4 * 1] *= vec.y;
    (*mtx)[1 + 4 * 1] *= vec.y;
    (*mtx)[2 + 4 * 1] *= vec.y;
    (*mtx)[0 + 4 * 2] *= vec.z;
    (*mtx)[1 + 4 * 2] *= vec.z;
    (*mtx)[2 + 4 * 2] *= vec.z;
}

void mat4_rotate_around_vec3(Mat4* mtx, struct Vec3* vec) {
    if (vec->x != 0.0f) {
        mat4_rotate_around_axis(mtx, X_AXIS, vec->x);
    }
    if (vec->y != 0.0f) {
        mat4_rotate_around_axis(mtx, Y_AXIS, vec->y);
    }
    if (vec->z != 0.0f) {
        mat4_rotate_around_axis(mtx, Z_AXIS, vec->z);
    }
}

void mat4_set_identity(Mat4* mtx) {
    (*mtx)[0 + 4 * 0] = 1.0f;
    (*mtx)[1 + 4 * 0] = 0.0f;
    (*mtx)[2 + 4 * 0] = 0.0f;
    (*mtx)[3 + 4 * 0] = 0.0f;
    (*mtx)[0 + 4 * 1] = 0.0f;
    (*mtx)[1 + 4 * 1] = 1.0f;
    (*mtx)[2 + 4 * 1] = 0.0f;
    (*mtx)[3 + 4 * 1] = 0.0f;
    (*mtx)[0 + 4 * 2] = 0.0f;
    (*mtx)[1 + 4 * 2] = 0.0f;
    (*mtx)[2 + 4 * 2] = 1.0f;
    (*mtx)[3 + 4 * 2] = 0.0f;
    (*mtx)[0 + 4 * 3] = 0.0f;
    (*mtx)[1 + 4 * 3] = 0.0f;
    (*mtx)[2 + 4 * 3] = 0.0f;
    (*mtx)[3 + 4 * 3] = 1.0f;
}

void mat4_copy_to(const Mat4* src, Mat4* dst) {
    (*dst)[0 + 4 * 0] = (*src)[0 + 4 * 0];
    (*dst)[1 + 4 * 0] = (*src)[1 + 4 * 0];
    (*dst)[2 + 4 * 0] = (*src)[2 + 4 * 0];
    (*dst)[3 + 4 * 0] = (*src)[3 + 4 * 0];
    (*dst)[0 + 4 * 1] = (*src)[0 + 4 * 1];
    (*dst)[1 + 4 * 1] = (*src)[1 + 4 * 1];
    (*dst)[2 + 4 * 1] = (*src)[2 + 4 * 1];
    (*dst)[3 + 4 * 1] = (*src)[3 + 4 * 1];
    (*dst)[0 + 4 * 2] = (*src)[0 + 4 * 2];
    (*dst)[1 + 4 * 2] = (*src)[1 + 4 * 2];
    (*dst)[2 + 4 * 2] = (*src)[2 + 4 * 2];
    (*dst)[3 + 4 * 2] = (*src)[3 + 4 * 2];
    (*dst)[0 + 4 * 3] = (*src)[0 + 4 * 3];
    (*dst)[1 + 4 * 3] = (*src)[1 + 4 * 3];
    (*dst)[2 + 4 * 3] = (*src)[2 + 4 * 3];
    (*dst)[3 + 4 * 3] = (*src)[3 + 4 * 3];
}

/**
 * Rotates a mat4f matrix about a given axis
 * by a set angle in degrees.
 */
void mat4_rotate_around_axis(Mat4* mtx, enum RotationAxis axis, float angle_degrees) {
    struct Vec3 rot;

    switch (axis) {
    case X_AXIS:
        rot.x = 1.0f;
        rot.y = 0.0f;
        rot.z = 0.0f;
        break;
    case Y_AXIS:
        rot.x = 0.0f;
        rot.y = 1.0f;
        rot.z = 0.0f;
        break;
    case Z_AXIS:
        rot.x = 0.0f;
        rot.y = 0.0f;
        rot.z = 1.0f;
        break;
    default:
        printf("Bad axis number\n");
        break;
    }

    Mat4 rMat;
    mat4_set_to_rotation_matrix(&rMat, rot, angle_degrees);
    mat4_mul(mtx, &rMat);
}

void mat4_mul(Mat4* m1, const Mat4* m2) {
    float tmp[4];
    for (int j = 0; j < 4; j++) {
        tmp[0] = (*m1)[j];
        tmp[1] = (*m1)[4 + j];
        tmp[2] = (*m1)[8 + j];
        tmp[3] = (*m1)[12 + j];
        for (int i = 0; i < 4; i++) {
            (*m1)[4 * i + j] = (*m2)[4 * i] * tmp[0] + (*m2)[4 * i + 1] * tmp[1] +
                (*m2)[4 * i + 2] * tmp[2] + (*m2)[4 * i + 3] * tmp[3];
        }
    }
}

/**
 * Creates a rotation matrix to multiply the primary matrix by.
 *
 * Rotation happens around Vec3 axis.
 *
 * Matrix has form-
 *
 * | (1-c)z^2+c (1-c)zy-sx (1-c)xz-sy 0 |
 * | (1-c)zy-sx (1-c)y^2+c (1-c)xy-sz 0 |
 * | (1-c)xz-sy (1-c)xy-sz (1-c)x^2+c 0 |
 * |      0          0          0     1 |
 */
void mat4_set_to_rotation_matrix(Mat4* mtx, Vec3 axis, float angle_degrees) {
    float oneMinusCos;

    float s = sin_deg(angle_degrees);
    float c = cos_deg(angle_degrees);

    oneMinusCos = 1.0 - c;

    (*mtx)[0 + 4 * 0] = oneMinusCos * axis.z * axis.z + c;
    (*mtx)[1 + 4 * 0] = oneMinusCos * axis.z * axis.y + s * axis.x;
    (*mtx)[2 + 4 * 0] = oneMinusCos * axis.z * axis.x - s * axis.y;
    (*mtx)[3 + 4 * 0] = 0.0f;
    (*mtx)[0 + 4 * 1] = oneMinusCos * axis.z * axis.y - s * axis.x;
    (*mtx)[1 + 4 * 1] = oneMinusCos * axis.y * axis.y + c;
    (*mtx)[2 + 4 * 1] = oneMinusCos * axis.y * axis.x + s * axis.z;
    (*mtx)[3 + 4 * 1] = 0.0f;
    (*mtx)[0 + 4 * 2] = oneMinusCos * axis.z * axis.x + s * axis.y;
    (*mtx)[1 + 4 * 2] = oneMinusCos * axis.y * axis.x - s * axis.z;
    (*mtx)[2 + 4 * 2] = oneMinusCos * axis.x * axis.x + c;
    (*mtx)[3 + 4 * 2] = 0.0f;
    (*mtx)[0 + 4 * 3] = 0.0f;
    (*mtx)[1 + 4 * 3] = 0.0f;
    (*mtx)[2 + 4 * 3] = 0.0f;
    (*mtx)[3 + 4 * 3] = 1.0f;
}

void mat4_translate_by_vec3(Mat4* mtx, Vec3 vec) {
    (*mtx)[0 + 4 * 3] += vec.x;
    (*mtx)[1 + 4 * 3] += vec.y;
    (*mtx)[2 + 4 * 3] += vec.z;
}

void vec3_transform_by_mat4(Vec3 *vec, Mat4 *mtx)
{
    float tmp[4];
    for ( int i = 0; i < 4; ++i )
       tmp[i] = vec->x * (*mtx)[i + 4 * 0] + vec->y * (*mtx)[i + 4 * 1] + vec->z + (*mtx)[i + 4 * 2];

    vec->x = tmp[0] / tmp[3];
    vec->y = tmp[1] / tmp[3];
    vec->z = tmp[2] / tmp[3];
}


#pragma endregion