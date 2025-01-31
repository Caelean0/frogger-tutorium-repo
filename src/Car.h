#pragma once

#include "raylib.h"
#include "enum_car.h"
#include <config.h>

struct Car
{
    Vector2 position = {100.0,100.0};           // Achtung Vector2 ist ein Raylib Datentyp. Die Struktur besteht aus 2 floats x und y.
    float speed = 3;
    street road = top;
    Texture texture = LoadTexture("assets/graphics/car.png");
    Rectangle hitbox = {position.x,position.y,(float)texture.width,(float)texture.height};
    void carmove()
    {
        // Autos bewegen
        // Fährt ein Auto aus dem Bildschirm, wird es random auf der engegendgesetzten Seite
        // außerhalb des Bildschirms platziert

            if (position.x < (float)(0 - texture.width) && road == top)
                position.x = (float)GetRandomValue(Game::ScreenWidth,
                                                           Game::cars_spawning_range + Game::ScreenWidth);
            else
                position.x -= speed;

            if (position.x > (float)(Game::ScreenWidth) && road == bottom)
                position.x = (float)GetRandomValue(0, -Game::cars_spawning_range);
            else
                position.x -= speed;
        hitbox.x=position.x;

    }
};
