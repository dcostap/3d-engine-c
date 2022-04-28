import pathlib
from fileinput import filename
import os
import math
from tabnanny import filename_only
import textwrap

from numpy import append

import time


def process_obj_file(file):
    vertices = []
    indices = []
    normals = []
    uvs = []
    final_indices = []
    final_indices_id = {}
    final_vertices = []
    final_normals = []
    final_uvs = []

    # STEP 1: simply store all the info found in the .obj file
    with open(file, "r") as opened_file:
        for line in opened_file.readlines():
            parts = line.split(" ")
            if parts[0] == "v":
                vertices.append(
                    {
                        "x": float(parts[1]),
                        "y": float(parts[2]),
                        "z": float(parts[3]),
                    }
                )
            elif parts[0] == "vn":
                normals.append(
                    {
                        "x": float(parts[1]),
                        "y": float(parts[2]),
                        "z": float(parts[3]),
                    }
                )
            elif parts[0] == "vt":
                uvs.append(
                    {
                        "u": float(parts[1]),
                        "v": float(parts[2]),
                    }
                )
            elif parts[0] == "f":
                if len(parts) > 4:
                        print(f"⚠⚠⚠ {file} has something other than triangles. Indices len() = {len(parts)}")
                        exit()
                for i in range(1, 4):
                    vertex_indices = parts[i].split("/")

                    indices.append(
                        {
                            "vertex": int(vertex_indices[0]) - 1,
                            "normal": int(vertex_indices[2]) - 1,
                            "uv": (int(vertex_indices[1]) - 1) if (vertex_indices[1] != '') else -1,
                        }
                    )

    # STEP 2: process the info; the .obj format indexes normals, etc separately, but OpenGl only supports one index array.
    # Thus, we find all the truly unique vertices (same attributes - normals, vertex pos., UVs...) and output our single index array.
    current_new_index = 0
    for index in indices:
        new_id = (index["vertex"], index["normal"], index["uv"])
        existing_identical_index = final_indices_id.get(new_id, None)

        if existing_identical_index is not None:
            final_indices.append(existing_identical_index)
        else:
            final_indices_id[new_id] = current_new_index
            final_indices.append(current_new_index)
            final_vertices.append(vertices[index["vertex"]])
            final_normals.append(normals[index["normal"]])
            if index["uv"] != -1:
                final_uvs.append(uvs[index["uv"]])
            current_new_index += 1

    # STEP 3:  Store the processed info into new .c geo files
    original_filename_no_extension = file.split("/")[-1].split(".")[0]
    filename_no_extension = "geo_" + original_filename_no_extension

    vertices_c = ""

    for vertex in final_vertices:
        vertices_c += \
            f"""\
        {{ {'{0:.5}'.format(vertex["x"])}f, {'{0:.5}'.format(vertex["y"])}f, {'{0:.5}'.format(vertex["z"])}f }},
"""

    normals_c = ""
    for normal in final_normals:
        normals_c += \
            f"""\
        {{ {'{0:.5}'.format(normal["x"])}f, {'{0:.5}'.format(normal["y"])}f, {'{0:.5}'.format(normal["z"])}f }},
"""

    uvs_c = ""
    if len(final_uvs) > 0:
        for uv in final_uvs:
            # UVs are mirrored vertically so they can be correctly displayed in OpenGL
            uvs_c += \
                f"""\
            {{ {'{0:.5}'.format(uv["u"])}f, {'{0:.5}'.format(1 - uv["v"])}f }},
    """

    indices_c = ""
    for index in final_indices:
        indices_c += f"{str(index)},"

    with open("./src/models/" + filename_no_extension + ".h", "w") as c_file:
        c_file.write(f"""\
#include "../graphics.h"

extern Mesh {filename_no_extension};
        """)

    with open("./src/models/" + filename_no_extension + ".c", "w") as c_file:
        c_file.write(
            f"""\
#include "{filename_no_extension}.h"

static float vertices[{str(len(final_vertices))}][3] = {{
{vertices_c}
}};

static float normals[{str(len(final_normals))}][3] = {{
{normals_c}
}};

static float uvs[{str(len(final_uvs))}][2] = {{
{uvs_c}
}};

static int indices[{str(len(final_indices))}] = {{
{indices_c}
}};

Mesh {filename_no_extension} = {{
    .vertices = vertices,
    .vertices_size = {str(len(final_vertices))},
    .normals = normals,
    .normals_size = {str(len(final_normals))},
    .indices = indices,
    .indices_size = {str(len(final_indices))},
    .uvs = { "uvs" if len(final_uvs) > 0 else "NULL" },
    .uvs_size = {str(len(final_uvs))},
    .texture_file = { ('"./assets/models/' + original_filename_no_extension + '.png"') if len(final_uvs) > 0 else "NULL" },
}};
"""
        )


def explore_folder_recursive(root):
    for file in os.listdir(root):
        file = root + "/" + file
        if os.path.isfile(file):
            if pathlib.Path(file).suffix == ".obj":
                start_time = time.time()
                process_obj_file(file)
                print(file + " finished, took %.2f seconds." %
                      (time.time() - start_time))
        else:
            explore_folder_recursive(file)


# Delete existing generated .c geo files
for root, dirs, files in os.walk("./src/models/"):
    path = root.split(os.sep)
    for file in files:
        print("Removing " + root + file + "...")
        os.remove(root + file)
print("-----------------")

explore_folder_recursive("assets/models")
