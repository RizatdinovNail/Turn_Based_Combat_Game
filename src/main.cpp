#include "raylib.h"

int main()
{
    InitWindow(1280, 720, "C++ RPG Prototype - raylib");
    SetTargetFPS(60);

    Camera3D camera = {0};
    camera.position = {10.0f, 12.0f, 10.0f};
    camera.target = {0.0f, 0.0f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(Color{24, 28, 36, 255});

        BeginMode3D(camera);
        DrawGrid(10, 1.0f);
        EndMode3D();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}