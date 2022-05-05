from dataclasses import dataclass, field
import os
import pathlib
import textwrap
import time
from typing import Tuple
import pathlib
import struct
from pygltflib import GLTF2
from pygltflib import Node


@dataclass
class RawModelData:
    name: str
    indices: list = field(default_factory=list)
    vertices: list = field(default_factory=list)
    normals: list = field(default_factory=list)
    uvs: list = field(default_factory=list)
    bones: list = field(default_factory=list)
    weights: list = field(default_factory=list)
    texture: str = None
    skeleton_name: str = None


@dataclass
class AnimBoneData:
    name: str = ""
    index: int = None
    position: list = field(default_factory=list)
    rotation: list = field(default_factory=list)
    scale: list = field(default_factory=list)
    inverse_bind: list = field(default_factory=list)
    anim_keyframe_translation_timings: list = field(default_factory=list)
    anim_keyframe_rotation_timings: list = field(default_factory=list)
    anim_keyframe_scale_timings: list = field(default_factory=list)
    anim_keyframe_translations: list = field(default_factory=list)
    anim_keyframe_rotations: list = field(default_factory=list)
    anim_keyframe_scales: list = field(default_factory=list)
    children_indices: list = field(default_factory=list)
    parent_index: int = None


@dataclass
class AnimData:
    name: str = ""
    skeleton_name: str = None
    bones_indexed: list = field(default_factory=list)


