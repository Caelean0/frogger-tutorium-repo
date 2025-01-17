#pragma once

#include "raylib.h"

struct Frog
{
    Vector2 position = {580.0,400.0};
    int speed = 70;
    int cooldown_move = 0;
    const int def_cooldowntime = 7;
    Texture texture = LoadTexture("assets/graphics/frog.png");
};
