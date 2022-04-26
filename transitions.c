#include "raylib.h"
#include <stdio.h>
#include "deflib.h"

void ShowLevel(int level, char path[16]) {

    int contFrames;
    char text[7] = "Fase ", nomeFase[64];
    text[5] = level + '0';
    text[6] = '\0';

    int screenWidth = GetScreenWidth();

    FILE *fp = fopen(path, "r");
    if(fscanf(fp, "Nome: %s", nomeFase) < 0) {
        printf("Erro na leitura do nome!\n");
    }

    for(contFrames = 0; contFrames < 60; contFrames++) {

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(text,
        (screenWidth-MeasureText(text, 50))/2, 300, 50, RED);
        DrawText(nomeFase,
        (screenWidth-MeasureText(nomeFase, 20))/2, 360, 20, GRAY);

        EndDrawing();

    }

}
