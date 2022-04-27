#include <stdio.h>
#include "raylib.h"
#include "deflib.h"

void PrintTab(int idNivel, Jogador player, Texture2D vida, Texture2D enerTexture) {

    const int screenHeight = GetScreenHeight();
    const int screenWidth = GetScreenWidth();
    int i;

    char text[7] = "Fase  ";
    text[5] = idNivel + '0';
    text[6] = '\0';

    DrawRectangle(0, N_LINHAS*LIN_SIZE,
                  screenWidth, screenHeight - N_LINHAS*LIN_SIZE,
                  GRAY);

    int spaceX = 25;
    for(i = 0; i < player.vidas; i++) {
        spaceX = i*(20);
        DrawTexture(vida, 25+spaceX, N_LINHAS*LIN_SIZE + 25, RAYWHITE);
    }

    if(player.timer > 0) {
        spaceX = 25 + spaceX + 50;
        DrawTexture(enerTexture, spaceX+25, N_LINHAS*LIN_SIZE + 25, RAYWHITE);
    }

    DrawText(text,
    (screenWidth-MeasureText(text, 40))/2, 630, 40, RAYWHITE);

}

void CheckPause(int *screen_game) {

    if(IsKeyPressed(KEY_P)) {
        if(*screen_game == GAME) {
            *screen_game = PAUSE;
        } else {
            *screen_game = GAME;
        }
    }

}
