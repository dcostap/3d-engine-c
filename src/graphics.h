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

    // name of root bone of related skeleton a.k.a. armature
    // this is only informative
    char *skeleton;

    // index of each bone (maximum of 4) that affects each vertex
    int (*bones)[4];
    int bones_size;

    float (*weights)[4];
    int weights_size;

    int *indices;
    int indices_size;
    //TODO: join all common size fields, there's redundant data

    char *texture_file;
    GLuint texture_id;
} Mesh;

typedef struct AnimSkeletonBone {
    char *name;
    int index;

    Mat4 inverse_bind;

    Vec3 bind_position;
    Quaternion bind_rotation;
    Vec3 bind_scale;

    int keyframe_translation_size;
    float *anim_keyframe_translation_timings;
    Vec3 *anim_keyframe_translations;
    int keyframe_rotation_size;
    Quaternion *anim_keyframe_rotations;
    float *anim_keyframe_rotation_timings;
    int keyframe_scale_size;
    Vec3 *anim_keyframe_scales;
    float *anim_keyframe_scale_timings;

    int *children_indices;
    int children_size;
} AnimSkeletonBone;

typedef struct SkeletonAnimation {
    char *name;
    char *skeleton_name;

    AnimSkeletonBone **indexed_bones;
    int indexed_bones_size;
    Mat4 *joint_transforms;
    float duration;
} SkeletonAnimation;

typedef struct EntityAnimation {
    float time;
    SkeletonAnimation *data;
} EntityAnimation;

typedef struct Entity
{
    Vec3 position;
    Vec3 rotation;
    Vec3 scale;
    Mat4 world_transform;
    Mesh *mesh;
    EntityAnimation *animation;
} Entity;

void draw_mesh(Mesh *mesh);
void draw_entity(Entity *ent);
void bind_mesh_to_opengl(Mesh *mesh);
bool load_shader(GLuint *shader_program_id, char *vert_shader_file, char *frag_shader_file);
bool load_shaders();
void start_shader(GLuint shader_id);
void stop_shader();

extern GLuint gl_3d_shader;