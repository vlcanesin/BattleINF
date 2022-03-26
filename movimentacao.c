/*#include "raylib.h"
#include <stdio.h>

int main() {

    int screenWidth = 1000;
    int screenHeight = 600;

    int sqr_len = 100;
    Rectangle sqr = {(screenWidth-sqr_len)/2.0, (screenHeight-sqr_len)/2.0, sqr_len, sqr_len};

    InitWindow(screenWidth, screenHeight, "Movement of a square");
    SetTargetFPS(120);

    while(!WindowShouldClose()) {

    //------------- UPDATING --------------//
        float x = sqr.x, y = sqr.y;

        if(IsKeyDown(KEY_RIGHT)) sqr.x += 10.0;
        if(IsKeyDown(KEY_LEFT)) sqr.x -= 10.0;
        if(IsKeyDown(KEY_UP)) sqr.y -= 10.0;
        if(IsKeyDown(KEY_DOWN)) sqr.y += 10.0;

        if(sqr.x < 0 || sqr.x > screenWidth-sqr_len) sqr.x = x;
        if(sqr.y < 0 || sqr.y > screenHeight-sqr_len) sqr.y = y;

    //-------------- DRAWING --------------//
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawRectangleRec(sqr, RED);

        EndDrawing();

    }

    return 0;

}*/
