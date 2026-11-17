#include "raylib.h"

int main(void) {
    InitWindow(800, 600, "Gravity Golf");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawCircle(400, 300, 20, YELLOW);
        EndDrawing();
    }
    
    
    CloseWindow();
    
    return 0;
}