#include <iostream>
#include "include/raylib.h"

using std::string;

class Menus{
    public: // EVERYTHING NEEDED TO BE IMPLEMENTED
        void initMenus();
        void reWriteHi();
        string splash();
        string mainMenu();
        string gameScreen();
        string instructions();
        string quitScreen();
    private:
        const int screenWidth = 1080; // FIX
        const int screenHeight = 720;
        int hiScore = 0;
        int count = 0;
        int userScore = 0;
};