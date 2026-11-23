#include "raylib.h"

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 750
#define PADDLE_HEIGHT 5
#define PADDLE_WIDTH 45
#define GOAL_WIDTH 120

//colours
#define COLOUR_NIGHTSKY_FADE1 CLITERAL(Color){234, 60, 205, 20}   // #ea3ccd
#define COLOUR_NIGHTSKY_FADE2 CLITERAL(Color){234, 60, 205, 40}   // #ea3ccd
#define COLOUR_NIGHTSKY_FADE3 CLITERAL(Color){234, 60, 205, 60}   // #ea3ccd
#define COLOUR_NIGHTSKY CLITERAL(Color){41, 26, 122, 255}   // #291a7a

#define COLOUR_MAGENTA CLITERAL(Color){ 234, 60, 205, 255 }   // #ea3ccd
#define COLOUR_PINK CLITERAL(Color){ 237, 110, 162, 255 }  // #ed6ea2
#define COLOUR_PEACH CLITERAL(Color){ 237, 155, 113, 255 }  // #ed9b71
#define COLOUR_OLIVE CLITERAL(Color){ 208, 204, 78, 255 }   // #d0cc4e
#define COLOUR_LIME CLITERAL(Color){ 194, 251, 79, 255 }   // #c2fb4f

#define COLOUR_WHITE_2 CLITERAL(Color){ 255, 255, 255, 40 }
#define COLOUR_WHITE_1 CLITERAL(Color){ 255, 255, 255, 20 } 



int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Drawing");
    SetTargetFPS(60);
    Texture2D ship = LoadTexture("PongAsset/pong_alien.png");

    while (!WindowShouldClose()) {     
        //updates

        //draw
        BeginDrawing();
            DrawTexture(ship, 100, 100, WHITE);
        EndDrawing();
    }
    
    CloseWindow();
    
    return 0;
}

void draw_alien(void){

}