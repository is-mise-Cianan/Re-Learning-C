#include "raylib.h"
#include<unistd.h>

int main(void) {
    InitWindow(800, 600, "Gravity Golf");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        for (int i = 1 ; i < 8; i++)
        {
            ClearBackground(BLACK);
            DrawCircle(800/i, 300, 20, YELLOW);
            sleep(1);
        }
        EndDrawing();
    }
    
    
    CloseWindow();
    
    return 0;
}