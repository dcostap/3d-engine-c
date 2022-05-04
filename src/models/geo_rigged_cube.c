                #include "geo_rigged_cube.h"

                static float vertices[24][3] = {
                { 1.0f, 2.1884f, -1.0f },
{ 1.0f, 2.1884f, -1.0f },
{ 1.0f, 2.1884f, -1.0f },
{ 1.0f, 0.18839f, -1.0f },
{ 1.0f, 0.18839f, -1.0f },
{ 1.0f, 0.18839f, -1.0f },
{ 0.42784f, 2.1798f, 0.42112f },
{ 0.42784f, 2.1798f, 0.42112f },
{ 0.42784f, 2.1798f, 0.42112f },
{ 1.0258f, 0.15537f, 1.3893f },
{ 1.0258f, 0.15537f, 1.3893f },
{ 1.0258f, 0.15537f, 1.3893f },
{ -1.0f, 2.1884f, -1.0f },
{ -1.0f, 2.1884f, -1.0f },
{ -1.0f, 2.1884f, -1.0f },
{ -1.0f, 0.18839f, -1.0f },
{ -1.0f, 0.18839f, -1.0f },
{ -1.0f, 0.18839f, -1.0f },
{ -1.0f, 2.1884f, 1.0f },
{ -1.0f, 2.1884f, 1.0f },
{ -1.0f, 2.1884f, 1.0f },
{ -1.0f, 0.18839f, 1.0f },
{ -1.0f, 0.18839f, 1.0f },
{ -1.0f, 0.18839f, 1.0f },

                };

                static float normals[24][3] = {
                { 0.0f, 0.0f, -1.0f },
{ 0.0030251f, 0.99999f, 0.0030251f },
{ 0.97366f, 0.17872f, 0.14157f },
{ -0.0074798f, -0.99994f, -0.0074798f },
{ 0.0f, 0.0f, -1.0f },
{ 0.97366f, 0.17872f, 0.14157f },
{ 0.0030251f, 0.99999f, 0.0030251f },
{ 0.056078f, 0.24141f, 0.9688f },
{ 0.97366f, 0.17872f, 0.14157f },
{ -0.0074798f, -0.99994f, -0.0074798f },
{ 0.056078f, 0.24141f, 0.9688f },
{ 0.97366f, 0.17872f, 0.14157f },
{ -1.0f, 0.0f, -0.0f },
{ 0.0f, 0.0f, -1.0f },
{ 0.0030251f, 0.99999f, 0.0030251f },
{ -1.0f, 0.0f, -0.0f },
{ -0.0074798f, -0.99994f, -0.0074798f },
{ 0.0f, 0.0f, -1.0f },
{ -1.0f, 0.0f, -0.0f },
{ 0.0030251f, 0.99999f, 0.0030251f },
{ 0.056078f, 0.24141f, 0.9688f },
{ -1.0f, 0.0f, -0.0f },
{ -0.0074798f, -0.99994f, -0.0074798f },
{ 0.056078f, 0.24141f, 0.9688f },

                };

                                static float uvs[24][2] = {
                    { 0.625f, 0.5f },
{ 0.625f, 0.5f },
{ 0.625f, 0.5f },
{ 0.375f, 0.5f },
{ 0.375f, 0.5f },
{ 0.375f, 0.5f },
{ 0.625f, 0.75f },
{ 0.625f, 0.75f },
{ 0.625f, 0.75f },
{ 0.375f, 0.75f },
{ 0.375f, 0.75f },
{ 0.375f, 0.75f },
{ 0.625f, 0.25f },
{ 0.625f, 0.25f },
{ 0.875f, 0.5f },
{ 0.375f, 0.25f },
{ 0.125f, 0.5f },
{ 0.375f, 0.25f },
{ 0.625f, 0.0f },
{ 0.875f, 0.75f },
{ 0.625f, 1.0f },
{ 0.375f, 0.0f },
{ 0.125f, 0.75f },
{ 0.375f, 1.0f },

                };


                                static int bones[24][4] = {
                    { 0, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 1, 0, 0, 0 },
{ 1, 0, 0, 0 },
{ 1, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 },

                };

                                static float weights[24][4] = {
                    { 1.0f, 0.0f, 0.0f, 0.0f, },
{ 1.0f, 0.0f, 0.0f, 0.0f, },
{ 1.0f, 0.0f, 0.0f, 0.0f, },
{ 1.0f, 0.0f, 0.0f, 0.0f, },
{ 1.0f, 0.0f, 0.0f, 0.0f, },
{ 1.0f, 0.0f, 0.0f, 0.0f, },
{ 1.0f, 0.0f, 0.0f, 0.0f, },
{ 1.0f, 0.0f, 0.0f, 0.0f, },
{ 1.0f, 0.0f, 0.0f, 0.0f, },
{ 1.0f, 0.0f, 0.0f, 0.0f, },
{ 1.0f, 0.0f, 0.0f, 0.0f, },
{ 1.0f, 0.0f, 0.0f, 0.0f, },
{ 1.0f, 0.0f, 0.0f, 0.0f, },
{ 1.0f, 0.0f, 0.0f, 0.0f, },
{ 1.0f, 0.0f, 0.0f, 0.0f, },
{ 1.0f, 0.0f, 0.0f, 0.0f, },
{ 1.0f, 0.0f, 0.0f, 0.0f, },
{ 1.0f, 0.0f, 0.0f, 0.0f, },
{ 1.0f, 0.0f, 0.0f, 0.0f, },
{ 1.0f, 0.0f, 0.0f, 0.0f, },
{ 1.0f, 0.0f, 0.0f, 0.0f, },
{ 1.0f, 0.0f, 0.0f, 0.0f, },
{ 1.0f, 0.0f, 0.0f, 0.0f, },
{ 1.0f, 0.0f, 0.0f, 0.0f, },

                };


                static int indices[36] = {
                1,14,19,1,19,6,10,7,20,10,20,23,21,18,12,21,12,15,16,3,9,16,9,22,5,2,8,5,8,11,17,13,0,17,0,4,
                };

                Mesh geo_rigged_cube = {
                    .vertices = vertices,
                    .vertices_size = 24,
                    .normals = normals,
                    .normals_size = 24,
                    .indices = indices,
                    .indices_size = 36,
                    .uvs = uvs,
                    .uvs_size = 24,
                    .texture_file = "./assets/models/rigged_cube.png",
                    .bones = bones,
                    .bones_size = 24,
                    .weights = weights,
                    .weights_size = 24,
                };
