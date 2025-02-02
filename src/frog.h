#pragma once

#include "raylib.h"
#include "config.h"


struct Frog
{
    enum State{moving, vibing};

    Vector2 position = Game::frogStartPos;
    int speed = 70;
    int cooldown_move = 0;
    const int def_cooldowntime = 15;
    Texture texture = LoadTexture("assets/graphics/frog.png");
    Rectangle hitbox = {position.x, position.y, (float)texture.width, (float)texture.height};

    void move()
    {
        // Input abfragen für Frosch und Frosch bewegen
        if (cooldown_move > 0)
        {
            cooldown_move--;
        } else {
            if (IsKeyDown(KEY_UP))
            {
                position.y -= (float) speed;
                cooldown_move = def_cooldowntime;
            }
            if (IsKeyDown(KEY_DOWN))
            {
                position.y += (float) speed;
                cooldown_move = def_cooldowntime;
            }

            if (IsKeyDown(KEY_LEFT))
            {
                position.x -= (float) speed;
                cooldown_move = def_cooldowntime;
            }
            if (IsKeyDown(KEY_RIGHT))
            {
                position.x += (float) speed;
                cooldown_move = def_cooldowntime;
            }
            hitbox.x = position.x;
            hitbox.y = position.y;
        }
    };

    void checkCollision(Rectangle p_carHitbox)
    {
        if (CheckCollisionRecs(hitbox, p_carHitbox))
        {
            position = Game::frogStartPos;
        }
    }

};
