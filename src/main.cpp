#include <raylib.h>
#include "game.h"

int main()
{
    const int WIDTH = 1280;
    const int HEIGHT = 720;
    const int FPS = 60;
    const int GRID_SIZE = 10;
    const float GRID_SPACING = 3.0f;

    InitWindow(WIDTH, HEIGHT, "Turn-Based Combat");
    SetTargetFPS(FPS);

    Camera3D camera = {0};
    camera.position = {10.0f, 12.0f, 10.0f};
    camera.target = {0.0f, 0.0f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_ORTHOGRAPHIC;

    Game game = Game(GRID_SIZE, GRID_SPACING);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(Color{24, 28, 36, 255});

        BeginMode3D(camera);
        DrawGrid(GRID_SIZE, GRID_SPACING);

        game.Run();

        EndMode3D();
        EndDrawing();
    }

    game.Stop();
    CloseWindow();
    return 0;
}