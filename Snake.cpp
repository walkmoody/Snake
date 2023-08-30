#include <iostream>
#include "include/raylib.h"
#include "Snake.hpp"

void Snake::initSnake(){ 
    snakePosX[0]  = screenWidth/2 - ((boardX/2) - 5) + 150; //Sets all positions of the snake (always the same starting position)
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
    gameCont = true;
    count = 50;
    snakeLength = 3;
    snake = LoadImage("images/Snake.png");   //Sets all the texturees and resizes them for the snake/fruit
    ImageResize(&snake, charWH, charWH);
    snakeSkinUp = LoadTextureFromImage(snake);
    ImageRotateCW(&snake);
    snakeSkinRight = LoadTextureFromImage(snake);
    ImageRotateCW(&snake);
    snakeSkinDown = LoadTextureFromImage(snake);
    ImageRotateCW(&snake);
    snakeSkinLeft = LoadTextureFromImage(snake);
    
    snakeTail = LoadImage("images/snakeTail.png");   
    ImageResize(&snakeTail, charWH, charWH);
    snakeTailUp = LoadTextureFromImage(snakeTail);
    ImageRotateCW(&snakeTail);
    snakeTailRight = LoadTextureFromImage(snakeTail);
    ImageRotateCW(&snakeTail);
    snakeTailDown = LoadTextureFromImage(snakeTail);
    ImageRotateCW(&snakeTail);
    snakeTailLeft = LoadTextureFromImage(snakeTail);

    UnloadImage(snake);
    UnloadImage(snakeTail);

    body = LoadImage("images/snakeBody.png");
    ImageResize(&body, charWH, charWH) ;
    snakeBody = LoadTextureFromImage(body); 
    UnloadImage(body);   
    fruit = LoadImage("images/apple.png");
    ImageResize(&fruit, charWH, charWH);
    fruitTexture = LoadTextureFromImage(fruit); 
    UnloadImage(fruit);   
}

bool Snake::gameContinue(){ //sends back true/false based on whether the game should continue
    return gameCont;
}

void Snake::close(){ //deallocates all the textures
    UnloadTexture(snakeSkinRight);
    UnloadTexture(snakeSkinLeft);
    UnloadTexture(snakeSkinDown);
    UnloadTexture(snakeSkinUp);
    UnloadTexture(snakeTailRight);
    UnloadTexture(snakeTailLeft);
    UnloadTexture(snakeTailDown);
    UnloadTexture(snakeTailUp);
    UnloadTexture(snakeBody);
    UnloadTexture(fruitTexture);
}

void Snake::snakeMovement(float x, float y){ // moves snake and calculates all of the tail keeps snake on grid
    for(int i = 0; i < snakeLength -1; i ++){
        snakePosX[snakeLength - i - 1] = snakePosX[snakeLength - i - 2];
        snakePosY[snakeLength - i - 1] = snakePosY[snakeLength - i - 2];
    } 
    
    snakeTailX = snakePosX[snakeLength - 1]; // MAKE A COPY OF THE TAIL TO NOT LOSE INFORMATION
    snakeTailY = snakePosY[snakeLength - 1];
    std::cout << snakeTailX << " " << snakeTailY << std::endl;

    snakePosX[0] += x;
    snakePosY[0] += y;

    if (snakePosX[0] < screenWidth/2 - (boardX/2))
        snakePosX[0] -= x; 
    if (snakePosX[0] > screenWidth/2 + ((boardX/2) - charWH))
        snakePosX[0] -= x;
    if (snakePosY[0] > screenHeight/2 + ((boardY/2) - charWH))
        snakePosY[0] -= y;
    if (snakePosY[0] < screenHeight/2 - (boardY/2))
        snakePosY[0] -= y;
    for(int i = 1; i < snakeLength -1; i ++) // checks to see if there is overlap if true returns Death 
        if (snakePosX[0] == snakePosX[i] && snakePosY[0] == snakePosY[i]) 
            gameCont = false; //DEATH
}

