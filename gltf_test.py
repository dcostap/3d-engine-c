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
        index = bufferView.byteOffset + accessor.byteOffset + i * \
            data_byte_length  # the location in the buffer of this vertex
        d = data[index:index+data_byte_length]  # the vertex data
        all_data.append(d)
    return all_data

# GLTF format notes
# https://www.khronos.org/files/gltf20-reference-guide.pdf
#
# Scenes: ignore it, we'll have just one
# nodes: stuff that has a position etc in the scene: meshes & bones
#   may reference a mesh
#   may reference a skin
# mesh: thing with geometry data
#   primitive: geometry data, we'll have one per mesh?
#       vertex data: indices + position, normals, relationship with armature bones (weight, joints)...
# skin / armature
#     list of bone nodes
# animations
#   channel: what node it affects (i'll ignore any target other than bone nodes aka joints), and what property the anim is modifying
#   sampler: animation data in keyframes; times (input) and transformation (output)
# GLTF doesn't seem to link animations with any mesh / armature / whatever

# for rigging / skinning vertices I need...
#   a) base / pose position of the bones
#   b) current position in animation
#   the a-b diff is what you transform on each vertex
# absolute position of the armature (in the scene) isn't needed, so i just ignore it?
#
#

def parse_gltf_file(file: str) -> RawModelData:
    fname = pathlib.Path(file)
    gltf = GLTF2().load(fname)

    for index, node in enumerate(gltf.nodes):
        print()
        print("--> Searching node number " + str(index))
        if node.mesh is not None:
            mesh = gltf.meshes[node.mesh]

            if node.skin is not None:
                print("this mesh node has skin aka armature")
                skin = gltf.skins[node.skin]
                for joint in skin.joints:
                    print(f"node with index {joint} is one of its joints" )

                print("therefore, its mesh must also give us more info...")

                for primitive in mesh.primitives:
                    print("   -> list of the joints that affect each vertex, size ", len(read_gltf_accessor_data(gltf, gltf.accessors[primitive.attributes.JOINTS_0])))
                    print("   -> list of the weights for each vertex<->joint, size ", len(read_gltf_accessor_data(gltf, gltf.accessors[primitive.attributes.WEIGHTS_0])))

        else:
            print("is not a mesh, may be a skeleton bone")


        # for primitive in mesh.primitives:
        #     for pos in read_gltf_accessor_data(gltf, gltf.accessors[primitive.attributes.POSITION]):
        #         v = struct.unpack("<fff", pos)
        #         data.vertices.append(
        #             {
        #                 "x": v[0],
        #                 "y": v[1],
        #                 "z": v[2],
        #             }
        #         )


parse_gltf_file("./assets/models/rigged_figure.gltf")
