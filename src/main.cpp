#include <cstdlib>
#include <iostream>

#include "raylib.h"

#include "config.h"

#include "Car.h"
#include "Frog.h"

int main() {
    // Raylib initialization
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    SetTargetFPS(60);

    Car cars[Game::cars_max];
    Frog frog;

    // Autos random auf y-Aches positionieren
    for (int i = 0; i < Game::cars_max; i++)
    {
        cars[i].position.y = (float) GetRandomValue(Game::street_y_start, Game::street_width - Game::street_padding);
        cars[i].position.x = (float) GetRandomValue(0, Game::cars_spawning_range);
    }

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    // Your own initialization code here
    // ...
    // ...

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Input abfragen für Frosch und Frosch bewegen
        if (frog.cooldown_move > 0)
            frog.cooldown_move--;
        else
        {
            if (IsKeyDown(KEY_UP))
            {
                frog.position.y -= (float) frog.speed;
                frog.cooldown_move = frog.def_cooldowntime;
            }
            if (IsKeyDown(KEY_DOWN))
            {
                frog.position.y += (float) frog.speed;
                frog.cooldown_move = frog.def_cooldowntime;
            }

            if (IsKeyDown(KEY_LEFT))
            {
                frog.position.x -= (float) frog.speed;
                frog.cooldown_move = frog.def_cooldowntime;
            }
            if (IsKeyDown(KEY_RIGHT))
            {
                frog.position.x += (float) frog.speed;
                frog.cooldown_move = frog.def_cooldowntime;
            }
        }


        // Autos bewegen
        // Fährt ein Auto links aus dem Bildschirm, wird es random
        // außerhalb des Bildschirms platziert
        for (int i = 0; i < Game::cars_max; i++) {
            if (cars[i].position.x < (float)(0 - cars[i].texture.width))
                cars[i].position.x = (float) GetRandomValue(Game::ScreenWidth, Game::cars_spawning_range + Game::ScreenWidth);
            else
                cars[i].position.x -= (float) cars[i].speed;
        }

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

            DrawTexture(frog.texture, (int) frog.position.x, (int) frog.position.y, WHITE);

            for (auto car : cars)
                DrawTexture(car.texture, (int) car.position.x, (int) car.position.y, WHITE);

        EndDrawing();
    } // Main game loop end

    // De-initialization here
    // ...
    // ...

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
