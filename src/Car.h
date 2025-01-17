#pragma once

#include "raylib.h"

struct Car
{
    Vector2 position = {100.0,100.0};           // Achtung Vector2 ist ein Raylib Datentyp. Die Struktur besteht aus 2 floats x und y.
    int speed = 5;
    Texture texture = LoadTexture("assets/graphics/auto.png");
};
