#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define PADDLE_HEIGHT 5
#define PADDLE_WIDTH 45

typedef struct Ball {
    struct Vector2 ball_coords;
    float radius;
    struct Vector2 ball_velocity;
} Ball;

typedef struct Paddle {
    struct Vector2 paddle_coords;
    float paddle_height;
    float paddle_width;
    float paddle_velocity;
} Paddle;

typedef struct Game {
    Paddle paddle1;
    Paddle paddle2;
    Ball ball;
    int game;
    int score_1;
    int score_2;
} Game;

void game_reset(Game *g);
void game_set(Game *g);
void game_update(Game *g);
void game_draw(Game *g);

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");
    SetTargetFPS(60);

    Game g;

    game_set(&g);

    while (!WindowShouldClose()) {     
        game_update(&g);

        BeginDrawing();
            game_draw(&g);
        EndDrawing();
    }
    
    CloseWindow();
    
    return 0;
}

void game_draw(Game *g){
    ClearBackground(BLACK);

    if(g->game == 1){
        DrawRectangle(g->paddle1.paddle_coords.x, g->paddle1.paddle_coords.y, g->paddle1.paddle_height, g->paddle1.paddle_width, WHITE);
        DrawRectangle(g->paddle2.paddle_coords.x, g->paddle2.paddle_coords.y, g->paddle2.paddle_height, g->paddle2.paddle_width, WHITE);

        DrawCircle(g->ball.ball_coords.x, g->ball.ball_coords.y, g->ball.radius, WHITE);
    }

    if(g->game == 0){
        //make into function oassing string through pointer
        int text_length = MeasureText("!!GAME OVER!!", 50);
        DrawText("!!GAME OVER!!", SCREEN_WIDTH/2 - (text_length/2), (SCREEN_HEIGHT/2), 50, WHITE);
        text_length = MeasureText("!!PRESS R TO RESTART!!", 30);
        DrawText("!!PRESS R TO RESTART!!", SCREEN_WIDTH/2 - (text_length/2), (SCREEN_HEIGHT/2) + 40, 30, WHITE);
    }
}

