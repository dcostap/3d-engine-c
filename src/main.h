#pragma once

#include "engine.h"

typedef struct Camera
{
    Vec3 position;
    Vec3 rotation;
    Mat4 world_transform;
} Camera;

int main(void);
bool main_loop(float delta);