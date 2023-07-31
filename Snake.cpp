#include <iostream>
#include "include/raylib.h"
#include "Snake.hpp"

void Snake::initSnake(){
    snakePosX[0]  = screenWidth/2 - ((boardX/2) - 5) + 150;
    snakePosY[0]  = screenHeight/2 - ((boardY/2) - 5) + 150;
    snakePosX[1]  = screenWidth/2 - ((boardX/2) - 5) + 100;
    snakePosY[1]  = screenHeight/2 - ((boardY/2) - 5) + 150;
    snakePosX[2]  = screenWidth/2 - ((boardX/2) - 5) + 50;
    snakePosY[2]  = screenHeight/2 - ((boardY/2) - 5) + 150;
    foodX =  screenWidth/2 - ((boardY/2) - 5) + 400;
    foodY = screenHeight/2 - ((boardY/2) - 5) + 150;
    right = false;
    left = false;
    down = false;
    up = false;
    count = 50;
    snakeLength = 3;
    snake = LoadImage("images/Snake.png");   
    ImageResize(&snake, charWH, charWH) ;
    snakeSkin = LoadTextureFromImage(snake);
    UnloadImage(snake);   
    body = LoadImage("images/snakeBody.png");
    ImageResize(&body, charWH, charWH) ;
    snakeBody = LoadTextureFromImage(body); 
    UnloadImage(body);   
}

void Snake::snakeMovement(float x, float y){
    for(int i = 0; i < snakeLength -1; i ++){
        snakePosX[snakeLength - i - 1] = snakePosX[snakeLength - i - 2];
        snakePosY[snakeLength - i - 1] = snakePosY[snakeLength - i - 2];
    }

    snakePosX[0] += x;
    snakePosY[0] += y;

    if (snakePosX[0] < screenWidth/2 - (boardX/2))
        snakePosX[0] -= x; // Return Death
    if (snakePosX[0] > screenWidth/2 + ((boardX/2) - charWH))
        snakePosX[0]  -= x;
    if (snakePosY[0]  > screenHeight/2 + ((boardY/2) - charWH))
        snakePosY[0]  -= y;
    if (snakePosY[0]  < screenHeight/2 - (boardY/2))
        snakePosY[0]  -= y;
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
        snakeMovement(50,0);
    if (left == true)
        snakeMovement(-50,0);
    if (up == true)
        snakeMovement(0,-50);
    if (down == true)
        snakeMovement(0,+50);
    
}
void Snake::snakeEat(){
    if(foodX == snakePosX[0] && foodY == snakePosY[0]){
        snakeLength++;
        foodRand();
    }
}

void Snake::foodRand(){
    bool restart = true; // Tests to make sure food is not inside of snake
    while(restart){
        restart = false;
        foodX = screenWidth/2 - ((boardX/2) - 5) + (rand() % 19) * 50;
        foodY = screenHeight/2 - ((boardY/2) - 5) + (rand() % 13) * 50;
    for(int i = 0; i < snakeLength; i++){
        if(foodX == snakePosX[i] && foodY == snakePosY[i]){
            restart = true;
            break;
    }}}
}

void Snake::printSnake(){
    for(int i =0; i < snakeLength; i++){
        if (i == 0)
            DrawTexture(snakeSkin, snakePosX[i], snakePosY[i], WHITE);
        else
            DrawTexture(snakeBody, snakePosX[i], snakePosY[i], WHITE);
    }
        DrawRectangle(foodX, foodY, 40, 40, BLACK);
}