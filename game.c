/*******************************************************************************************
*
*   raylib [textures] example - Texture loading and drawing a part defined by a rectangle
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define MAX_FRAME_SPEED     15
#define MIN_FRAME_SPEED      1

void Game_screen(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1800;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "raylib [texture] example - texture rectangle");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D scarfy = LoadTexture("resources/oi.png");
    float x = 0;
    float y = 0;
    float limitey = 0, limitex = 0;      // Texture loading

     // Number of spritesheet frames shown by second

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Source rectangle (part of the texture to use for drawing)

    // Destination rectangle (screen rectangle where drawing part of texture)


    // Origin of the texture (rotation/scale point), it's relative to destination rectangle size


    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        Rectangle tela = {0,0,screenWidth,screenHeight,GREEN};
        Rectangle pers = {x,y,70,70,GREEN};
        limitey = screenHeight - 90;
        limitex = screenWidth - 80;
        //----------------------------------------------------------------------------------
        if(IsKeyDown(KEY_UP)){
            y-= 10;
        }
        if(IsKeyDown(KEY_DOWN)){
            y+= 10;
        }
        if(IsKeyDown(KEY_RIGHT)){
            x+= 10;
        }
        if(IsKeyDown(KEY_LEFT)){
            x-= 10;
        }
        if(x > limitex){
            x = limitex;

        };
        if(x < 0){
            x = 0;

        };
        if(y > limitey){
            y = limitey;

        };
        if(y < 0){
            y = 0;

        };
        //----------------------------------------------------------------------------------


        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            DrawRectangle(0,0,screenWidth,screenHeight,BLACK);
            DrawRectangle(x,y,80,90,GREEN);
            DrawTexture(scarfy,x,y,WHITE);



        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(scarfy);       // Texture unloading

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

}
