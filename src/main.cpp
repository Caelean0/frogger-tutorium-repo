#include <cstdlib>

#include "raylib.h"

#include "config.h"

#include "Car.h"

int main() {
    // Raylib initialization
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    SetTargetFPS(60);

    Car cars[15];

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    // Your own initialization code here
    // ...
    // ...

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Updates that are made by frame are coded here
        // ...
        // ...

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
