#include <iostream>
#include "include/raylib.h"
#include "Snake.hpp"

void Snake::initSnake(){
    snakePosX = 400;
    snakePosY = 300;
    right = false;
    left = false;
    down = false;
    up = false;
    snake = LoadImage("images/Snake.png");   
    ImageResize(&snake, charWH, charWH) ;
    snakeSkin = LoadTextureFromImage(snake);
    UnloadImage(snake);     
}

void Snake::snakeMovement(float x, float y){
    snakePosX += x;
    snakePosY += y;
    if (snakePosX < screenWidth/2 - 475)
        snakePosX -= x;
    if (snakePosX > screenWidth/2 + (475 - charWH))
        snakePosX -= x;
    if (snakePosY > screenHeight/2 + (325 - charWH))
        snakePosY -= y;
    if (snakePosY < screenHeight/2 - 325)
        snakePosY -= y;
}

void Snake::inputSnake(){
    if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && left != true){
        right = true;
        left = false;
        down = false;
        up = false;
    }
    else if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && right != true){
        right = false;
        left = true;
        down = false;
        up = false;
    }
    else if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && up != true){
        right = false;
        left = false;
        down = true;
        up = false;
    }
    else if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && down != true){
        right = false;
        left = false;  
        down = false;
        up = true;
    }
    
    if (right == true)
        snakeMovement(5,0);
    if (left == true)
        snakeMovement(-5,0);
    if (up == true)
        snakeMovement(0,-5);
    if (down == true)
        snakeMovement(0,+5);
    
}

void Snake::printSnake(){
    DrawTexture(snakeSkin, snakePosX, snakePosY, WHITE);

}