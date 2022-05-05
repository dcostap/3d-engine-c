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

void vec3_lerp(float progress, Vec3 start, Vec3 end, Vec3 *result)
{
    result->x = start.x + (end.x - start.x) * progress;
    result->y = start.y + (end.y - start.y) * progress;
    result->z = start.z + (end.z - start.z) * progress;
}

void rotate_vector(Vec3 *vector, float rotation_x, float rotation_y, float rotation_z)
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

    if (length != 0.0f)
    {
        v->x /= length;
        v->y /= length;
        v->z /= length;
    }
}

void vec3_set(Vec3 *dest, Vec3 src)
{
    dest->x = src.x;
    dest->y = src.y;
    dest->z = src.z;
}

void vec3_scl(Vec3 *dest, float x, float y, float z)
{
    dest->x *= x;
    dest->y *= y;
    dest->z *= z;
}

void vec3_set_values(Vec3 *dest, float x, float y, float z)
{
    dest->x = x;
    dest->y = y;
    dest->z = z;
}

void vec3_add(Vec3 *dest, Vec3 a)
{
    dest->x += a.x;
    dest->y += a.y;
    dest->z += a.z;
}

void vec3_add_values(Vec3 *dest, float x_add, float y_add, float z_add)
{
    dest->x += x_add;
    dest->y += y_add;
    dest->z += z_add;
}

void print_vector(Vec3 vec)
{
    printf("[%.6f, %.6f, %.6f]\n", vec.x, vec.y, vec.z);
}

void vec3_sub(Vec3 *dest, Vec3 a)
{
    dest->x -= a.x;
    dest->y -= a.y;
    dest->z -= a.z;
}

void vec3_sub_vec_into(Vec3 a, Vec3 b, Vec3 *dest)
{
    dest->x = a.x - b.x;
    dest->y = a.y - b.y;
    dest->z = a.z - b.z;
}

void vec3_cross(Vec3 *dest, Vec3 a, Vec3 b)
{
    dest->x = a.y * b.z - b.y * a.z;
    dest->y = a.z * b.x - b.z * a.x;
    dest->z = a.x * b.y - b.x * a.y;
}

#pragma endregion

#pragma region MATRICES

void print_matrix(Mat4 mtx)
{
    for (int i = 0; i < 4; i++)
    {
        printf("[");
        for (int j = 0; j < 4; j++)
        {
            printf("%f, ", mtx.mtx[j + 4 * i]);
        }
        printf("]\n");
    }
    printf("\n");
}

void set_projection_matrix(Mat4 *mtx, float fov, float near, float far, int width, int height)
{
    mat4_set_identity(mtx);

    float aspect_ratio = (float)width / (float)height;

    float y_scale = (1.0f / tanf(to_radians(fov / 2.0f))) * aspect_ratio;
    float x_scale = y_scale / aspect_ratio;
    float frustrum_length = far - near;

    //    [column + row * 4]
    mtx->mtx[0 + 0 * 4] = x_scale;
    mtx->mtx[1 + 1 * 4] = y_scale;
    mtx->mtx[2 + 2 * 4] = -(far + near) / frustrum_length;
    mtx->mtx[3 + 2 * 4] = -1.0f;
    mtx->mtx[2 + 3 * 4] = -(2 * far * near) / frustrum_length;
    mtx->mtx[3 + 3 * 4] = 0.0f;
}

void mat4_scale_by_vec3(Mat4 *mtx, Vec3 vec)
{
    //    [column + row * 4]
    mtx->mtx[0 + 0 * 4] *= vec.x;
    mtx->mtx[0 + 1 * 4] *= vec.x;
    mtx->mtx[0 + 2 * 4] *= vec.x;
    mtx->mtx[1 + 0 * 4] *= vec.y;
    mtx->mtx[1 + 1 * 4] *= vec.y;
    mtx->mtx[1 + 2 * 4] *= vec.y;
    mtx->mtx[2 + 0 * 4] *= vec.z;
    mtx->mtx[2 + 1 * 4] *= vec.z;
    mtx->mtx[2 + 2 * 4] *= vec.z;
}

