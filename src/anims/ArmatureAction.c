        #include "ArmatureAction.h"

                    static float Bone_parent_anim_keyframe_translation_timings[] = {
        0.041667f, 0.083333f, 0.125f, 0.16667f, 0.20833f, 0.25f, 0.29167f, 0.33333f, 0.375f, 0.41667f, 0.45833f, 0.5f, 0.54167f, 0.58333f, 0.625f, 0.66667f, 0.70833f, 0.75f, 0.79167f, 0.83333f, 0.875f, 0.91667f, 0.95833f, 1.0f, 1.0417f, 1.0833f, 1.125f, 1.1667f, 1.2083f, 1.25f, 1.2917f, 1.3333f, 1.375f, 1.4167f, 1.4583f, 1.5f, 1.5417f, 1.5833f, 1.625f, 1.6667f, 1.7083f, 1.75f, 1.7917f, 1.8333f, 1.875f, 1.9167f, 1.9583f, 2.0f, 2.0417f, 2.0833f, 2.125f, 2.1667f, 2.2083f, 2.25f, 2.2917f, 2.3333f, 2.375f, 2.4167f, 2.4583f, 2.5f
    };

    static Vec3 Bone_parent_anim_keyframe_translations[] = {
        { 0.0f, 0.0f, 0.0f }, { 4.2385e-05f, 0.0013923f, 0.00093947f }, { 0.0001676f, 0.0055056f, 0.0037149f }, { 0.00037274f, 0.012244f, 0.008262f }, { 0.00065491f, 0.021513f, 0.014516f }, { 0.0010112f, 0.033217f, 0.022413f }, { 0.0014387f, 0.047259f, 0.031888f }, { 0.0019344f, 0.063545f, 0.042877f }, { 0.0024956f, 0.08198f, 0.055316f }, { 0.0031193f, 0.10247f, 0.06914f }, { 0.0038025f, 0.12491f, 0.084284f }, { 0.0045424f, 0.14922f, 0.10068f }, { 0.0053361f, 0.17529f, 0.11828f }, { 0.0061807f, 0.20303f, 0.137f }, { 0.0070732f, 0.23235f, 0.15678f }, { 0.0080107f, 0.26315f, 0.17756f }, { 0.0089904f, 0.29533f, 0.19928f }, { 0.010009f, 0.3288f, 0.22186f }, { 0.011065f, 0.36347f, 0.24525f }, { 0.012153f, 0.39923f, 0.26938f }, { 0.013272f, 0.43599f, 0.29419f }, { 0.014419f, 0.47367f, 0.31961f }, { 0.015591f, 0.51215f, 0.34558f }, { 0.016784f, 0.55135f, 0.37203f }, { 0.017996f, 0.59117f, 0.39889f }, { 0.019225f, 0.63152f, 0.42612f }, { 0.020466f, 0.67229f, 0.45363f }, { 0.021717f, 0.7134f, 0.48137f }, { 0.022976f, 0.75475f, 0.50927f }, { 0.024239f, 0.79624f, 0.53726f }, { 0.025504f, 0.83778f, 0.56529f }, { 0.026767f, 0.87927f, 0.59329f }, { 0.028025f, 0.92062f, 0.62119f }, { 0.029277f, 0.96173f, 0.64893f }, { 0.030518f, 1.0025f, 0.67644f }, { 0.031746f, 1.0428f, 0.70366f }, { 0.032958f, 1.0827f, 0.73053f }, { 0.034152f, 1.1219f, 0.75698f }, { 0.035323f, 1.1603f, 0.78295f }, { 0.03647f, 1.198f, 0.80837f }, { 0.037589f, 1.2348f, 0.83318f }, { 0.038678f, 1.2705f, 0.85731f }, { 0.039733f, 1.3052f, 0.8807f }, { 0.040752f, 1.3387f, 0.90328f }, { 0.041732f, 1.3709f, 0.925f }, { 0.042669f, 1.4017f, 0.94578f }, { 0.043562f, 1.431f, 0.96556f }, { 0.044406f, 1.4587f, 0.98428f }, { 0.0452f, 1.4848f, 1.0019f }, { 0.04594f, 1.5091f, 1.0183f }, { 0.046623f, 1.5315f, 1.0334f }, { 0.047247f, 1.552f, 1.0472f }, { 0.047808f, 1.5705f, 1.0597f }, { 0.048304f, 1.5868f, 1.0707f }, { 0.048731f, 1.6008f, 1.0801f }, { 0.049088f, 1.6125f, 1.088f }, { 0.04937f, 1.6218f, 1.0943f }, { 0.049575f, 1.6285f, 1.0988f }, { 0.0497f, 1.6326f, 1.1016f }, { 0.049743f, 1.634f, 1.1026f }
    };

    static float Bone_parent_anim_keyframe_rotation_timings[] = {
        0.041667f, 2.5f
    };

    static Quaternion Bone_parent_anim_keyframe_rotations[] = {
        { 0.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f, 1.0f }
    };

    static float Bone_parent_anim_keyframe_scale_timings[] = {
        0.041667f, 2.5f
    };

    static Vec3 Bone_parent_anim_keyframe_scales[] = {
        { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }
    };

                    static int Bone_parent_children_indices[] = {
            1
        };


    static AnimSkeletonBone Bone_parent = {
        .name = "Bone_parent",
        .index = 0,
        .inverse_bind = {
            .mtx = { 1.0f, -0.0f, 0.0f, -0.0f, -0.0f, 1.0f, -0.0f, 0.0f, 0.0f, -0.0f, 1.0f, -0.0f, -0.0f, 0.0f, -0.0f, 1.0f }
        },



        .keyframe_translation_size = 60,
        .anim_keyframe_translation_timings = Bone_parent_anim_keyframe_translation_timings,
        .anim_keyframe_translations = Bone_parent_anim_keyframe_translations,
        .keyframe_rotation_size = 2,
        .anim_keyframe_rotation_timings = Bone_parent_anim_keyframe_rotation_timings,
        .anim_keyframe_rotations = Bone_parent_anim_keyframe_rotations,
        .keyframe_scale_size = 2,
        .anim_keyframe_scale_timings = Bone_parent_anim_keyframe_scale_timings,
        .anim_keyframe_scales = Bone_parent_anim_keyframe_scales,
        .children_indices = Bone_parent_children_indices,
        .children_size = 1,
    };

    static float Bone_001_anim_keyframe_translation_timings[] = {
        0.041667f, 2.5f
    };

    static Vec3 Bone_001_anim_keyframe_translations[] = {
        { 0.0f, 1.0f, 0.0f }, { 1.0086e-07f, 1.0f, 5.3144e-08f }
    };

    static float Bone_001_anim_keyframe_rotation_timings[] = {

    };

    static Quaternion Bone_001_anim_keyframe_rotations[] = {

    };

    static float Bone_001_anim_keyframe_scale_timings[] = {

    };

    static Vec3 Bone_001_anim_keyframe_scales[] = {

    };



    static AnimSkeletonBone Bone_001 = {
        .name = "Bone_001",
        .index = 1,
        .inverse_bind = {
            .mtx = { 0.98298f, -0.048263f, 0.17728f, -0.0f, 0.18356f, 0.2157f, -0.95905f, 0.0f, 0.0080459f, 0.97527f, 0.22089f, -0.0f, -0.18356f, -0.2157f, 0.95905f, 1.0f }
        },
                        .bind_position = { .x = 0, .y = 1, .z = 0, },

                        .bind_scale = { .x = 1, .y = 0.9999999403953552, .z = 1, },

                        .bind_rotation = { .x = 0.6217679381370544, .y = 0.054399967193603516, .z = 0.07451723515987396, .w = 0.7777483463287354, },

        .keyframe_translation_size = 2,
        .anim_keyframe_translation_timings = Bone_001_anim_keyframe_translation_timings,
        .anim_keyframe_translations = Bone_001_anim_keyframe_translations,
        .keyframe_rotation_size = 0,
        .anim_keyframe_rotation_timings = Bone_001_anim_keyframe_rotation_timings,
        .anim_keyframe_rotations = Bone_001_anim_keyframe_rotations,
        .keyframe_scale_size = 0,
        .anim_keyframe_scale_timings = Bone_001_anim_keyframe_scale_timings,
        .anim_keyframe_scales = Bone_001_anim_keyframe_scales,
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

