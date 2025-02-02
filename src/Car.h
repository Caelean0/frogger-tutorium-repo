#pragma once

#include "raylib.h"
#include "config.h"

struct Car
{
    Vector2 position = {100.0,100.0};           // Achtung Vector2 ist ein Raylib Datentyp. Die Struktur besteht aus 2 floats x und y.
    int speed = 5;
    Texture texture = LoadTexture("assets/graphics/car.png");

    Rectangle hitbox = {position.x, position.y, (float)texture.width, (float)texture.height};



    void move()
    {
        // Fährt ein Auto links aus dem Bildschirm, wird es random
        // außerhalb des Bildschirms platziert
        if (position.x < (float)(0 - texture.width))
        {
            position.x = (float) GetRandomValue(Game::ScreenWidth, Game::cars_spawning_range + Game::ScreenWidth);
        } else {
            position.x -= (float) speed;
        }
        hitbox.x = position.x;
    };
};