void mat4_rotate_around_vec3(Mat4 *mtx, struct Vec3 *vec)
{
    if (vec->x != 0.0f)
    {
        mat4_rotate_around_axis(mtx, X_AXIS, vec->x);
    }
    if (vec->y != 0.0f)
    {
        mat4_rotate_around_axis(mtx, Y_AXIS, vec->y);
    }
    if (vec->z != 0.0f)
    {
        mat4_rotate_around_axis(mtx, Z_AXIS, vec->z);
    }
}

void mat4_set_identity(Mat4 *mtx)
{
    mtx->mtx[0 + 0 * 4] = 1.0f;
    mtx->mtx[0 + 1 * 4] = 0.0f;
    mtx->mtx[0 + 2 * 4] = 0.0f;
    mtx->mtx[0 + 3 * 4] = 0.0f;
    mtx->mtx[1 + 0 * 4] = 0.0f;
    mtx->mtx[1 + 1 * 4] = 1.0f;
    mtx->mtx[1 + 2 * 4] = 0.0f;
    mtx->mtx[1 + 3 * 4] = 0.0f;
    mtx->mtx[2 + 0 * 4] = 0.0f;
    mtx->mtx[2 + 1 * 4] = 0.0f;
    mtx->mtx[2 + 2 * 4] = 1.0f;
    mtx->mtx[2 + 3 * 4] = 0.0f;
    mtx->mtx[3 + 0 * 4] = 0.0f;
    mtx->mtx[3 + 1 * 4] = 0.0f;
    mtx->mtx[3 + 2 * 4] = 0.0f;
    mtx->mtx[3 + 3 * 4] = 1.0f;
}

void mat4_copy_to(const Mat4 *src, Mat4 *dst)
{
    dst->mtx[0 + 0 * 4] = src->mtx[0 + 0 * 4];
    dst->mtx[0 + 1 * 4] = src->mtx[0 + 1 * 4];
    dst->mtx[0 + 2 * 4] = src->mtx[0 + 2 * 4];
    dst->mtx[0 + 3 * 4] = src->mtx[0 + 3 * 4];
    dst->mtx[1 + 0 * 4] = src->mtx[1 + 0 * 4];
    dst->mtx[1 + 1 * 4] = src->mtx[1 + 1 * 4];
    dst->mtx[1 + 2 * 4] = src->mtx[1 + 2 * 4];
    dst->mtx[1 + 3 * 4] = src->mtx[1 + 3 * 4];
    dst->mtx[2 + 0 * 4] = src->mtx[2 + 0 * 4];
    dst->mtx[2 + 1 * 4] = src->mtx[2 + 1 * 4];
    dst->mtx[2 + 2 * 4] = src->mtx[2 + 2 * 4];
    dst->mtx[2 + 3 * 4] = src->mtx[2 + 3 * 4];
    dst->mtx[3 + 0 * 4] = src->mtx[3 + 0 * 4];
    dst->mtx[3 + 1 * 4] = src->mtx[3 + 1 * 4];
    dst->mtx[3 + 2 * 4] = src->mtx[3 + 2 * 4];
    dst->mtx[3 + 3 * 4] = src->mtx[3 + 3 * 4];
}

Vec3 X_AXIS = {1.0f, 0.0f, 0.0f};
Vec3 Y_AXIS = {0.0f, 1.0f, 0.0f};
Vec3 Z_AXIS = {0.0f, 0.0f, 1.0f};

/**
 * Rotates a mat4f matrix about a given axis
 * by a set angle in degrees.
 */
void mat4_rotate_around_axis(Mat4 *mtx, Vec3 axis, float angle_degrees)
{
    Mat4 rMat;
    mat4_set_to_rotation_matrix(&rMat, axis, angle_degrees);
    mat4_mul(mtx, &rMat);
}

