#include <iostream>
#include <fstream>
#include "include/raylib.h"
#include "menus.hpp"
#include "game.hpp"
#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif


void Menus::initMenus(){
    count = 0;
    userScore = 0;
    std::ifstream fin;
    fin.open("images/files/hiscore.txt");
    if(fin.eof())
        hiScore = 0;
    else 
        fin >> hiScore;
    fin.close();
}

void Menus::reWriteHi(){
    std::ofstream fout;
    fout.open("images/files/hiscore.txt");
    fout << hiScore;

    fout.close();

}
string Menus::splash(){
    Image fruit = LoadImage("images/apple.png");
    ImageResize(&fruit, 300, 300);
    Texture2D fruitTexture = LoadTextureFromImage(fruit);
    UnloadImage(fruit);
    while(count < 90){
        BeginDrawing();

            ClearBackground(BLACK);
            DrawTexture(fruitTexture, screenWidth/3, screenHeight/4, WHITE);
            DrawText("SNAKEEE", 300, 300, 20, LIGHTGRAY);

        EndDrawing();
        if (WindowShouldClose()) // LINE NEEDED TO CLOSE THE GAME
            return "quit";
        count++;
    }
    UnloadTexture(fruitTexture);
    return "menu";
}

string Menus::mainMenu(){
    SetTargetFPS(120);
    Image space = LoadImage("images/space.png");   
    ImageResize(&space, screenWidth, screenHeight) ;
    Texture2D texture  = LoadTextureFromImage(space);
    UnloadImage(space);
    Image space2 = LoadImage("images/space2.png");   
    ImageResize(&space2, screenWidth, screenHeight) ;
    Texture2D texture2  = LoadTextureFromImage(space2);
    UnloadImage(space2);   
    
    // Load shader and setup location points and values
    Shader shader = LoadShader(0, TextFormat("images/shaders/wave.fs", GLSL_VERSION));

    int secondsLoc = GetShaderLocation(shader, "secondes");
    int freqXLoc = GetShaderLocation(shader, "freqX");
    int freqYLoc = GetShaderLocation(shader, "freqY");
    int ampXLoc = GetShaderLocation(shader, "ampX");
    int ampYLoc = GetShaderLocation(shader, "ampY");
    int speedXLoc = GetShaderLocation(shader, "speedX");
    int speedYLoc = GetShaderLocation(shader, "speedY");

    // Shader uniform values that can be updated at any time
    float freqX = 25.0f;
    float freqY = 25.0f;
    float ampX = 5.0f;
    float ampY = 5.0f;
    float speedX = 1.0f;
    float speedY = 1.0f;

    float screenSize[2] = { (float)GetScreenWidth(), (float)GetScreenHeight() };
    SetShaderValue(shader, GetShaderLocation(shader, "size"), &screenSize, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, freqXLoc, &freqX, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, freqYLoc, &freqY, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, ampXLoc, &ampX, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, ampYLoc, &ampY, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, speedXLoc, &speedX, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, speedYLoc, &speedY, SHADER_UNIFORM_FLOAT);

    float seconds = 0.0f;
    if (userScore > hiScore)
        hiScore = userScore;

    while (!WindowShouldClose()){   // Detect window close button or ESC key
        if (IsKeyDown(KEY_SPACE))
            return "game";
        if (IsKeyDown(KEY_I))
            return "instructions";

        seconds += GetFrameTime();

        SetShaderValue(shader, secondsLoc, &seconds, SHADER_UNIFORM_FLOAT);
        
        BeginDrawing();
            ClearBackground(RAYWHITE);
           
            BeginShaderMode(shader);


                DrawTexture(texture, 0, 0, WHITE);
                DrawTexture(texture, texture.width, 0, WHITE);
                DrawText("SNAKE THE VIDEO GAME", screenHeight/4, screenWidth/4, 50, WHITE);
            EndShaderMode();

            DrawTexture(texture2, 0, 0, WHITE);
            DrawTexture(texture2, texture2.width, 0, WHITE);
           
            DrawText("Press space to continue", screenWidth/2 - 30, screenHeight/3, 20, WHITE);
            DrawText(TextFormat("Your score: %01i", userScore), 100, 100, 20, WHITE);
            DrawText(TextFormat("High score: %01i", hiScore), 100, 70, 20, WHITE);
                        
           

        EndDrawing();

    }
    UnloadShader(shader);   
    UnloadTexture(texture);
    UnloadTexture(texture2); 
    return "quit";
}

string Menus::gameScreen(){
    Game mainGame;
    mainGame.initGame();
    string screen = mainGame.gameLoop(userScore);
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