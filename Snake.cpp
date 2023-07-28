#include <iostream>
#include "include/raylib.h"
#include "Snake.hpp"

void Snake::initSnake(){
    snakePosX = screenWidth/2;
    snakePosY = screenHeight/2;
    snake = LoadImage("images/Snake.png");   
    ImageResize(&snake, 35, 35) ;
    snakeSkin = LoadTextureFromImage(snake);
    UnloadImage(snake);     
}
void Snake::inputSnake(){
    if( snakePosX % 5 == 0)
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) 
        snakePosX += 5.0f;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) 
        snakePosX -= 5.0f;
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) 
        snakePosY -= 5.0f;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) 
        snakePosY += 5.0f;
}
void Snake::printSnake(){
    DrawTexture(snakeSkin, snakePosX, snakePosY, WHITE);
    //DrawRectangle(snakePosX, snakePosY, 35, 35, RED);
}