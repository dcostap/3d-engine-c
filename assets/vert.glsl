#version 140

in vec3 in_position;
in vec3 in_normal;
in vec2 in_uv;
out vec3 frag_normal;
out vec3 frag_position;
out vec2 frag_uv;
uniform mat4 local_transform;
uniform mat4 view_transform;
uniform mat4 proj_transform;

void main(void) {
    frag_position = in_position;
    frag_normal = in_normal;
    frag_uv = in_uv;
    gl_Position = proj_transform * view_transform * local_transform * vec4(in_position, 1.0);
}
