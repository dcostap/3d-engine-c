from dataclasses import dataclass, field
import os
import pathlib
import textwrap
import time
import numpy
import transformations
import pathlib
import struct
from pygltflib import GLTF2


@dataclass
class RawModelData:
    indices: list = field(default_factory=list)
    vertices: list = field(default_factory=list)
    normals: list = field(default_factory=list)
    uvs: list = field(default_factory=list)
    bones: list = field(default_factory=list)
    weights: list = field(default_factory=list)


@dataclass
class AnimBone:
    name: str
    inverse_bind: numpy.array
    anim_keyframe_timings: list = field(default_factory=list)
    anim_keyframe_transforms: list = field(default_factory=list)
    children: list = field(default_factory=list)


@dataclass
class AnimData:
    root_bone: AnimBone
    name: str


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


def parse_gltf_file(file: str) -> RawModelData:
    fname = pathlib.Path(file)
    gltf = GLTF2().load(fname)

    all_mesh_nodes = {}
    all_bone_nodes = {}
    data = RawModelData()
    for index, node in enumerate(gltf.nodes):
        if node.mesh is not None:
            all_mesh_nodes[index] = (gltf.meshes[node.mesh], node.skin)
        else:
            all_bone_nodes[index] = node

    # for now we'll just pick the first mesh
    for (mesh, skin) in all_mesh_nodes.values():
        if len(mesh.primitives) > 1:
            print("Multiple mesh primitives?!")
            exit()

        for primitive in mesh.primitives:
            for index in read_gltf_accessor_data(gltf, gltf.accessors[primitive.indices]):
                v = struct.unpack("<H", index)
                data.indices.append(v[0])
            for pos in read_gltf_accessor_data(gltf, gltf.accessors[primitive.attributes.POSITION]):
                v = struct.unpack("<fff", pos)
                data.vertices.append(
                    {
                        "x": v[0],
                        "y": v[1],
                        "z": v[2],
                    }
                )
            for normal in read_gltf_accessor_data(gltf, gltf.accessors[primitive.attributes.NORMAL]):
                v = struct.unpack("<fff", normal)
                data.normals.append(
                    {
                        "x": v[0],
                        "y": v[1],
                        "z": v[2],
                    }
                )
            if primitive.attributes.TEXCOORD_0 is not None:
                for uvs in read_gltf_accessor_data(gltf, gltf.accessors[primitive.attributes.TEXCOORD_0]):
                    v = struct.unpack("<ff", uvs)
                    data.uvs.append(
                        {
                            "u": v[0],
                            "v": v[1],
                        }
                    )
            # TODO: support more than 4 bones per vertex (JOINTS_N, WEIGHTS_N)
            if skin is not None:
                for bones in read_gltf_accessor_data(gltf, gltf.accessors[primitive.attributes.JOINTS_0]):
                    v = struct.unpack("<BBBB", bones)
                    data.bones.append(v)

                for weights in read_gltf_accessor_data(gltf, gltf.accessors[primitive.attributes.WEIGHTS_0]):
                    v = struct.unpack("<ffff", weights)
                    data.weights.append(v)

    return data


def explore_folder_recursive(root):
    for file in os.listdir(root):
        file = root + "/" + file
        if os.path.isfile(file):
            if pathlib.Path(file).suffix == ".gltf":
                print(file)
                start_time = time.time()
                export_data(file, parse_gltf_file(file))
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
