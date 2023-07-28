#include <iostream>
#include "include/raylib.h"

using std::string;

class Menus{
    public: // EVERYTHING NEEDED TO BE IMPLEMENTED
        void initMenus();
        string splash();
        string mainMenu();
        string gameScreen();
        string gameOver();
        string instructions();
        string quitScreen();
    private:
        int count = 0;
};