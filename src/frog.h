#pragma once

#include <string>

#include "raylib.h"
#include "config.h"

struct Frog
{
    Vector2 position = Game::frogPos;
    int health = 2;
    int points =0;
    int speed = 50;
    int cooldown_move = 0;
    int invincibility=0;
    const int def_cooldowntime = 24;
    Texture texture = LoadTexture("assets/graphics/frog.png");
    Rectangle hitbox={position.x,position.y,(float)texture.width,(float)texture.height};


 void frogmove()
 {
     if (cooldown_move > 0)
         cooldown_move--;
     else
     {
         if (IsKeyDown(KEY_UP))
         {
             position.y -= (float)speed;
             cooldown_move = def_cooldowntime;
         }
         if (IsKeyDown(KEY_DOWN))
         {
             position.y += (float)speed;
             cooldown_move = def_cooldowntime;
         }

         if (IsKeyDown(KEY_LEFT))
         {
             position.x -= (float)speed;
             cooldown_move = def_cooldowntime;
         }
         if (IsKeyDown(KEY_RIGHT))
         {
             position.x += (float)speed;
             cooldown_move = def_cooldowntime;
         }
         hitbox.x=position.x;
         hitbox.y=position.y;
     }
 }
    void checkCollision(Rectangle carhitbox)
 {
     if (invincibility<0){
         if (CheckCollisionRecs(hitbox,carhitbox))
         {
             health=health-1;
             invincibility=60;
             if (health==0)
             {
                 health=2;
                 position=Game::frogPos;
             }
         }
     }
 }

};
