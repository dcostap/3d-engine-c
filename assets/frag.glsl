#version 140
in vec3 frag_position;
in vec3 frag_normal;
out vec4 out_color;

void main(void) {
    float diff = dot(vec3(0.0, 0.0, -1.0), frag_normal);

    out_color = vec4(diff, diff, diff, 1.0);
}
