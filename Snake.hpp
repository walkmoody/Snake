#include <iostream>
#include "include/raylib.h"

class Snake{
    public:
        void initSnake();
        void foodRand();
        void inputSnake();
        void printSnake();
        void snakeEat();
        bool gameContinue();
        void snakeMovement(float, float);
        int foodCount();
        void close();
    private:
        const int screenWidth = 1080; // FIX
        const int screenHeight = 720;
        const int boardX = 950;
        const int boardY = 650;
        const int charWH = 40;
        bool right, left, down, up = false;
        bool gameCont = true;
        int snakePosX[250], snakePosY[250]; 
        int count, snakeLength;
        int foodX, foodY;
        int snakeTailX, snakeTailY; // used to create copy of tail to not lose information
        Image snake;
        Texture2D snakeSkinRight;
        Texture2D snakeSkinLeft;
        Texture2D snakeSkinDown;
        Texture2D snakeSkinUp;
        Image snakeTail;
        Texture2D snakeTailLeft;
        Texture2D snakeTailUp;
        Texture2D snakeTailRight;
        Texture2D snakeTailDown;
        Image body;
        Texture2D snakeBody;
        Image fruit;
        Texture2D fruitTexture;
};