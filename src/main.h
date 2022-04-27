#pragma once

#include "engine.h"

typedef struct Mesh
{
    GLuint vao, ebo;
    float (*vertices)[3];
    int vertices_size;
    float (*normals)[3];
    int normals_size;
    int *indices;
    int indices_size;
} Mesh;

typedef struct Entity
{
    Vec3 position;
    Vec3 rotation;
    Vec3 scale;
    Mat4 world_transform;
    Mesh *mesh;
} Entity;

typedef struct Camera
{
    Vec3 position;
    Vec3 rotation;
    Mat4 world_transform;
} Camera;

int main(void);
bool main_loop(float delta);