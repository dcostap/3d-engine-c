        #include "walk_final.h"

                    static float root_anim_keyframe_translation_timings[] = {
        -0.041667f, 0.0f, 0.041667f, 0.083333f, 0.125f, 0.16667f, 0.20833f, 0.25f, 0.29167f, 0.33333f, 0.375f, 0.41667f, 0.45833f, 0.5f, 0.54167f, 0.58333f, 0.625f, 0.66667f, 0.70833f, 0.75f, 0.79167f, 0.83333f, 0.875f, 0.91667f, 0.95833f, 1.0f, 1.0417f
    };

    static Vec3 root_anim_keyframe_translations[] = {
        { 0.0013558f, 0.86375f, -0.055348f }, { 0.0012981f, 0.9008f, -0.051221f }, { 0.0011974f, 0.98355f, -0.044009f }, { 0.0010982f, 1.0885f, -0.036901f }, { 0.0010104f, 1.1989f, -0.030614f }, { 0.00098544f, 1.2758f, -0.028831f }, { 0.0011205f, 1.2509f, -0.038505f }, { 0.0012756f, 1.1953f, -0.049612f }, { 0.0013205f, 1.1256f, -0.055262f }, { 0.0012871f, 1.0516f, -0.058602f }, { 0.0012069f, 0.98137f, -0.060255f }, { 0.0010989f, 0.92186f, -0.060491f }, { 0.00097737f, 0.8801f, -0.059407f }, { 0.00085439f, 0.86394f, -0.057f }, { 0.0007069f, 0.90617f, -0.050623f }, { 0.0005178f, 1.0076f, -0.041621f }, { 0.00030835f, 1.1289f, -0.033836f }, { 0.00013754f, 1.2309f, -0.029932f }, { 6.4328e-05f, 1.2742f, -0.032571f }, { 9.6558e-05f, 1.2522f, -0.040752f }, { 0.00018665f, 1.1942f, -0.049509f }, { 0.00035951f, 1.1143f, -0.056119f }, { 0.00061685f, 1.0268f, -0.060124f }, { 0.00089977f, 0.94632f, -0.061635f }, { 0.0011494f, 0.88723f, -0.060762f }, { 0.0013069f, 0.86401f, -0.057614f }, { 0.0013558f, 0.86375f, -0.055348f }
    };

    static float root_anim_keyframe_rotation_timings[] = {
        -0.041667f, 0.0f, 0.041667f, 0.083333f, 0.125f, 0.16667f, 0.20833f, 0.25f, 0.29167f, 0.33333f, 0.375f, 0.41667f, 0.45833f, 0.5f, 0.54167f, 0.58333f, 0.625f, 0.66667f, 0.70833f, 0.75f, 0.79167f, 0.83333f, 0.875f, 0.91667f, 0.95833f, 1.0f, 1.0417f
    };

    static Quaternion root_anim_keyframe_rotations[] = {
        { 0.0052506f, 0.00043184f, -0.038725f, 0.99924f }, { 0.0052506f, 0.00043184f, -0.038725f, 0.99924f }, { 0.008477f, 0.00040413f, -0.036191f, 0.99931f }, { 0.015859f, 0.00034072f, -0.030391f, 0.99941f }, { 0.025539f, 0.0002575f, -0.022779f, 0.99941f }, { 0.036453f, 0.00016358f, -0.01419f, 0.99923f }, { 0.047537f, 6.8111e-05f, -0.0054582f, 0.99885f }, { 0.055442f, -3.4567e-08f, 0.00077418f, 0.99846f }, { 0.052038f, -3.4658e-05f, 0.0034581f, 0.99864f }, { 0.044164f, -0.00011472f, 0.009664f, 0.99898f }, { 0.034236f, -0.00021558f, 0.017482f, 0.99926f }, { 0.023946f, -0.00032003f, 0.025579f, 0.99939f }, { 0.014712f, -0.00041367f, 0.032837f, 0.99935f }, { 0.0079392f, -0.0004823f, 0.038157f, 0.99924f }, { 0.005248f, -0.00050957f, 0.04027f, 0.99917f }, { 0.0089668f, -0.00048821f, 0.038719f, 0.99921f }, { 0.018266f, -0.00042987f, 0.034428f, 0.99924f }, { 0.030355f, -0.00034317f, 0.027937f, 0.99915f }, { 0.042439f, -0.0002368f, 0.019796f, 0.9989f }, { 0.051728f, -0.00011951f, 0.010558f, 0.99861f }, { 0.055442f, -3.4565e-08f, 0.00077418f, 0.99846f }, { 0.051729f, 0.00011369f, -0.0090097f, 0.99862f }, { 0.042441f, 0.00021659f, -0.018248f, 0.99893f }, { 0.030357f, 0.00030426f, -0.02639f, 0.99919f }, { 0.018268f, 0.00037227f, -0.032881f, 0.99929f }, { 0.0089693f, 0.00041623f, -0.037174f, 0.99927f }, { 0.0052506f, 0.00043184f, -0.038725f, 0.99924f }
    };

    static float root_anim_keyframe_scale_timings[] = {
        -0.041667f, 0.0f, 0.041667f, 0.083333f, 0.125f, 0.16667f, 0.20833f, 0.25f, 0.29167f, 0.33333f, 0.375f, 0.41667f, 0.45833f, 0.5f, 0.54167f, 0.58333f, 0.625f, 0.66667f, 0.70833f, 0.75f, 0.79167f, 0.83333f, 0.875f, 0.91667f, 0.95833f, 1.0f, 1.0417f
    };

    static Vec3 root_anim_keyframe_scales[] = {
        { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.99804f, 1.0012f, 0.99987f }, { 0.99353f, 1.0041f, 0.99958f }, { 0.9876f, 1.0078f, 0.9992f }, { 0.98096f, 1.0119f, 0.99877f }, { 0.97433f, 1.0161f, 0.99834f }, { 0.96987f, 1.0189f, 0.99805f }, { 0.9716f, 1.0178f, 0.99817f }, { 0.97599f, 1.0151f, 0.99845f }, { 0.9819f, 1.0114f, 0.99883f }, { 0.98827f, 1.0074f, 0.99924f }, { 0.99408f, 1.0037f, 0.99962f }, { 0.99834f, 1.001f, 0.99989f }, { 1.0f, 1.0f, 1.0f }, { 0.99575f, 1.0027f, 0.99973f }, { 0.98659f, 1.0084f, 0.99913f }, { 0.97626f, 1.0149f, 0.99847f }, { 0.96987f, 1.0189f, 0.99805f }, { 0.97386f, 1.0164f, 0.99831f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }
    };

                    static int root_children_indices[] = {
            1, 10, 13
        };


    static AnimSkeletonBone root = {
        .name = "root",
        .index = 0,
        .inverse_bind = {
            .mtx = { 1.0f, -0.001546f, 8.5774e-05f, -0.0f, 0.001546f, 0.99385f, -0.11071f, 0.0f, 8.5912e-05f, 0.11071f, 0.99385f, -0.0f, -0.0023949f, -1.0397f, 0.17151f, 1.0f }
        },
                        .bind_position = { .x = 0.0012981431791558862, .y = 0.9008029103279114, .z = -0.051221270114183426, },

                        .bind_scale = { .x = 0.9999999403953552, .y = 0.9999999403953552, .z = 1, },

                        .bind_rotation = { .x = 0.005250636022537947, .y = 0.0004318371065892279, .z = -0.03872477635741234, .w = 0.9992360472679138, },

        .keyframe_translation_size = 27,
        .anim_keyframe_translation_timings = root_anim_keyframe_translation_timings,
        .anim_keyframe_translations = root_anim_keyframe_translations,
        .keyframe_rotation_size = 27,
        .anim_keyframe_rotation_timings = root_anim_keyframe_rotation_timings,
        .anim_keyframe_rotations = root_anim_keyframe_rotations,
        .keyframe_scale_size = 27,
        .anim_keyframe_scale_timings = root_anim_keyframe_scale_timings,
        .anim_keyframe_scales = root_anim_keyframe_scales,
        .children_indices = root_children_indices,
        .children_size = 3,
    };

    static float body_anim_keyframe_translation_timings[] = {
        -0.041667f, 1.0417f
    };

    static Vec3 body_anim_keyframe_translations[] = {
        { 7.9621e-09f, 0.49993f, -9.5896e-09f }, { 7.9621e-09f, 0.49993f, -9.5896e-09f }
    };

    static float body_anim_keyframe_rotation_timings[] = {
        -0.041667f, 0.0f, 0.041667f, 0.083333f, 0.125f, 0.16667f, 0.20833f, 0.25f, 0.29167f, 0.33333f, 0.375f, 0.41667f, 0.45833f, 0.5f, 0.54167f, 0.58333f, 0.625f, 0.66667f, 0.70833f, 0.75f, 0.79167f, 0.83333f, 0.875f, 0.91667f, 0.95833f, 1.0f, 1.0417f
    };

    static Quaternion body_anim_keyframe_rotations[] = {
        { 0.023468f, 0.73275f, 0.027315f, 0.67955f }, { 0.023468f, 0.73275f, 0.027315f, 0.67955f }, { 0.01865f, 0.73231f, 0.019341f, 0.68044f }, { 0.0076044f, 0.73107f, 0.0010613f, 0.68226f }, { -0.0069118f, 0.72893f, -0.022953f, 0.68417f }, { -0.023288f, 0.72581f, -0.050033f, 0.68567f }, { -0.03989f, 0.7219f, -0.077475f, 0.68649f }, { -0.051689f, 0.71865f, -0.096971f, 0.68663f }, { -0.047789f, 0.7179f, -0.091426f, 0.68846f }, { -0.038822f, 0.71602f, -0.078513f, 0.69256f }, { -0.027632f, 0.71339f, -0.062071f, 0.69746f }, { -0.016232f, 0.71036f, -0.044797f, 0.70222f }, { -0.0063329f, 0.70739f, -0.028956f, 0.7062f }, { 0.00036187f, 0.70508f, -0.016773f, 0.70893f }, { 0.0018845f, 0.7042f, -0.010783f, 0.70992f }, { -0.005588f, 0.70427f, -0.015154f, 0.70975f }, { -0.021445f, 0.70419f, -0.028967f, 0.7091f }, { -0.041389f, 0.70387f, -0.047602f, 0.70752f }, { -0.06109f, 0.70356f, -0.066409f, 0.70488f }, { -0.076248f, 0.70396f, -0.080777f, 0.7015f }, { -0.082644f, 0.70606f, -0.086171f, 0.69801f }, { -0.075273f, 0.71094f, -0.077413f, 0.69492f }, { -0.055804f, 0.71762f, -0.056341f, 0.6919f }, { -0.030127f, 0.72412f, -0.029053f, 0.6884f }, { -0.0043127f, 0.72902f, -0.0018312f, 0.68447f }, { 0.015541f, 0.73185f, 0.019014f, 0.68103f }, { 0.023468f, 0.73275f, 0.027315f, 0.67955f }
    };

    static float body_anim_keyframe_scale_timings[] = {
        -0.041667f, 1.0417f
    };

    static Vec3 body_anim_keyframe_scales[] = {
        { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }
    };

                    static int body_children_indices[] = {
            2, 5, 7
        };


    static AnimSkeletonBone body = {
        .name = "body",
        .index = 1,
        .inverse_bind = {
            .mtx = { -0.012709f, -3.778e-09f, 0.99992f, -0.0f, -7.4671e-09f, 1.0f, 1.2513e-09f, 0.0f, -0.99992f, -1.4152e-07f, -0.012709f, 0.0f, 7.8425e-09f, -1.5491f, -1.9857e-09f, 1.0f }
        },
                        .bind_position = { .x = 7.498178966613978e-09, .y = 0.49993014335632324, .z = 9.402103096078918e-09, },

                        .bind_scale = { .x = 0.9999999403953552, .y = 1.000000238418579, .z = 1.000000238418579, },

                        .bind_rotation = { .x = 0.023468157276511192, .y = 0.7327451705932617, .z = 0.027315320447087288, .w = 0.6795496344566345, },

        .keyframe_translation_size = 2,
        .anim_keyframe_translation_timings = body_anim_keyframe_translation_timings,
        .anim_keyframe_translations = body_anim_keyframe_translations,
        .keyframe_rotation_size = 27,
        .anim_keyframe_rotation_timings = body_anim_keyframe_rotation_timings,
        .anim_keyframe_rotations = body_anim_keyframe_rotations,
        .keyframe_scale_size = 2,
        .anim_keyframe_scale_timings = body_anim_keyframe_scale_timings,
        .anim_keyframe_scales = body_anim_keyframe_scales,
        .children_indices = body_children_indices,
        .children_size = 3,
    };

    static float arm_up_R_anim_keyframe_translation_timings[] = {
        -0.041667f, 0.0f, 0.041667f, 0.083333f, 0.125f, 0.16667f, 0.20833f, 0.25f, 0.29167f, 0.33333f, 0.375f, 0.41667f, 0.45833f, 0.5f, 0.54167f, 0.58333f, 0.625f, 0.66667f, 0.70833f, 0.75f, 0.79167f, 0.83333f, 0.875f, 0.91667f, 0.95833f, 1.0f, 1.0417f
    };

    static Vec3 arm_up_R_anim_keyframe_translations[] = {
        { 0.040988f, 1.4056f, -0.74052f }, { 0.040988f, 1.4056f, -0.74052f }, { 0.041784f, 1.4f, -0.73466f }, { 0.043746f, 1.3863f, -0.71978f }, { 0.046295f, 1.3684f, -0.69948f }, { 0.048873f, 1.3501f, -0.67718f }, { 0.050891f, 1.3355f, -0.65641f }, { 0.051656f, 1.3293f, -0.64123f }, { 0.031023f, 1.3263f, -0.63425f }, { -0.016485f, 1.3194f, -0.63263f }, { -0.076278f, 1.3108f, -0.63411f }, { -0.1382f, 1.302f, -0.63717f }, { -0.19374f, 1.294f, -0.64062f }, { -0.23448f, 1.2882f, -0.64336f }, { -0.25067f, 1.2858f, -0.64422f }, { -0.23247f, 1.2847f, -0.6356f }, { -0.17745f, 1.2825f, -0.6118f }, { -0.11061f, 1.2821f, -0.58538f }, { -0.057129f, 1.2848f, -0.56707f }, { -0.020541f, 1.2896f, -0.55746f }, { 0.0025074f, 1.296f, -0.55448f }, { 0.017481f, 1.3089f, -0.56806f }, { 0.028001f, 1.3305f, -0.60246f }, { 0.034841f, 1.3559f, -0.64728f }, { 0.03877f, 1.3802f, -0.69216f }, { 0.040562f, 1.3984f, -0.7267f }, { 0.040988f, 1.4056f, -0.74052f }
    };

    static float arm_up_R_anim_keyframe_rotation_timings[] = {
        -0.041667f, 0.0f, 0.041667f, 0.083333f, 0.125f, 0.16667f, 0.20833f, 0.25f, 0.29167f, 0.33333f, 0.375f, 0.41667f, 0.45833f, 0.5f, 0.54167f, 0.58333f, 0.625f, 0.66667f, 0.70833f, 0.75f, 0.79167f, 0.83333f, 0.875f, 0.91667f, 0.95833f, 1.0f, 1.0417f
    };

    static Quaternion arm_up_R_anim_keyframe_rotations[] = {
        { -0.87005f, -0.10624f, -0.23642f, 0.41933f }, { -0.87005f, -0.10624f, -0.23642f, 0.41933f }, { -0.853f, -0.11f, -0.25359f, 0.44269f }, { -0.80554f, -0.1189f, -0.29575f, 0.4995f }, { -0.73308f, -0.12937f, -0.3486f, 0.5695f }, { -0.64925f, -0.13823f, -0.39792f, 0.63327f }, { -0.57759f, -0.14368f, -0.43281f, 0.67707f }, { -0.54673f, -0.14525f, -0.44637f, 0.69336f }, { -0.57893f, -0.16173f, -0.42287f, 0.67814f }, { -0.65345f, -0.20242f, -0.35572f, 0.63678f }, { -0.74106f, -0.2455f, -0.25606f, 0.57009f }, { -0.81855f, -0.26938f, -0.14308f, 0.48676f }, { -0.87483f, -0.26335f, -0.035007f, 0.40509f }, { -0.90901f, -0.2272f, 0.059647f, 0.34427f }, { -0.92193f, -0.1636f, 0.14206f, 0.32108f }, { -0.9052f, -0.082744f, 0.22476f, 0.35107f }, { -0.85052f, -0.0035494f, 0.29991f, 0.43205f }, { -0.78548f, 0.062935f, 0.3347f, 0.51676f }, { -0.74106f, 0.12054f, 0.3285f, 0.57305f }, { -0.7191f, 0.16999f, 0.30193f, 0.60236f }, { -0.71378f, 0.21314f, 0.26587f, 0.61189f }, { -0.73598f, 0.22068f, 0.204f, 0.60664f }, { -0.78527f, 0.17291f, 0.10428f, 0.5853f }, { -0.83459f, 0.088028f, -0.016135f, 0.54355f }, { -0.86307f, -0.0058922f, -0.12906f, 0.48828f }, { -0.87036f, -0.078107f, -0.20763f, 0.43961f }, { -0.87005f, -0.10624f, -0.23642f, 0.41933f }
    };

    static float arm_up_R_anim_keyframe_scale_timings[] = {
        -0.041667f, 1.0417f
    };

    static Vec3 arm_up_R_anim_keyframe_scales[] = {
        { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }
    };

                    static int arm_up_R_children_indices[] = {
            3
        };


    static AnimSkeletonBone arm_up_R = {
        .name = "arm_up_R",
        .index = 2,
        .inverse_bind = {
            .mtx = { -0.00012465f, -0.99995f, 0.0098066f, -0.0f, -0.012709f, 0.0098075f, 0.99987f, 0.0f, -0.99992f, -4.0018e-09f, -0.01271f, 0.0f, 0.036495f, -0.72078f, -2.8712f, 1.0f }
        },
                        .bind_position = { .x = 0.04098827764391899, .y = 1.4055755138397217, .z = -0.740519642829895, },

                        .bind_scale = { .x = 1.0000001192092896, .y = 0.9999999403953552, .z = 0.9999998807907104, },

                        .bind_rotation = { .x = -0.8700465559959412, .y = -0.10624326020479202, .z = -0.23641714453697205, .w = 0.4193308353424072, },

        .keyframe_translation_size = 27,
        .anim_keyframe_translation_timings = arm_up_R_anim_keyframe_translation_timings,
        .anim_keyframe_translations = arm_up_R_anim_keyframe_translations,
        .keyframe_rotation_size = 27,
        .anim_keyframe_rotation_timings = arm_up_R_anim_keyframe_rotation_timings,
        .anim_keyframe_rotations = arm_up_R_anim_keyframe_rotations,
        .keyframe_scale_size = 2,
        .anim_keyframe_scale_timings = arm_up_R_anim_keyframe_scale_timings,
        .anim_keyframe_scales = arm_up_R_anim_keyframe_scales,
        .children_indices = arm_up_R_children_indices,
        .children_size = 1,
    };

    static float arm_down_R_anim_keyframe_translation_timings[] = {
        -0.041667f, 1.0417f
    };

    static Vec3 arm_down_R_anim_keyframe_translations[] = {
        { 3.1122e-08f, 0.78473f, 2.3054e-07f }, { 3.1122e-08f, 0.78473f, 2.3054e-07f }
    };

    static float arm_down_R_anim_keyframe_rotation_timings[] = {
        -0.041667f, 0.0f, 0.041667f, 0.083333f, 0.125f, 0.16667f, 0.20833f, 0.25f, 0.29167f, 0.33333f, 0.375f, 0.41667f, 0.45833f, 0.5f, 0.54167f, 0.58333f, 0.625f, 0.66667f, 0.70833f, 0.75f, 0.79167f, 0.83333f, 0.875f, 0.91667f, 0.95833f, 1.0f, 1.0417f
    };

    static Quaternion arm_down_R_anim_keyframe_rotations[] = {
        { -0.29542f, 0.015487f, 0.39401f, 0.8702f }, { -0.29542f, 0.015487f, 0.39401f, 0.8702f }, { -0.29773f, 0.010664f, 0.37578f, 0.87752f }, { -0.30296f, -0.00070033f, 0.32965f, 0.89417f }, { -0.30866f, -0.014146f, 0.2678f, 0.91258f }, { -0.3131f, -0.02509f, 0.20356f, 0.92731f }, { -0.31567f, -0.028677f, 0.15206f, 0.93617f }, { -0.31657f, -0.019375f, 0.13052f, 0.93935f }, { -0.29152f, -0.00018146f, 0.15017f, 0.9447f }, { -0.22943f, 0.020355f, 0.19607f, 0.95315f }, { -0.14415f, 0.040564f, 0.25392f, 0.95556f }, { -0.048116f, 0.058544f, 0.31218f, 0.947f }, { 0.04609f, 0.072577f, 0.36153f, 0.92839f }, { 0.12746f, 0.081519f, 0.39559f, 0.90588f }, { 0.18733f, 0.084637f, 0.40999f, 0.88863f }, { 0.23027f, 0.084926f, 0.41261f, 0.87722f }, { 0.26031f, 0.085498f, 0.41442f, 0.86786f }, { 0.27429f, 0.085149f, 0.41556f, 0.86303f }, { 0.27902f, 0.083471f, 0.41622f, 0.86136f }, { 0.28029f, 0.080815f, 0.4166f, 0.86102f }, { 0.28051f, 0.077521f, 0.41678f, 0.86116f }, { 0.24069f, 0.071297f, 0.42004f, 0.8721f }, { 0.13568f, 0.060268f, 0.4249f, 0.89298f }, { -0.0077881f, 0.045811f, 0.42364f, 0.90464f }, { -0.15107f, 0.031009f, 0.4135f, 0.89735f }, { -0.25573f, 0.019818f, 0.40034f, 0.87974f }, { -0.29542f, 0.015487f, 0.39401f, 0.8702f }
    };

    static float arm_down_R_anim_keyframe_scale_timings[] = {
        -0.041667f, 1.0417f
    };

    static Vec3 arm_down_R_anim_keyframe_scales[] = {
        { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }
    };

                    static int arm_down_R_children_indices[] = {
            4
        };


    static AnimSkeletonBone arm_down_R = {
        .name = "arm_down_R",
        .index = 3,
        .inverse_bind = {
            .mtx = { -0.00015119f, -0.99993f, 0.011896f, -0.0f, -0.012708f, 0.011897f, 0.99985f, 0.0f, -0.99992f, -2.6776e-09f, -0.012709f, 0.0f, 0.036453f, -1.5115f, -2.8681f, 1.0f }
        },
                        .bind_position = { .x = -2.8482878278168755e-08, .y = 0.7847299575805664, .z = -7.816369773649967e-09, },

                        .bind_scale = { .x = 0.9999998807907104, .y = 0.9999998807907104, .z = 1, },

                        .bind_rotation = { .x = -0.2954191267490387, .y = 0.015486865304410458, .z = 0.39401155710220337, .w = 0.8701968789100647, },

        .keyframe_translation_size = 2,
        .anim_keyframe_translation_timings = arm_down_R_anim_keyframe_translation_timings,
        .anim_keyframe_translations = arm_down_R_anim_keyframe_translations,
        .keyframe_rotation_size = 27,
        .anim_keyframe_rotation_timings = arm_down_R_anim_keyframe_rotation_timings,
        .anim_keyframe_rotations = arm_down_R_anim_keyframe_rotations,
        .keyframe_scale_size = 2,
        .anim_keyframe_scale_timings = arm_down_R_anim_keyframe_scale_timings,
        .anim_keyframe_scales = arm_down_R_anim_keyframe_scales,
        .children_indices = arm_down_R_children_indices,
        .children_size = 1,
    };

    static float hand_R_anim_keyframe_translation_timings[] = {
        -0.041667f, 1.0417f
    };

    static Vec3 hand_R_anim_keyframe_translations[] = {
        { -1.1764e-07f, 0.64695f, -3.6093e-07f }, { -1.1764e-07f, 0.64695f, -3.6093e-07f }
    };

    static float hand_R_anim_keyframe_rotation_timings[] = {
        -0.041667f, 0.0f, 0.041667f, 0.083333f, 0.125f, 0.16667f, 0.20833f, 0.25f, 0.29167f, 0.33333f, 0.375f, 0.41667f, 0.45833f, 0.5f, 0.54167f, 0.58333f, 0.625f, 0.66667f, 0.70833f, 0.75f, 0.79167f, 0.83333f, 0.875f, 0.91667f, 0.95833f, 1.0f, 1.0417f
    };

    static Quaternion hand_R_anim_keyframe_rotations[] = {
        { -0.1282f, 0.0020095f, 0.042077f, 0.99085f }, { -0.1282f, 0.0020095f, 0.042077f, 0.99085f }, { -0.1282f, 0.0020095f, 0.042077f, 0.99085f }, { -0.1282f, 0.0020095f, 0.042077f, 0.99085f }, { -0.1282f, 0.0020095f, 0.042077f, 0.99085f }, { -0.1282f, 0.0020096f, 0.042077f, 0.99085f }, { -0.1282f, 0.0020095f, 0.042077f, 0.99085f }, { -0.1282f, 0.0020095f, 0.042077f, 0.99085f }, { -0.11844f, 0.0018568f, 0.040453f, 0.99213f }, { -0.0958f, 0.0015026f, 0.036677f, 0.99472f }, { -0.067151f, 0.0010543f, 0.031884f, 0.99723f }, { -0.037393f, 0.00058867f, 0.026888f, 0.99894f }, { -0.010694f, 0.0001709f, 0.022388f, 0.99969f }, { 0.0088568f, -0.000135f, 0.019084f, 0.99978f }, { 0.016614f, -0.00025638f, 0.017771f, 0.9997f }, { 0.016614f, -0.00025639f, 0.017771f, 0.9997f }, { 0.016614f, -0.00025637f, 0.017771f, 0.9997f }, { 0.016614f, -0.00025638f, 0.017771f, 0.9997f }, { 0.016614f, -0.00025639f, 0.017771f, 0.9997f }, { 0.016614f, -0.00025639f, 0.017771f, 0.9997f }, { 0.016614f, -0.00025639f, 0.017771f, 0.9997f }, { 0.0058915f, -8.8605e-05f, 0.019586f, 0.99979f }, { -0.020974f, 0.00033177f, 0.024123f, 0.99949f }, { -0.055946f, 0.00087895f, 0.030005f, 0.99798f }, { -0.090847f, 0.001425f, 0.03585f, 0.99522f }, { -0.11756f, 0.0018431f, 0.040306f, 0.99225f }, { -0.1282f, 0.0020095f, 0.042077f, 0.99085f }
    };

    static float hand_R_anim_keyframe_scale_timings[] = {
        -0.041667f, 1.0417f
    };

    static Vec3 hand_R_anim_keyframe_scales[] = {
        { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }
    };



    static AnimSkeletonBone hand_R = {
        .name = "hand_R",
        .index = 4,
        .inverse_bind = {
            .mtx = { 0.028277f, -0.99933f, 0.023208f, -0.0f, -0.013493f, 0.022834f, 0.99965f, 0.0f, -0.99951f, -0.02858f, -0.012838f, -0.0f, 0.099111f, -2.1888f, -2.8435f, 1.0f }
        },
                        .bind_position = { .x = 6.5751390998514125e-09, .y = 0.6469464898109436, .z = -5.973691941107973e-07, },

                        .bind_scale = { .x = 1, .y = 1.000000238418579, .z = 1, },

                        .bind_rotation = { .x = -0.1282026618719101, .y = 0.0020095286890864372, .z = 0.04207684472203255, .w = 0.9908530116081238, },

        .keyframe_translation_size = 2,
        .anim_keyframe_translation_timings = hand_R_anim_keyframe_translation_timings,
        .anim_keyframe_translations = hand_R_anim_keyframe_translations,
        .keyframe_rotation_size = 27,
        .anim_keyframe_rotation_timings = hand_R_anim_keyframe_rotation_timings,
        .anim_keyframe_rotations = hand_R_anim_keyframe_rotations,
        .keyframe_scale_size = 2,
        .anim_keyframe_scale_timings = hand_R_anim_keyframe_scale_timings,
        .anim_keyframe_scales = hand_R_anim_keyframe_scales,
        .children_indices = NULL,
        .children_size = 0,
    };

    static float neck_anim_keyframe_translation_timings[] = {
        -0.041667f, 1.0417f
    };

    static Vec3 neck_anim_keyframe_translations[] = {
        { 2.8103e-16f, 1.2908f, -1.8626e-08f }, { 2.8103e-16f, 1.2908f, -1.8626e-08f }
    };

    static float neck_anim_keyframe_rotation_timings[] = {
        -0.041667f, 0.0f, 0.041667f, 0.083333f, 0.125f, 0.16667f, 0.20833f, 0.25f, 0.29167f, 0.33333f, 0.375f, 0.41667f, 0.45833f, 0.5f, 0.54167f, 0.58333f, 0.625f, 0.66667f, 0.70833f, 0.75f, 0.79167f, 0.83333f, 0.875f, 0.91667f, 0.95833f, 1.0f, 1.0417f
    };

    static Quaternion neck_anim_keyframe_rotations[] = {
        { 0.0066866f, -0.0010674f, -0.014032f, 0.99988f }, { 0.0066866f, -0.0010674f, -0.014032f, 0.99988f }, { 0.0074644f, -0.00088117f, -0.013215f, 0.99988f }, { 0.0094096f, -0.00041531f, -0.011169f, 0.99989f }, { 0.011938f, 0.00019023f, -0.0085109f, 0.99989f }, { 0.014464f, 0.00079531f, -0.0058543f, 0.99988f }, { 0.016405f, 0.0012601f, -0.0038135f, 0.99986f }, { 0.017179f, 0.0014457f, -0.0029987f, 0.99985f }, { 0.017702f, 0.0013218f, -0.0018516f, 0.99984f }, { 0.018614f, 0.0010583f, 0.00081058f, 0.99983f }, { 0.019192f, 0.00077131f, 0.004175f, 0.99981f }, { 0.018867f, 0.00054734f, 0.007669f, 0.99979f }, { 0.017099f, 0.0004642f, 0.010809f, 0.9998f }, { 0.01329f, 0.00060427f, 0.013115f, 0.99983f }, { 0.0066866f, 0.0010674f, 0.014032f, 0.99988f }, { 0.00026207f, 0.0021829f, 0.015648f, 0.99988f }, { -0.0029778f, 0.0039437f, 0.019205f, 0.9998f }, { -0.0039325f, 0.0059691f, 0.022769f, 0.99972f }, { -0.0035034f, 0.0078806f, 0.024415f, 0.99966f }, { -0.0025897f, 0.0093029f, 0.022227f, 0.99971f }, { -0.0020866f, 0.0098615f, 0.014285f, 0.99985f }, { -0.0014369f, 0.0090529f, 0.0042252f, 0.99995f }, { 0.00018781f, 0.0070291f, -0.0032489f, 0.99997f }, { 0.0023f, 0.0043976f, -0.0084738f, 0.99995f }, { 0.0044121f, 0.0017662f, -0.011787f, 0.99992f }, { 0.0060368f, -0.00025784f, -0.013527f, 0.99989f }, { 0.0066866f, -0.0010674f, -0.014032f, 0.99988f }
    };

    static float neck_anim_keyframe_scale_timings[] = {
        -0.041667f, 1.0417f
    };

    static Vec3 neck_anim_keyframe_scales[] = {
        { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }
    };

                    static int neck_children_indices[] = {
            6
        };


    static AnimSkeletonBone neck = {
        .name = "neck",
        .index = 5,
        .inverse_bind = {
            .mtx = { -0.012709f, -2.432e-09f, 0.99992f, -0.0f, 1.3435e-07f, 1.0f, 1.7076e-09f, -0.0f, -0.99992f, 2.8496e-10f, -0.012709f, -0.0f, -3.949e-07f, -2.8399f, -3.2817e-09f, 1.0f }
        },
                        .bind_position = { .x = -4.40619762898109e-16, .y = 1.2908024787902832, .z = -3.725290076417309e-09, },

                        .bind_scale = { .x = 0.9999999403953552, .y = 0.9999999403953552, .z = 0.9999998807907104, },

                        .bind_rotation = { .x = 0.00668659433722496, .y = -0.0010674368822947145, .z = -0.01403229683637619, .w = 0.9998786449432373, },

        .keyframe_translation_size = 2,
        .anim_keyframe_translation_timings = neck_anim_keyframe_translation_timings,
        .anim_keyframe_translations = neck_anim_keyframe_translations,
        .keyframe_rotation_size = 27,
        .anim_keyframe_rotation_timings = neck_anim_keyframe_rotation_timings,
        .anim_keyframe_rotations = neck_anim_keyframe_rotations,
        .keyframe_scale_size = 2,
        .anim_keyframe_scale_timings = neck_anim_keyframe_scale_timings,
        .anim_keyframe_scales = neck_anim_keyframe_scales,
        .children_indices = neck_children_indices,
        .children_size = 1,
    };

    static float head_anim_keyframe_translation_timings[] = {
        -0.041667f, 1.0417f
    };

    static Vec3 head_anim_keyframe_translations[] = {
        { 2.9834e-08f, 0.4233f, -6.1827e-09f }, { 2.9834e-08f, 0.4233f, -6.1827e-09f }
    };

    static float head_anim_keyframe_rotation_timings[] = {
        -0.041667f, 0.0f, 0.041667f, 0.083333f, 0.125f, 0.16667f, 0.20833f, 0.25f, 0.29167f, 0.33333f, 0.375f, 0.41667f, 0.45833f, 0.5f, 0.54167f, 0.58333f, 0.625f, 0.66667f, 0.70833f, 0.75f, 0.79167f, 0.83333f, 0.875f, 0.91667f, 0.95833f, 1.0f, 1.0417f
    };

    static Quaternion head_anim_keyframe_rotations[] = {
        { -0.0011987f, 0.010506f, -0.00015692f, 0.99994f }, { -0.0011987f, 0.010506f, -0.00015692f, 0.99994f }, { -0.0022199f, 0.011219f, -0.0011274f, 0.99993f }, { -0.0047742f, 0.013002f, -0.0035546f, 0.9999f }, { -0.0080944f, 0.015319f, -0.0067098f, 0.99983f }, { -0.011412f, 0.017635f, -0.0098625f, 0.99973f }, { -0.01396f, 0.019413f, -0.012284f, 0.99964f }, { -0.014978f, 0.020123f, -0.013251f, 0.9996f }, { -0.013923f, 0.018916f, -0.015443f, 0.9996f }, { -0.011477f, 0.015904f, -0.019905f, 0.99961f }, { -0.0083867f, 0.011691f, -0.024346f, 0.9996f }, { -0.0051809f, 0.0066667f, -0.027037f, 0.9996f }, { -0.0023023f, 0.0011109f, -0.026396f, 0.99965f }, { -0.00019042f, -0.0047422f, -0.020724f, 0.99977f }, { 0.00064859f, -0.010667f, -0.0079289f, 0.99991f }, { -0.00058513f, -0.014498f, 0.0065595f, 0.99987f }, { -0.0036686f, -0.015008f, 0.016224f, 0.99975f }, { -0.0076762f, -0.013369f, 0.022039f, 0.99964f }, { -0.011683f, -0.01075f, 0.024982f, 0.99956f }, { -0.014762f, -0.0083207f, 0.026028f, 0.99952f }, { -0.015989f, -0.0072489f, 0.02615f, 0.9995f }, { -0.01489f, -0.0059316f, 0.024192f, 0.99958f }, { -0.012152f, -0.0026446f, 0.019321f, 0.99974f }, { -0.0085935f, 0.0016283f, 0.012992f, 0.99988f }, { -0.0050337f, 0.0059021f, 0.0066619f, 0.99995f }, { -0.0022945f, 0.0091903f, 0.0017915f, 0.99995f }, { -0.0011987f, 0.010506f, -0.00015692f, 0.99994f }
    };

    static float head_anim_keyframe_scale_timings[] = {
        -0.041667f, 1.0417f
    };

    static Vec3 head_anim_keyframe_scales[] = {
        { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }
    };



    static AnimSkeletonBone head = {
        .name = "head",
        .index = 6,
        .inverse_bind = {
            .mtx = { -0.012708f, -0.010309f, 0.99987f, -0.0f, -0.00013088f, 0.99995f, 0.010308f, 0.0f, -0.99992f, 2.6193e-10f, -0.012709f, 0.0f, 0.00042714f, -3.2631f, -0.033637f, 1.0f }
        },
                        .bind_position = { .x = 3.1227593427773925e-11, .y = 0.4232964515686035, .z = 8.717682575820618e-09, },

                        .bind_scale = { .x = 0.9999999403953552, .y = 1, .z = 0.9999999403953552, },

                        .bind_rotation = { .x = -0.0011986615136265755, .y = 0.010505684651434422, .z = -0.00015691628505010158, .w = 0.9999440908432007, },

        .keyframe_translation_size = 2,
        .anim_keyframe_translation_timings = head_anim_keyframe_translation_timings,
        .anim_keyframe_translations = head_anim_keyframe_translations,
        .keyframe_rotation_size = 27,
        .anim_keyframe_rotation_timings = head_anim_keyframe_rotation_timings,
        .anim_keyframe_rotations = head_anim_keyframe_rotations,
        .keyframe_scale_size = 2,
        .anim_keyframe_scale_timings = head_anim_keyframe_scale_timings,
        .anim_keyframe_scales = head_anim_keyframe_scales,
        .children_indices = NULL,
        .children_size = 0,
    };

    static float arm_up_L_anim_keyframe_translation_timings[] = {
        -0.041667f, 0.0f, 0.041667f, 0.083333f, 0.125f, 0.16667f, 0.20833f, 0.25f, 0.29167f, 0.33333f, 0.375f, 0.41667f, 0.45833f, 0.5f, 0.54167f, 0.58333f, 0.625f, 0.66667f, 0.70833f, 0.75f, 0.79167f, 0.83333f, 0.875f, 0.91667f, 0.95833f, 1.0f, 1.0417f
    };

    static Vec3 arm_up_L_anim_keyframe_translations[] = {
        { -0.26697f, 1.2858f, 0.63764f }, { -0.26697f, 1.2858f, 0.63764f }, { -0.24065f, 1.2869f, 0.62906f }, { -0.16006f, 1.2901f, 0.60278f }, { -0.083276f, 1.2931f, 0.57774f }, { -0.038678f, 1.2949f, 0.5632f }, { -0.017472f, 1.2957f, 0.55629f }, { -0.011586f, 1.296f, 0.55437f }, { -0.010226f, 1.3034f, 0.56698f }, { -0.0068455f, 1.3206f, 0.59625f }, { -0.0021488f, 1.3423f, 0.6332f }, { 0.0034125f, 1.3648f, 0.67154f }, { 0.0095046f, 1.385f, 0.70596f }, { 0.015844f, 1.3998f, 0.73123f }, { 0.022154f, 1.4056f, 0.74132f }, { 0.028031f, 1.403f, 0.73237f }, { 0.032411f, 1.3936f, 0.70632f }, { 0.034595f, 1.3785f, 0.67706f }, { 0.035344f, 1.3616f, 0.65663f }, { 0.035467f, 1.345f, 0.6458f }, { 0.035342f, 1.3293f, 0.64233f }, { 0.012818f, 1.3154f, 0.64164f }, { -0.043202f, 1.3044f, 0.64068f }, { -0.11595f, 1.2961f, 0.63962f }, { -0.18867f, 1.2903f, 0.63864f }, { -0.2446f, 1.2869f, 0.63792f }, { -0.26697f, 1.2858f, 0.63764f }
    };

    static float arm_up_L_anim_keyframe_rotation_timings[] = {
        -0.041667f, 0.0f, 0.041667f, 0.083333f, 0.125f, 0.16667f, 0.20833f, 0.25f, 0.29167f, 0.33333f, 0.375f, 0.41667f, 0.45833f, 0.5f, 0.54167f, 0.58333f, 0.625f, 0.66667f, 0.70833f, 0.75f, 0.79167f, 0.83333f, 0.875f, 0.91667f, 0.95833f, 1.0f, 1.0417f
    };

    static Quaternion arm_up_L_anim_keyframe_rotations[] = {
        { 0.25586f, -0.30956f, -0.87741f, 0.2624f }, { 0.25586f, -0.30956f, -0.87741f, 0.2624f }, { 0.263f, -0.34589f, -0.8741f, 0.21713f }, { 0.28022f, -0.45404f, -0.84305f, 0.067737f }, { -0.28843f, 0.54372f, 0.7842f, 0.078747f }, { -0.28992f, 0.58643f, 0.73938f, 0.15928f }, { -0.29074f, 0.604f, 0.71608f, 0.19461f }, { -0.29239f, 0.60851f, 0.70936f, 0.20257f }, { -0.27729f, 0.60123f, 0.72652f, 0.18385f }, { -0.2355f, 0.58234f, 0.76543f, 0.13977f }, { -0.17447f, 0.55356f, 0.81059f, 0.077943f }, { -0.10087f, 0.51721f, 0.84988f, 0.0051742f }, { 0.02237f, -0.47815f, -0.87511f, 0.071088f }, { -0.053281f, -0.44367f, -0.88297f, 0.14383f }, { -0.11981f, -0.42251f, -0.87403f, 0.20786f }, { -0.20311f, -0.44315f, -0.83991f, 0.23858f }, { -0.32834f, -0.5208f, -0.76229f, 0.19967f }, { -0.40365f, -0.6047f, -0.66712f, 0.1623f }, { -0.43258f, -0.65935f, -0.59819f, 0.14249f }, { -0.44075f, -0.68665f, -0.56219f, 0.1349f }, { -0.43939f, -0.69515f, -0.55236f, 0.13642f }, { -0.40456f, -0.68326f, -0.59093f, 0.14243f }, { -0.3018f, -0.64171f, -0.68671f, 0.15988f }, { -0.12836f, -0.55878f, -0.79567f, 0.19546f }, { 0.068055f, -0.44466f, -0.86154f, 0.23534f }, { 0.20795f, -0.34753f, -0.87716f, 0.258f }, { 0.25586f, -0.30956f, -0.87741f, 0.2624f }
    };

    static float arm_up_L_anim_keyframe_scale_timings[] = {
        -0.041667f, 1.0417f
    };

    static Vec3 arm_up_L_anim_keyframe_scales[] = {
        { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }
    };

                    static int arm_up_L_children_indices[] = {
            8
        };


    static AnimSkeletonBone arm_up_L = {
        .name = "arm_up_L",
        .index = 7,
        .inverse_bind = {
            .mtx = { -0.00012465f, 0.99995f, -0.0098066f, -0.0f, 0.012709f, 0.0098073f, 0.99987f, -0.0f, 0.99992f, 4.7439e-09f, -0.01271f, -0.0f, -0.036495f, -0.72078f, -2.8712f, 1.0f }
        },
                        .bind_position = { .x = -0.266967236995697, .y = 1.2858409881591797, .z = 0.637640118598938, },

                        .bind_scale = { .x = 0.9999998807907104, .y = 0.9999997615814209, .z = 0.9999998807907104, },

                        .bind_rotation = { .x = 0.25586047768592834, .y = -0.3095550835132599, .z = -0.877414345741272, .w = 0.26240265369415283, },

        .keyframe_translation_size = 27,
        .anim_keyframe_translation_timings = arm_up_L_anim_keyframe_translation_timings,
        .anim_keyframe_translations = arm_up_L_anim_keyframe_translations,
        .keyframe_rotation_size = 27,
        .anim_keyframe_rotation_timings = arm_up_L_anim_keyframe_rotation_timings,
        .anim_keyframe_rotations = arm_up_L_anim_keyframe_rotations,
        .keyframe_scale_size = 2,
        .anim_keyframe_scale_timings = arm_up_L_anim_keyframe_scale_timings,
        .anim_keyframe_scales = arm_up_L_anim_keyframe_scales,
        .children_indices = arm_up_L_children_indices,
        .children_size = 1,
    };

    static float arm_down_L_anim_keyframe_translation_timings[] = {
        -0.041667f, 1.0417f
    };

    static Vec3 arm_down_L_anim_keyframe_translations[] = {
        { 1.2491e-07f, 0.78473f, 2.2654e-07f }, { 1.2491e-07f, 0.78473f, 2.2654e-07f }
    };

    static float arm_down_L_anim_keyframe_rotation_timings[] = {
        -0.041667f, 0.0f, 0.041667f, 0.083333f, 0.125f, 0.16667f, 0.20833f, 0.25f, 0.29167f, 0.33333f, 0.375f, 0.41667f, 0.45833f, 0.5f, 0.54167f, 0.58333f, 0.625f, 0.66667f, 0.70833f, 0.75f, 0.79167f, 0.83333f, 0.875f, 0.91667f, 0.95833f, 1.0f, 1.0417f
    };

    static Quaternion arm_down_L_anim_keyframe_rotations[] = {
        { 0.18733f, -0.084637f, -0.40999f, 0.88863f }, { 0.18733f, -0.084637f, -0.40999f, 0.88863f }, { 0.19418f, -0.084146f, -0.41061f, 0.88691f }, { 0.21112f, -0.08291f, -0.41208f, 0.88247f }, { 0.23313f, -0.081258f, -0.4138f, 0.87625f }, { 0.25544f, -0.079529f, -0.41533f, 0.86944f }, { 0.27312f, -0.07812f, -0.41638f, 0.86367f }, { 0.28051f, -0.077521f, -0.41678f, 0.86116f }, { 0.24543f, -0.076006f, -0.42091f, 0.86996f }, { 0.16029f, -0.071521f, -0.42817f, 0.88649f }, { 0.047135f, -0.063953f, -0.4321f, 0.89832f }, { -0.073347f, -0.053627f, -0.42911f, 0.89867f }, { -0.18097f, -0.041465f, -0.41941f, 0.88861f }, { -0.25939f, -0.028529f, -0.4063f, 0.87568f }, { -0.29542f, -0.015487f, -0.39401f, 0.8702f }, { -0.30578f, -0.0026125f, -0.36303f, 0.88017f }, { -0.3145f, 0.0082784f, -0.29316f, 0.90282f }, { -0.31811f, 0.014878f, -0.2173f, 0.92269f }, { -0.3182f, 0.017936f, -0.16524f, 0.93334f }, { -0.31734f, 0.01912f, -0.13839f, 0.93797f }, { -0.31657f, 0.019375f, -0.13052f, 0.93935f }, { -0.28222f, 0.011795f, -0.15284f, 0.94702f }, { -0.19206f, -0.007842f, -0.20968f, 0.95869f }, { -0.067497f, -0.034085f, -0.2823f, 0.95634f }, { 0.058615f, -0.059631f, -0.349f, 0.93338f }, { 0.15177f, -0.07784f, -0.39388f, 0.9032f }, { 0.18733f, -0.084637f, -0.40999f, 0.88863f }
    };

    static float arm_down_L_anim_keyframe_scale_timings[] = {
        -0.041667f, 1.0417f
    };

    static Vec3 arm_down_L_anim_keyframe_scales[] = {
        { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }
    };

                    static int arm_down_L_children_indices[] = {
            9
        };


    static AnimSkeletonBone arm_down_L = {
        .name = "arm_down_L",
        .index = 8,
        .inverse_bind = {
            .mtx = { -0.00015119f, 0.99993f, -0.011896f, -0.0f, 0.012708f, 0.011896f, 0.99985f, -0.0f, 0.99992f, 3.2742e-09f, -0.012709f, -0.0f, -0.036453f, -1.5115f, -2.8681f, 1.0f }
        },
                        .bind_position = { .x = 1.2491103973388817e-07, .y = 0.7847299575805664, .z = 2.2666222321277019e-07, },

                        .bind_scale = { .x = 1, .y = 0.9999999403953552, .z = 0.9999998807907104, },

                        .bind_rotation = { .x = 0.18732678890228271, .y = -0.08463732153177261, .z = -0.40998542308807373, .w = 0.8886265754699707, },

        .keyframe_translation_size = 2,
        .anim_keyframe_translation_timings = arm_down_L_anim_keyframe_translation_timings,
        .anim_keyframe_translations = arm_down_L_anim_keyframe_translations,
        .keyframe_rotation_size = 27,
        .anim_keyframe_rotation_timings = arm_down_L_anim_keyframe_rotation_timings,
        .anim_keyframe_rotations = arm_down_L_anim_keyframe_rotations,
        .keyframe_scale_size = 2,
        .anim_keyframe_scale_timings = arm_down_L_anim_keyframe_scale_timings,
        .anim_keyframe_scales = arm_down_L_anim_keyframe_scales,
        .children_indices = arm_down_L_children_indices,
        .children_size = 1,
    };

    static float hand_L_anim_keyframe_translation_timings[] = {
        -0.041667f, 1.0417f
    };

    static Vec3 hand_L_anim_keyframe_translations[] = {
        { 2.4884e-09f, 0.64695f, -3.5236e-07f }, { 2.4884e-09f, 0.64695f, -3.5236e-07f }
    };

    static float hand_L_anim_keyframe_rotation_timings[] = {
        -0.041667f, 0.0f, 0.041667f, 0.083333f, 0.125f, 0.16667f, 0.20833f, 0.25f, 0.29167f, 0.33333f, 0.375f, 0.41667f, 0.45833f, 0.5f, 0.54167f, 0.58333f, 0.625f, 0.66667f, 0.70833f, 0.75f, 0.79167f, 0.83333f, 0.875f, 0.91667f, 0.95833f, 1.0f, 1.0417f
    };

    static Quaternion hand_L_anim_keyframe_rotations[] = {
        { 0.016614f, 0.00025638f, -0.017771f, 0.9997f }, { 0.016614f, 0.00025638f, -0.017771f, 0.9997f }, { 0.016614f, 0.00025637f, -0.017771f, 0.9997f }, { 0.016614f, 0.00025638f, -0.017771f, 0.9997f }, { 0.016614f, 0.00025638f, -0.017771f, 0.9997f }, { 0.016614f, 0.00025638f, -0.017771f, 0.9997f }, { 0.016614f, 0.00025638f, -0.017771f, 0.9997f }, { 0.016614f, 0.00025638f, -0.017771f, 0.9997f }, { 0.0067796f, 0.00010249f, -0.019436f, 0.99979f }, { -0.015999f, -0.00025393f, -0.023284f, 0.9996f }, { -0.044734f, -0.00070352f, -0.028122f, 0.9986f }, { -0.074478f, -0.0011689f, -0.033112f, 0.99667f }, { -0.10108f, -0.0015851f, -0.037559f, 0.99417f }, { -0.12051f, -0.0018891f, -0.040796f, 0.99187f }, { -0.1282f, -0.0020095f, -0.042077f, 0.99085f }, { -0.1282f, -0.0020095f, -0.042077f, 0.99085f }, { -0.1282f, -0.0020095f, -0.042077f, 0.99085f }, { -0.1282f, -0.0020095f, -0.042077f, 0.99085f }, { -0.1282f, -0.0020095f, -0.042077f, 0.99085f }, { -0.1282f, -0.0020095f, -0.042077f, 0.99085f }, { -0.1282f, -0.0020095f, -0.042077f, 0.99085f }, { -0.11756f, -0.001843f, -0.040306f, 0.99225f }, { -0.090847f, -0.001425f, -0.03585f, 0.99522f }, { -0.055946f, -0.00087896f, -0.030005f, 0.99798f }, { -0.020974f, -0.00033177f, -0.024123f, 0.99949f }, { 0.0058915f, 8.8593e-05f, -0.019586f, 0.99979f }, { 0.016614f, 0.00025638f, -0.017771f, 0.9997f }
    };

    static float hand_L_anim_keyframe_scale_timings[] = {
        -0.041667f, 1.0417f
    };

    static Vec3 hand_L_anim_keyframe_scales[] = {
        { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }
    };



    static AnimSkeletonBone hand_L = {
        .name = "hand_L",
        .index = 9,
        .inverse_bind = {
            .mtx = { 0.028277f, 0.99933f, -0.023208f, -0.0f, 0.013493f, 0.022834f, 0.99965f, 0.0f, 0.99951f, -0.02858f, -0.012838f, -0.0f, -0.099111f, -2.1888f, -2.8435f, 1.0f }
        },
                        .bind_position = { .x = -1.2263652138244652e-07, .y = 0.6469465494155884, .z = -1.1165280255909238e-07, },

                        .bind_scale = { .x = 1.0000001192092896, .y = 1.0000001192092896, .z = 1, },

                        .bind_rotation = { .x = 0.016614297404885292, .y = 0.000256380153587088, .z = -0.017770981416106224, .w = 0.999704122543335, },

        .keyframe_translation_size = 2,
        .anim_keyframe_translation_timings = hand_L_anim_keyframe_translation_timings,
        .anim_keyframe_translations = hand_L_anim_keyframe_translations,
        .keyframe_rotation_size = 27,
        .anim_keyframe_rotation_timings = hand_L_anim_keyframe_rotation_timings,
        .anim_keyframe_rotations = hand_L_anim_keyframe_rotations,
        .keyframe_scale_size = 2,
        .anim_keyframe_scale_timings = hand_L_anim_keyframe_scale_timings,
        .anim_keyframe_scales = hand_L_anim_keyframe_scales,
        .children_indices = NULL,
        .children_size = 0,
    };

    static float leg_up_R_anim_keyframe_translation_timings[] = {
        -0.041667f, 0.0f, 0.041667f, 0.083333f, 0.125f, 0.16667f, 0.20833f, 0.25f, 0.29167f, 0.33333f, 0.375f, 0.41667f, 0.45833f, 0.5f, 0.54167f, 0.58333f, 0.625f, 0.66667f, 0.70833f, 0.75f, 0.79167f, 0.83333f, 0.875f, 0.91667f, 0.95833f, 1.0f, 1.0417f
    };

    static Vec3 leg_up_R_anim_keyframe_translations[] = {
        { -0.46172f, 0.68218f, 0.087741f }, { -0.46172f, 0.68218f, 0.087741f }, { -0.46172f, 0.68488f, 0.11202f }, { -0.46172f, 0.68708f, 0.13171f }, { -0.46172f, 0.68701f, 0.13107f }, { -0.46172f, 0.68622f, 0.12401f }, { -0.46172f, 0.6852f, 0.11483f }, { -0.46172f, 0.68413f, 0.10521f }, { -0.4622f, 0.6777f, 0.095754f }, { -0.46378f, 0.64753f, 0.088988f }, { -0.46736f, 0.57169f, 0.089388f }, { -0.47723f, 0.5756f, 0.082643f }, { -0.48141f, 0.58816f, 0.07446f }, { -0.48197f, 0.60735f, 0.065816f }, { -0.48254f, 0.6309f, 0.057536f }, { -0.48287f, 0.65651f, 0.05035f }, { -0.48277f, 0.68191f, 0.044937f }, { -0.48213f, 0.70494f, 0.041941f }, { -0.4809f, 0.72362f, 0.041984f }, { -0.47912f, 0.73629f, 0.045677f }, { -0.4768f, 0.74158f, 0.053632f }, { -0.47404f, 0.73776f, 0.063072f }, { -0.47106f, 0.72768f, 0.071304f }, { -0.46802f, 0.71423f, 0.078618f }, { -0.46504f, 0.69915f, 0.084934f }, { -0.46253f, 0.68572f, 0.089118f }, { -0.46172f, 0.68218f, 0.087741f }
    };

    static float leg_up_R_anim_keyframe_rotation_timings[] = {
        -0.041667f, 0.0f, 0.041667f, 0.083333f, 0.125f, 0.16667f, 0.20833f, 0.25f, 0.29167f, 0.33333f, 0.375f, 0.41667f, 0.45833f, 0.5f, 0.54167f, 0.58333f, 0.625f, 0.66667f, 0.70833f, 0.75f, 0.79167f, 0.83333f, 0.875f, 0.91667f, 0.95833f, 1.0f, 1.0417f
    };

    static Quaternion leg_up_R_anim_keyframe_rotations[] = {
        { -0.029487f, -0.10292f, -0.99381f, 0.029614f }, { -0.029487f, -0.10292f, -0.99381f, 0.029614f }, { -0.023503f, -0.15921f, -0.98674f, 0.021007f }, { 0.003235f, 0.34088f, 0.94007f, 0.0078409f }, { -0.012926f, 0.47616f, 0.87873f, 0.030521f }, { -0.02094f, 0.54007f, 0.84033f, 0.041661f }, { -0.024489f, 0.56768f, 0.82157f, 0.046571f }, { -0.025446f, 0.57505f, 0.81632f, 0.047892f }, { -0.023919f, 0.57306f, 0.81785f, 0.046431f }, { -0.018083f, 0.5642f, 0.82443f, 0.040869f }, { -0.0044208f, 0.53688f, 0.84318f, 0.02796f }, { 0.019102f, 0.45319f, 0.89119f, 0.0062605f }, { -0.03042f, -0.32787f, -0.94423f, 0.0031463f }, { -0.031227f, -0.20815f, -0.97759f, 0.0042137f }, { -0.028301f, -0.10075f, -0.9945f, 0.0048494f }, { -0.022737f, -0.015147f, -0.99961f, 0.0051777f }, { -0.016209f, 0.04574f, -0.99881f, 0.0054123f }, { -0.010219f, 0.08469f, -0.99634f, 0.0057492f }, { -0.0056852f, 0.10689f, -0.99423f, 0.0063055f }, { -0.00298f, 0.11733f, -0.99306f, 0.0071237f }, { -0.0021419f, 0.11984f, -0.99276f, 0.0082013f }, { -0.0044382f, 0.11157f, -0.99369f, 0.010602f }, { -0.0094874f, 0.09225f, -0.99559f, 0.014483f }, { -0.015962f, 0.064419f, -0.99761f, 0.019133f }, { -0.02303f, 0.027227f, -0.99907f, 0.024103f }, { -0.028906f, -0.030072f, -0.99872f, 0.028446f }, { -0.029487f, -0.10292f, -0.99381f, 0.029614f }
    };

    static float leg_up_R_anim_keyframe_scale_timings[] = {
        -0.041667f, 1.0417f
    };

    static Vec3 leg_up_R_anim_keyframe_scales[] = {
        { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }
    };

                    static int leg_up_R_children_indices[] = {
            11
        };


    static AnimSkeletonBone leg_up_R = {
        .name = "leg_up_R",
        .index = 10,
        .inverse_bind = {
            .mtx = { -0.99955f, 0.030002f, 3.9604e-06f, -0.0f, -0.030003f, -0.99955f, 5.9246e-08f, 0.0f, -7.3528e-07f, 1.1551e-06f, 0.99999f, -0.0f, -0.43115f, 1.5402f, 1.8515e-06f, 1.0f }
        },
                        .bind_position = { .x = -0.46172037720680237, .y = 0.6821807026863098, .z = 0.08774129301309586, },

                        .bind_scale = { .x = 1.0000009536743164, .y = 1, .z = 1.0000088214874268, },

                        .bind_rotation = { .x = -0.029487401247024536, .y = -0.10291800647974014, .z = -0.9938115477561951, .w = 0.02961396984755993, },

        .keyframe_translation_size = 27,
        .anim_keyframe_translation_timings = leg_up_R_anim_keyframe_translation_timings,
        .anim_keyframe_translations = leg_up_R_anim_keyframe_translations,
        .keyframe_rotation_size = 27,
        .anim_keyframe_rotation_timings = leg_up_R_anim_keyframe_rotation_timings,
        .anim_keyframe_rotations = leg_up_R_anim_keyframe_rotations,
        .keyframe_scale_size = 2,
        .anim_keyframe_scale_timings = leg_up_R_anim_keyframe_scale_timings,
        .anim_keyframe_scales = leg_up_R_anim_keyframe_scales,
        .children_indices = leg_up_R_children_indices,
        .children_size = 1,
    };

    static float leg_down_R_anim_keyframe_translation_timings[] = {
        -0.041667f, 1.0417f
    };

    static Vec3 leg_down_R_anim_keyframe_translations[] = {
        { 1.6764e-08f, 0.6413f, 3.9946e-14f }, { 1.6764e-08f, 0.6413f, 3.9946e-14f }
    };

    static float leg_down_R_anim_keyframe_rotation_timings[] = {
        -0.041667f, 0.0f, 0.041667f, 0.083333f, 0.125f, 0.16667f, 0.20833f, 0.25f, 0.29167f, 0.33333f, 0.375f, 0.41667f, 0.45833f, 0.5f, 0.54167f, 0.58333f, 0.625f, 0.66667f, 0.70833f, 0.75f, 0.79167f, 0.83333f, 0.875f, 0.91667f, 0.95833f, 1.0f, 1.0417f
    };

    static Quaternion leg_down_R_anim_keyframe_rotations[] = {
        { 0.0033233f, 0.005365f, 0.00015394f, 0.99998f }, { 0.0033233f, 0.005365f, 0.00015394f, 0.99998f }, { 0.0037434f, 0.00058197f, 0.00070385f, 0.99999f }, { 0.0050803f, -0.014649f, 0.0024549f, 0.99988f }, { 0.0061289f, -0.026603f, 0.003829f, 0.99962f }, { 0.0066682f, -0.032753f, 0.0045359f, 0.99943f }, { 0.0069148f, -0.035566f, 0.0048593f, 0.99933f }, { 0.0069823f, -0.036337f, 0.0049478f, 0.9993f }, { -0.012173f, -0.035465f, 0.0051235f, 0.99928f }, { -0.088184f, -0.031762f, 0.0058023f, 0.99558f }, { -0.27683f, -0.021045f, 0.0073581f, 0.96066f }, { -0.57601f, 0.0023032f, 0.0093845f, 0.81739f }, { -0.66929f, 0.017572f, 0.0098661f, 0.74273f }, { -0.66611f, 0.025401f, 0.0086836f, 0.74537f }, { -0.6552f, 0.031367f, 0.0053794f, 0.75478f }, { -0.63449f, 0.03541f, 0.00068116f, 0.77212f }, { -0.60285f, 0.037829f, -0.0044044f, 0.79695f }, { -0.56027f, 0.039109f, -0.0089772f, 0.82734f }, { -0.50743f, 0.039704f, -0.012474f, 0.86069f }, { -0.44528f, 0.039926f, -0.014646f, 0.89438f }, { -0.3749f, 0.039955f, -0.015442f, 0.92608f }, { -0.30024f, 0.038345f, -0.014546f, 0.95298f }, { -0.22475f, 0.034521f, -0.01231f, 0.97373f }, { -0.14973f, 0.029136f, -0.0092691f, 0.98825f }, { -0.077758f, 0.022377f, -0.00572f, 0.9967f }, { -0.017811f, 0.013566f, -0.002006f, 0.99975f }, { 0.0033233f, 0.005365f, 0.00015394f, 0.99998f }
    };

    static float leg_down_R_anim_keyframe_scale_timings[] = {
        -0.041667f, 1.0417f
    };

    static Vec3 leg_down_R_anim_keyframe_scales[] = {
        { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }
    };

                    static int leg_down_R_children_indices[] = {
            12
        };


    static AnimSkeletonBone leg_down_R = {
        .name = "leg_down_R",
        .index = 11,
        .inverse_bind = {
            .mtx = { -0.99968f, 0.025207f, 4.4665e-06f, -0.0f, -0.025208f, -0.99968f, 5.7065e-08f, 0.0f, -2.3492e-07f, 1.1366e-06f, 0.99999f, -0.0f, -0.43546f, 0.89682f, 2.0852e-06f, 1.0f }
        },
                        .bind_position = { .x = -1.3324348735466174e-08, .y = 0.6413009166717529, .z = -2.980229574234272e-08, },

                        .bind_scale = { .x = 1, .y = 1, .z = 0.9999999403953552, },

                        .bind_rotation = { .x = 0.0033233468420803547, .y = 0.005364958196878433, .z = 0.00015393717330880463, .w = 0.999980092048645, },

        .keyframe_translation_size = 2,
        .anim_keyframe_translation_timings = leg_down_R_anim_keyframe_translation_timings,
        .anim_keyframe_translations = leg_down_R_anim_keyframe_translations,
        .keyframe_rotation_size = 27,
        .anim_keyframe_rotation_timings = leg_down_R_anim_keyframe_rotation_timings,
        .anim_keyframe_rotations = leg_down_R_anim_keyframe_rotations,
        .keyframe_scale_size = 2,
        .anim_keyframe_scale_timings = leg_down_R_anim_keyframe_scale_timings,
        .anim_keyframe_scales = leg_down_R_anim_keyframe_scales,
        .children_indices = leg_down_R_children_indices,
        .children_size = 1,
    };

    static float foot_R_anim_keyframe_translation_timings[] = {
        -0.041667f, 1.0417f
    };

    static Vec3 foot_R_anim_keyframe_translations[] = {
        { 6.5376e-08f, 0.76329f, -2.681e-09f }, { 6.5376e-08f, 0.76329f, -2.681e-09f }
    };

    static float foot_R_anim_keyframe_rotation_timings[] = {
        -0.041667f, 0.0f, 0.041667f, 0.083333f, 0.125f, 0.16667f, 0.20833f, 0.25f, 0.29167f, 0.33333f, 0.375f, 0.41667f, 0.45833f, 0.5f, 0.54167f, 0.58333f, 0.625f, 0.66667f, 0.70833f, 0.75f, 0.79167f, 0.83333f, 0.875f, 0.91667f, 0.95833f, 1.0f, 1.0417f
    };

    static Quaternion foot_R_anim_keyframe_rotations[] = {
        { 0.62412f, -0.022476f, -0.059076f, 0.77877f }, { 0.62412f, -0.022476f, -0.059076f, 0.77877f }, { 0.62593f, -0.022793f, -0.059911f, 0.77724f }, { 0.63021f, -0.023547f, -0.061895f, 0.77359f }, { 0.63581f, -0.024535f, -0.064496f, 0.76876f }, { 0.64182f, -0.025604f, -0.067311f, 0.76346f }, { 0.64727f, -0.026577f, -0.069873f, 0.75859f }, { 0.65014f, -0.027093f, -0.07123f, 0.75598f }, { 0.66641f, -0.025415f, -0.074196f, 0.74145f }, { 0.71018f, -0.020637f, -0.082275f, 0.69889f }, { 0.76517f, -0.013976f, -0.092668f, 0.63698f }, { 0.80893f, -0.0079302f, -0.10113f, 0.57908f }, { 0.82543f, -0.005197f, -0.10416f, 0.55479f }, { 0.81831f, -0.0071818f, -0.1007f, 0.56584f }, { 0.79708f, -0.013606f, -0.091486f, 0.59675f }, { 0.76388f, -0.023052f, -0.078033f, 0.64021f }, { 0.72431f, -0.03329f, -0.063054f, 0.68577f }, { 0.68597f, -0.042199f, -0.049418f, 0.72472f }, { 0.65514f, -0.04853f, -0.039048f, 0.75294f }, { 0.63513f, -0.051906f, -0.032708f, 0.76997f }, { 0.62677f, -0.052424f, -0.03041f, 0.77684f }, { 0.62482f, -0.050031f, -0.03183f, 0.77851f }, { 0.62399f, -0.045182f, -0.036109f, 0.77929f }, { 0.62386f, -0.038879f, -0.042177f, 0.77943f }, { 0.62405f, -0.032125f, -0.048961f, 0.77919f }, { 0.62419f, -0.025931f, -0.055388f, 0.77888f }, { 0.62412f, -0.022476f, -0.059076f, 0.77877f }
    };

    static float foot_R_anim_keyframe_scale_timings[] = {
        -0.041667f, 1.0417f
    };

    static Vec3 foot_R_anim_keyframe_scales[] = {
        { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }
    };



    static AnimSkeletonBone foot_R = {
        .name = "foot_R",
        .index = 12,
        .inverse_bind = {
            .mtx = { -0.99167f, -0.0688f, 0.10886f, -0.0f, 0.11797f, -0.14627f, 0.98219f, -0.0f, -0.051656f, 0.98684f, 0.15316f, -0.0f, -0.44949f, -0.012262f, -0.072576f, 1.0f }
        },
                        .bind_position = { .x = 3.708438356397892e-08, .y = 0.7632906436920166, .z = 2.9410044177780037e-08, },

                        .bind_scale = { .x = 0.9999999403953552, .y = 1.0000001192092896, .z = 1, },

                        .bind_rotation = { .x = 0.6241202354431152, .y = -0.022476334124803543, .z = -0.059076447039842606, .w = 0.778767466545105, },

        .keyframe_translation_size = 2,
        .anim_keyframe_translation_timings = foot_R_anim_keyframe_translation_timings,
        .anim_keyframe_translations = foot_R_anim_keyframe_translations,
        .keyframe_rotation_size = 27,
        .anim_keyframe_rotation_timings = foot_R_anim_keyframe_rotation_timings,
        .anim_keyframe_rotations = foot_R_anim_keyframe_rotations,
        .keyframe_scale_size = 2,
        .anim_keyframe_scale_timings = foot_R_anim_keyframe_scale_timings,
        .anim_keyframe_scales = foot_R_anim_keyframe_scales,
        .children_indices = NULL,
        .children_size = 0,
    };

    static float leg_up_L_anim_keyframe_translation_timings[] = {
        -0.041667f, 0.0f, 0.041667f, 0.083333f, 0.125f, 0.16667f, 0.20833f, 0.25f, 0.29167f, 0.33333f, 0.375f, 0.41667f, 0.45833f, 0.5f, 0.54167f, 0.58333f, 0.625f, 0.66667f, 0.70833f, 0.75f, 0.79167f, 0.83333f, 0.875f, 0.91667f, 0.95833f, 1.0f, 1.0417f
    };

    static Vec3 leg_up_L_anim_keyframe_translations[] = {
        { 0.47829f, 0.47828f, 0.015624f }, { 0.47829f, 0.47828f, 0.015624f }, { 0.47807f, 0.48977f, 0.016696f }, { 0.47754f, 0.51655f, 0.019687f }, { 0.47684f, 0.55183f, 0.024621f }, { 0.47607f, 0.59123f, 0.031965f }, { 0.47532f, 0.63002f, 0.043035f }, { 0.47486f, 0.65567f, 0.063118f }, { 0.47411f, 0.65944f, 0.084977f }, { 0.47248f, 0.66345f, 0.09518f }, { 0.47043f, 0.66752f, 0.099042f }, { 0.46816f, 0.67152f, 0.09885f }, { 0.46583f, 0.67534f, 0.095942f }, { 0.46364f, 0.67872f, 0.091456f }, { 0.46227f, 0.68075f, 0.087818f }, { 0.46225f, 0.68018f, 0.088618f }, { 0.46216f, 0.67769f, 0.090854f }, { 0.46211f, 0.67642f, 0.093445f }, { 0.4621f, 0.67634f, 0.095574f }, { 0.46148f, 0.65704f, 0.099053f }, { 0.46001f, 0.6107f, 0.10465f }, { 0.46057f, 0.55492f, 0.10762f }, { 0.46462f, 0.50715f, 0.10193f }, { 0.4706f, 0.4859f, 0.08987f }, { 0.47619f, 0.48634f, 0.078086f }, { 0.47862f, 0.4861f, 0.04436f }, { 0.4785f, 0.48421f, 0.010052f }
    };

    static float leg_up_L_anim_keyframe_rotation_timings[] = {
        -0.041667f, 0.0f, 0.041667f, 0.083333f, 0.125f, 0.16667f, 0.20833f, 0.25f, 0.29167f, 0.33333f, 0.375f, 0.41667f, 0.45833f, 0.5f, 0.54167f, 0.58333f, 0.625f, 0.66667f, 0.70833f, 0.75f, 0.79167f, 0.83333f, 0.875f, 0.91667f, 0.95833f, 1.0f, 1.0417f
    };

    static Quaternion leg_up_L_anim_keyframe_rotations[] = {
        { -0.030136f, 0.23176f, 0.97229f, 0.0058805f }, { -0.030136f, 0.23176f, 0.97229f, 0.0058805f }, { -0.028432f, 0.20944f, 0.97739f, 0.0061519f }, { -0.024353f, 0.15638f, 0.98737f, 0.0067801f }, { -0.0188f, 0.084954f, 0.99618f, 0.0075891f }, { -0.012464f, 0.0045492f, 0.99988f, 0.0084518f }, { -0.0062494f, -0.073118f, 0.99726f, 0.0092425f }, { -0.0024086f, -0.11984f, 0.99274f, 0.0097265f }, { -0.0040956f, -0.11134f, 0.99371f, 0.01104f }, { -0.0077265f, -0.093956f, 0.99545f, 0.013794f }, { -0.012302f, -0.070389f, 0.99729f, 0.017267f }, { -0.017344f, -0.041194f, 0.99878f, 0.021122f }, { -0.022467f, -0.005736f, 0.99942f, 0.025098f }, { -0.027116f, 0.038495f, 0.99847f, 0.028836f }, { -0.02941f, 0.10296f, 0.99376f, 0.03116f }, { -0.023908f, 0.20796f, 0.97753f, 0.024967f }, { -0.01172f, 0.32857f, 0.94437f, 0.0082351f }, { -0.0031114f, -0.4392f, -0.89829f, 0.012953f }, { -0.015686f, -0.51863f, -0.85428f, 0.03119f }, { -0.02339f, -0.56247f, -0.8254f, 0.04245f }, { -0.025862f, -0.57572f, -0.81594f, 0.046079f }, { -0.020369f, -0.56971f, -0.82056f, 0.041195f }, { -0.0072571f, -0.54848f, -0.83561f, 0.029514f }, { 0.0086045f, -0.50644f, -0.8621f, 0.015315f }, { 0.022591f, -0.43623f, -0.89955f, 0.0026027f }, { -0.02999f, 0.32791f, 0.94422f, 0.004635f }, { -0.030136f, 0.23176f, 0.97229f, 0.0058805f }
    };

    static float leg_up_L_anim_keyframe_scale_timings[] = {
        -0.041667f, 1.0417f
    };

    static Vec3 leg_up_L_anim_keyframe_scales[] = {
        { 1.0f, 1.0f, 0.99998f }, { 1.0f, 1.0f, 0.99998f }
    };

                    static int leg_up_L_children_indices[] = {
            14
        };


    static AnimSkeletonBone leg_up_L = {
        .name = "leg_up_L",
        .index = 13,
        .inverse_bind = {
            .mtx = { -0.99955f, -0.030003f, 1.1318e-05f, 0.0f, 0.030003f, -0.99955f, -4.1426e-07f, 0.0f, 7.0476e-07f, -2.1927e-06f, 1.0f, -0.0f, 0.43115f, 1.5402f, -4.716e-06f, 1.0f }
        },
                        .bind_position = { .x = 0.47829365730285645, .y = 0.47827810049057007, .z = 0.015624482184648514, },

                        .bind_scale = { .x = 0.9999980330467224, .y = 0.999998152256012, .z = 0.9999837279319763, },

                        .bind_rotation = { .x = -0.030136331915855408, .y = 0.23176166415214539, .z = 0.9722878932952881, .w = 0.005880477372556925, },

        .keyframe_translation_size = 27,
        .anim_keyframe_translation_timings = leg_up_L_anim_keyframe_translation_timings,
        .anim_keyframe_translations = leg_up_L_anim_keyframe_translations,
        .keyframe_rotation_size = 27,
        .anim_keyframe_rotation_timings = leg_up_L_anim_keyframe_rotation_timings,
        .anim_keyframe_rotations = leg_up_L_anim_keyframe_rotations,
        .keyframe_scale_size = 2,
        .anim_keyframe_scale_timings = leg_up_L_anim_keyframe_scale_timings,
        .anim_keyframe_scales = leg_up_L_anim_keyframe_scales,
        .children_indices = leg_up_L_children_indices,
        .children_size = 1,
    };

    static float leg_down_L_anim_keyframe_translation_timings[] = {
        -0.041667f, 1.0417f
    };

    static Vec3 leg_down_L_anim_keyframe_translations[] = {
        { -5.0005e-08f, 0.6413f, 2.0827e-13f }, { -2.0775e-08f, 0.6413f, -5.9604e-08f }
    };

    static float leg_down_L_anim_keyframe_rotation_timings[] = {
        -0.041667f, 0.0f, 0.041667f, 0.083333f, 0.125f, 0.16667f, 0.20833f, 0.25f, 0.29167f, 0.33333f, 0.375f, 0.41667f, 0.45833f, 0.5f, 0.54167f, 0.58333f, 0.625f, 0.66667f, 0.70833f, 0.75f, 0.79167f, 0.83333f, 0.875f, 0.91667f, 0.95833f, 1.0f, 1.0417f
    };

    static Quaternion leg_down_L_anim_keyframe_rotations[] = {
        { -0.66211f, -0.02609f, -0.008468f, 0.74891f }, { -0.66211f, -0.02609f, -0.008468f, 0.74891f }, { -0.64269f, -0.027265f, -0.0066607f, 0.76561f }, { -0.59047f, -0.03022f, -0.0019642f, 0.80649f }, { -0.51866f, -0.033863f, 0.0041558f, 0.8543f }, { -0.44664f, -0.037097f, 0.0099563f, 0.89389f }, { -0.39417f, -0.03922f, 0.013995f, 0.91809f }, { -0.3749f, -0.039955f, 0.015442f, 0.92608f }, { -0.35113f, -0.039212f, 0.014729f, 0.93539f }, { -0.29435f, -0.037016f, 0.012949f, 0.95489f }, { -0.22009f, -0.033341f, 0.010473f, 0.97485f }, { -0.1412f, -0.028224f, 0.0076194f, 0.98955f }, { -0.069924f, -0.021798f, 0.0047045f, 0.9973f }, { -0.01781f, -0.014192f, 0.002024f, 0.99974f }, { 0.0033234f, -0.005365f, -0.00015394f, 0.99998f }, { 0.0042563f, 0.0048508f, -0.0015814f, 0.99998f }, { 0.0048866f, 0.015504f, -0.0022605f, 0.99987f }, { 0.0052259f, 0.024816f, -0.0024917f, 0.99968f }, { 0.0053629f, 0.031476f, -0.0026771f, 0.99949f }, { 0.0053989f, 0.0352f, -0.0030885f, 0.99936f }, { 0.0054026f, 0.036337f, -0.0038272f, 0.99932f }, { -0.066421f, 0.033693f, -0.0051641f, 0.99721f }, { -0.24738f, 0.025299f, -0.0070407f, 0.96856f }, { -0.46023f, 0.011689f, -0.0087137f, 0.88768f }, { -0.61438f, -0.0035525f, -0.009622f, 0.78894f }, { -0.66929f, -0.017572f, -0.0098661f, 0.74273f }, { -0.66211f, -0.02609f, -0.008468f, 0.74891f }
    };

    static float leg_down_L_anim_keyframe_scale_timings[] = {
        -0.041667f, 1.0417f
    };

    static Vec3 leg_down_L_anim_keyframe_scales[] = {
        { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }
    };

                    static int leg_down_L_children_indices[] = {
            15
        };


    static AnimSkeletonBone leg_down_L = {
        .name = "leg_down_L",
        .index = 14,
        .inverse_bind = {
            .mtx = { -0.99968f, -0.025208f, 1.086e-05f, 0.0f, 0.025208f, -0.99968f, -3.2942e-07f, 0.0f, 2.3491e-07f, -2.1228e-06f, 1.0f, -0.0f, 0.43546f, 0.89683f, -4.5817e-06f, 1.0f }
        },
                        .bind_position = { .x = -2.0489167695814103e-08, .y = 0.6413010358810425, .z = 1.9895196601282805e-13, },

                        .bind_scale = { .x = 1, .y = 0.9999999403953552, .z = 1, },

                        .bind_rotation = { .x = -0.6621079444885254, .y = -0.026089992374181747, .z = -0.00846795178949833, .w = 0.7489063143730164, },

        .keyframe_translation_size = 2,
        .anim_keyframe_translation_timings = leg_down_L_anim_keyframe_translation_timings,
        .anim_keyframe_translations = leg_down_L_anim_keyframe_translations,
        .keyframe_rotation_size = 27,
        .anim_keyframe_rotation_timings = leg_down_L_anim_keyframe_rotation_timings,
        .anim_keyframe_rotations = leg_down_L_anim_keyframe_rotations,
        .keyframe_scale_size = 2,
        .anim_keyframe_scale_timings = leg_down_L_anim_keyframe_scale_timings,
        .anim_keyframe_scales = leg_down_L_anim_keyframe_scales,
        .children_indices = leg_down_L_children_indices,
        .children_size = 1,
    };

    static float foot_L_anim_keyframe_translation_timings[] = {
        -0.041667f, 1.0417f
    };

    static Vec3 foot_L_anim_keyframe_translations[] = {
        { 1.3012e-08f, 0.76329f, -2.3306e-08f }, { -6.0341e-08f, 0.76329f, 5.2717e-08f }
    };

    static float foot_L_anim_keyframe_rotation_timings[] = {
        -0.041667f, 0.0f, 0.041667f, 0.083333f, 0.125f, 0.16667f, 0.20833f, 0.25f, 0.29167f, 0.33333f, 0.375f, 0.41667f, 0.45833f, 0.5f, 0.54167f, 0.58333f, 0.625f, 0.66667f, 0.70833f, 0.75f, 0.79167f, 0.83333f, 0.875f, 0.91667f, 0.95833f, 1.0f, 1.0417f
    };

    static Quaternion foot_L_anim_keyframe_rotations[] = {
        { 0.81676f, 0.007647f, 0.10012f, 0.56817f }, { 0.81676f, 0.007647f, 0.10012f, 0.56817f }, { 0.80636f, 0.010634f, 0.095769f, 0.58352f }, { 0.78082f, 0.017618f, 0.085436f, 0.61863f }, { 0.74457f, 0.026807f, 0.071492f, 0.66317f }, { 0.70105f, 0.036929f, 0.055659f, 0.70998f }, { 0.65596f, 0.046571f, 0.040096f, 0.75229f }, { 0.62678f, 0.052424f, 0.03041f, 0.77684f }, { 0.6266f, 0.050768f, 0.03192f, 0.77703f }, { 0.62618f, 0.046847f, 0.035517f, 0.77746f }, { 0.62564f, 0.041729f, 0.040251f, 0.77796f }, { 0.62507f, 0.036144f, 0.045482f, 0.77841f }, { 0.62455f, 0.030684f, 0.050696f, 0.77873f }, { 0.62419f, 0.025916f, 0.055406f, 0.77887f }, { 0.62412f, 0.022477f, 0.059076f, 0.77877f }, { 0.6236f, 0.021362f, 0.061603f, 0.77902f }, { 0.62298f, 0.02266f, 0.06343f, 0.77933f }, { 0.62446f, 0.025085f, 0.064954f, 0.77795f }, { 0.6295f, 0.027125f, 0.066624f, 0.77366f }, { 0.63828f, 0.027878f, 0.068697f, 0.76623f }, { 0.65014f, 0.027094f, 0.07123f, 0.75598f }, { 0.67883f, 0.023995f, 0.076725f, 0.72988f }, { 0.7264f, 0.018683f, 0.085639f, 0.68166f }, { 0.77528f, 0.012663f, 0.094886f, 0.62432f }, { 0.81147f, 0.0076146f, 0.10176f, 0.57541f }, { 0.82543f, 0.0051973f, 0.10416f, 0.55478f }, { 0.81676f, 0.007647f, 0.10012f, 0.56817f }
    };

    static float foot_L_anim_keyframe_scale_timings[] = {
        -0.041667f, 1.0417f
    };

    static Vec3 foot_L_anim_keyframe_scales[] = {
        { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }
    };



    static AnimSkeletonBone foot_L = {
        .name = "foot_L",
        .index = 15,
        .inverse_bind = {
            .mtx = { -0.99167f, 0.068813f, -0.10886f, -0.0f, -0.11797f, -0.14626f, 0.98219f, 0.0f, 0.051656f, 0.98687f, 0.15316f, -0.0f, 0.44949f, -0.012268f, -0.072578f, 1.0f }
        },
                        .bind_position = { .x = 4.880990722710976e-09, .y = 0.7632909417152405, .z = -7.42622852101249e-10, },

                        .bind_scale = { .x = 0.9999999403953552, .y = 1, .z = 1.0000001192092896, },

                        .bind_rotation = { .x = 0.8167591691017151, .y = 0.0076470221392810345, .z = 0.10011875629425049, .w = 0.5681745409965515, },

        .keyframe_translation_size = 2,
        .anim_keyframe_translation_timings = foot_L_anim_keyframe_translation_timings,
        .anim_keyframe_translations = foot_L_anim_keyframe_translations,
        .keyframe_rotation_size = 27,
        .anim_keyframe_rotation_timings = foot_L_anim_keyframe_rotation_timings,
        .anim_keyframe_rotations = foot_L_anim_keyframe_rotations,
        .keyframe_scale_size = 2,
        .anim_keyframe_scale_timings = foot_L_anim_keyframe_scale_timings,
        .anim_keyframe_scales = foot_L_anim_keyframe_scales,
        .children_indices = NULL,
        .children_size = 0,
    };


                static Mat4 walk_final_joint_transforms[16];
static AnimSkeletonBone *walk_final_indexed_bones[] = { &root, &body, &arm_up_R, &arm_down_R, &hand_R, &neck, &head, &arm_up_L, &arm_down_L, &hand_L, &leg_up_R, &leg_down_R, &foot_R, &leg_up_L, &leg_down_L, &foot_L };

SkeletonAnimation walk_final = {
    .name = "walk_final",
    .skeleton_name = "Armature",
    .indexed_bones = walk_final_indexed_bones,
    .indexed_bones_size = 16,
    .joint_transforms = walk_final_joint_transforms,
    .duration = 1.0417f,
};

