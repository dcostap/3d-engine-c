#include "shader.h"

GLuint gl_shader_program = 0;

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
    store_data_in_vbo(mesh->vertices, sizeof(mesh->vertices[0]) * mesh->vertices_size, mesh->vertices_size, "in_position");
    store_data_in_vbo(mesh->normals, sizeof(mesh->normals[0]) * mesh->normals_size, mesh->normals_size, "in_normal");

    glBindVertexArray(0);
}

void store_data_in_vbo(float *data, GLsizeiptr data_size, int number_of_elements, char *attribute_name)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);

    GLint attrib_id = glGetAttribLocation(gl_shader_program, attribute_name);
    glVertexAttribPointer(attrib_id, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(attrib_id);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void draw_entity(Entity *ent)
{
    GLuint id = glGetUniformLocation(gl_shader_program, "local_transform");
    glUniformMatrix4fv(id, 1, GL_FALSE, ent->world_transform);

    draw_mesh(ent->mesh);
}

void draw_mesh(Mesh *mesh)
{
    glBindVertexArray(mesh->vao);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);

    glDrawElements(GL_TRIANGLES, mesh->indices_size, GL_UNSIGNED_INT, NULL);

    glBindVertexArray(0);

    //     glBegin(GL_POLYGON);
    //     for (int index = 0; index < geo_mario.indices_size; index++)  {
    //             int i = geo_mario.indices[index];
    //             // printf("%d", i);
    //             float *vert = geo_mario.vertices[i];
    //             // printf("%f\n", vert);
    //             glVertex3f(vert[0], vert[1], vert[2]);
    //     }
    //     glEnd();
}
