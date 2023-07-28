#include <iostream>
#include "include/raylib.h"
#include "menus.hpp"

using std::string;

int main(void)
{
    const int screenWidth = 1080; // FIX
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Snake");

    SetTargetFPS(60);
    bool looping = true;
    string screen = "splash";
    Menus displayScreen;
    displayScreen.initMenus();

    while (looping){
        if (screen == "splash")
            screen = displayScreen.splash();
        else if (screen == "menu")
            screen = displayScreen.mainMenu();
        else if (screen == "game")
            screen = displayScreen.gameScreen();    
        else if (screen == "gameScreen")
            screen = displayScreen.gameOver();
        else if (screen == "gameScreen")
            screen = displayScreen.instructions();
        else if (screen == "gameScreen")
            screen = displayScreen.quitScreen();
        else{
            looping = false;
        }
    }
    
    CloseWindow(); 
    return 0;
}