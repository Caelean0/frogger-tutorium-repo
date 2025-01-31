#include <cstdlib>
#include <iostream>
#include "raylib.h"
#include "config.h"
#include "Car.h"
#include "Frog.h"
#include "enum_car.h"

int main()
{
    // Raylib initialization
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    SetTargetFPS(60);

    Car cars[Game::cars_max];
    Frog frog;

    // Autos random auf y-Aches positionieren für straße 1
    for (int i = 0; i < Game::cars_max / 2; i++)
    {
        cars[i].position.y = (float)GetRandomValue(Game::street_y_start + Game::street_padding,
                                                   Game::street_y_start + Game::street_width - Game::street_padding);
        cars[i].position.x = (float)GetRandomValue(0, Game::cars_spawning_range);
        cars[i].hitbox.y=cars[i].position.y;
    }

    // Autos random auf y-Aches positionieren für straße 2 und sowohl die Textur und die bewegungsrichtung angepasst
    for (int i = Game::cars_max / 2; i < Game::cars_max; i++)
    {
        cars[i].road = bottom;
        cars[i].texture = LoadTexture("assets/graphics/car_flip.png");
        cars[i].speed = -cars[i].speed;
        cars[i].position.y = (float)GetRandomValue(Game::street_y_start + 50 + Game::street_width + Game::street_padding-60,
                                                   Game::street_y_start + 50 + Game::street_width + Game::street_width -
                                                   Game::street_padding);
        cars[i].position.x = (float)GetRandomValue(0, Game::cars_spawning_range);
        cars[i].hitbox.y=cars[i].position.y;
    }

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif


    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Input abfragen für Frosch und Frosch bewegen
        //reseten des frosches wenn er oben aus dem bildschirm geht
        if (frog.position.y < 0)
        {
            frog.position.y = 950;
            frog.points++;
        }
        frog.frogmove();
        for (int i=0;i<Game::cars_max;++i)
        {
            cars[i].carmove();
            frog.checkCollision(cars[i].hitbox);
        }
        frog.invincibility=frog.invincibility-1;


        BeginDrawing();
        // You can draw on the screen between BeginDrawing() and EndDrawing()
        // ...
        // ...
        ClearBackground(WHITE);
        //  Wir zeichnen alle Autos aus dem car-Array. Wir nutzen dafür aber nicht die klassische
        //  C for-Schleife, sondern die modernere C++ foreach Schleife.
        //            for (int i = 0; i < Game::cars_max; i++)
        //            {
        //                DrawTexture(cars[i].texture, (int) cars[i].position.x, (int) cars[i].position.y, WHITE);
        //            }
        //
        // Strasse zeichnen
        DrawRectangle(0, Game::street_y_start, Game::ScreenWidth, Game::street_width, GRAY);
        DrawRectangle(0, Game::street_y_start + 50 + Game::street_width, Game::ScreenWidth, Game::street_width, GRAY);

        if (frog.invincibility>0)
        {
            DrawTexture(frog.texture, (int)frog.position.x, (int)frog.position.y, RED);
        }else
        {
            DrawTexture(frog.texture, (int)frog.position.x, (int)frog.position.y, WHITE);
        }


        DrawRectangleLinesEx(frog.hitbox,1,RED);
        for (auto car : cars)
        {
            DrawTexture(car.texture, (int)car.position.x, (int)car.position.y, WHITE);
            DrawRectangleLinesEx(car.hitbox,1,RED);
        }
        DrawText(std::to_string(frog.health).c_str(),10,0,30,BLACK);
        DrawText(std::to_string(frog.points).c_str(),10,40,30,BLACK);

        EndDrawing();
    } // Main game loop end

    // De-initialization here
    // ...
    // ...

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}