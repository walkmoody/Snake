#include <iostream>
#include "include/raylib.h"

class Snake{
    public:
        void initSnake();
        void inputSnake();
        void printSnake();
    private:
        const int screenWidth = 1080; // FIX
        const int screenHeight = 720;
        int snakePosX, snakePosY;
};