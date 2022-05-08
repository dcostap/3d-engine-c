#include "graphics.h"
#include "png/lodepng.h"

GLuint gl_3d_shader = 0;
GLuint gl_2d_shader = 0;

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

bool load_shaders() {
    load_shader(&gl_3d_shader, "assets/vert_3d.glsl", "assets/frag_3d.glsl");
    load_shader(&gl_2d_shader, "assets/vert_2d.glsl", "assets/frag_2d.glsl");
}

bool load_shader(GLuint *shader_program_id, char *vert_shader_file, char *frag_shader_file)
{
    size_t size;

    const char *vert_shader = read_file(vert_shader_file, &size);
    const char *frag_shader = read_file(frag_shader_file, &size);

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

    *shader_program_id = new_program;

    // cleanup
    glDetachShader(new_program, fragment_id);
    glDetachShader(new_program, vertex_id);
    glDeleteShader(fragment_id);
    glDeleteShader(vertex_id);
    glUseProgram(0);
    return true;
}

void start_shader(GLuint shader_id)
{
    glUseProgram(shader_id);
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

    GLint attrib_id = glGetAttribLocation(gl_3d_shader, attribute_name);
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

    GLint attrib_id = glGetAttribLocation(gl_3d_shader, attribute_name);
    glVertexAttribPointer(attrib_id, attribute_number, GL_INT, GL_FALSE, attribute_number * sizeof(GLint), NULL);
    glEnableVertexAttribArray(attrib_id);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void draw_entity(Entity *ent)
{
    GLuint id = glGetUniformLocation(gl_3d_shader, "local_transform");
    glUniformMatrix4fv(id, 1, GL_FALSE, ent->world_transform.mtx);

    if (ent->animation != NULL)
    {
        ent->animation->time += delta;
        if (ent->animation->time > ent->animation->data->duration)
        {
            ent->animation->time = 0.0f;
        }

        if (ent->mesh->bones != NULL && ent->mesh->weights != NULL)
        {
            reset_animation_matrices(ent->animation->data);
            calculate_animation_joint_matrices(ent->animation->time, ent->animation->data);

            for (int i = 0; i < 19; i++)
            {
                char *name;
                asprintf(&name, "joint_matrices[%d]", i);
                id = glGetUniformLocation(gl_3d_shader, name);
                glUniformMatrix4fv(id, 1, GL_FALSE, ent->animation->data->joint_transforms[i].mtx);
            }
        }
    }

    draw_mesh(ent->mesh);
}

void reset_animation_matrices(SkeletonAnimation *anim)
{
    for (int i = 0; i < anim->indexed_bones_size; i++)
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

    Quaternion final_rotation;
    quat_set_identity(&final_rotation);

    for (int i = 0; i < bone->keyframe_translation_size; i++)
    {
        float time = bone->anim_keyframe_translation_timings[i];
        if (anim_time <= time || i == bone->keyframe_translation_size - 1)
        {
            Vec3 next_translation = {0};
            vec3_set(&next_translation, bone->anim_keyframe_translations[i]);

            int previous_keyframe = i <= 0 ? i : i - 1;
            float previous_keyframe_time = bone->anim_keyframe_translation_timings[previous_keyframe];

            vec3_set(&new_translation, bone->anim_keyframe_translations[previous_keyframe]);
            float time_elapsed = time - previous_keyframe_time;
            if (time_elapsed > 0.0f)
            {
                float interpolation_needed = (anim_time - previous_keyframe_time) / time_elapsed;

                vec3_lerp(interpolation_needed, new_translation, next_translation, &new_translation);
            }
            break;
        }
    }

    for (int current_keyframe = 0; current_keyframe < bone->keyframe_rotation_size; current_keyframe++)
    {
        float time = bone->anim_keyframe_rotation_timings[current_keyframe];
        if (anim_time <= time || current_keyframe == bone->keyframe_rotation_size - 1)
        {
            Quaternion previous_rotation;
            quat_set_identity(&previous_rotation);
            Quaternion next_rotation;
            quat_set_identity(&next_rotation);
            next_rotation = bone->anim_keyframe_rotations[current_keyframe];

            int previous_keyframe = current_keyframe <= 0 ? current_keyframe : current_keyframe - 1;
            float previous_keyframe_time = bone->anim_keyframe_rotation_timings[previous_keyframe];

            if (previous_keyframe == current_keyframe)
            {
                final_rotation = bone->anim_keyframe_rotations[0];
            }
            else
            {
                final_rotation = bone->anim_keyframe_rotations[previous_keyframe];
            }

            float time_elapsed = time - previous_keyframe_time;
            if (time_elapsed > 0.0f)
            {
                float interpolation_needed = (anim_time - previous_keyframe_time) / time_elapsed;
                quat_slerp(interpolation_needed, final_rotation, next_rotation, &final_rotation);
            }
            break;
        }
    }

    Mat4 anim_pos;
    mat4_set_identity(&anim_pos);
    mat4_translate_by_vec3(&anim_pos, new_translation);

    Mat4 anim_rot;
    mat4_set_quaternion(final_rotation, &anim_rot);

    Mat4 local_transform;
    mat4_set_identity(&local_transform);
    mat4_mul(&local_transform, &anim_pos);
    mat4_mul(&local_transform, &anim_rot);

    Mat4 final_transform;
    final_transform = parent_transform;
    mat4_mul(&final_transform, &local_transform);

    for (int i = 0; i < bone->children_size; i++)
    {
        process_bone(anim_time, anim->indexed_bones[bone->children_indices[i]], final_transform, anim);
    }

    mat4_mul(&final_transform, &bone->inverse_bind);

    anim->joint_transforms[bone->index] = final_transform;
}