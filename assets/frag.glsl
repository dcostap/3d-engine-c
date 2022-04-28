#version 140
in vec3 frag_position;
in vec3 frag_normal;
in vec2 frag_uv;
out vec4 out_color;

uniform sampler2D texture_sampler;

void main(void) {
    float diff = dot(vec3(0.0, 0.0, -1.0), frag_normal);

    // out_color = vec4(diff, diff, diff, 1.0);
    out_color = texture(texture_sampler, frag_uv).rgba;
    // out_color *= diff;
}
