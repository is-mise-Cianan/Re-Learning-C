#include "raylib.h"

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 750
#define PADDLE_HEIGHT 5
#define PADDLE_WIDTH 45
#define GOAL_WIDTH 160

//colours
#define COLOUR_NIGHTSKY_FADE1 CLITERAL(Color){41, 26, 122, 20}   // #291a7a
#define COLOUR_NIGHTSKY_FADE2 CLITERAL(Color){41, 26, 122, 60}   // #291a7a
#define COLOUR_NIGHTSKY_FADE3 CLITERAL(Color){41, 26, 122, 140}   // #291a7a
#define COLOUR_NIGHTSKY CLITERAL(Color){41, 26, 122, 255}   // #291a7a

#define COLOUR_MAGENTA CLITERAL(Color){ 234, 60, 205, 255 }   // #ea3ccd
#define COLOUR_PINK CLITERAL(Color){ 237, 110, 162, 255 }  // #ed6ea2
#define COLOUR_PEACH CLITERAL(Color){ 237, 155, 113, 255 }  // #ed9b71
#define COLOUR_OLIVE CLITERAL(Color){ 208, 204, 78, 255 }   // #d0cc4e
#define COLOUR_LIME CLITERAL(Color){ 194, 251, 79, 255 }   // #c2fb4f


#define MAX_SCORE 1

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
void draw_centred_text(char *text, int y, int font_size);

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

void draw_centred_text(char *text, int y, int font_size){
    int text_length = MeasureText(text, font_size);
    DrawText(text, SCREEN_WIDTH/2 - (text_length/2), y, font_size, WHITE);
}

