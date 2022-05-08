#pragma once

#include "engine.h"

typedef struct Camera
{
    Vec3 position;
    Vec3 rotation;
    Mat4 transform;
} Camera;

int main(int argc, char *argv[]);
bool main_loop();