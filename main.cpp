#include <iostream>
#include "include/raylib.h"
#include "menus.hpp"

using std::string;

int main(void)
{
    const int screenWidth = 1080; // FIX
    const int screenHeight = 720;
    Image image = LoadImage("images/apple.png");
    
    InitWindow(screenWidth, screenHeight, "Snake");
    SetWindowIcon(image);
    UnloadImage(image);

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
        else if (screen == "gameOver")
            screen = displayScreen.gameOver();
        else if (screen == "instructions")
            screen = displayScreen.instructions();
        else if (screen == "quitScreen")
            screen = displayScreen.quitScreen();
        else{
            looping = false;
        }
    }
    displayScreen.reWriteHi();
    CloseWindow(); 
    return 0;
}