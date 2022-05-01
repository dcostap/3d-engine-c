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

    // root bone of related skeleton a.k.a. armature
    // this is only informative
    char *skeleton;

    // index of each bone (maximum of 4) that affects each vertex
    int (*bones)[4];
    int bones_size;

    float (*weights)[4];
    int weights_size;

    int *indices;
    int indices_size;
    //TODO: join all common sizes, there's redundant data

    char *texture_file;
    GLuint texture_id;
} Mesh;

typedef struct AnimSkeletonBone {
    char *name;
    Mat4 inverse_bind;

    int keyframe_size;
    float *anim_keyframe_timings;
    Mat4 *anim_keyframe_transforms;

    struct AnimSkeletonBone *parent;
} AnimSkeletonBone;

typedef struct SkeletonAnimation {
    char *name;

    AnimSkeletonBone *indexed_bones;
    int indexed_bones_size;

    // root bone of related skeleton
    AnimSkeletonBone root;
} SkeletonAnimation;

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