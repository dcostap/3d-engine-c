#version 140

in vec3 in_position;
in vec3 in_normal;
out vec3 frag_normal;
out vec3 frag_position;
uniform mat4 local_transform;
uniform mat4 view_transform;
uniform mat4 proj_transform;

void main(void) {
    frag_position = in_position;
    frag_normal = in_normal;
    gl_Position = proj_transform * view_transform * local_transform * vec4(in_position, 1.0);
}
