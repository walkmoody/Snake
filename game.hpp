#include <iostream>
#include "include/raylib.h"
#include "Snake.hpp"

class Game{
    public:
        void initGame();
        void generateBoard();
        Color randomColor();
        std::string gameLoop(int& userScore);
        

    private:
        const int screenWidth = 1080; // FIX
        const int screenHeight = 720;
        Shader shader;
        Snake user;
        Image board;
        Image checkedIm;
        Texture2D texture;
        Texture2D checked;
        int count;
        bool gameStart = true;

};