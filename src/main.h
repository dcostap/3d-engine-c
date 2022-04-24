#include "engine.h"

typedef struct Mesh
{
    GLuint vao, vbo, ebo;
    float vertices[1000][3];
    int vertices_size;
    int indices[1000];
    int indices_size;
} Mesh;

typedef struct Entity
{
    Vec3 position;
    Vec3 rotation;
    Vec3 scale;
    Mat4 world_transform;
    Mesh mesh;
} Entity;

typedef struct Camera {
    Vec3 position;
    Vec3 rotation;
    Vec3 scale;
    Mat4 world_transform;
} Camera;

void camera_update_transform(Camera* camera);
void entity_update_transform(Entity* ent);
void mesh_apply_transform(Mesh* mesh, Mat4* transform);
int main(void);
bool main_loop(float delta);
void bind_mesh_to_opengl(Mesh* mesh);
void init_entity(Entity* ent);
void draw_entity(Entity* ent);
void check_gl_errors(char* context);
void draw_mesh(Mesh* mesh);
int init_shaders(char* vert_shader_filename, char* frag_shader_filename);


// This won't work if the array is stored in the heap
#define ARRAY_LENGTH_STACK(x)  (int) (sizeof(x) / sizeof((x)[0]))