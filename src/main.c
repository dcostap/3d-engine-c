#include "engine.h"

bool main_loop(float delta);
int main(void);

typedef struct
{
    Triangle triangles[100];
    int triangles_pos;
    Vector rotation;
    Vector position;
} Mesh;

Mesh meshes[100] = {0};
int meshes_pos = 0;

void plane_to_triangles(float v1_x, float v1_y, float v1_z,
                        float v2_x, float v2_y, float v2_z,
                        float v3_x, float v3_y, float v3_z,
                        float v4_x, float v4_y, float v4_z,
                        Mesh *mesh)
{
    Vector v1 = {.x = v1_x, .y = v1_y, .z = v1_z};
    Vector v2 = {.x = v2_x, .y = v2_y, .z = v2_z};
    Vector v3 = {.x = v3_x, .y = v3_y, .z = v3_z};
    Vector v4 = {.x = v4_x, .y = v4_y, .z = v4_z};

    mesh->triangles[mesh->triangles_pos].v1 = v1;
    mesh->triangles[mesh->triangles_pos].v2 = v2;
    mesh->triangles[mesh->triangles_pos].v3 = v4;
    update_triangle_normal(&mesh->triangles[mesh->triangles_pos]);

    mesh->triangles_pos++;

    mesh->triangles[mesh->triangles_pos].v1 = v2;
    mesh->triangles[mesh->triangles_pos].v2 = v3;
    mesh->triangles[mesh->triangles_pos].v3 = v4;
    update_triangle_normal(&mesh->triangles[mesh->triangles_pos]);

    mesh->triangles_pos++;
}

void make_cube(float size, Mesh *mesh)
{
    mesh->triangles_pos = 0;

    // front face
    plane_to_triangles(
        0, 0, 0,
        0, size, 0,
        size, size, 0,
        size, 0, 0,
        mesh);

    // back face
    plane_to_triangles(
        0, 0, size,
        size, 0, size,
        size, size, size,
        0, size, size,
        mesh);

    // // right face
    plane_to_triangles(
        size, 0, 0,
        size, size, 0,
        size, size, size,
        size, 0, size,
        mesh);
    // // left face
    plane_to_triangles(
        0, 0, 0,
        0, 0, size,
        0, size, size,
        0, size, 0,
        mesh);

    // // top face
    plane_to_triangles(
        0, size, 0,
        0, size, size,
        size, size, size,
        size, size, 0,
        mesh);
    // // bottom face
    plane_to_triangles(
        0, 0, 0,
        size, 0, 0,
        size, 0, size,
        0, 0, size,
        mesh);
}

float fov = 90;
float z_near = 10;
float z_far = 400;

float to_radians(float degrees)
{
    return degrees * PI / 180.0f;
}

void project_vertex(Vector *vertex)
{
    // normalize world units from -1 to 1 as seen by the camera
    vertex->x /= SCREEN_WIDTH;
    vertex->y /= SCREEN_HEIGHT;
    vertex->z = (vertex->z - z_near) / (z_far - z_near);

    float orig_z = vertex->z;

    // project positions to 3D
    float f = 1 / tanf(to_radians(fov / 2.0f)); // x, y become bigger on the edges of the camera / view
    float aspect_ratio = SCREEN_HEIGHT / (float)SCREEN_WIDTH;

    vertex->x = aspect_ratio * f * vertex->x;
    vertex->y = f * vertex->y;

    // don't really understand these but the z coord on the final trans. vertex is not used for now
    float q = z_far / (z_far - z_near);
    vertex->z = vertex->z * (q - (q * z_near));

    // further away = smaller
    if (fabs(orig_z) > 0.0001) // avoid divide by 0
    {
        // printf("%.3f\n", orig_z);
        vertex->x /= orig_z;
        vertex->y /= orig_z;
    }

    // go back from normalized to screen units
    vertex->x *= SCREEN_WIDTH;
    vertex->y *= SCREEN_HEIGHT;

    // center view,
    // objects at (0, 0) are in the middle if camera is in (0, 0)
    vertex->x += SCREEN_WIDTH / 2.0f;
    vertex->y += SCREEN_HEIGHT / 2.0f;
}

float cos_deg(float degrees)
{
    return cosf(to_radians(degrees));
}

float sin_deg(float degrees)
{
    return sinf(to_radians(degrees));
}

void rotate_vector(Vector *vector, float rotation_x, float rotation_y, float rotation_z)
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

void transform_mesh(Mesh *mesh)
{
    for (int i = 0; i < mesh->triangles_pos; i++)
    {
        Triangle *triangle = &mesh->triangles[i];
        Vector *vertices[4][2];
        vertices[0][0] = &triangle->v1;
        vertices[0][1] = &triangle->trans_v1;

        vertices[1][0] = &triangle->v2;
        vertices[1][1] = &triangle->trans_v2;

        vertices[2][0] = &triangle->v3;
        vertices[2][1] = &triangle->trans_v3;

        vertices[3][0] = &triangle->normal;
        vertices[3][1] = &triangle->trans_normal;

        for (int v = 0; v < 4; v++)
        {
            Vector *vertex = vertices[v][0];
            Vector *transformed_vertex = vertices[v][1];
            transformed_vertex->x = vertex->x;
            transformed_vertex->y = vertex->y;
            transformed_vertex->z = vertex->z;

            rotate_vector(transformed_vertex, mesh->rotation.x, mesh->rotation.y, mesh->rotation.z);

            transformed_vertex->x += mesh->position.x;
            transformed_vertex->y += mesh->position.y;
            transformed_vertex->z += mesh->position.z;
        }
    }
}

int main(void)
{
    make_cube(70, &meshes[meshes_pos]);
    meshes_pos++;

    return init_engine(main_loop);
}

bool main_loop(float delta)
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            return true;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                return true;
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // set_pixel(10, 10, 255, 255, 255);

    for (int i = 0; i < meshes_pos; i++)
    {
        Mesh *m = &meshes[i];

        m->rotation.y += 120 * delta;
        m->position.z = 200;

        transform_mesh(m);

        for (int t = 0; t < m->triangles_pos; t++)
        {
            Triangle *triangle = &m->triangles[t];
            Color color;

            Vector cam;
            cam.z = 1.0f;

            float diff_to_cam = vec_dot_product(cam, triangle->trans_normal);

            diff_to_cam = (diff_to_cam + 1) / 2.0f;

            color.r = 255 * diff_to_cam;
            color.g = 255 * diff_to_cam;
            color.b = 255 * diff_to_cam;

            project_vertex(&triangle->trans_v1);
            project_vertex(&triangle->trans_v2);
            project_vertex(&triangle->trans_v3);

            draw_filled_triangle(color, *triangle);
        }
    }

    SDL_RenderPresent(renderer);

    return false;
}