def export_anim_data(data: AnimData):
    new_filename_no_extension = data.name

    with open("./src/anims/" + new_filename_no_extension + ".h", "w") as file:
        file.write(textwrap.dedent(
            f"""\
                #include "../graphics.h"

                extern SkeletonAnimation {new_filename_no_extension};
            """))

    bone_nodes_code = []
    for (index, bone) in data.bones_indexed.items():
        has_children = len(bone.children_indices) > 0

        if has_children:
            indices = f"""\
                static int {bone.name}_children_indices[] = {{
                    { ", ".join([str(i) for i in bone.children_indices]) }
                }};
            """
        else:
            indices = ""

        if bone.position:
            bone_position = f"""\
                .bind_position = {{ .x = {bone.position[0]}, .y = {bone.position[1]}, .z = {bone.position[2]}, }},
            """
        else:
            bone_position = ""

        if bone.scale:
            bone_scale = f"""\
                .bind_scale = {{ .x = {bone.scale[0]}, .y = {bone.scale[1]}, .z = {bone.scale[2]}, }},
            """
        else:
            bone_scale = ""

        if bone.rotation:
            bone_rotation = f"""\
                .bind_rotation = {{ .x = {bone.rotation[0]}, .y = {bone.rotation[1]}, .z = {bone.rotation[2]}, .w = {bone.rotation[3]}, }},
            """
        else:
            bone_rotation = ""

        print(bone.anim_keyframe_translation_timings)
        bone_nodes_code.append(f"""\
            static float {bone.name}_anim_keyframe_translation_timings[] = {{
                {", ".join( ['{0:.5}f'.format(time) for time in bone.anim_keyframe_translation_timings] )}
            }};

            static Vec3 {bone.name}_anim_keyframe_translations[] = {{
                {", ".join(
                    [f"{{ {'{0:.5}f'.format(trans[0])}, {'{0:.5}f'.format(trans[1])}, {'{0:.5}f'.format(trans[2])} }}" for trans in bone.anim_keyframe_translations]
                )}
            }};

            static float {bone.name}_anim_keyframe_rotation_timings[] = {{
                {", ".join( ['{0:.5}f'.format(time) for time in bone.anim_keyframe_rotation_timings] )}
            }};

            static Quaternion {bone.name}_anim_keyframe_rotations[] = {{
                {", ".join(
                    [f"{{ {'{0:.5}f'.format(trans[0])}, {'{0:.5}f'.format(trans[1])}, {'{0:.5}f'.format(trans[2])}, {'{0:.5}f'.format(trans[3])} }}" for trans in bone.anim_keyframe_rotations]
                )}
            }};

            static float {bone.name}_anim_keyframe_scale_timings[] = {{
                {", ".join( ['{0:.5}f'.format(time) for time in bone.anim_keyframe_scale_timings] )}
            }};

            static Vec3 {bone.name}_anim_keyframe_scales[] = {{
                {", ".join(
                    [f"{{ {'{0:.5}f'.format(trans[0])}, {'{0:.5}f'.format(trans[1])}, {'{0:.5}f'.format(trans[2])} }}" for trans in bone.anim_keyframe_scales]
                )}
            }};

            {indices}

            static AnimSkeletonBone {bone.name} = {{
                .name = "{bone.name}",
                .index = {bone.index},
                .inverse_bind = {{
                    .mtx = {{ {", ".join( ['{0:.5}f'.format(f) for f in bone.inverse_bind] )} }}
                }},
                {bone_position}
                {bone_scale}
                {bone_rotation}
                .keyframe_translation_size = {len(bone.anim_keyframe_translation_timings)},
                .anim_keyframe_translation_timings = {bone.name}_anim_keyframe_translation_timings,
                .anim_keyframe_translations = {bone.name}_anim_keyframe_translations,
                .keyframe_rotation_size = {len(bone.anim_keyframe_rotation_timings)},
                .anim_keyframe_rotation_timings = {bone.name}_anim_keyframe_rotation_timings,
                .anim_keyframe_rotations = {bone.name}_anim_keyframe_rotations,
                .keyframe_scale_size = {len(bone.anim_keyframe_scale_timings)},
                .anim_keyframe_scale_timings = {bone.name}_anim_keyframe_scale_timings,
                .anim_keyframe_scales = {bone.name}_anim_keyframe_scales,
                .children_indices = { f"{bone.name}_children_indices" if has_children else "NULL"},
                .children_size = { f"{len(bone.children_indices)}" if has_children else "0"},
            }};
        """)

    animation_code = f"""\
        static Mat4 {data.name}_joint_transforms[{len(data.bones_indexed)}];
        static AnimSkeletonBone *{data.name}_indexed_bones[] = {{ { ', '.join(["&" + bone.name for bone in data.bones_indexed.values()]) } }};

        SkeletonAnimation {data.name} = {{
            .name = \"{data.name}\",
            .skeleton_name = \"{data.skeleton_name}\",
            .indexed_bones = {data.name}_indexed_bones,
            .indexed_bones_size = {len(data.bones_indexed)},
            .joint_transforms = {data.name}_joint_transforms,
        }};
    """

    with open("./src/anims/" + new_filename_no_extension + ".c", "w") as file:
        file.write(textwrap.dedent(
            f"""\
                #include "{new_filename_no_extension}.h"

                {os.linesep.join(bone_nodes_code)}

                {animation_code}
            """))


