#include <cstdlib>
#include <iostream>

#include "raylib.h"

#include "config.h"

#include "Car.h"

int main() {
    // Raylib initialization
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    SetTargetFPS(60);

    Car cars[15];

    // Autos random auf y-Aches positionieren
    for (int i = 0; i < 15; i++)
    {
        cars[i].position.y = (float) GetRandomValue(50, 200);
        cars[i].position.x = (float) GetRandomValue(0, 3500);
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
        // Autos bewegen
        // Fährt ein Auto links aus dem Bildschirm, wird es random
        // außerhalb des Bildschirms plaziert
        for (int i = 0; i < 15; i++) {
            if (cars[i].position.x < (float)(0 - cars[i].texture.width))
                cars[i].position.x = (float) GetRandomValue(960, 4460);
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
//            for (int i = 0; i < 15; i++)
//            {
//                DrawTexture(cars[i].texture, (int) cars[i].position.x, (int) cars[i].position.y, WHITE);
//            }
//
            DrawRectangle(0, 50, 960, 260, GRAY);

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