void game_update(Game *g){
    float dt = GetFrameTime();

    //paddle1 dimensions
    float paddle1_top = g->paddle1.paddle_coords.y;
    float paddle1_bottom = g->paddle1.paddle_coords.y + PADDLE_HEIGHT;
    float paddle1_left = g->paddle1.paddle_coords.x;
    float paddle1_right = g->paddle1.paddle_coords.x + PADDLE_WIDTH;

    //paddle2 dimensions
    float paddle2_top = g->paddle2.paddle_coords.y;
    float paddle2_bottom = g->paddle2.paddle_coords.y + PADDLE_HEIGHT;
    float paddle2_left = g->paddle2.paddle_coords.x;
    float paddle2_right = g->paddle2.paddle_coords.x + PADDLE_WIDTH;

    //ball dimensions
    float ball_top = g->ball.ball_coords.y + g->ball.radius;
    float ball_bottom = g->ball.ball_coords.y + g->ball.radius;
    float ball_left =  g->ball.ball_coords.x - g->ball.radius;
    float ball_right = g->ball.ball_coords.x + g->ball.radius;

    //KEY CONTROLS
    //movement controls
    if (g->game != 0){
        if (IsKeyDown(KEY_D)){
            g->paddle1.paddle_coords.x += g->paddle1.paddle_velocity * dt;
        }
        if (IsKeyDown(KEY_A)){
            g->paddle1.paddle_coords.x -= g->paddle1.paddle_velocity * dt;
        }

        if (IsKeyDown(KEY_RIGHT)){
            g->paddle2.paddle_coords.x += g->paddle2.paddle_velocity * dt;
        }
        if (IsKeyDown(KEY_LEFT)){
            g->paddle2.paddle_coords.x -= g->paddle2.paddle_velocity * dt;
        }
    }

    //restart controls
    if (g->game == 0){
        if (IsKeyDown(KEY_R)){
            game_reset(g);
        }
    }
    else{
        //PADDLE RULES
        if (g->paddle1.paddle_coords.x >= SCREEN_WIDTH - PADDLE_WIDTH){
            g->paddle1.paddle_coords.x = SCREEN_WIDTH - PADDLE_WIDTH;
        }
        else if (g->paddle1.paddle_coords.x <= 0){
            g->paddle1.paddle_coords.x = 1;
        }

        if (g->paddle2.paddle_coords.x >= SCREEN_WIDTH - PADDLE_WIDTH){
            g->paddle2.paddle_coords.x = SCREEN_WIDTH - PADDLE_WIDTH;
        }
        else if (g->paddle2.paddle_coords.x <= 0){
            g->paddle2.paddle_coords.x = 1;
        }

        //BALL RULES
        g->ball.ball_coords.x += dt * g->ball.ball_velocity.x;
        g->ball.ball_coords.y += dt * g->ball.ball_velocity.y;

        //ball touching wall
        if (g->ball.ball_coords.x >= SCREEN_WIDTH - g->ball.radius){
            g->ball.ball_velocity.x = -(g->ball.ball_velocity.x);
        }

        else if (g->ball.ball_coords.x <=  g->ball.radius){
            g->ball.ball_velocity.x = -(g->ball.ball_velocity.x);
        }

        //ball touching top
        if (g->ball.ball_coords.y <= 0 && (g->ball.ball_velocity.y <= 0) ){
            g->ball.ball_coords.y = 1;
            g->ball.ball_velocity.y = -(g->ball.ball_velocity.y);
        }

        //ball touching bottom
        if (g->ball.ball_coords.y == SCREEN_HEIGHT){
            g->ball.ball_coords.x = SCREEN_WIDTH/2;
            g->ball.ball_coords.y = SCREEN_HEIGHT * 0.2;
            g->ball.ball_velocity.y = 150;
        }

        //ball touching paddle1
        if (
            g->ball.ball_velocity.y > 0 && // moving down
            ball_bottom >= paddle1_top && // reached the paddle top
            ball_top <= paddle1_bottom && // hasn't passed through it
            ball_right >= paddle1_left && // overlaps horizontally
            ball_left   <= paddle1_right  // overlaps horizontally
        ){
            g->ball.ball_coords.y = paddle1_top - g->ball.radius;
            g->ball.ball_velocity.y = -(g->ball.ball_velocity.y);
        }

        //ball touching paddle2
        if (
            g->ball.ball_velocity.y > 0 && // moving down
            ball_bottom >= paddle2_top && // reached the paddle top
            ball_top <= paddle2_bottom && // hasn't passed through it
            ball_right >= paddle2_left && // overlaps horizontally
            ball_left   <= paddle2_right  // overlaps horizontally
        ){
            g->ball.ball_coords.y = paddle2_top - g->ball.radius;
            g->ball.ball_velocity.y = -(g->ball.ball_velocity.y);
        }

        //ball goes off the bottom
        if (g->ball.ball_coords.y > SCREEN_HEIGHT){
            g->game = 0;
        }

    }

}

//this function is to initally set up the same with paddles and ball in the correct positions.
void game_set(Game *g){
    g->paddle1 = (Paddle){{SCREEN_WIDTH/2 - PADDLE_HEIGHT, SCREEN_HEIGHT*0.8}, PADDLE_WIDTH, PADDLE_HEIGHT, 450.0f};
    g->paddle2 = (Paddle){{SCREEN_WIDTH/2 - PADDLE_HEIGHT, SCREEN_HEIGHT*0.2}, PADDLE_WIDTH, PADDLE_HEIGHT, 450.0f};

    g->ball = (Ball){SCREEN_WIDTH/2, SCREEN_HEIGHT * 0.2, 10, {250, 150}};

    g->game = 1;

    g->score_1 = 0;
    g->score_2 = 0;
}

//this function is used to 
void game_reset(Game *g){
    g->ball.ball_coords.x = SCREEN_WIDTH/2;
    g->ball.ball_coords.y = SCREEN_HEIGHT * 0.2;
    g->ball.ball_velocity.x = 250;
    g->ball.ball_velocity.x = 150;

    g->score_1 = 0;
    g->score_2 = 0;
    g->game = 1;
}