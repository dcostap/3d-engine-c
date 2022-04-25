#version 140

in vec3 in_position;
out vec3 vert_position;
uniform mat4 local_transform;
uniform mat4 view_transform;
uniform mat4 proj_transform;

void main(void) {
    vert_position = in_position;
    gl_Position = proj_transform * view_transform * local_transform * vec4(in_position, 1.0);
}
