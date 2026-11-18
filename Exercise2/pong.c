#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define PADDLE_HEIGHT 5
#define PADDLE_WIDTH 45

struct Ball {
    struct Vector2 ball_coords;
    float radius;
    struct Vector2 ball_velocity;
};

struct Paddle {
    struct Vector2 paddle_coords;
    float paddle_height;
    float paddle_width;
    float paddle_velocity;
};

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");
    SetTargetFPS(60);

    struct Paddle paddle1 = {{SCREEN_WIDTH/2 - PADDLE_HEIGHT, SCREEN_HEIGHT*0.8}, PADDLE_WIDTH, PADDLE_HEIGHT, 450.0f};
    struct Paddle paddle2 = {{SCREEN_WIDTH/2 - PADDLE_HEIGHT, SCREEN_HEIGHT*0.2}, PADDLE_WIDTH, PADDLE_HEIGHT, 450.0f};

    struct Ball ball = {SCREEN_WIDTH/2, SCREEN_HEIGHT * 0.2, 10, {250, 150}};

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        //paddle dimensions
        float paddle_top = paddle.paddle_coords.y;
        float paddle_bottom = paddle.paddle_coords.y + PADDLE_HEIGHT;
        float paddle_left = paddle.paddle_coords.x;
        float paddle_right = paddle.paddle_coords.x + PADDLE_WIDTH;

        //ball dimensions
        float ball_top = ball.ball_coords.y + ball.radius;
        float ball_bottom = ball.ball_coords.y + ball.radius;
        float ball_left =  ball.ball_coords.x - ball.radius;
        float ball_right = ball.ball_coords.x + ball.radius;

        int game = 1;

        //KEY CONTROLS
        //movement controls
        if (game != 0){
            if (IsKeyDown(KEY_D)){
                paddle1.paddle_coords.x += paddle.paddle_velocity * dt;
            }
            if (IsKeyDown(KEY_A)){
                paddle1.paddle_coords.x -= paddle.paddle_velocity * dt;
            }

            if (IsKeyDown(KEY_RIGHT)){
                paddle2.paddle_coords.x += paddle.paddle_velocity * dt;
            }
            if (IsKeyDown(KEY_LEFT)){
                paddle2.paddle_coords.x -= paddle.paddle_velocity * dt;
            }
        }

        //restart controls
        if (game == 0){
            if (IsKeyDown(KEY_R)){
                ball.ball_coords.x = SCREEN_WIDTH/2;
                ball.ball_coords.y = SCREEN_HEIGHT * 0.2;
                ball.ball_velocity.x = 250;
                ball.ball_velocity.x = 150;
                game = 1;
            }
        }
        else{
            //PADDLE RULES
            if (paddle.paddle_coords.x >= SCREEN_WIDTH - PADDLE_WIDTH){
                paddle.paddle_coords.x = SCREEN_WIDTH - PADDLE_WIDTH;
            }
            else if (paddle.paddle_coords.x <= 0){
                paddle.paddle_coords.x = 1;
            }

            //BALL RULES
            ball.ball_coords.x += dt * ball.ball_velocity.x;
            ball.ball_coords.y += dt * ball.ball_velocity.y;

            //ball touching wall
            if (ball.ball_coords.x >= SCREEN_WIDTH - ball.radius){
                ball.ball_velocity.x = -(ball.ball_velocity.x);
            }

            else if (ball.ball_coords.x <=  ball.radius){
                ball.ball_velocity.x = -(ball.ball_velocity.x);
            }

            //ball touching top
            if (ball.ball_coords.y <= 0 && (ball.ball_velocity.y <= 0) ){
                ball.ball_coords.y = 1;
                ball.ball_velocity.y = -(ball.ball_velocity.y);
            }

            //ball touching bottom
            if (ball.ball_coords.y == SCREEN_HEIGHT){
                ball.ball_coords.x = SCREEN_WIDTH/2;
                ball.ball_coords.y = SCREEN_HEIGHT * 0.2;
                ball.ball_velocity.y = 150;
            }

            //ball touching paddle
            if (
                ball.ball_velocity.y > 0 && // moving down
                ball_bottom >= paddle_top && // reached the paddle top
                ball_top <= paddle_bottom && // hasn't passed through it
                ball_right >= paddle_left && // overlaps horizontally
                ball_left   <= paddle_right  // overlaps horizontally
            ){
                ball.ball_coords.y = paddle_top - ball.radius;
                ball.ball_velocity.y = -(ball.ball_velocity.y);
            }

            //ball goes off the bottom
            if (ball.ball_coords.y > SCREEN_HEIGHT){
                game = 0;
            }

            //ball touching block


            //ball touching ground

        }

        


        BeginDrawing();
            ClearBackground(BLACK);

            if(game == 1){
                DrawRectangle(paddle.paddle_coords.x, paddle.paddle_coords.y, paddle.paddle_height, paddle.paddle_width, WHITE);

                DrawCircle(ball.ball_coords.x, ball.ball_coords.y, ball.radius, WHITE);
            }

            if(game == 0){
                int text_length = MeasureText("!!GAME OVER!!", 50);
                DrawText("!!GAME OVER!!", SCREEN_WIDTH/2 - (text_length/2), (SCREEN_HEIGHT/2), 50, WHITE);
                text_length = MeasureText("!!PRESS R TO RESTART!!", 30);
                DrawText("!!PRESS R TO RESTART!!", SCREEN_WIDTH/2 - (text_length/2), (SCREEN_HEIGHT/2) + 40, 30, WHITE);
            }

        EndDrawing();
    }
    
    
    CloseWindow();
    
    return 0;
}