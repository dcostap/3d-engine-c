        #include "Anim_0.h"

                    static float torso_joint_1_anim_keyframe_translation_timings[] = {
        0.0f, 1.25f
    };

    static Vec3 torso_joint_1_anim_keyframe_translations[] = {
        { 3.9762e-10f, -1.1506e-07f, 0.686f }, { 3.9762e-10f, -1.1506e-07f, 0.686f }
    };

                    static int torso_joint_1_children_indices[] = {
            1, 11, 15
        };


    static AnimSkeletonBone torso_joint_1 = {
        .name = "torso_joint_1",
        .index = 0,
        .inverse_bind = {
            .mtx = { 0.99401f, 0.10926f, -0.002538f, -0.0f, 0.00048377f, 0.018815f, 0.99982f, -0.0f, 0.10928f, -0.99382f, 0.018645f, -0.0f, 0.075537f, 0.040579f, -0.022803f, 1.0f }
        },
        .keyframe_size = 2,
        .anim_keyframe_translation_timings = torso_joint_1_anim_keyframe_translation_timings,
        .anim_keyframe_translations = torso_joint_1_anim_keyframe_translations,
        .children_indices = torso_joint_1_children_indices,
        .children_size = 3,
    };

    static float torso_joint_2_anim_keyframe_translation_timings[] = {
        0.0f, 1.25f
    };

    static Vec3 torso_joint_2_anim_keyframe_translations[] = {
        { 0.00099998f, 0.17149f, 3.6868e-09f }, { 0.00099998f, 0.17149f, 3.6868e-09f }
    };

                    static int torso_joint_2_children_indices[] = {
            2
        };


    static AnimSkeletonBone torso_joint_2 = {
        .name = "torso_joint_2",
        .index = 1,
        .inverse_bind = {
            .mtx = { -0.070512f, -0.76004f, 0.64604f, -0.0f, 0.78196f, -0.44422f, -0.43726f, 0.0f, 0.61932f, 0.47434f, 0.62564f, -0.0f, -0.76115f, 0.20657f, 0.6336f, 1.0f }
        },
        .keyframe_size = 2,
        .anim_keyframe_translation_timings = torso_joint_2_anim_keyframe_translation_timings,
        .anim_keyframe_translations = torso_joint_2_anim_keyframe_translations,
        .children_indices = torso_joint_2_children_indices,
        .children_size = 1,
    };

    static float torso_joint_3_anim_keyframe_translation_timings[] = {
        0.0f, 1.25f
    };

    static Vec3 torso_joint_3_anim_keyframe_translations[] = {
        { -5.0342e-14f, 0.21802f, -7.7114e-09f }, { -5.0342e-14f, 0.21802f, -7.7114e-09f }
    };

                    static int torso_joint_3_children_indices[] = {
            3, 5, 8
        };


    static AnimSkeletonBone torso_joint_3 = {
        .name = "torso_joint_3",
        .index = 2,
        .inverse_bind = {
            .mtx = { 0.10967f, -0.89152f, -0.4395f, -0.0f, -0.10048f, -0.44985f, 0.88743f, 0.0f, -0.98887f, -0.053163f, -0.13892f, -0.0f, 0.10768f, 0.40415f, -0.99317f, 1.0f }
        },
        .keyframe_size = 2,
        .anim_keyframe_translation_timings = torso_joint_3_anim_keyframe_translation_timings,
        .anim_keyframe_translations = torso_joint_3_anim_keyframe_translations,
        .children_indices = torso_joint_3_children_indices,
        .children_size = 3,
    };

    static float neck_joint_1_anim_keyframe_translation_timings[] = {
        0.0f, 1.25f
    };

    static Vec3 neck_joint_1_anim_keyframe_translations[] = {
        { -8.6098e-15f, 0.05256f, -3.4131e-09f }, { 4.6035e-15f, 0.052559f, 2.6834e-08f }
    };

                    static int neck_joint_1_children_indices[] = {
            4
        };


    static AnimSkeletonBone neck_joint_1 = {
        .name = "neck_joint_1",
        .index = 3,
        .inverse_bind = {
            .mtx = { 1.0f, 6.2166e-08f, 1.3088e-06f, -0.0f, 2.5974e-09f, 0.99991f, -0.01376f, 0.0f, -4.7828e-08f, 0.013759f, 0.9999f, -0.0f, 1.2446e-10f, -0.85674f, 0.024791f, 1.0f }
        },
        .keyframe_size = 2,
        .anim_keyframe_translation_timings = neck_joint_1_anim_keyframe_translation_timings,
        .anim_keyframe_translations = neck_joint_1_anim_keyframe_translations,
        .children_indices = neck_joint_1_children_indices,
        .children_size = 1,
    };

    static float neck_joint_2_anim_keyframe_translation_timings[] = {
        0.0f, 1.25f
    };

    static Vec3 neck_joint_2_anim_keyframe_translations[] = {
        { -1.3281e-13f, 0.066506f, 3.785e-08f }, { 1.8174e-15f, 0.066506f, -1.1976e-09f }
    };



    static AnimSkeletonBone neck_joint_2 = {
        .name = "neck_joint_2",
        .index = 4,
        .inverse_bind = {
            .mtx = { 0.99998f, -0.005831f, 6.9412e-08f, -0.0f, 0.0058143f, 0.99711f, 0.075804f, 0.0f, -0.00044082f, -0.075803f, 0.99711f, -0.0f, -0.0039886f, -0.68401f, -0.052002f, 1.0f }
        },
        .keyframe_size = 2,
        .anim_keyframe_translation_timings = neck_joint_2_anim_keyframe_translation_timings,
        .anim_keyframe_translations = neck_joint_2_anim_keyframe_translations,
        .children_indices = NULL,
        .children_size = 0,
    };

    static float arm_joint_L_1_anim_keyframe_translation_timings[] = {
        0.0f, 1.25f
    };

    static Vec3 arm_joint_L_1_anim_keyframe_translations[] = {
        { 0.088f, -0.00097993f, 0.00019985f }, { 0.088f, -0.00098002f, 0.00019986f }
    };

                    static int arm_joint_L_1_children_indices[] = {
            6
        };


    static AnimSkeletonBone arm_joint_L_1 = {
        .name = "arm_joint_L_1",
        .index = 5,
        .inverse_bind = {
            .mtx = { -1.0f, 4.1325e-08f, -1.4465e-06f, -0.0f, -1.4484e-10f, 0.99999f, -0.0036493f, 0.0f, 1.847e-07f, -0.0036499f, -0.99999f, -0.0f, -3.1094e-09f, -1.193f, 0.0053536f, 1.0f }
        },
        .keyframe_size = 2,
        .anim_keyframe_translation_timings = arm_joint_L_1_anim_keyframe_translation_timings,
        .anim_keyframe_translations = arm_joint_L_1_anim_keyframe_translations,
        .children_indices = arm_joint_L_1_children_indices,
        .children_size = 1,
    };

    static float arm_joint_L_2_anim_keyframe_translation_timings[] = {
        0.0f, 1.25f
    };

    static Vec3 arm_joint_L_2_anim_keyframe_translations[] = {
        { -3.4827e-08f, 0.24453f, 1.9704e-08f }, { -1.2002e-08f, 0.24453f, -4.2892e-08f }
    };

                    static int arm_joint_L_2_children_indices[] = {
            7
        };


    static AnimSkeletonBone arm_joint_L_2 = {
        .name = "arm_joint_L_2",
        .index = 6,
        .inverse_bind = {
            .mtx = { 1.0f, 5.5894e-08f, 1.295e-06f, -0.0f, 5.9312e-10f, 0.99997f, -0.0075185f, 0.0f, -3.3706e-08f, 0.0075179f, 0.99996f, -0.0f, 2.5746e-09f, -1.1265f, 0.0079697f, 1.0f }
        },
        .keyframe_size = 2,
        .anim_keyframe_translation_timings = arm_joint_L_2_anim_keyframe_translation_timings,
        .anim_keyframe_translations = arm_joint_L_2_anim_keyframe_translations,
        .children_indices = arm_joint_L_2_children_indices,
        .children_size = 1,
    };

    static float arm_joint_L_3_anim_keyframe_translation_timings[] = {
        0.0f, 1.25f
    };

    static Vec3 arm_joint_L_3_anim_keyframe_translations[] = {
        { -2.5849e-08f, 0.18552f, -4.0212e-08f }, { -3.7431e-08f, 0.18552f, -4.2965e-08f }
    };



    static AnimSkeletonBone arm_joint_L_3 = {
        .name = "arm_joint_L_3",
        .index = 7,
        .inverse_bind = {
            .mtx = { 1.0f, 3.0107e-07f, 6.9455e-07f, -0.0f, -1.095e-07f, 0.97984f, -0.19977f, 0.0f, 5.2099e-07f, 0.19977f, 0.97983f, -0.0f, 1.2632e-07f, -1.0513f, 0.22455f, 1.0f }
        },
        .keyframe_size = 2,
        .anim_keyframe_translation_timings = arm_joint_L_3_anim_keyframe_translation_timings,
        .anim_keyframe_translations = arm_joint_L_3_anim_keyframe_translations,
        .children_indices = NULL,
        .children_size = 0,
    };

    static float arm_joint_R_1_anim_keyframe_translation_timings[] = {
        0.0f, 1.25f
    };

    static Vec3 arm_joint_R_1_anim_keyframe_translations[] = {
        { -0.088f, -0.00098018f, 0.00019977f }, { -0.088f, -0.00098016f, 0.00019976f }
    };

                    static int arm_joint_R_1_children_indices[] = {
            9
        };


    static AnimSkeletonBone arm_joint_R_1 = {
        .name = "arm_joint_R_1",
        .index = 8,
        .inverse_bind = {
            .mtx = { 0.63143f, 0.64929f, -0.42394f, -0.0f, -0.0041896f, -0.54385f, -0.83917f, 0.0f, -0.77541f, 0.53165f, -0.34068f, -0.0f, -0.22815f, 0.15466f, 0.95145f, 1.0f }
        },
        .keyframe_size = 2,
        .anim_keyframe_translation_timings = arm_joint_R_1_anim_keyframe_translation_timings,
        .anim_keyframe_translations = arm_joint_R_1_anim_keyframe_translations,
        .children_indices = arm_joint_R_1_children_indices,
        .children_size = 1,
    };

    static float arm_joint_R_2_anim_keyframe_translation_timings[] = {
        0.0f, 1.25f
    };

    static Vec3 arm_joint_R_2_anim_keyframe_translations[] = {
        { -2.4802e-08f, 0.24453f, -5.3369e-08f }, { 1.2859e-08f, 0.24453f, -5.9385e-08f }
    };

                    static int arm_joint_R_2_children_indices[] = {
            10
        };


    static AnimSkeletonBone arm_joint_R_2 = {
        .name = "arm_joint_R_2",
        .index = 9,
        .inverse_bind = {
            .mtx = { 0.53019f, 0.76004f, -0.37581f, -0.0f, 0.001753f, -0.44422f, -0.89592f, 0.0f, -0.84787f, 0.47435f, -0.23685f, -0.0f, -0.18343f, 0.20656f, 0.97321f, 1.0f }
        },
        .keyframe_size = 2,
        .anim_keyframe_translation_timings = arm_joint_R_2_anim_keyframe_translation_timings,
        .anim_keyframe_translations = arm_joint_R_2_anim_keyframe_translations,
        .children_indices = arm_joint_R_2_children_indices,
        .children_size = 1,
    };

    static float arm_joint_R_3_anim_keyframe_translation_timings[] = {
        0.0f, 1.25f
    };

    static Vec3 arm_joint_R_3_anim_keyframe_translations[] = {
        { -8.8265e-08f, 0.18552f, 6.9749e-08f }, { -1.6912e-08f, 0.18552f, 1.4479e-07f }
    };



    static AnimSkeletonBone arm_joint_R_3 = {
        .name = "arm_joint_R_3",
        .index = 10,
        .inverse_bind = {
            .mtx = { -0.062387f, 0.89152f, -0.44867f, -0.0f, -0.0056899f, -0.44985f, -0.89308f, 0.0f, -0.99803f, -0.053162f, 0.033137f, -0.0f, 0.0016208f, 0.40416f, 0.99899f, 1.0f }
        },
        .keyframe_size = 2,
        .anim_keyframe_translation_timings = arm_joint_R_3_anim_keyframe_translation_timings,
        .anim_keyframe_translations = arm_joint_R_3_anim_keyframe_translations,
        .children_indices = NULL,
        .children_size = 0,
    };

    static float leg_joint_L_1_anim_keyframe_translation_timings[] = {
        0.0f, 1.25f
    };

    static Vec3 leg_joint_L_1_anim_keyframe_translations[] = {
        { 0.067619f, -0.072264f, -0.0044608f }, { 0.067619f, -0.072264f, -0.0044608f }
    };

                    static int leg_joint_L_1_children_indices[] = {
            12
        };


    static AnimSkeletonBone leg_joint_L_1 = {
        .name = "leg_joint_L_1",
        .index = 11,
        .inverse_bind = {
            .mtx = { -0.99933f, -0.028713f, -0.022849f, 0.0f, 2.9616e-07f, -0.62264f, 0.78251f, 0.0f, -0.03669f, 0.78197f, 0.62221f, -0.0f, 0.078368f, 0.056742f, -0.063475f, 1.0f }
        },
        .keyframe_size = 2,
        .anim_keyframe_translation_timings = leg_joint_L_1_anim_keyframe_translation_timings,
        .anim_keyframe_translations = leg_joint_L_1_anim_keyframe_translations,
        .children_indices = leg_joint_L_1_children_indices,
        .children_size = 1,
    };

    static float leg_joint_L_2_anim_keyframe_translation_timings[] = {
        0.0f, 1.25f
    };

    static Vec3 leg_joint_L_2_anim_keyframe_translations[] = {
        { 1.1592e-08f, 0.26611f, 1.0707e-08f }, { 1.1592e-08f, 0.26611f, 1.0707e-08f }
    };

                    static int leg_joint_L_2_children_indices[] = {
            13
        };


    static AnimSkeletonBone leg_joint_L_2 = {
        .name = "leg_joint_L_2",
        .index = 12,
        .inverse_bind = {
            .mtx = { -0.99973f, 0.0051311f, -0.022647f, -0.0f, -7.9751e-05f, -0.97605f, -0.21754f, 0.0f, -0.023215f, -0.21747f, 0.97577f, -0.0f, 0.078434f, 0.35795f, 0.02222f, 1.0f }
        },
        .keyframe_size = 2,
        .anim_keyframe_translation_timings = leg_joint_L_2_anim_keyframe_translation_timings,
        .anim_keyframe_translations = leg_joint_L_2_anim_keyframe_translations,
        .children_indices = leg_joint_L_2_children_indices,
        .children_size = 1,
    };

    static float leg_joint_L_3_anim_keyframe_translation_timings[] = {
        0.0f, 1.25f
    };

    static Vec3 leg_joint_L_3_anim_keyframe_translations[] = {
        { 1.0062e-08f, 0.27582f, -3.0135e-09f }, { 1.0062e-08f, 0.27582f, -3.0135e-09f }
    };

                    static int leg_joint_L_3_children_indices[] = {
            14
        };


    static AnimSkeletonBone leg_joint_L_3 = {
        .name = "leg_joint_L_3",
        .index = 13,
        .inverse_bind = {
            .mtx = { -0.83047f, 0.033974f, 0.55603f, -0.0f, 0.091635f, -0.97621f, 0.19651f, -0.0f, 0.54947f, 0.21415f, 0.80758f, -0.0f, -0.0003084f, 0.59687f, -0.15929f, 1.0f }
        },
        .keyframe_size = 2,
        .anim_keyframe_translation_timings = leg_joint_L_3_anim_keyframe_translation_timings,
        .anim_keyframe_translations = leg_joint_L_3_anim_keyframe_translations,
        .children_indices = leg_joint_L_3_children_indices,
        .children_size = 1,
    };

    static float leg_joint_L_5_anim_keyframe_translation_timings[] = {
        0.0f, 1.25f
    };

    static Vec3 leg_joint_L_5_anim_keyframe_translations[] = {
        { -0.0023465f, 0.066173f, -0.027856f }, { -0.0023465f, 0.066173f, -0.027856f }
    };



    static AnimSkeletonBone leg_joint_L_5 = {
        .name = "leg_joint_L_5",
        .index = 14,
        .inverse_bind = {
            .mtx = { 0.11138f, -0.64928f, 0.75235f, -0.0f, 0.62352f, -0.54385f, -0.56165f, 0.0f, 0.77383f, 0.53165f, 0.34427f, -0.0f, -0.5502f, 0.15466f, 0.80907f, 1.0f }
        },
        .keyframe_size = 2,
        .anim_keyframe_translation_timings = leg_joint_L_5_anim_keyframe_translation_timings,
        .anim_keyframe_translations = leg_joint_L_5_anim_keyframe_translations,
        .children_indices = NULL,
        .children_size = 0,
    };

    static float leg_joint_R_1_anim_keyframe_translation_timings[] = {
        0.0f, 1.25f
    };

    static Vec3 leg_joint_R_1_anim_keyframe_translations[] = {
        { -0.068457f, -0.071471f, -0.0044608f }, { -0.068457f, -0.071471f, -0.0044608f }
    };

                    static int leg_joint_R_1_children_indices[] = {
            16
        };


    static AnimSkeletonBone leg_joint_R_1 = {
        .name = "leg_joint_R_1",
        .index = 15,
        .inverse_bind = {
            .mtx = { -0.99933f, -0.028741f, 0.022843f, -0.0f, 0.035765f, -0.62161f, 0.78251f, -0.0f, -0.0082892f, 0.78279f, 0.62221f, -0.0f, -0.081498f, 0.052146f, -0.063475f, 1.0f }
        },
        .keyframe_size = 2,
        .anim_keyframe_translation_timings = leg_joint_R_1_anim_keyframe_translation_timings,
        .anim_keyframe_translations = leg_joint_R_1_anim_keyframe_translations,
        .children_indices = leg_joint_R_1_children_indices,
        .children_size = 1,
    };

    static float leg_joint_R_2_anim_keyframe_translation_timings[] = {
        0.0f, 1.25f
    };

    static Vec3 leg_joint_R_2_anim_keyframe_translations[] = {
        { 1.2039e-08f, 0.26611f, 7.1801e-09f }, { 1.2039e-08f, 0.26611f, 7.1801e-09f }
    };

                    static int leg_joint_R_2_children_indices[] = {
            17
        };


    static AnimSkeletonBone leg_joint_R_2 = {
        .name = "leg_joint_R_2",
        .index = 16,
        .inverse_bind = {
            .mtx = { -0.99817f, -0.0051276f, 0.060232f, -0.0f, -0.0081032f, -0.97605f, -0.21739f, 0.0f, 0.059905f, -0.21747f, 0.97421f, -0.0f, -0.077542f, 0.35795f, 0.025154f, 1.0f }
        },
        .keyframe_size = 2,
        .anim_keyframe_translation_timings = leg_joint_R_2_anim_keyframe_translation_timings,
        .anim_keyframe_translations = leg_joint_R_2_anim_keyframe_translations,
        .children_indices = leg_joint_R_2_children_indices,
        .children_size = 1,
    };

    static float leg_joint_R_3_anim_keyframe_translation_timings[] = {
        0.0f, 1.25f
    };

    static Vec3 leg_joint_R_3_anim_keyframe_translations[] = {
        { 3.6277e-09f, 0.27582f, 4.7626e-09f }, { 3.6277e-09f, 0.27582f, 4.7626e-09f }
    };

                    static int leg_joint_R_3_children_indices[] = {
            18
        };


    static AnimSkeletonBone leg_joint_R_3 = {
        .name = "leg_joint_R_3",
        .index = 17,
        .inverse_bind = {
            .mtx = { -0.99469f, -0.033973f, -0.097161f, -0.0f, 0.012197f, -0.97621f, 0.21648f, 0.0f, -0.1022f, 0.21414f, 0.97143f, -0.0f, -0.075065f, 0.59687f, -0.1405f, 1.0f }
        },
        .keyframe_size = 2,
        .anim_keyframe_translation_timings = leg_joint_R_3_anim_keyframe_translation_timings,
        .anim_keyframe_translations = leg_joint_R_3_anim_keyframe_translations,
        .children_indices = leg_joint_R_3_children_indices,
        .children_size = 1,
    };

    static float leg_joint_R_5_anim_keyframe_translation_timings[] = {
        0.0f, 1.25f
    };

    static Vec3 leg_joint_R_5_anim_keyframe_translations[] = {
        { -0.0014585f, 0.066199f, -0.027857f }, { -0.0014585f, 0.066199f, -0.027857f }
    };



    static AnimSkeletonBone leg_joint_R_5 = {
        .name = "leg_joint_R_5",
        .index = 18,
        .inverse_bind = {
            .mtx = { 0.99401f, -0.10925f, 0.0016388f, -0.0f, 0.00041779f, 0.018816f, 0.99982f, -0.0f, -0.10926f, -0.99382f, 0.018744f, -0.0f, -0.075558f, 0.040579f, -0.022735f, 1.0f }
        },
        .keyframe_size = 2,
        .anim_keyframe_translation_timings = leg_joint_R_5_anim_keyframe_translation_timings,
        .anim_keyframe_translations = leg_joint_R_5_anim_keyframe_translations,
        .children_indices = NULL,
        .children_size = 0,
    };


                static Mat4 Anim_0_joint_transforms[19];
static AnimSkeletonBone *Anim_0_indexed_bones[] = { &torso_joint_1, &torso_joint_2, &torso_joint_3, &neck_joint_1, &neck_joint_2, &arm_joint_L_1, &arm_joint_L_2, &arm_joint_L_3, &arm_joint_R_1, &arm_joint_R_2, &arm_joint_R_3, &leg_joint_L_1, &leg_joint_L_2, &leg_joint_L_3, &leg_joint_L_5, &leg_joint_R_1, &leg_joint_R_2, &leg_joint_R_3, &leg_joint_R_5 };

SkeletonAnimation Anim_0 = {
    .name = "Anim_0",
    .skeleton_name = "Armature",
    .indexed_bones = Anim_0_indexed_bones,
    .indexed_bones_size = 19,
    .joint_transforms = Anim_0_joint_transforms,
};

