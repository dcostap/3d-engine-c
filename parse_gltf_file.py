import pathlib
import struct

from pygltflib import GLTF2
from process_assets import RawModelData

def read_gltf_accessor_data(gltf, accessor) -> list:
    bufferView = gltf.bufferViews[accessor.bufferView]
    buffer = gltf.buffers[bufferView.buffer]
    data = gltf.get_data_from_buffer_uri(buffer.uri)

    data_byte_length = int(bufferView.byteLength / accessor.count)

    all_data = []
    for i in range(accessor.count):
        index = bufferView.byteOffset + accessor.byteOffset + i*data_byte_length  # the location in the buffer of this vertex
        d = data[index:index+data_byte_length]  # the vertex data
        all_data.append(d)
    return all_data

def parse_gltf_file(file: str) -> RawModelData:
    fname = pathlib.Path(file)
    gltf = GLTF2().load(fname)

    mesh = gltf.meshes[gltf.scenes[gltf.scene].nodes[0]]

    data = RawModelData()
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
        for uvs in read_gltf_accessor_data(gltf, gltf.accessors[primitive.attributes.TEXCOORD_0]):
            v = struct.unpack("<ff", uvs)
            data.uvs.append(
                {
                    "u": v[0],
                    "v": v[1],
                }
            )

    return data