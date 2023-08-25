#include <iostream>
#include "include/raylib.h"
#include "game.hpp"
#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

using std::string;

void Game::initGame(){
    Image board = LoadImage("images/SnakeBoard.png");   
    ImageResize(&board, screenHeight, screenHeight) ;
    texture = LoadTextureFromImage(board);
    UnloadImage(board);     
    generateBoard();
    user.initSnake();
    SetTargetFPS(10); // allows the user to actually see what is going on in the game (keeping them on the grids)
    count = 0;

}

Color Game::randomColor(){
    int c1, c2, c3;
    c1 = rand() % 255;
    c2 = rand() % 255;
    c3 = rand() % 255;
    return { (unsigned char)c1,  (unsigned char) c2,  (unsigned char) c3, 255};
}

void Game::generateBoard(){
    int width = 950;
    int height = 650;
    Color Color1 = randomColor();
    Color Color2 = randomColor();
    // Dynamic memory allocation to store pixels data (Color type)
    Color *pixels = (Color *)malloc(width*height*sizeof(Color));

    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            if (((x / 50 + y / 50) /1 ) % 2 == 0) 
                pixels[y*width + x] = Color1; // Orange
            else 
                pixels[y*width + x] = Color2; // Gold
    }}

    checkedIm = {
        .data = pixels,             // We can assign pixels directly to data
        .width = width,
        .height = height,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
        
    };

    checked = LoadTextureFromImage(checkedIm);
    UnloadImage(checkedIm);
}

string Game::gameLoop(int &userScore){
    shader = LoadShader(0, TextFormat("images/shaders/wave.fs", GLSL_VERSION));

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
     
    bool looping = true; 
    Color BackGround = {200, 130, 255, 255}; // Purple  200 122 255
    while (looping){
        seconds += GetFrameTime();

        SetShaderValue(shader, secondsLoc, &seconds, SHADER_UNIFORM_FLOAT);
        if(user.gameContinue()){
            user.snakeEat();
            user.inputSnake();
        }
        else if (count < 30){
            count++;
        }
            else return "menu";
        if (WindowShouldClose()){ 
            return "quit";
        }
        if(IsKeyDown(KEY_R))
            return "menu";
       
        
        BeginDrawing();
            ClearBackground(BackGround); 
            BeginShaderMode(shader);
                DrawTexture(checked, screenWidth/2 - checked.width/2, screenHeight/2 - checked.height/2, Fade(WHITE, 0.7f));
            EndShaderMode();
            DrawText(TextFormat("Score: %01i", user.foodCount()), screenWidth/2 -40, 10, 25, DARKGRAY);
            user.printSnake();
            if (count > 0){
                DrawRectangle(screenWidth/2 - 300, screenHeight/2 - 300,600, 600, Fade(WHITE, 0.5f));
            }
            if (count > 2){
                DrawRectangle(screenWidth/2 - 300, screenHeight/2 - 300,600, 600, WHITE);
                DrawText(TextFormat("Game over your score was: %01i", user.foodCount()), screenWidth/4, screenHeight/2, 30, DARKGRAY);
            }

        EndDrawing();
        userScore = user.foodCount();
       
    }
    user.close();
    UnloadTexture(checked); 
    UnloadShader(shader);
    SetTargetFPS(120); //changes frame rate back to 120
    return "menu";
}