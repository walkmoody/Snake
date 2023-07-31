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
            
            DrawText("SNAKEEE", 300, 300, 20, LIGHTGRAY);

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
        if (IsKeyDown(KEY_I))
            return "instructions";
        
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawText("SNAKE THE VIDEO GAME", screenHeight/4, screenWidth/4, 50, BLACK);
            //DrawText("SNAKE THE VIDEO GAME", screenWidth/4, screenHeight/4, 50, BLACK);
            DrawText("Press space to continue", screenWidth/2, screenHeight/3, 20, BLACK);

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
    while (!WindowShouldClose()){   // Detect window close button or ESC key
        if (IsKeyDown(KEY_SPACE))
            return "game";
        if (IsKeyDown(KEY_P))
            return "menu";
        
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawText("Heres instructions", screenHeight/4, screenWidth/4, 50, BLACK);
            //DrawText("SNAKE THE VIDEO GAME", screenWidth/4, screenHeight/4, 50, BLACK);
            DrawText("Use arrows or WASD,", screenWidth/2, screenHeight/3 - 10, 20, BLACK);
            DrawText("press P to go back or space to start", screenWidth/2, screenHeight/3 + 10, 20, BLACK);
        EndDrawing();
    }
    return "quit";
}

string Menus::quitScreen(){
    return "quit";
}