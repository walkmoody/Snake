#include <iostream>
#include "include/raylib.h"
#include "menus.hpp"

using std::string;

int main(void)
{
    const int screenWidth = 1080; 
    const int screenHeight = 720;
    Image image = LoadImage("images/apple.png");
    
    InitWindow(screenWidth, screenHeight, "Snake");
    SetWindowIcon(image); // sets the icon to the apple
    UnloadImage(image);

    SetTargetFPS(60);
    bool looping = true; 
    string screen = "splash";
    Menus displayScreen; // Calls class displayScreen
    displayScreen.initMenus();

    while (looping){ // continues to loop as strings are returning indicating what should be ran.
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
    displayScreen.reWriteHi(); //checks to see if highscore is bigger if it is; rewrites
    CloseWindow(); 
    return 0;
}