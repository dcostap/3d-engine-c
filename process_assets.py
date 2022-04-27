import pathlib
from fileinput import filename
import os
import math
import textwrap

from numpy import append

import time


def process_obj_file(file):
    vertices = []
    indices = []
    normals = []
    final_indices = []
    final_indices_id = {}
    final_vertices = []
    final_normals = []

    ## STEP 1: simply store all the info found in the .obj file
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
            elif parts[0] == "f":
                for i in range(1, 4):
                    vertex_indices = parts[i].split("/")
                    indices.append(
                        {
                            "vertex": int(vertex_indices[0]) - 1,
                            "normal": int(vertex_indices[2]) - 1,
                        }
                    )

    ## STEP 2: process the info; .obj format indexes normals, etc separately, but OpenGl only supports one index array.
    ## Thus, we find all the truly unique vertices (same attributes - normals, vertex pos., UVs...) and output our single index array.
    current_new_index = 0
    for index in indices:
        new_id = (index["vertex"], index["normal"])
        existing_identical_index = final_indices_id.get(new_id, None)

        if existing_identical_index is not None:
            final_indices.append(existing_identical_index)
        else:
            final_indices_id[new_id] = current_new_index
            final_indices.append(current_new_index)
            final_vertices.append(vertices[index["vertex"]])
            final_normals.append(normals[index["normal"]])
            current_new_index += 1

    ## STEP 3:  Store the processed info into new .c geo files
    filename_no_extension = file.split("/")[-1].split(".")[0]
    filename_no_extension = "geo_" + filename_no_extension

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

    indices_c = ""
    for index in final_indices:
        indices_c += f"{str(index)},"

    with open("./src/models/" + filename_no_extension + ".h", "w") as c_file:
        c_file.write(f"""\
#include "../main.h"

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
