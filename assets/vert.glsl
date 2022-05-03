#version 140

in vec3 in_position;
in vec3 in_normal;
in vec2 in_uv;

in vec4 in_joints;
in vec4 in_weights;

out vec3 frag_normal;
out vec3 frag_position;
out vec2 frag_uv;
uniform mat4 local_transform;
uniform mat4 view_transform;
uniform mat4 proj_transform;
uniform mat4 joint_matrices[19];

void main(void) {
    mat4 skin_matrix = in_weights.x * joint_matrices[int(in_joints.x)] + in_weights.y * joint_matrices[int(in_joints.y)] +
                in_weights.z * joint_matrices[int(in_joints.z)] + in_weights.w * joint_matrices[int(in_joints.w)];

    frag_position = in_position;
    frag_normal = in_normal;
    frag_uv = in_uv;
    gl_Position = proj_transform * view_transform * local_transform * skin_matrix * vec4(in_position, 1.0);
}
