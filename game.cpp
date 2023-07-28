#include <iostream>
#include "include/raylib.h"
#include "game.hpp"
using std::string;

void Game::initGame(){
    ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };
}

string Game::gameLoop(){
    
    bool looping = true;
    while (looping){
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) 
            ballPosition.x += 2.0f;
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) 
            ballPosition.x -= 2.0f;
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) 
            ballPosition.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) 
            ballPosition.y += 2.0f;
        if (WindowShouldClose()){ // LINE NEEDED TO CLOSE THE GAME
            return "quit";
        }
        if(IsKeyDown(KEY_R))
            return "menu";
    
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);

            DrawCircleV(ballPosition, 50, MAROON);

        EndDrawing();
    }
    return "menu";
}