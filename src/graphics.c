#include "graphics.h"
#include "png/lodepng.h"
#include "anims/ArmatureAction.h"

GLuint gl_shader_program = 0;
#define uint unsigned int
#define uchar unsigned char

void store_int_data_in_vbo(void *data, GLsizeiptr data_size, int attribute_number, char *attribute_name);
void store_float_data_in_vbo(void *data, GLsizeiptr data_size, int attribute_number, char *attribute_name);
void calculate_animation_joint_matrices(float anim_time, SkeletonAnimation *anim);
void process_bone(float anim_time, AnimSkeletonBone *bone, Mat4 parent_transform, SkeletonAnimation *anim);
void reset_animation_matrices(SkeletonAnimation *anim);

uchar *load_png(const char *filename, uint *width, uint *height)
{
    uchar *image;
    uint error = lodepng_decode_file(&image, width, height, filename, LCT_RGBA, 8);

    if (image == NULL)
    {
        printf("Loading image %s failed\n", filename);
        exit_app();
    }
    else if (error != 0)
    {
        printf("error %s\n", lodepng_error_text(error));
        exit_app();
    }

    return image;
}

bool load_shaders()
{
    size_t size;

    const char *vert_shader = read_file("assets/vert.glsl", &size);
    const char *frag_shader = read_file("assets/frag.glsl", &size);

    GLint status;
    char err_buf[512];

    // vertex
    GLuint vertex_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_id, 1, &vert_shader, NULL);
    glCompileShader(vertex_id);
    glGetShaderiv(vertex_id, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        glGetShaderInfoLog(vertex_id, sizeof(err_buf), NULL, err_buf);
        err_buf[sizeof(err_buf) - 1] = '\0';
        fprintf(stderr, "Vertex shader compilation failed: %s\n", err_buf);
        return false;
    }

    // fragment
    GLuint fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_id, 1, &frag_shader, NULL);
    glCompileShader(fragment_id);
    glGetShaderiv(fragment_id, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        glGetShaderInfoLog(fragment_id, sizeof(err_buf), NULL, err_buf);
        err_buf[sizeof(err_buf) - 1] = '\0';
        fprintf(stderr, "Fragment shader compilation failed: %s\n", err_buf);
        return false;
    }

    GLuint new_program = glCreateProgram();
    glAttachShader(new_program, vertex_id);
    glAttachShader(new_program, fragment_id);

    glBindFragDataLocation(new_program, 0, "out_color");

    glLinkProgram(new_program);
    glUseProgram(new_program);

    glGetProgramiv(new_program, GL_LINK_STATUS, &status);
    if (status != GL_TRUE)
    {
        glGetProgramInfoLog(new_program, sizeof(err_buf), NULL, err_buf);
        err_buf[sizeof(err_buf) - 1] = '\0';
        fprintf(stderr, "Program (shader) linking failed: %s\n", err_buf);
        return false;
    }

    gl_shader_program = new_program;

    // cleanup
    glDetachShader(new_program, fragment_id);
    glDetachShader(new_program, vertex_id);
    glDeleteShader(fragment_id);
    glDeleteShader(vertex_id);
    glUseProgram(0);
    return true;
}

void start_shader()
{
    glUseProgram(gl_shader_program);
}

void stop_shader()
{
    glUseProgram(0);
}

void bind_mesh_to_opengl(Mesh *mesh)
{
    glGenVertexArrays(1, &mesh->vao);
    glBindVertexArray(mesh->vao);

    // Bind indices
    glGenBuffers(1, &mesh->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mesh->indices[0]) * mesh->indices_size, mesh->indices, GL_STATIC_DRAW);

    // Bind attributes
    store_float_data_in_vbo(mesh->vertices, sizeof(mesh->vertices[0]) * mesh->vertices_size, 3, "in_position");
    store_float_data_in_vbo(mesh->normals, sizeof(mesh->normals[0]) * mesh->normals_size, 3, "in_normal");

    if (mesh->uvs != NULL)
    {
        store_float_data_in_vbo(mesh->uvs, sizeof(mesh->uvs[0]) * mesh->uvs_size, 2, "in_uv");
    }

    if (mesh->weights != NULL)
    {
        store_float_data_in_vbo(mesh->weights, sizeof(mesh->weights[0]) * mesh->weights_size, 4, "in_weights");
    }

    if (mesh->bones != NULL)
    {
        store_int_data_in_vbo(mesh->bones, sizeof(mesh->bones[0]) * mesh->bones_size, 4, "in_joints");
    }

    glBindVertexArray(0);

    if (mesh->texture_file != NULL)
    {
        glGenTextures(1, &mesh->texture_id);
        glBindTexture(GL_TEXTURE_2D, mesh->texture_id);

        //GL_NEAREST = no smoothing
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        uint width, height;
        uchar *texture = load_png(mesh->texture_file, &width, &height);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);

        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void store_float_data_in_vbo(void *data, GLsizeiptr data_size, int attribute_number, char *attribute_name)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);

    GLint attrib_id = glGetAttribLocation(gl_shader_program, attribute_name);
    glVertexAttribPointer(attrib_id, attribute_number, GL_FLOAT, GL_FALSE, attribute_number * sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(attrib_id);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void store_int_data_in_vbo(void *data, GLsizeiptr data_size, int attribute_number, char *attribute_name)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);

    GLint attrib_id = glGetAttribLocation(gl_shader_program, attribute_name);
    glVertexAttribPointer(attrib_id, attribute_number, GL_INT, GL_FALSE, attribute_number * sizeof(GLint), NULL);
    glEnableVertexAttribArray(attrib_id);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

