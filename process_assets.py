from dataclasses import dataclass, field
import os
import pathlib
import textwrap
import time
from typing import Tuple
import numpy
import transformations
import pathlib
import struct
from pygltflib import GLTF2
from pygltflib import Node


@dataclass
class RawModelData:
    indices: list = field(default_factory=list)
    vertices: list = field(default_factory=list)
    normals: list = field(default_factory=list)
    uvs: list = field(default_factory=list)
    bones: list = field(default_factory=list)
    weights: list = field(default_factory=list)
    skeleton_name: str = None


@dataclass
class AnimBoneData:
    name: str = ""
    inverse_bind: list = field(default_factory=list)
    anim_keyframe_timings: list = field(default_factory=list)
    anim_keyframe_translations: list = field(default_factory=list)
    anim_keyframe_rotations: list = field(default_factory=list)
    anim_keyframe_scales: list = field(default_factory=list)
    children: list = field(default_factory=list)
    parent_index: int = None


@dataclass
class AnimData:
    name: str = ""
    bones_indexed: list = field(default_factory=list)


def export_data(file: str, data: RawModelData):
    # Store the processed info into new .c geo files
    original_filename_no_extension = file.split("/")[-1].split(".")[0]
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
                static float bones[{str(len(data.bones))}][4] = {{
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
                    .texture_file = { ('"./assets/models/' + original_filename_no_extension + '.png"') if len(data.uvs) > 0 else "NULL" },
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

    data_byte_length = int(bufferView.byteLength / accessor.count)

    all_data = []
    for i in range(accessor.count):
        index = bufferView.byteOffset + accessor.byteOffset + i * \
            data_byte_length  # the location in the buffer of this vertex
        d = data[index:index+data_byte_length]  # the vertex data
        all_data.append(d)
    return all_data


def parse_gltf_file(file: str) -> Tuple[RawModelData, list]:
    fname = pathlib.Path(file)
    gltf = GLTF2().load(fname)

    mesh_data = RawModelData()

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

        if len(mesh.primitives) > 1:
            print("Multiple mesh primitives?!")
            exit()

        for primitive in mesh.primitives:
            for index in read_gltf_accessor_data(gltf, gltf.accessors[primitive.indices]):
                v = struct.unpack("<H", index)
                mesh_data.indices.append(v[0])
            for pos in read_gltf_accessor_data(gltf, gltf.accessors[primitive.attributes.POSITION]):
                v = struct.unpack("<fff", pos)
                mesh_data.vertices.append(
                    {
                        "x": v[0],
                        "y": v[1],
                        "z": v[2],
                    }
                )
            for normal in read_gltf_accessor_data(gltf, gltf.accessors[primitive.attributes.NORMAL]):
                v = struct.unpack("<fff", normal)
                mesh_data.normals.append(
                    {
                        "x": v[0],
                        "y": v[1],
                        "z": v[2],
                    }
                )
            if primitive.attributes.TEXCOORD_0 is not None:
                for uvs in read_gltf_accessor_data(gltf, gltf.accessors[primitive.attributes.TEXCOORD_0]):
                    v = struct.unpack("<ff", uvs)
                    mesh_data.uvs.append(
                        {
                            "u": v[0],
                            "v": v[1],
                        }
                    )
            # TODO: support more than 4 bones per vertex (JOINTS_N, WEIGHTS_N)
            if node.skin is not None:
                mesh_data.skeleton_name = gltf.skins[node.skin].name
                for bones in read_gltf_accessor_data(gltf, gltf.accessors[primitive.attributes.JOINTS_0]):
                    v = struct.unpack("<BBBB", bones)
                    skin_data = skins[node.skin]
                    mesh_data.bones.append([ skin_data.bones_global_index_to_local_index[index] for index in v ])

                for weights in read_gltf_accessor_data(gltf, gltf.accessors[primitive.attributes.WEIGHTS_0]):
                    v = struct.unpack("<ffff", weights)
                    mesh_data.weights.append(v)

    anims = []

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
                local_index = skin.bones_global_index_to_local_index[index]
                inverse_binds[local_index] = struct.unpack("<ffffffffffffffff", matrix)

            for index, bone_node in enumerate(skin.bones_indexed):
                bone_data = AnimBoneData()
                processed_bones[index] = bone_data

                bone_data.name = bone_node.name
                bone_data.children = list(bone_node.children)
                bone_data.inverse_bind = inverse_binds[index]

            for index, bone in processed_bones.items():
                for child_index in bone.children:
                    child = processed_bones[skin.bones_global_index_to_local_index[child_index]]
                    child.parent_index = index

        for channel in anim.channels:
            bone_index = channel.target.node
            animation_type = channel.target.path

            skin_index_for_this_bone = next((sk for sk in skins if bone_index in skins[sk].bones_global_index_to_local_index.keys()), None)

            if skin_index_for_this_bone is None:
                print(f"Bone in animation {anim.name} doesn't refer to any bone inside any Skin present in the file")
                exit()
            elif skin_index_for_this_animation is not None and skin_index_for_this_bone != skin_index_for_this_animation:
                print(f"Animation {anim.name} refers to nodes that belong to more than 1 skin!")
                exit()
            elif skin_index_for_this_animation is None:
                skin_index_for_this_animation = skin_index_for_this_bone
                initalize_bones(skins[skin_index_for_this_animation])

            local_bone_index = skins[skin_index_for_this_animation].bones_global_index_to_local_index[bone_index]
            bone_data = processed_bones[local_bone_index]

            for time in read_gltf_accessor_data(gltf, gltf.accessors[anim.samplers[channel.sampler].input]):
                bone_data.anim_keyframe_timings.append(struct.unpack("<f", time))

            for transform in read_gltf_accessor_data(gltf, gltf.accessors[anim.samplers[channel.sampler].output]):
                if animation_type == 'translation':
                    bone_data.anim_keyframe_translations.append(struct.unpack("<fff", transform))
                elif animation_type == 'rotation':
                    bone_data.anim_keyframe_rotations.append(struct.unpack("<ffff", transform))
                elif animation_type == 'scale':
                    bone_data.anim_keyframe_scales.append(struct.unpack("<fff", transform))

        anim_data.bones_indexed = processed_bones
        anims.append(anim_data)

    return (mesh_data, anims)


def explore_folder_recursive(root):
    for file in os.listdir(root):
        file = root + "/" + file
        if os.path.isfile(file):
            if pathlib.Path(file).suffix == ".gltf":
                print(file)
                start_time = time.time()
                parse_gltf_file(file)
                # export_data(file, parse_gltf_file(file))
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
