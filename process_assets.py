from dataclasses import dataclass, field
import os
import pathlib
import textwrap
import time

@dataclass
class RawModelData:
    indices: list = field(default_factory=list)
    vertices: list = field(default_factory=list)
    normals: list = field(default_factory=list)
    uvs: list = field(default_factory=list)


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
                }};
                """))


def explore_folder_recursive(root):
    from parse_obj_file import parse_obj_file
    from parse_gltf_file import parse_gltf_file

    for file in os.listdir(root):
        file = root + "/" + file
        if os.path.isfile(file):
            if pathlib.Path(file).suffix == ".obj":
                start_time = time.time()
                export_data(file, parse_obj_file(file))
                print(file + " finished, took %.2f seconds." %
                      (time.time() - start_time))
            elif pathlib.Path(file).suffix == ".gltf":
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
