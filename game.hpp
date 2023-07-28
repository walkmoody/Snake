#include <iostream>
#include "include/raylib.h"
#include "Snake.hpp"

class Game{
    public:
        void initGame();
        std::string gameLoop();
    private:
        
        const int screenWidth = 1080; // FIX
        const int screenHeight = 720;
        Snake user;
};