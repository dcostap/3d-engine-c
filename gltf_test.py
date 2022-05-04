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
# POST-SKINNING NOTES:
# ⚠️ In every armature, there must be at least one bone assigned per vertex, due to how GLTF exports the vertex-bone association
#       (when no bone in a index slot, exported index is 0, but with weight 0. But if there is 0 bones associated, defaults to "weight of 1 in bone 0")
#       (this is probs. due to how vertex skinning is calculated, there must be always a matrix you can transform the vertex with)
#       so, always have a root bone that affects every vertex. This is the standard practice.
#       otherwise the anim you see in blender is diff than what you'll see in GLTF viewers
#
#
# PRE-SKINNNING CODE NOTES:
#
# Scenes: ignore it, we'll have just one
# nodes: stuff that has a position etc in the scene: meshes & bones
#   may reference a mesh
#   may reference a skin
# mesh: thing with geometry data
#   primitive: geometry data, we'll have one per mesh?
#       vertex data: indices + position, normals, relationship with armature bones (weight, joints)...
#           we'll refer to each relevant joint via indices
# skin / armature
#     list of bone nodes (we need this list to know the index of each bone node)
#     inverse bind matrix for each node
# animations
#   channel: what node it affects (i'll ignore any target other than bone nodes aka joints), what property the anim is modifying and the sampler used
#   sampler: animation data in keyframes; times (input) and transformation (output)
# GLTF doesn't seem to link animations with any mesh / armature / whatever
#   mesh implicitly has armature data set in each vertex buffer (weights and joints)
#   so a mesh implicitly can only be animated by animations that use that armature
#   since this link isn't enforced, we'll store the names to document the actual supposes usages
#       each armature has a name
#           (for now it's the root node's name...
#           TODO: grab the name from the node that represents the actual armature / whatever, in the gltf scene graph...),
#       and we'll put that name in the meshes that use it
#       each animation has a link to the root node, which has that name, or later on we'll add a name field to the animation struct
#   About sharing animations on different meshes: in blender each one will have diff armature objects,
#       but if we identify armatures by root node's name / whatever, we can name them the same to indicate that they share the skeleton and thus the animations
# ELI5
# each mesh is linked to -> specific armature
#   link isn't enforced, we just store name of "armature" in the mesh
# in theory, one armature can have multiple animations
# in practice, I'll store one armature (list of bones) per animation
# I'll store the anim data on each bone, to make things simpler
# so in practice, i just need to link one mesh with its animation
#
# bone indexing can be a problem, since mesh vertex info refers to each bone by index, and this index is loaded in gltf as the scene node index

# for transforming the vertices for animation (aka skinning) I need...
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
