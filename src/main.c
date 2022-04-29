#include "main.h"
#include "models/geo_stall.h"
#include "models/geo_teapot.h"
#include "input.h"

Camera camera;

void camera_update_transform(Camera *camera);
void entity_update_transform(Entity *ent);
void check_gl_errors(char *context);
void draw();

Entity ent1 = {
    .position = {0.0f, 0.0f, 0.0f},
    .rotation = {0.0f, 0.0f, 0.0f},
    .scale = {1.0f, 1.0f, 1.0f},
};

Entity ent2 = {
    .position = {20.0f, 0.0f, 0.0f},
    .rotation = {0.0f, 0.0f, 0.0f},
    .scale = {1.0f, 1.0f, 1.0f},
};

int main()
{
    return start_sdl_and_main_loop(main_loop, dispose);
}

static bool is_first_loop = true;

bool main_loop(float delta)
{
    if (is_first_loop)
    {
        is_first_loop = false;

        if (!load_shaders())
        {
            return true;
        }

        ent1.mesh = &geo_stall;
        ent2.mesh = &geo_teapot;

        bind_mesh_to_opengl(&geo_stall);
        bind_mesh_to_opengl(&geo_teapot);

        camera.position.z = 15.f;
    }

    update_input();

    if (is_there_event(SDL_QUIT)) {
        exit_app();
        return;
    }

    float cam_speed = 0.15f;
    float cam_rot_speed = 1.5f;

    if (is_key_pressed(SDLK_ESCAPE))
        return true;

    if (is_key_pressed(SDLK_w))
    {
        camera.position.z -= cos_deg(camera.rotation.y);
        camera.position.x += sin_deg(camera.rotation.y);
    }
    if (is_key_pressed(SDLK_s))
    {
        camera.position.z += cos_deg(camera.rotation.y);
        camera.position.x -= sin_deg(camera.rotation.y);
    }
    if (is_key_pressed(SDLK_a))
    {
        camera.position.z -= sin_deg(camera.rotation.y);
        camera.position.x -= cos_deg(camera.rotation.y);
    }
    if (is_key_pressed(SDLK_d))
    {
        camera.position.z += sin_deg(camera.rotation.y);
        camera.position.x += cos_deg(camera.rotation.y);
    }
    if (is_key_pressed(SDLK_q))
        camera.position.y += cam_speed;
    if (is_key_pressed(SDLK_e))
        camera.position.y -= cam_speed;

    if (is_key_pressed(SDLK_KP_5))
        camera.rotation.x += cam_rot_speed;
    if (is_key_pressed(SDLK_KP_8))
        camera.rotation.x -= cam_rot_speed;
    if (is_key_pressed(SDLK_KP_4))
        camera.rotation.y -= cam_rot_speed;
    if (is_key_pressed(SDLK_KP_6))
        camera.rotation.y += cam_rot_speed;
    if (is_key_pressed(SDLK_KP_7))
        camera.rotation.z += cam_rot_speed;
    if (is_key_pressed(SDLK_KP_9))
        camera.rotation.z -= cam_rot_speed;

    draw();

    return false;
}

void draw()
{
    glViewport(0, 0, screen_width, screen_height);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.3f, 0.2f, 0.5f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    start_shader();

    Mat4 projection;
    set_projection_matrix(&projection, 90.0f, 0.1f, 100.0f, screen_width, screen_height);

    GLuint id = glGetUniformLocation(gl_shader_program, "proj_transform");
    glUniformMatrix4fv(id, 1, GL_FALSE, projection);

    camera_update_transform(&camera);
    id = glGetUniformLocation(gl_shader_program, "view_transform");
    glUniformMatrix4fv(id, 1, GL_FALSE, camera.world_transform);

    ent2.rotation.y += 2.0f;
    entity_update_transform(&ent1);
    entity_update_transform(&ent2);

    draw_entity(&ent1);
    draw_entity(&ent2);

    stop_shader();

    SDL_GL_SwapWindow(sdl_window);
}

void camera_update_transform(Camera* camera)
{
    Mat4 rot;
    mat4_set_identity(&rot);
    mat4_rotate_around_axis(&rot, X_AXIS, camera->rotation.x * -1);
    mat4_rotate_around_axis(&rot, Y_AXIS, camera->rotation.y * -1);
    mat4_rotate_around_axis(&rot, Z_AXIS, camera->rotation.z * -1);

    Mat4 trans;
    mat4_set_identity(&trans);

    vec3_scl(&camera->position, -1.f, -1.f, -1.f);
    mat4_translate_by_vec3(&trans, camera->position);
    vec3_scl(&camera->position, -1.f, -1.f, -1.f);

    mat4_set_identity(&camera->world_transform);
    mat4_mul(&camera->world_transform, &rot);
    mat4_mul(&camera->world_transform, &trans);
}

void entity_update_transform(Entity* ent)
{
    Mat4 rot;
    mat4_set_identity(&rot);
    mat4_rotate_around_axis(&rot, X_AXIS, ent->rotation.x);
    mat4_rotate_around_axis(&rot, Y_AXIS, ent->rotation.y);
    mat4_rotate_around_axis(&rot, Z_AXIS, ent->rotation.z);

    Mat4 trans;
    mat4_set_identity(&trans);
    mat4_translate_by_vec3(&trans, ent->position);

    Mat4 scl;
    mat4_set_identity(&scl);
    mat4_scale_by_vec3(&scl, ent->scale);
    mat4_mul(&ent->world_transform, &scl);

    mat4_set_identity(&ent->world_transform);
    mat4_mul(&ent->world_transform, &trans);
    mat4_mul(&ent->world_transform, &rot);
    mat4_mul(&ent->world_transform, &scl);
}

void check_gl_errors(char* context)
{
    GLenum error = glGetError();
    if (GL_NO_ERROR != error)
    {
        printf("GL Error %x encountered in %s.\n", error, context);
        exit_app();
    }
}

void dispose()
{
}
