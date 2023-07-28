#include <iostream>
#include "include/raylib.h"
#include "menus.hpp"
#include "game.hpp"

void Menus::initMenus(){
    count = 0;
}
string Menus::splash(){
 
    while(count < 60){
        BeginDrawing();

            ClearBackground(BLACK);
            
            DrawText("SNAKE", 300, 300, 20, LIGHTGRAY);

        EndDrawing();
        if (WindowShouldClose()) // LINE NEEDED TO CLOSE THE GAME
            return "quit";
        
        count++;
    }
    return "menu";
}

string Menus::mainMenu(){
    while (!WindowShouldClose()){   // Detect window close button or ESC key
        if (IsKeyDown(KEY_SPACE))
            return "game";
        
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawText("SNAKE THE VIDEO GAME", screenWidth/4, screenHeight/3, 40, BLACK);

        EndDrawing();

    }
    return "quit";
}

string Menus::gameScreen(){
    Game mainGame;
    mainGame.initGame();
    string screen = mainGame.gameLoop();
    if (screen == "menu")
        return "menu";
    if (screen == "quit")
        return "quit";
    else 
        return "quit";
}

string Menus::gameOver(){
    return "menu";
}

string Menus::instructions(){
    return "menu";
}

string Menus::quitScreen(){
    return "quit";
}