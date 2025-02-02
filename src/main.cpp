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
    for (auto& car : cars)
    {
        car.position.y = (float) GetRandomValue(Game::street_y_start, Game::street_width - Game::street_padding);
        car.position.x = (float) GetRandomValue(0, Game::cars_spawning_range);
        car.hitbox.x = car.position.x;
        car.hitbox.y = car.position.y;
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
        // Frosch bewegen
        frog.move();


        // Autos bewegen

        for (auto& car : cars)
        {
            car.move();
            frog.checkCollision(car.hitbox);
        }

        BeginDrawing();
        {  // You can draw on the screen between BeginDrawing() and EndDrawing()
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
            DrawRectangleLinesEx(frog.hitbox, 4, BLACK);

            for (auto car: cars)
            {
                DrawTexture(car.texture, (int) car.position.x, (int) car.position.y, WHITE);
                DrawRectangleLinesEx(car.hitbox, 1, BLACK);

            }
        }
        EndDrawing();
    } // Main game loop end

    // De-initialization here
    // ...
    // ...

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