def export_model_data(data: RawModelData):
    # Store the processed info into new .c geo files
    original_filename_no_extension = data.name
    new_filename_no_extension = "geo_" + original_filename_no_extension

    vertices_c = ""
    for vertex in data.vertices:
        vertices_c += textwrap.dedent(
            f"""\
                {{ {'{0:.5}'.format(vertex["x"])}f, {'{0:.5}'.format(vertex["y"])}f, {'{0:.5}'.format(vertex["z"])}f }},
            """)

    normals_c = ""
    for normal in data.normals:
        normals_c += textwrap.dedent(
            f"""\
                {{ {'{0:.5}'.format(normal["x"])}f, {'{0:.5}'.format(normal["y"])}f, {'{0:.5}'.format(normal["z"])}f }},
            """)

    uvs_c = ""
    if len(data.uvs) > 0:
        for uv in data.uvs:
            # UVs are mirrored vertically so they can be correctly displayed in OpenGL
            uvs_c += textwrap.dedent(
                f"""\
                    {{ {'{0:.5}'.format(uv["u"])}f, {'{0:.5}'.format(1 - uv["v"])}f }},
                """)

    bones_c = ""
    if len(data.bones) > 0:
        for bone in data.bones:
            bones_c += textwrap.dedent(
                f"""\
                    {{ {str(bone[0])}, {str(bone[1])}, {str(bone[2])}, {str(bone[3])} }},
                """)
    weights_c = ""
    if len(data.weights) > 0:
        for weight in data.weights:
            weights_c += textwrap.dedent(
                f"""\
                    {{ {'{0:.5}'.format(weight[0])}f, {'{0:.5}'.format(weight[1])}f, {'{0:.5}'.format(weight[2])}f, {'{0:.5}'.format(weight[3])}f, }},
                """)

    indices_c = ""
    for index in data.indices:
        indices_c += f"{str(index)},"

    with open("./src/models/" + new_filename_no_extension + ".h", "w") as c_file:
        c_file.write(textwrap.dedent(
            f"""\
                #include "../graphics.h"

                extern Mesh {new_filename_no_extension};
            """))

    if len(data.uvs) > 0:
        uvs_c_full = textwrap.dedent(
            f"""\
                static float uvs[{str(len(data.uvs))}][2] = {{
                    {uvs_c}
                }};
            """)
    else:
        uvs_c_full = ""

    if len(data.bones) > 0:
        bones_c_full = textwrap.dedent(
            f"""\
                static int bones[{str(len(data.bones))}][4] = {{
                    {bones_c}
                }};
            """)
    else:
        bones_c_full = ""

    if len(data.weights) > 0:
        weights_c_full = textwrap.dedent(
            f"""\
                static float weights[{str(len(data.weights))}][4] = {{
                    {weights_c}
                }};
            """)
    else:
        weights_c_full = ""

    with open("./src/models/" + new_filename_no_extension + ".c", "w") as c_file:
        c_file.write(textwrap.dedent(
            f"""\
                #include "{new_filename_no_extension}.h"

                static float vertices[{str(len(data.vertices))}][3] = {{
                {vertices_c}
                }};

                static float normals[{str(len(data.normals))}][3] = {{
                {normals_c}
                }};

                {uvs_c_full}

                {bones_c_full}
                {weights_c_full}

                static int indices[{str(len(data.indices))}] = {{
                {indices_c}
                }};

                Mesh {new_filename_no_extension} = {{
                    .vertices = vertices,
                    .vertices_size = {str(len(data.vertices))},
                    .normals = normals,
                    .normals_size = {str(len(data.normals))},
                    .indices = indices,
                    .indices_size = {str(len(data.indices))},
                    .uvs = { "uvs" if len(data.uvs) > 0 else "NULL" },
                    .uvs_size = {str(len(data.uvs))},
                    .texture_file = { ('"./assets/models/' + original_filename_no_extension + '.png"') if data.texture else "NULL" },
                    .bones = { "bones" if len(data.bones) > 0 else "NULL" },
                    .bones_size = {str(len(data.bones))},
                    .weights = { "weights" if len(data.bones) > 0 else "NULL" },
                    .weights_size = {str(len(data.weights))},
                }};
                """))


def read_gltf_accessor_data(gltf, accessor) -> list:
    bufferView = gltf.bufferViews[accessor.bufferView]
    buffer = gltf.buffers[bufferView.buffer]
    data = gltf.get_data_from_buffer_uri(buffer.uri)

    all_data = []
    for i in range(accessor.count):
        # https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/accessor.schema.json
        # https://docs.python.org/3/library/struct.html#format-strings
        unpack_format = None
        component_byte_length = 0
        if int(accessor.componentType) == 5126:
            unpack_format = "f"
            component_byte_length = 4
        elif int(accessor.componentType) == 5121:
            unpack_format = "B"
            component_byte_length = 1
        elif int(accessor.componentType) == 5123:
            unpack_format = "H"
            component_byte_length = 2
        elif int(accessor.componentType) == 5125:
            unpack_format = "I"
            component_byte_length = 4

        n = 1
        if accessor.type == "VEC2":
            n = 2
        elif accessor.type == "VEC3":
            n = 3
        elif accessor.type == "VEC4":
            n = 4
        elif accessor.type == "MAT4":
            n = 16

        data_byte_length = n * component_byte_length

        index = bufferView.byteOffset + accessor.byteOffset + i * \
            data_byte_length  # the location in the buffer of this vertex / etc
        d = data[index:index+data_byte_length]

        if unpack_format is None:
            raise ValueError(f"Unsupported data type with id: {accessor.componentType}. Needs to be added.")

        d = struct.unpack("<" + unpack_format * n, d)
        all_data.append(d[0] if n == 1 else d)
    return all_data


