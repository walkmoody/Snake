#include <iostream>
#include "include/raylib.h"
#include "game.hpp"


using std::string;

void Game::initGame(){
    
    user.initSnake();
}

string Game::gameLoop(){

    bool looping = true;
    while (looping){

        user.inputSnake();
        if (WindowShouldClose()){ // LINE NEEDED TO CLOSE THE GAME
            return "quit";
        }
        if(IsKeyDown(KEY_R))
            return "menu";
    
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Move the snake around with arrow Keys", 10, 10, 20, DARKGRAY);

            user.printSnake();

        EndDrawing();
    }
    return "menu";
}