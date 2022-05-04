        #include "ArmatureAction.h"

                    static float Bone_parent_anim_keyframe_translation_timings[] = {
        0.041667f, 0.083333f, 0.125f, 0.16667f, 0.20833f, 0.25f, 0.29167f, 0.33333f, 0.375f, 0.41667f, 0.45833f, 0.5f, 0.54167f, 0.58333f, 0.625f, 0.66667f, 0.70833f, 0.75f, 0.79167f, 0.83333f, 0.875f, 0.91667f, 0.95833f, 1.0f, 1.0417f, 1.0833f, 1.125f, 1.1667f, 1.2083f, 1.25f, 1.2917f, 1.3333f, 1.375f, 1.4167f, 1.4583f, 1.5f, 1.5417f, 1.5833f, 1.625f, 1.6667f, 1.7083f, 1.75f, 1.7917f, 1.8333f, 1.875f, 1.9167f, 1.9583f, 2.0f, 2.0417f, 2.0833f, 2.125f, 2.1667f, 2.2083f, 2.25f, 2.2917f, 2.3333f, 2.375f, 2.4167f, 2.4583f, 2.5f
    };

    static Vec3 Bone_parent_anim_keyframe_translations[] = {
        { 0.0f, 0.0f, 0.0f }, { 4.2385e-05f, 2.456e-05f, 0.00093947f }, { 0.0001676f, 9.7119e-05f, 0.0037149f }, { 0.00037274f, 0.00021599f, 0.008262f }, { 0.00065491f, 0.00037949f, 0.014516f }, { 0.0010112f, 0.00058594f, 0.022413f }, { 0.0014387f, 0.00083365f, 0.031888f }, { 0.0019344f, 0.0011209f, 0.042877f }, { 0.0024956f, 0.0014461f, 0.055316f }, { 0.0031193f, 0.0018075f, 0.06914f }, { 0.0038025f, 0.0022034f, 0.084284f }, { 0.0045424f, 0.0026322f, 0.10068f }, { 0.0053361f, 0.0030921f, 0.11828f }, { 0.0061807f, 0.0035815f, 0.137f }, { 0.0070732f, 0.0040986f, 0.15678f }, { 0.0080107f, 0.0046419f, 0.17756f }, { 0.0089904f, 0.0052096f, 0.19928f }, { 0.010009f, 0.0058f, 0.22186f }, { 0.011065f, 0.0064115f, 0.24525f }, { 0.012153f, 0.0070424f, 0.26938f }, { 0.013272f, 0.0076909f, 0.29419f }, { 0.014419f, 0.0083555f, 0.31961f }, { 0.015591f, 0.0090343f, 0.34558f }, { 0.016784f, 0.0097258f, 0.37203f }, { 0.017996f, 0.010428f, 0.39889f }, { 0.019225f, 0.01114f, 0.42612f }, { 0.020466f, 0.011859f, 0.45363f }, { 0.021717f, 0.012584f, 0.48137f }, { 0.022976f, 0.013314f, 0.50927f }, { 0.024239f, 0.014046f, 0.53726f }, { 0.025504f, 0.014778f, 0.56529f }, { 0.026767f, 0.01551f, 0.59329f }, { 0.028025f, 0.01624f, 0.62119f }, { 0.029277f, 0.016965f, 0.64893f }, { 0.030518f, 0.017684f, 0.67644f }, { 0.031746f, 0.018396f, 0.70366f }, { 0.032958f, 0.019098f, 0.73053f }, { 0.034152f, 0.01979f, 0.75698f }, { 0.035323f, 0.020469f, 0.78295f }, { 0.03647f, 0.021133f, 0.80837f }, { 0.037589f, 0.021782f, 0.83318f }, { 0.038678f, 0.022412f, 0.85731f }, { 0.039733f, 0.023024f, 0.8807f }, { 0.040752f, 0.023614f, 0.90328f }, { 0.041732f, 0.024182f, 0.925f }, { 0.042669f, 0.024725f, 0.94578f }, { 0.043562f, 0.025242f, 0.96556f }, { 0.044406f, 0.025732f, 0.98428f }, { 0.0452f, 0.026192f, 1.0019f }, { 0.04594f, 0.026621f, 1.0183f }, { 0.046623f, 0.027016f, 1.0334f }, { 0.047247f, 0.027378f, 1.0472f }, { 0.047808f, 0.027703f, 1.0597f }, { 0.048304f, 0.02799f, 1.0707f }, { 0.048731f, 0.028238f, 1.0801f }, { 0.049088f, 0.028444f, 1.088f }, { 0.04937f, 0.028608f, 1.0943f }, { 0.049575f, 0.028727f, 1.0988f }, { 0.0497f, 0.028799f, 1.1016f }, { 0.049743f, 0.028824f, 1.1026f }
    };

                    static int Bone_parent_children_indices[] = {
            1
        };


    static AnimSkeletonBone Bone_parent = {
        .name = "Bone_parent",
        .index = 0,
        .inverse_bind = {
            .mtx = { 0.98298f, -0.048263f, 0.17728f, -0.0f, 0.18356f, 0.2157f, -0.95905f, 0.0f, 0.0080459f, 0.97527f, 0.22089f, -0.0f, -0.18356f, -0.2157f, 0.95905f, 1.0f }
        },

        .keyframe_size = 60,
        .anim_keyframe_translation_timings = Bone_parent_anim_keyframe_translation_timings,
        .anim_keyframe_translations = Bone_parent_anim_keyframe_translations,
        .children_indices = Bone_parent_children_indices,
        .children_size = 1,
    };

    static float Bone_001_anim_keyframe_translation_timings[] = {
        0.041667f, 2.5f
    };

    static Vec3 Bone_001_anim_keyframe_translations[] = {
        { 0.0f, 1.0f, 0.0f }, { 1.632e-08f, 1.0f, -1.0309e-07f }
    };



    static AnimSkeletonBone Bone_001 = {
        .name = "Bone_001",
        .index = 1,
        .inverse_bind = {
            .mtx = { 1.0f, -0.0f, 0.0f, -0.0f, -0.0f, 1.0f, -0.0f, 0.0f, 0.0f, -0.0f, 1.0f, -0.0f, -0.0f, 0.0f, -0.0f, 1.0f }
        },
                        .position = { .x = 0, .y = 1, .z = 0, },

        .keyframe_size = 2,
        .anim_keyframe_translation_timings = Bone_001_anim_keyframe_translation_timings,
        .anim_keyframe_translations = Bone_001_anim_keyframe_translations,
        .children_indices = NULL,
        .children_size = 0,
    };


                static Mat4 ArmatureAction_joint_transforms[2];
static AnimSkeletonBone *ArmatureAction_indexed_bones[] = { &Bone_parent, &Bone_001 };

SkeletonAnimation ArmatureAction = {
    .name = "ArmatureAction",
    .skeleton_name = "Armature",
    .indexed_bones = ArmatureAction_indexed_bones,
    .indexed_bones_size = 2,
    .joint_transforms = ArmatureAction_joint_transforms,
};

