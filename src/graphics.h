#pragma once

#include "engine.h"
#include "main.h"

void draw_mesh(Mesh *mesh);
void draw_entity(Entity *ent);
void bind_mesh_to_opengl(Mesh *mesh);
bool load_shaders();
void start_shader();
void stop_shader();

extern GLuint gl_shader_program;