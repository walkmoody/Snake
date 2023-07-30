#include <iostream>
#include "include/raylib.h"

class Snake{
    public:
        void initSnake();
        void inputSnake();
        void printSnake();
        void snakeMovement(float, float);
    private:
        const int screenWidth = 1080; // FIX
        const int screenHeight = 720;
        int charWH = 35;
        bool right, left, down, up = false;
        int snakePosX, snakePosY;
        Image snake;
        Texture2D snakeSkin;
};