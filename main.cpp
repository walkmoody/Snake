#include "include/raylib.h"


int main(void)
{
    const int screenWidth = 1080; // FIX
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Test");

    Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 }; // REMOVE BALL OBJECT

    SetTargetFPS(60);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.0f;
        
        
        BeginDrawing();

            ClearBackground(BLACK);
            

            DrawText("Congrats! You created your first window!", screenWidth/4, screenHeight/3, 20, LIGHTGRAY);

            DrawCircleV(ballPosition, 50, MAROON);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}