#version 140
in vec3 vert_position;
out vec4 out_color;

void main(void) {
    out_color = vec4((vert_position.x + 1) / 2.0, 0.0, 0.0, 1.0);
}
