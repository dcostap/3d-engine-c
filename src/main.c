#include "engine.h"
#include "assets/mario.h"
#include <math.h>
// #include "test.c"

bool main_loop(float delta);
int main(void);
bool init_shaders();

GLuint gl_shader_program;

typedef struct Mesh
{
    GLuint vao, vbo, ebo;
    float vertices[6][3];
    int vertices_size;
    int indices[6];
    int indices_size;
} Mesh;

Mesh mesh = {
    .vertices = {{-0.5f, -0.7f, 0.0f, 1.0f},
                 {-1.0f, 0.0f, 0.0f, 0.0f},
                 {1.0f, 1.0f, 1.0f, 0.0f},
                 {1.0f, -1.0f, 1.0f, 1.0f}},
    .vertices_size = 4,
    .indices = {0, 1, 2, 0, 2, 3},
    .indices_size = 6};

int main(void)
{
    return init_engine(main_loop);
    // return main_test();
}

static bool is_first_loop = true;

bool main_loop(float delta)
{
    if (is_first_loop)
    {
        is_first_loop = false;
        if (!init_shaders())
        {
            return true;
        }

        init_mesh(&mesh);
    }

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

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // glEnable(GL_DEPTH_TEST);
    glClearColor(0.3f, 0.2f, 0.5f, 0.f);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);

    draw_mesh(&mesh);

    // glClearColor(0.3f, 0.2f, 0.5f, 0.f);
    // glClear(GL_COLOR_BUFFER_BIT);

    // glBegin(GL_TRIANGLES);
    // glColor3f(1, 0, 0);
    // glVertex3f(-0.6, -0.75, 0.5);
    // glColor3f(0, 1, 0);
    // glVertex3f(0.6, -0.75, 0);
    // glColor3f(0, 0, 1);
    // glVertex3f(0, 0.75, 0);
    // glEnd();

    SDL_GL_SwapWindow(sdl_window);

    return false;
}

static const char *vert_shader = "\
#version 400 core                                                                                       \n\
                                                                                                        \n\
in vec3 in_position;                                                                                       \n\
                                                                                                        \n\
void main(void) {                                                                                       \n\
    gl_Position = vec4(in_position.x, in_position.y, 0.0, 1.0);                                                  \n\
}                                                                                                       \n\
";

static const char *frag_shader = "\
#version 400 core                                                              \n\
                                                                               \n\
out vec4 out_color;                                                          \n\
                                                                               \n\
void main(void) {                                                              \n\
    out_color = vec4(1.0, 0.0, 0.0, 1.0);                                      \n\
}                                                                              \n\
";

const GLfloat verts[6][4] = {
    //  x      y      s      t
    {-0.5f, -0.7f, 0.0f, 1.0f}, // BL
    {-1.0f, 0.0f, 0.0f, 0.0f},  // TL
    {1.0f, 1.0f, 1.0f, 0.0f},   // TR
    {1.0f, -1.0f, 1.0f, 1.0f},  // BR
};

const GLint indicies[] = {
    0, 1, 2, 0, 2, 3};

void init_mesh(Mesh *mesh)
{
    printf("%d", sizeof(mesh->vertices));
    // Populate vertex buffer
    glGenBuffers(1, &mesh->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mesh->vertices), mesh->vertices, GL_STATIC_DRAW);

    // Populate element buffer
    glGenBuffers(1, &mesh->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mesh->indices), mesh->indices, GL_STATIC_DRAW);

    // Bind vertex position attribute
    GLint pos_attr_loc = glGetAttribLocation(gl_shader_program, "in_position");
    glVertexAttribPointer(pos_attr_loc, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(pos_attr_loc);

    // Bind vertex texture coordinate attribute
    // GLint tex_attr_loc = glGetAttribLocation(gl_shader_program, "in_Texcoord");
    // glVertexAttribPointer(tex_attr_loc, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (void*)(2*sizeof(GLfloat)));
    // glEnableVertexAttribArray(tex_attr_loc);
}

void draw_mesh(Mesh *mesh)
{
    // glBindVertexArray(mesh->vao);
    // glEnableVertexAttribArray(0);
    // GLint pos_attr_loc = glGetAttribLocation(gl_shader_program, "position");

    glDrawElements(GL_TRIANGLES, mesh->indices_size, GL_UNSIGNED_INT, NULL);

    // glDisableVertexAttribArray(0);
    // glBindVertexArray(0);
}

bool init_shaders()
{
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

    gl_shader_program = glCreateProgram();
    glAttachShader(gl_shader_program, vertex_id);
    glAttachShader(gl_shader_program, fragment_id);

    glBindFragDataLocation(gl_shader_program, 0, "out_color");

    glLinkProgram(gl_shader_program);
    glUseProgram(gl_shader_program);

    return true;
}