def parse_gltf_file(file: str) -> Tuple[list, list]:
    fname = pathlib.Path(file)
    gltf = GLTF2().load(fname)

    exported_meshes = []

    @dataclass
    class SkinWithBones:
        skin_node: Node = None
        bones_indexed: list = field(default_factory=list)
        bones_global_index_to_local_index: dict = field(default_factory=dict)

    # Index the skins (armatures) and store its bones, mapping its global node index to the local bone index that'll be used in the application
    skins = {}
    for index, skin in enumerate(gltf.skins):
        skin_data = SkinWithBones()
        skin_data.skin_node = skin
        for (new_local_index, joint_index) in enumerate(skin.joints):
            skin_data.bones_indexed.append(gltf.nodes[joint_index])
            skin_data.bones_global_index_to_local_index[joint_index] = new_local_index
        skins[index] = skin_data

    # store the data of all mesh nodes
    for node in [node for node in gltf.nodes if node.mesh is not None]:
        mesh = gltf.meshes[node.mesh]
        mesh_data = RawModelData(mesh.name)

        if len(mesh.primitives) > 1:
            print("⚠️ Multiple mesh primitives are not supported")
            exit()

        for primitive in mesh.primitives:
            if primitive.material:
                for material in gltf.materials[primitive.material]:
                    texture_index = material.pbrMetallicRoughness.baseColorTexture
                    if texture_index:
                        texture = gltf.textures[texture_index]
                        if texture:
                            mesh_data.texture = gltf.images[texture.source].uri

            for index in read_gltf_accessor_data(gltf, gltf.accessors[primitive.indices]):
                mesh_data.indices.append(index)
            for pos in read_gltf_accessor_data(gltf, gltf.accessors[primitive.attributes.POSITION]):
                mesh_data.vertices.append(
                    {
                        "x": pos[0],
                        "y": pos[1],
                        "z": pos[2],
                    }
                )
            for normal in read_gltf_accessor_data(gltf, gltf.accessors[primitive.attributes.NORMAL]):
                mesh_data.normals.append(
                    {
                        "x": normal[0],
                        "y": normal[1],
                        "z": normal[2],
                    }
                )
            if primitive.attributes.TEXCOORD_0 is not None:
                for uv in read_gltf_accessor_data(gltf, gltf.accessors[primitive.attributes.TEXCOORD_0]):
                    mesh_data.uvs.append(
                        {
                            "u": uv[0],
                            "v": uv[1],
                        }
                    )
            # TODO: support more than 4 bones per vertex (JOINTS_N, WEIGHTS_N)
            if node.skin is not None:
                mesh_data.skeleton_name = gltf.skins[node.skin].name
                for bones in read_gltf_accessor_data(gltf, gltf.accessors[primitive.attributes.JOINTS_0]):
                    skin_data = skins[node.skin]
                    # very tricky... Node's JOINTS_N referes to an index in the skin's joints array, instead of index to the joint node in the scene
                    mesh_data.bones.append(
                        [skin_data.bones_global_index_to_local_index[gltf.skins[node.skin].joints[index]] for index in bones])

                for weight in read_gltf_accessor_data(gltf, gltf.accessors[primitive.attributes.WEIGHTS_0]):
                    mesh_data.weights.append(weight)

            exported_meshes.append(mesh_data)

    exported_anims = []

    # Process animations, and for each one create a new skin with new bones that contain data relevant to the animation
    for anim in gltf.animations:
        if anim.name is None:
            print("Animation with no name!")
            exit()

        anim_data = AnimData()
        anim_data.name = anim.name
        processed_bones = {}
        skin_index_for_this_animation = None

        def initalize_bones(skin):
            inverse_binds = {}
            for index, matrix in enumerate(read_gltf_accessor_data(gltf, gltf.accessors[skin.skin_node.inverseBindMatrices])):
                local_index = skin.bones_global_index_to_local_index[skin.skin_node.joints[index]]
                inverse_binds[local_index] = matrix

            for index, bone_node in enumerate(skin.bones_indexed):
                bone_data = AnimBoneData()
                processed_bones[index] = bone_data

                bone_data.index = index
                bone_data.name = bone_node.name.replace(".", "_")
                bone_data.children_indices = [ skin.bones_global_index_to_local_index[index] for index in bone_node.children]
                bone_data.inverse_bind = inverse_binds[index]
                bone_data.position = bone_node.translation
                bone_data.rotation = bone_node.rotation
                bone_data.scale = bone_node.scale

            for index, bone in processed_bones.items():
                for child_index in bone.children_indices:
                    child = processed_bones[child_index]
                    child.parent_index = index

        for channel in anim.channels:
            bone_index = channel.target.node
            animation_type = channel.target.path

            skin_index_for_this_bone = next(
                (sk for sk in skins if bone_index in skins[sk].bones_global_index_to_local_index.keys()), None)

            if skin_index_for_this_bone is None:
                print(
                    f"Bone in animation {anim.name} doesn't refer to any bone inside any Skin present in the file")
                exit()
            elif skin_index_for_this_animation is not None and skin_index_for_this_bone != skin_index_for_this_animation:
                print(
                    f"Animation {anim.name} refers to nodes that belong to more than 1 skin!")
                exit()
            elif skin_index_for_this_animation is None:
                skin_index_for_this_animation = skin_index_for_this_bone
                initalize_bones(skins[skin_index_for_this_animation])

            local_bone_index = skins[skin_index_for_this_animation].bones_global_index_to_local_index[bone_index]
            bone_data = processed_bones[local_bone_index]

            timings = []
            for time in read_gltf_accessor_data(gltf, gltf.accessors[anim.samplers[channel.sampler].input]):
                timings.append(time)

            for transform in read_gltf_accessor_data(gltf, gltf.accessors[anim.samplers[channel.sampler].output]):
                if animation_type == 'translation':
                    bone_data.anim_keyframe_translation_timings = timings
                    bone_data.anim_keyframe_translations.append(transform)
                elif animation_type == 'rotation':
                    bone_data.anim_keyframe_rotation_timings = timings
                    bone_data.anim_keyframe_rotations.append(transform)
                elif animation_type == 'scale':
                    bone_data.anim_keyframe_scale_timings = timings
                    bone_data.anim_keyframe_scales.append(transform)

        anim_data.bones_indexed = processed_bones
        anim_data.skeleton_name = gltf.skins[skin_index_for_this_animation].name
        exported_anims.append(anim_data)

    return (exported_meshes, exported_anims)


def explore_folder_recursive(root):
    for file in os.listdir(root):
        file = root + "/" + file
        if os.path.isfile(file):
            if pathlib.Path(file).suffix == ".gltf":
                print(file)
                start_time = time.time()

                data = parse_gltf_file(file)
                for model_data in data[0]:
                    export_model_data(model_data)
                for anim_data in data[1]:
                    export_anim_data(anim_data)

                print(file + " finished, took %.2f seconds." %
                      (time.time() - start_time))
        else:
            explore_folder_recursive(file)


if __name__ == "__main__":
    # Delete existing generated .c geo files
    for root, dirs, files in os.walk("./src/models/"):
        path = root.split(os.sep)
        for file in files:
            print("Removing " + root + file + "...")
            os.remove(root + file)
    print("-----------------")

    explore_folder_recursive("assets/models")
