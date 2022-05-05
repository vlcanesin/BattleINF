#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include "deflib.h"

/*
- TRANSITIONS:
  - Possui a função que mostra a tela de transição
  entre fases.
*/

void ShowLevel(char level, char path[16]) {

    int contFrames;
    char text[7] = "Fase _", nomeFase[64];
    if(level == 'x') {
        text[5] = 'x';
    } else {
        text[5] = level + '0';
    }
    text[6] = '\0';

    int screenWidth = GetScreenWidth();

    FILE *fp = fopen(path, "r");
    fscanf(fp, "Nome: ");
    if(fgets(nomeFase, 63, fp) == NULL) {
        printf("Erro na leitura do nome!\n");
    }

    for(contFrames = 0; contFrames < 60; contFrames++) {  // CONTA 1 SEGUNDO

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(text,
        (screenWidth-MeasureText(text, 50))/2, 300, 50, RED);
        DrawText(nomeFase,
        (screenWidth-MeasureText(nomeFase, 20))/2, 360, 20, GRAY);

        EndDrawing();

    }

}
