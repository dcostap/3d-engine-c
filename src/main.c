#include "main.h"
#include "input.h"
#include "models/geo_f_mut00_005.h"
#include "anims/walk_final.h"

Camera camera;

void camera_update_transform(Camera *camera);
void entity_update_transform(Entity *ent);
void check_gl_errors(char *context);
void draw();

Entity ent1 = {
    .position = {0.0f, 0.0f, 0.0f},
    .rotation = {0.0f, 0.0f, 0.0f},
    .scale = {1.0f, 1.0f, 1.0f},
    .animation = &(EntityAnimation){
        .data = &walk_final
    }
};

Entity ent2 = {
    .position = {20.0f, 0.0f, 0.0f},
    .rotation = {0.0f, 0.0f, 0.0f},
    .scale = {1.0f, 1.0f, 1.0f},
};

int main(int argc, char *argv[])
{
    return start_sdl_and_main_loop(main_loop);
}

static bool is_first_loop = true;

float mouse_mov_x = 0.0f;
float mouse_mov_y = 0.0f;

bool main_loop()
{
    if (is_first_loop)
    {
        is_first_loop = false;

        if (!load_shaders())
        {
            return true;
        }

        ent1.mesh = &geo_f_mut00_005;
        // ent2.mesh = &geo_untitled;

        bind_mesh_to_opengl(&geo_f_mut00_005);
        // bind_mesh_to_opengl(&geo_untitled);

        camera.position.z = 15.f;

        // SDL_SetWindowGrab(sdl_window, true);
        // SDL_ShowCursor(SDL_ENABLE);
        SDL_SetRelativeMouseMode(true);
    }

    reset_key_inputs();

    mouse_mov_x = 0.0f;
    mouse_mov_y = 0.0f;

    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        update_key_inputs(e);

        if (e.type == SDL_MOUSEMOTION) {
            mouse_mov_x = e.motion.xrel;
            mouse_mov_y = e.motion.yrel;
        }
    }

    if (is_there_event(SDL_QUIT))
    {
        exit_app();
        return 0;
    }

    float cam_speed = 20.0f;
    float cam_rot_speed = 50.0f;

    if (is_key_pressed(SDLK_ESCAPE))
        return true;

    if (is_key_pressed(SDLK_w))
    {
        camera.position.z -= cos_deg(camera.rotation.y) * cam_speed * delta;
        camera.position.x += sin_deg(camera.rotation.y) * cam_speed * delta;
    }
    if (is_key_pressed(SDLK_s))
    {
        camera.position.z += cos_deg(camera.rotation.y) * cam_speed * delta;
        camera.position.x -= sin_deg(camera.rotation.y) * cam_speed * delta;
    }
    if (is_key_pressed(SDLK_a))
    {
        camera.position.z -= sin_deg(camera.rotation.y) * cam_speed * delta;
        camera.position.x -= cos_deg(camera.rotation.y) * cam_speed * delta;
    }
    if (is_key_pressed(SDLK_d))
    {
        camera.position.z += sin_deg(camera.rotation.y) * cam_speed * delta;
        camera.position.x += cos_deg(camera.rotation.y) * cam_speed * delta;
    }
    if (is_key_pressed(SDLK_q))
        camera.position.y += cam_speed * delta;
    if (is_key_pressed(SDLK_e))
        camera.position.y -= cam_speed * delta;

    if (is_key_pressed(SDLK_KP_5))
        camera.rotation.x += cam_rot_speed * delta;
    if (is_key_pressed(SDLK_KP_8))
        camera.rotation.x -= cam_rot_speed * delta;
    if (is_key_pressed(SDLK_KP_4))
        camera.rotation.y -= cam_rot_speed * delta;
    if (is_key_pressed(SDLK_KP_6))
        camera.rotation.y += cam_rot_speed * delta;
    if (is_key_pressed(SDLK_KP_7))
        camera.rotation.z += cam_rot_speed * delta;
    if (is_key_pressed(SDLK_KP_9))
        camera.rotation.z -= cam_rot_speed * delta;

    camera.rotation.y += mouse_mov_x;
    camera.rotation.x += mouse_mov_y;

    draw();

    return false;
}

void draw()
{
    glViewport(0, 0, screen_width, screen_height);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.3f, 0.2f, 0.5f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    start_shader(gl_3d_shader);

    Mat4 projection;
    set_projection_matrix(&projection, 90.0f, 0.1f, 100.0f, screen_width, screen_height);

    GLuint id = glGetUniformLocation(gl_3d_shader, "proj_transform");
    glUniformMatrix4fv(id, 1, GL_FALSE, projection.mtx);

    camera_update_transform(&camera);
    id = glGetUniformLocation(gl_3d_shader, "view_transform");
    glUniformMatrix4fv(id, 1, GL_FALSE, camera.transform.mtx);

    ent2.rotation.y += 2.0f;
    entity_update_transform(&ent1);
    // entity_update_transform(&ent2);

    draw_entity(&ent1);
    // draw_entity(&ent2);

    stop_shader();

    SDL_GL_SwapWindow(sdl_window);
}

void camera_update_transform(Camera *camera)
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

    mat4_set_identity(&camera->transform);
    mat4_mul(&camera->transform, &rot);
    mat4_mul(&camera->transform, &trans);
}

void entity_update_transform(Entity *ent)
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

void check_gl_errors(char *context)
{
    GLenum error = glGetError();
    if (GL_NO_ERROR != error)
    {
        printf("GL Error %x encountered in %s.\n", error, context);
        exit_app();
    }
}
