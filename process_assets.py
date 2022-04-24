import os
import math
import textwrap

from numpy import append

vertices = []
indices = []

def process_obj_file(file):
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
            elif parts[0] == "f":
                indices.append(int(parts[1]) - 1)
                indices.append(int(parts[2]) - 1)
                indices.append(int(parts[3]) - 1)

    filename_no_extension = file.split("/")[-1].split(".")[0]

    vertices_c = ""

    for vertex in vertices:
        vertices_c += \
f"""\
        {{ {str(vertex["x"])}f, {str(vertex["y"])}f, {str(vertex["z"])}f }},
"""

    indices_c = ""
    for index in indices:
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

static float vertices[{str(len(vertices))}][3] = {{
{vertices_c}
}};

static int indices[{str(len(indices))}] = {{
{indices_c}
}};

static Mesh {filename_no_extension} = {{
    .vertices = vertices,
    .vertices_size = {str(len(vertices))},
    .indices = indices,
    .indices_size = {str(len(indices))},
}};
"""
)


root = "./assets/models"
for file in os.listdir(root):
    file = root + "/" + file
    if os.path.isfile(file):
        process_obj_file(file)
