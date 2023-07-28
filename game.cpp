#include <iostream>
#include "include/raylib.h"
#include "game.hpp"


using std::string;

void Game::initGame(){
    Image board = LoadImage("images/SnakeBoard.png");   
    ImageResize(&board, screenHeight, screenHeight) ;
    texture = LoadTextureFromImage(board);
    UnloadImage(board);     
    generateBoard();
    user.initSnake();

}

void Game::generateBoard(){
    int width = 960;
    int height = 650;

    // Dynamic memory allocation to store pixels data (Color type)
    Color *pixels = (Color *)malloc(width*height*sizeof(Color));

    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            if (((x / 32 + y / 32) /1 ) % 2 == 0) 
                pixels[y*width + x] = ORANGE;
            else 
                pixels[y*width + x] = GOLD;
    }}

    checkedIm = {
        .data = pixels,             // We can assign pixels directly to data
        .width = width,
        .height = height,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
        
    };

    checked = LoadTextureFromImage(checkedIm);
    UnloadImage(checkedIm);
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
            DrawTexture(checked, screenWidth/2 - checked.width/2, screenHeight/2 - checked.height/2, Fade(WHITE, 0.5f));
            DrawText("Move the snake around with arrow Keys", 10, 10, 20, DARKGRAY);

            user.printSnake();

        EndDrawing();
    }
    UnloadTexture(checked);  
    return "menu";
}