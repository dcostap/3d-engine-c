import os
import math
import textwrap

vertices = []
triangles = []


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
                v1 = vertices[int(parts[1]) - 1]
                v2 = vertices[int(parts[2]) - 1]
                v3 = vertices[int(parts[3]) - 1]

                v1v2 = {
                    "x": v2["x"] - v1["x"],
                    "y": v2["y"] - v1["y"],
                    "z": v2["z"] - v1["z"],
                }

                v1v3 = {
                    "x": v3["x"] - v1["x"],
                    "y": v3["y"] - v1["y"],
                    "z": v3["z"] - v1["z"],
                }

                def set_unit(vector):
                    length = math.sqrt(
                        pow(vector["x"], 2) +
                        pow(vector["y"], 2) +
                        pow(vector["z"], 2)
                    )

                    vector["x"] /= length
                    vector["y"] /= length
                    vector["z"] /= length

                set_unit(v1v2)
                set_unit(v1v3)

                def cross_product(v1, v2):
                    return {
                        "x": v1["y"] * v2["z"] - v1["z"] * v2["y"],
                        "y": v1["z"] * v2["x"] - v1["x"] * v2["z"],
                        "z": v1["x"] * v2["y"] - v1["y"] * v2["x"],
                    }

                normal = cross_product(v1v2, v1v3)
                set_unit(normal)

                triangles.append(
                    {
                        "v1": v1,
                        "v2": v2,
                        "v3": v3,
                        "normal": normal,
                    }
                )

    filename_no_extension = file.split("/")[-1].split(".")[0]

    triangles_c = ""

    index = 0
    for triangle in triangles:
        v1 = triangle["v1"]
        v2 = triangle["v2"]
        v3 = triangle["v3"]
        normal = triangle["normal"]

        triangles_c += f"""\
{{
    .v1 = {{ .x = {v1["x"]}, .y = {v1["y"]}, .z = {v1["z"]}}},
    .v2 = {{ .x = {v2["x"]}, .y = {v2["y"]}, .z = {v2["z"]}}},
    .v3 = {{ .x = {v3["x"]}, .y = {v3["y"]}, .z = {v3["z"]}}},
    .normal = {{.x = {normal["x"]}, .y = {normal["y"]}, .z = {normal["z"]}}}
}},
"""

        index += 1

    with open("./src/assets/" + filename_no_extension + ".h", "w") as c_file:
        c_file.write(
f"""\
#include "../utils_3d.h"

extern Mesh {filename_no_extension};
"""
        )

    with open("./src/assets/" + filename_no_extension + ".c", "w") as c_file:
        c_file.write(
f"""\
#include "mario.h"

Mesh {filename_no_extension} = {{
    .triangles = {{
        {triangles_c}
    }},
    .triangles_pos = {str(len(triangles))}
}};
"""
        )


root = "./assets"
for file in os.listdir(root):
    file = root + "/" + file
    if os.path.isfile(file):
        process_obj_file(file)
