#pragma once

#include "engine.h"

typedef struct Mesh
{
    GLuint vao, ebo;
    float (*vertices)[3];
    int vertices_size;
    float (*normals)[3];
    int normals_size;
    float (*uvs)[2];
    int uvs_size;

    int *indices;
    int indices_size;

    char *texture_file;
    GLuint texture_id;
} Mesh;

typedef struct Entity
{
    Vec3 position;
    Vec3 rotation;
    Vec3 scale;
    Mat4 world_transform;
    Mesh *mesh;
} Entity;

void draw_mesh(Mesh *mesh);
void draw_entity(Entity *ent);
void bind_mesh_to_opengl(Mesh *mesh);
bool load_shaders();
void start_shader();
void stop_shader();

extern GLuint gl_shader_program;