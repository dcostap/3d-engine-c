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

    with open(file, "r") as opened_file:
        print("Opened file " + file)
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


    # Store the info in a C file
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

float vertices[{str(len(final_vertices))}][3] = {{
{vertices_c}
}};

float normals[{str(len(final_normals))}][3] = {{
{normals_c}
}};

int indices[{str(len(final_indices))}] = {{
{indices_c}
}};

Mesh {filename_no_extension} = {{
    .vertices = (float**) vertices,
    .vertices_size = {str(len(final_vertices))},
    .normals = (float**) normals,
    .normals_size = {str(len(final_normals))},
    .indices = indices,
    .indices_size = {str(len(final_indices))},
}};
"""
        )

root = "./assets/models"
for file in os.listdir(root):
    file = root + "/" + file
    if os.path.isfile(file):
        start_time = time.time()
        process_obj_file(file)
        print(file + " finished, took %.2f seconds." % (time.time() - start_time))

