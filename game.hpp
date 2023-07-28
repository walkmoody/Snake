#include <iostream>
#include "include/raylib.h"

class Game{
    public:
        void initGame();
        std::string gameLoop();
    private:
        Vector2 ballPosition;
        const int screenWidth = 1080; // FIX
        const int screenHeight = 720;
};