void game_draw(Game *g){
    ClearBackground(COLOUR_MAGENTA);
    DrawRectangle(0, SCREEN_HEIGHT*0.3, SCREEN_WIDTH, SCREEN_HEIGHT *0.2, COLOUR_NIGHTSKY_FADE1);
    DrawRectangle(0, SCREEN_HEIGHT*0.2, SCREEN_WIDTH, SCREEN_HEIGHT *0.2, COLOUR_NIGHTSKY_FADE2);
    DrawRectangle(0, SCREEN_HEIGHT*0.1, SCREEN_WIDTH, SCREEN_HEIGHT *0.2, COLOUR_NIGHTSKY_FADE3);
    DrawCircle((SCREEN_WIDTH/2), (SCREEN_HEIGHT), (SCREEN_WIDTH) * 0.9, COLOUR_PINK);
    DrawCircle((SCREEN_WIDTH/2), (SCREEN_HEIGHT), (SCREEN_WIDTH) * 0.75, COLOUR_PEACH);
    DrawCircle((SCREEN_WIDTH/2), (SCREEN_HEIGHT), (SCREEN_WIDTH*0.55) , COLOUR_OLIVE);
    DrawCircle((SCREEN_WIDTH/2), (SCREEN_HEIGHT), (SCREEN_WIDTH*0.35), COLOUR_LIME);
    

    //DrawRectangle(x,y,h,w, col) -> draw sun rays around sun

    if(g->game == 1){
        DrawRectangle(g->paddle1.paddle_coords.x, g->paddle1.paddle_coords.y, g->paddle1.paddle_height, g->paddle1.paddle_width, WHITE);
        DrawRectangle(g->paddle2.paddle_coords.x, g->paddle2.paddle_coords.y, g->paddle2.paddle_height, g->paddle2.paddle_width, WHITE);

        DrawCircle(g->ball.ball_coords.x, g->ball.ball_coords.y, g->ball.radius, WHITE);

        DrawText(TextFormat("Player One Score: %d", g->score_1), 10, 10, 10, WHITE);
        DrawText(TextFormat("Player One Score: %d", g->score_2), 10, SCREEN_HEIGHT - 25, 10, WHITE);

        //Walls
        DrawRectangle(0, 0, SCREEN_WIDTH, 1, WHITE);
        DrawRectangle(0, SCREEN_HEIGHT-1, SCREEN_WIDTH, 1, WHITE);

        //Midline
        DrawRectangle(0, SCREEN_HEIGHT/2, SCREEN_WIDTH, 1, WHITE);

        //GOAL
        DrawRectangle(((SCREEN_WIDTH/2) - (GOAL_WIDTH/2)), 0, GOAL_WIDTH, 5, RED);
        DrawRectangle(((SCREEN_WIDTH/2) - (GOAL_WIDTH/2)), SCREEN_HEIGHT - 10, GOAL_WIDTH, 5, RED);
    }

    if(g->game == 0){
        //game over
        if (g->score_1 >= MAX_SCORE){
            draw_centred_text("!! Player One Wins !!", (SCREEN_HEIGHT/2), 25);
        } else if (g->score_2 >= MAX_SCORE){
            draw_centred_text("!!Player Two Wins!!", (SCREEN_HEIGHT/2), 25);
        }
        
        draw_centred_text("PRESS R TO RESTART", (SCREEN_HEIGHT/2) + 100, 25);
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
    float ball_top = g->ball.ball_coords.y - g->ball.radius;
    float ball_bottom = g->ball.ball_coords.y + g->ball.radius;
    float ball_left =  g->ball.ball_coords.x - g->ball.radius;
    float ball_right = g->ball.ball_coords.x + g->ball.radius;

    //goal dimensions
    //bottom goal
    float goal_left = (SCREEN_WIDTH/2) - (GOAL_WIDTH/2);
    float goal_right = (SCREEN_WIDTH/2) + (GOAL_WIDTH/2);

    //top goal


    //KEY CONTROLS
    //movement controls
    if (g->game != 0){
        //paddle 1
        if (IsKeyDown(KEY_RIGHT)){
            g->paddle1.paddle_coords.x += g->paddle1.paddle_velocity * dt;
        }
        if (IsKeyDown(KEY_LEFT)){
            g->paddle1.paddle_coords.x -= g->paddle1.paddle_velocity * dt;
        }

        //paddle 2
        if (IsKeyDown(KEY_D)){
            g->paddle2.paddle_coords.x += g->paddle2.paddle_velocity * dt;
        }
        if (IsKeyDown(KEY_A)){
            g->paddle2.paddle_coords.x -= g->paddle2.paddle_velocity * dt;
        }
    }

    //restart controls
    if (g->game == 0){
        if (IsKeyDown(KEY_R)){
            game_set(g);
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

        //BALL TOUCH ENDS
        //goal condition
        if( ball_left >= goal_left && ball_right <= goal_right){
            if ( g->ball.ball_coords.y >= SCREEN_HEIGHT && g->ball.ball_velocity.y > 0){
                game_reset(g);
                 g->score_1 ++;
            } else if( g->ball.ball_coords.y <= 0 && g->ball.ball_velocity.y < 0){
                game_reset(g);
                g->score_2 ++;
            }

        } 
        //touching end no goal -> bounce
        else{
            if ( g->ball.ball_coords.y >= SCREEN_HEIGHT ){
                g->ball.ball_velocity.y = -(g->ball.ball_velocity.y);
            }

            else if ( g->ball.ball_coords.y <= 0 ){
                g->ball.ball_velocity.y = -(g->ball.ball_velocity.y);
            }
        }

        if (g->score_1 >= MAX_SCORE || g->score_2 >= MAX_SCORE){
            g->game = 0;
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
            ball_left <= paddle1_right  // overlaps horizontally
        ){
            g->ball.ball_coords.y = paddle1_top - g->ball.radius;
            g->ball.ball_velocity.y = -(g->ball.ball_velocity.y);
        }

        //ball touching paddle2
        if (
            g->ball.ball_velocity.y < 0 && // moving down
            ball_bottom >= paddle2_top && // reached the paddle top
            ball_top <= paddle2_bottom && // hasn't passed through it
            ball_right >= paddle2_left && // overlaps horizontally
            ball_left <= paddle2_right  // overlaps horizontally
        ){
            g->ball.ball_coords.y = paddle2_top + g->ball.radius;
            g->ball.ball_velocity.y = -(g->ball.ball_velocity.y);
        }

    }

}

//this function is to initally set up the same with paddles and ball in the original positions.
void game_set(Game *g){
    g->paddle1 = (Paddle){{SCREEN_WIDTH/2 - PADDLE_HEIGHT, SCREEN_HEIGHT*0.85}, PADDLE_WIDTH, PADDLE_HEIGHT, 450.0f};
    g->paddle2 = (Paddle){{SCREEN_WIDTH/2 - PADDLE_HEIGHT, SCREEN_HEIGHT*0.15}, PADDLE_WIDTH, PADDLE_HEIGHT, 450.0f};

    g->ball = (Ball){SCREEN_WIDTH/2, SCREEN_HEIGHT * 0.2, 10, {250, 150}};

    g->game = 1;

    g->score_1 = 0;
    g->score_2 = 0;
}

//this function is used to restart the game after a point has been scored
void game_reset(Game *g){
    g->ball.ball_coords.x = SCREEN_WIDTH/2;
    g->ball.ball_coords.y = SCREEN_HEIGHT * 0.2;
    g->ball.ball_velocity.x = 250;
    g->ball.ball_velocity.x = 150;

    g->game = 1;
}