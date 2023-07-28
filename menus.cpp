#include <iostream>
#include "include/raylib.h"
#include "menus.hpp"

void Menus::initMenus(){
    count = 0;
}
string Menus::splash(){

    while(count <90 && !WindowShouldClose()){
        BeginDrawing();

            ClearBackground(BLACK);
            
            DrawText("SNAKE", 300, 300, 20, LIGHTGRAY);

        EndDrawing();
        count ++;
    }
    if (WindowShouldClose() == true)
        return "quit";
    else
        return "menu";
}

string Menus::mainMenu(){
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        /*
        if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 5.0f;
        if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.0f;
        
        */
        BeginDrawing();

            ClearBackground(RAYWHITE);
            

            DrawText("Congrats! You created your first window!", 300/4, 200/3, 20, BLACK);

            //DrawCircleV(ballPosition, 50, MAROON);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    return "quit"; // CHANGE TO GAME
}

string Menus::gameScreen(){
    return "menu";
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