void mat4_mul(Mat4 *m1, const Mat4 *m2)
{
    float tmp[4];
    for (int j = 0; j < 4; j++)
    {
        tmp[0] = m1->mtx[j];
        tmp[1] = m1->mtx[4 + j];
        tmp[2] = m1->mtx[8 + j];
        tmp[3] = m1->mtx[12 + j];
        for (int i = 0; i < 4; i++)
        {
            m1->mtx[4 * i + j] = m2->mtx[4 * i] * tmp[0] + m2->mtx[4 * i + 1] * tmp[1] +
                                 m2->mtx[4 * i + 2] * tmp[2] + m2->mtx[4 * i + 3] * tmp[3];
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
void mat4_set_to_rotation_matrix(Mat4 *mtx, Vec3 axis, float angle_degrees)
{
    float oneMinusCos;

    float s = sin_deg(angle_degrees);
    float c = cos_deg(angle_degrees);

    oneMinusCos = 1.0 - c;

    mtx->mtx[0 + 0 * 4] = oneMinusCos * axis.x * axis.x + c;
    mtx->mtx[0 + 1 * 4] = oneMinusCos * axis.x * axis.y + s * axis.z;
    mtx->mtx[0 + 2 * 4] = oneMinusCos * axis.x * axis.z - s * axis.y;
    mtx->mtx[0 + 3 * 4] = 0.0f;
    mtx->mtx[1 + 0 * 4] = oneMinusCos * axis.x * axis.y - s * axis.z;
    mtx->mtx[1 + 1 * 4] = oneMinusCos * axis.y * axis.y + c;
    mtx->mtx[1 + 2 * 4] = oneMinusCos * axis.y * axis.z + s * axis.x;
    mtx->mtx[1 + 3 * 4] = 0.0f;
    mtx->mtx[2 + 0 * 4] = oneMinusCos * axis.x * axis.z + s * axis.y;
    mtx->mtx[2 + 1 * 4] = oneMinusCos * axis.y * axis.z - s * axis.x;
    mtx->mtx[2 + 2 * 4] = oneMinusCos * axis.z * axis.z + c;
    mtx->mtx[2 + 3 * 4] = 0.0f;
    mtx->mtx[3 + 0 * 4] = 0.0f;
    mtx->mtx[3 + 1 * 4] = 0.0f;
    mtx->mtx[3 + 2 * 4] = 0.0f;
    mtx->mtx[3 + 3 * 4] = 1.0f;
}

void mat4_translate_by_vec3(Mat4 *mtx, Vec3 vec)
{
    mtx->mtx[0 + 4 * 3] += vec.x;
    mtx->mtx[1 + 4 * 3] += vec.y;
    mtx->mtx[2 + 4 * 3] += vec.z;
}

void mat4_look_at(Mat4 *mtx, Vec3 position, Vec3 look_at, Vec3 up)
{
    Vec3 z_axis;
    vec3_sub_vec_into(look_at, position, &z_axis);
    vec3_set_unit(&z_axis);

    Vec3 x_axis;
    vec3_cross(&x_axis, z_axis, up);
    vec3_set_unit(&x_axis);

    Vec3 y_axis;
    vec3_cross(&y_axis, x_axis, z_axis);

    vec3_scl(&z_axis, -1.f, -1.f, -1.f);

    mtx->mtx[0 + 0 * 4] = x_axis.x;
    mtx->mtx[0 + 1 * 4] = x_axis.y;
    mtx->mtx[0 + 2 * 4] = x_axis.z;
    mtx->mtx[0 + 3 * 4] = -vec3_dot_product(x_axis, position);
    mtx->mtx[1 + 0 * 4] = y_axis.x;
    mtx->mtx[1 + 1 * 4] = y_axis.y;
    mtx->mtx[1 + 2 * 4] = y_axis.z;
    mtx->mtx[1 + 3 * 4] = -vec3_dot_product(y_axis, position);
    mtx->mtx[2 + 0 * 4] = z_axis.x;
    mtx->mtx[2 + 1 * 4] = z_axis.y;
    mtx->mtx[2 + 2 * 4] = z_axis.z;
    mtx->mtx[2 + 3 * 4] = -vec3_dot_product(z_axis, position);
    mtx->mtx[3 + 0 * 4] = 0.f;
    mtx->mtx[3 + 1 * 4] = 0.f;
    mtx->mtx[3 + 2 * 4] = 0.f;
    mtx->mtx[3 + 3 * 4] = 1.f;
}

void vec3_transform_by_mat4(Vec3 *vec, Mat4 *mtx)
{
    float tmp[4];
    for (int i = 0; i < 4; ++i)
        tmp[i] = vec->x * mtx->mtx[i + 4 * 0] + vec->y * mtx->mtx[i + 4 * 1] + vec->z + mtx->mtx[i + 4 * 2];

    vec->x = tmp[0] / tmp[3];
    vec->y = tmp[1] / tmp[3];
    vec->z = tmp[2] / tmp[3];
}

void mat4_get_translation(Mat4 *src, Vec3 *dst)
{
    dst->x = src->mtx[3];
    dst->y = src->mtx[7];
    dst->y = src->mtx[11];
}

void mat4_get_scale(Mat4 *src, Vec3 *dst)
{
    dst->x = src->mtx[3];
    dst->y = src->mtx[7];
    dst->y = src->mtx[11];
}

void mat4_transpose(Mat4 *mat)
{
    float a01 = mat->mtx[1];
    float a02 = mat->mtx[2];
    float a03 = mat->mtx[3];
    float a12 = mat->mtx[6];
    float a13 = mat->mtx[7];
    float a23 = mat->mtx[11];

    mat->mtx[1] = mat->mtx[4];
    mat->mtx[2] = mat->mtx[8];
    mat->mtx[3] = mat->mtx[12];
    mat->mtx[4] = a01;
    mat->mtx[6] = mat->mtx[9];
    mat->mtx[7] = mat->mtx[13];
    mat->mtx[8] = a02;
    mat->mtx[9] = a12;
    mat->mtx[11] = mat->mtx[14];
    mat->mtx[12] = a03;
    mat->mtx[13] = a13;
    mat->mtx[14] = a23;
}

void mat4_invert(Mat4 *mat)
{
    float a00 = mat->mtx[0];
    float a01 = mat->mtx[1];
    float a02 = mat->mtx[2];
    float a03 = mat->mtx[3];
    float a10 = mat->mtx[4];
    float a11 = mat->mtx[5];
    float a12 = mat->mtx[6];
    float a13 = mat->mtx[7];
    float a20 = mat->mtx[8];
    float a21 = mat->mtx[9];
    float a22 = mat->mtx[10];
    float a23 = mat->mtx[11];
    float a30 = mat->mtx[12];
    float a31 = mat->mtx[13];
    float a32 = mat->mtx[14];
    float a33 = mat->mtx[15];

    float b00 = a00 * a11 - a01 * a10;
    float b01 = a00 * a12 - a02 * a10;
    float b02 = a00 * a13 - a03 * a10;
    float b03 = a01 * a12 - a02 * a11;
    float b04 = a01 * a13 - a03 * a11;
    float b05 = a02 * a13 - a03 * a12;
    float b06 = a20 * a31 - a21 * a30;
    float b07 = a20 * a32 - a22 * a30;
    float b08 = a20 * a33 - a23 * a30;
    float b09 = a21 * a32 - a22 * a31;
    float b10 = a21 * a33 - a23 * a31;
    float b11 = a22 * a33 - a23 * a32;

    // Calculate the determinant
    float det =
        b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;

    if (!det)
    {
        printf("mat4_invert: Invalid matrix input?\n");
        return;
    }

    det = 1.0f / det;

    mat->mtx[0] = (a11 * b11 - a12 * b10 + a13 * b09) * det;
    mat->mtx[1] = (a02 * b10 - a01 * b11 - a03 * b09) * det;
    mat->mtx[2] = (a31 * b05 - a32 * b04 + a33 * b03) * det;
    mat->mtx[3] = (a22 * b04 - a21 * b05 - a23 * b03) * det;
    mat->mtx[4] = (a12 * b08 - a10 * b11 - a13 * b07) * det;
    mat->mtx[5] = (a00 * b11 - a02 * b08 + a03 * b07) * det;
    mat->mtx[6] = (a32 * b02 - a30 * b05 - a33 * b01) * det;
    mat->mtx[7] = (a20 * b05 - a22 * b02 + a23 * b01) * det;
    mat->mtx[8] = (a10 * b10 - a11 * b08 + a13 * b06) * det;
    mat->mtx[9] = (a01 * b08 - a00 * b10 - a03 * b06) * det;
    mat->mtx[10] = (a30 * b04 - a31 * b02 + a33 * b00) * det;
    mat->mtx[11] = (a21 * b02 - a20 * b04 - a23 * b00) * det;
    mat->mtx[12] = (a11 * b07 - a10 * b09 - a12 * b06) * det;
    mat->mtx[13] = (a00 * b09 - a01 * b07 + a02 * b06) * det;
    mat->mtx[14] = (a31 * b01 - a30 * b03 - a32 * b00) * det;
    mat->mtx[15] = (a20 * b03 - a21 * b01 + a22 * b00) * det;
}

void print_mat4(Mat4 mat)
{
    for (int a = 0; a < 4; a++)
    {
        for (int b = 0; b < 4; b++)
        {
            printf("%.2f  ", mat.mtx[b + (a * 4)]);
        }
        printf("\n");
    }
    printf("_________\n");
}

#pragma endregion

#pragma region QUATERNIONS

void mat4_set_quaternion(Quaternion q, Mat4 *mtx)
{
    float xx = q.x * q.x;
    float xy = q.x * q.y;
    float xz = q.x * q.z;
    float xw = q.x * q.w;
    float yy = q.y * q.y;
    float yz = q.y * q.z;
    float yw = q.y * q.w;
    float zz = q.z * q.z;
    float zw = q.z * q.w;

    mtx->mtx[0 + 0 * 4] = 1.0f - 2 * (yy + zz);
    mtx->mtx[0 + 1 * 4] = 2.0f * (xy - zw);
    mtx->mtx[0 + 2 * 4] = 2.0f * (xz + yw);
    mtx->mtx[0 + 3 * 4] = 0.0f;
    mtx->mtx[1 + 0 * 4] = 2.0f * (xy + zw);
    mtx->mtx[1 + 1 * 4] = 1.0f - 2 * (xx + zz);
    mtx->mtx[1 + 2 * 4] = 2.0f * (yz - xw);
    mtx->mtx[1 + 3 * 4] = 0.0f;
    mtx->mtx[2 + 0 * 4] = 2.0f * (xz - yw);
    mtx->mtx[2 + 1 * 4] = 2.0f * (yz + xw);
    mtx->mtx[2 + 2 * 4] = 1.0f - 2 * (xx + yy);
    mtx->mtx[2 + 3 * 4] = 0.0f;
    mtx->mtx[3 + 0 * 4] = 0.0f;
    mtx->mtx[3 + 1 * 4] = 0.0f;
    mtx->mtx[3 + 2 * 4] = 0.0f;
    mtx->mtx[3 + 3 * 4] = 1.0f;
}

void quat_set_identity(Quaternion *q)
{
    q->x = 0.0f;
    q->y = 0.0f;
    q->z = 0.0f;
    q->w = 1.0f;
}

void quat_slerp(float alpha, Quaternion start, Quaternion end, Quaternion *result)
{
    float d = start.x * end.x + start.y * end.y + start.z * end.z + start.w * end.w;
    float absDot = d < 0.f ? -d : d;

    float scale0 = 1.0f - alpha;
    float scale1 = alpha;

    // Check if the angle between the 2 quaternions was big enough to
    // warrant such calculations
    if ((1 - absDot) > 0.1)
    { // Get the angle between the 2 quaternions,
        // and then store the sin() of that angle
        float angle = (float) acos(absDot);
        float invSinTheta = 1.0f / sin(angle);

        // Calculate the scale for q1 and q2, according to the angle and
        // its sine value
        scale0 = ((float) sin((1.0f - alpha) * angle) * invSinTheta);
        scale1 = ((float) sin((alpha * angle)) * invSinTheta);
    }

    if (d < 0.f)
        scale1 = -scale1;

    // Calculate the x, y, z and w values for the quaternion by using a
    // special form of linear interpolation for quaternions.
    result->x = (scale0 * start.x) + (scale1 * end.x);
    result->y = (scale0 * start.y) + (scale1 * end.y);
    result->z = (scale0 * start.z) + (scale1 * end.z);
    result->w = (scale0 * start.w) + (scale1 * end.w);
}

#pragma endregion