float anim_time = 0.0f;

void draw_entity(Entity *ent)
{
    anim_time += delta;
    if (anim_time > 2.0f)
        anim_time = 0.0f;

    GLuint id = glGetUniformLocation(gl_shader_program, "local_transform");
    glUniformMatrix4fv(id, 1, GL_FALSE, ent->world_transform.mtx);

    if (ent->mesh->bones != NULL && ent->mesh->weights != NULL)
    {
        reset_animation_matrices(&ArmatureAction);
        calculate_animation_joint_matrices(anim_time, &ArmatureAction);

        for (int i = 0; i < 19; i++) {
            // Mat4 m;
            // mat4_set_identity(m.mtx);

            // if (i == 1) {
            //     Vec3 v = { anim_time, 0.0f, 0.0f};
            //     mat4_translate_by_vec3(&m, v);
            // }

// print_mat4(ArmatureAction.joint_transforms[i]);

            char *name;
            asprintf(&name, "joint_matrices[%d]", i);
            id = glGetUniformLocation(gl_shader_program, name);
            glUniformMatrix4fv(id, 1, GL_FALSE, ArmatureAction.joint_transforms[i].mtx);
        }


// float data[19 * 16];
//         for (int i = 0; i < 19; i++) {
//             // Mat4 m;
//             // mat4_set_identity(m.mtx);

//             // if (i == 1) {
//             //     Vec3 v = { anim_time, 0.0f, 0.0f};
//             //     mat4_translate_by_vec3(&m, v);
//             // }

//             // char *name;
//             // asprintf(&name, "joint_matrices[%d]", i);

//             for (int j = 0; j < 16; j++) {
//                 data[j + i * 16] = ArmatureAction.joint_transforms[i].mtx[j];
//             }

//         }

//         id = glGetUniformLocation(gl_shader_program, "joint_matrices");
//         glUniformMatrix4fv(id, 19 * 16, GL_FALSE, data);


        // for (int i = 0; i < ArmatureAction.indexed_bones_size; i ++) {
        //     for (int a = 0; a < 4; a++) {
        //         for (int b = 0; b < 4; b++) {
        //             printf("%.2f  ", ArmatureAction.joint_transforms[i].mtx[b + (a * 4)]);
        //         }
        //         printf("\n");
        //     }
        //     printf("_________\n");
        // }
    }

    draw_mesh(ent->mesh);
}

void reset_animation_matrices(SkeletonAnimation *anim)
{
    for (int i = 0; i < ArmatureAction.indexed_bones_size; i++)
    {
        mat4_set_identity(&anim->joint_transforms[i]);
    }
}

void draw_mesh(Mesh *mesh)
{
    glBindVertexArray(mesh->vao);
    if (mesh->texture_file != NULL)
    {
        glBindTexture(GL_TEXTURE_2D, mesh->texture_id);
    }

    glDrawElements(GL_TRIANGLES, mesh->indices_size, GL_UNSIGNED_INT, NULL);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void calculate_animation_joint_matrices(float anim_time, SkeletonAnimation *anim)
{
    // let's assume the root bone is the first in the array
    AnimSkeletonBone *root = anim->indexed_bones[0];
    Mat4 idt;
    mat4_set_identity(&idt);
    process_bone(anim_time, root, idt, anim);
}

void process_bone(float anim_time, AnimSkeletonBone *bone, Mat4 parent_transform, SkeletonAnimation *anim)
{
    Vec3 new_translation = {0};
    Vec3 previous_translation = {0};
    Vec3 next_translation = {0};

    float interpolation_needed = -1.0f;

    for (int i = 0; i < bone->keyframe_size; i++)
    {
        float time = bone->anim_keyframe_translation_timings[i];
        if (anim_time <= time || i == bone->keyframe_size - 1)
        {
            vec3_set(&next_translation, bone->anim_keyframe_translations[i]);

            int previous_keyframe = i <= 0 ? i : i - 1;
            vec3_set(&previous_translation, bone->anim_keyframe_translations[previous_keyframe]);
            interpolation_needed = (anim_time - previous_keyframe) / (time - previous_keyframe);
            break;
        }
    }

    if (interpolation_needed < 0.0f)
    {
        printf("Fatal error %f", interpolation_needed);
        exit_app();
        return;
    }

    lerp_vectors(interpolation_needed, previous_translation, next_translation, &new_translation);

    Mat4 transf;
    mat4_set_identity(&transf);
    // mat4_translate_by_vec3(&transf, new_translation);

    mat4_mul(&transf, &parent_transform);

    for (int i = 0; i < bone->children_size; i++)
    {
        process_bone(anim_time, anim->indexed_bones[bone->children_indices[i]], transf, anim);
    }

    mat4_mul(&transf, &bone->inverse_bind);

    printf("%s\n", bone->name);

    anim->joint_transforms[bone->index] = transf;

    // memcpy(&anim->joint_transforms[bone->index], &transf, sizeof(transf));
}