void Snake::inputSnake(){ // Grabs the user input
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

int Snake::foodCount(){ // Keeps score (does not include the starting length of snake)
    return snakeLength -3; //Returns to the score to the score board
}

void Snake::foodRand(){ // Randomizes the fruit
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

void Snake::printSnake(){ // Calculates which way the snake should be printed and keeps snake attached to itself
    DrawTexture(fruitTexture, foodX, foodY, WHITE); // If death is true do Not print i = 1
    for(int i =0; i < snakeLength; i++){
        if (i == 0){
           continue;
        }
        else if (!gameCont && i == 1){ 
            continue;
        }
        else if (i == snakeLength -1){
            if(snakePosX[i] == snakePosX[i-1] && snakePosY[i] > snakePosY[i-1]){
                DrawTexture(snakeTailUp, snakePosX[i], snakePosY[i], WHITE);
                DrawTexture(snakeBody, snakePosX[i], snakePosY[i] -25, WHITE);
            }
            else if(snakePosX[i] == snakePosX[i-1] && snakePosY[i] < snakePosY[i-1]){
                DrawTexture(snakeTailDown, snakePosX[i], snakePosY[i], WHITE);
                DrawTexture(snakeBody, snakePosX[i], snakePosY[i] +25, WHITE);

            }
            else if(snakePosX[i] < snakePosX[i-1] && snakePosY[i] == snakePosY[i-1]){
                DrawTexture(snakeTailRight, snakePosX[i], snakePosY[i], WHITE);
                DrawTexture(snakeBody, snakePosX[i] +25, snakePosY[i], WHITE);
            }
            else if(snakePosX[i] > snakePosX[i-1] && snakePosY[i] == snakePosY[i-1]){
                DrawTexture(snakeTailLeft, snakePosX[i], snakePosY[i], WHITE);
                DrawTexture(snakeBody, snakePosX[i] -25, snakePosY[i], WHITE);
            }
            else{
                DrawTexture(snakeTailLeft, snakePosX[i], snakePosY[i], WHITE);
                DrawTexture(snakeBody, snakePosX[i] -25, snakePosY[i], WHITE);
            }
        }
        else{
            DrawTexture(snakeBody, snakePosX[i], snakePosY[i], WHITE);
            if(snakePosY[i] > snakePosY[i-1])
                DrawTexture(snakeBody, snakePosX[i], snakePosY[i] -25, WHITE);
            if( snakePosY[i] < snakePosY[i-1])
                DrawTexture(snakeBody, snakePosX[i], snakePosY[i] +25, WHITE);
            if(snakePosX[i] < snakePosX[i-1])
                DrawTexture(snakeBody, snakePosX[i] +25, snakePosY[i], WHITE);
            if(snakePosX[i] > snakePosX[i-1])
                DrawTexture(snakeBody, snakePosX[i] -25, snakePosY[i], WHITE);
           
        }
       
    }
    if(!gameCont){
        snakePosX[1] = snakePosX[2];
        snakePosY[1] = snakePosY[2];

        //DrawTexture(snakeTailRight, snakeTailX, snakeTailY, WHITE); // Does this work??
        //DrawTexture(snakeBody, snakePosX[snakeLength - 1] +25, snakePosY[snakeLength - 1], WHITE); // FIXME
    }
        if(right){
            DrawTexture(snakeBody, snakePosX[1] +20, snakePosY[1], WHITE);
            DrawTexture(snakeSkinRight, snakePosX[0], snakePosY[0], WHITE);
            
        }
        else if(left){
            DrawTexture(snakeBody, snakePosX[1] -20, snakePosY[1], WHITE);
            DrawTexture(snakeSkinLeft, snakePosX[0], snakePosY[0], WHITE);
        }
        else if(up){
            DrawTexture(snakeBody, snakePosX[1], snakePosY[1] -20, WHITE);
            DrawTexture(snakeSkinUp, snakePosX[0], snakePosY[0], WHITE);
        }
        else if(down){
            DrawTexture(snakeBody, snakePosX[1], snakePosY[1] +20, WHITE);
            DrawTexture(snakeSkinDown, snakePosX[0], snakePosY[0], WHITE);
            
        }
        else {
            DrawTexture(snakeBody, snakePosX[1] +20, snakePosY[1], WHITE);
            DrawTexture(snakeSkinRight, snakePosX[0], snakePosY[0], WHITE);
        }
}