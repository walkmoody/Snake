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
    Color Color1 = randomColor(); // Calls a random num gen
    Color Color2 = randomColor(); // Calls a random num gen
    // Dynamic memory allocation to store pixels data (Color type)
    Color *pixels = (Color *)malloc(width*height*sizeof(Color));

    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            if (((x / 50 + y / 50) /1 ) % 2 == 0) 
                pixels[y*width + x] = Color1;
            else 
                pixels[y*width + x] = Color2; 
    }}

    checkedIm = {
        .data = pixels,
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
        else if (count < 4){
            count++;
        }
        else if(IsKeyDown(KEY_SPACE))
            return "menu";
        
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
            if (count > 0 && count < 4){
                SetTargetFPS(60);
                DrawRectangle(screenWidth/2 - 300, screenHeight/2 - 300,600, 600, Fade(WHITE, 0.5f));
                DrawText(TextFormat("Game Over"), screenWidth/2 - 150, screenHeight/2-70, 50, Fade(DARKGRAY, 0.5f));
                DrawText(TextFormat("Your score was: %01i", user.foodCount()), screenWidth/2 - 150, screenHeight/2, 30, Fade(DARKGRAY, 0.5f));
                DrawText(TextFormat("Press R to return"), screenWidth/2 - 150, screenHeight/2+50, 30, DARKGRAY);
            }
            else if (count > 3){
                DrawRectangle(screenWidth/2 - 300, screenHeight/2 - 300,600, 600, WHITE);
                DrawText(TextFormat("Game Over"), screenWidth/2 - 150, screenHeight/2-100, 50, DARKGRAY);
                DrawText(TextFormat("Your score was: %01i", user.foodCount()), screenWidth/2 - 150 - (17 + ( user.foodCount() % 10) + 10), screenHeight/2, 30, DARKGRAY); // FIXME CENTER THE TEXT // 17
                DrawText(TextFormat("Press Space to restart"), (screenWidth/2) - 150 - (22 + 10), screenHeight/2+50, 30, DARKGRAY); // Take the length of the string (22)
                DrawText(TextFormat("Press R to return to menu"), screenWidth/2 - 150 - (25 + 10), screenHeight/2+100, 30, DARKGRAY); // Length is 25 * 1.5
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