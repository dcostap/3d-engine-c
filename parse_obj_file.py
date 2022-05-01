from process_assets import RawModelData

def parse_obj_file(file: str) -> RawModelData:
    raw_data = RawModelData()
    with open(file, "r") as opened_file:
        for line in opened_file.readlines():
            parts = line.split(" ")
            if parts[0] == "v":
                raw_data.vertices.append(
                    {
                        "x": float(parts[1]),
                        "y": float(parts[2]),
                        "z": float(parts[3]),
                    }
                )
            elif parts[0] == "vn":
                raw_data.normals.append(
                    {
                        "x": float(parts[1]),
                        "y": float(parts[2]),
                        "z": float(parts[3]),
                    }
                )
            elif parts[0] == "vt":
                raw_data.uvs.append(
                    {
                        "u": float(parts[1]),
                        "v": float(parts[2]),
                    }
                )
            elif parts[0] == "f":
                if len(parts) > 4:
                    print(
                        f"⚠⚠⚠ {file} has something other than triangles. Indices len() = {len(parts)}")
                    exit()
                for i in range(1, 4):
                    vertex_indices = parts[i].split("/")

                    raw_data.indices.append(
                        {
                            "vertex": int(vertex_indices[0]) - 1,
                            "normal": int(vertex_indices[2]) - 1,
                            "uv": (int(vertex_indices[1]) - 1) if (vertex_indices[1] != '') else -1,
                        }
                    )

    final_data = RawModelData()
    indices_id = {}

    # STEP 2: process the info; the .obj format indexes normals, etc separately, but OpenGl only supports one index array.
    # Thus, we find all the truly unique vertices (same attributes - normals, vertex pos., UVs...) and output our single index array.
    current_new_index = 0
    for index in raw_data.indices:
        new_id = (index["vertex"], index["normal"], index["uv"])
        existing_identical_index = indices_id.get(new_id, None)

        if existing_identical_index is not None:
            final_data.indices.append(existing_identical_index)
        else:
            indices_id[new_id] = current_new_index
            final_data.indices.append(current_new_index)
            final_data.vertices.append(raw_data.vertices[index["vertex"]])
            final_data.normals.append(raw_data.normals[index["normal"]])
            if index["uv"] != -1:
                final_data.uvs.append(raw_data.uvs[index["uv"]])
            current_new_index += 1
    return final_data
