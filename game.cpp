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
    SetTargetFPS(10); // change method later

}

Color Game::randomColor(){
    int c1, c2, c3;
    c1 = rand() % 255;
    c2 = rand() % 255;
    c3 = rand() % 255;
    return { (unsigned char)c1,  (unsigned char) c2,  (unsigned char) c3, 255};
}

void Game::generateBoard(){
    int width = 950;
    int height = 650;
    Color Color1 = randomColor();
    Color Color2 = randomColor();
    // Dynamic memory allocation to store pixels data (Color type)
    Color *pixels = (Color *)malloc(width*height*sizeof(Color));

    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            if (((x / 50 + y / 50) /1 ) % 2 == 0) 
                pixels[y*width + x] = Color1; // Orange
            else 
                pixels[y*width + x] = Color2; // Gold
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

string Game::gameLoop(int &userScore){

    bool looping = true;
    while (looping){

        user.inputSnake();
        user.snakeEat();
        if (WindowShouldClose()){ // LINE NEEDED TO CLOSE THE GAME
            return "quit";
        }
        if(IsKeyDown(KEY_R))
            return "menu";
        if(user.gameContinue() == false)
            return "menu";
    
        BeginDrawing();

            ClearBackground(LIGHTGRAY);
            DrawTexture(checked, screenWidth/2 - checked.width/2, screenHeight/2 - checked.height/2, Fade(WHITE, 0.5f));
            DrawText(TextFormat("Score: %01i", user.foodCount()), 10, 10, 20, DARKGRAY);

            user.printSnake();

        EndDrawing();
        userScore = user.foodCount();
    }
    user.close();
    UnloadTexture(checked);  
    SetTargetFPS(60);
    return "menu";
}