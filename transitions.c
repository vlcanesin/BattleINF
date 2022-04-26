#include "raylib.h"
#include <stdio.h>
#include "deflib.h"

void ShowLevel(int level) {

    int contFrames;
    char text[8] = "Nivel ";
    text[6] = level + '0';
    text[7] = '\0';

    int screenWidth = GetScreenWidth();

    for(contFrames = 0; contFrames < 60; contFrames++) {

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(text,
        (screenWidth-MeasureText(text, 50))/2, 300, 50, RED);

        EndDrawing();

    }

}
