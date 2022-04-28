#include <stdio.h>
#include <math.h>
#include "raylib.h"
#include "deflib.h"

void PrintTab(int idNivel, Jogador player, Texture2D vida, Texture2D enerTexture) {

    const int screenHeight = GetScreenHeight();
    const int screenWidth = GetScreenWidth();
    int i;

    char text[7] = "Fase _ ";
    text[5] = idNivel + '0';
    text[6] = '\0';

    char score[14] = "Score: ______ ";
    int numDig = 1;
    float scoreTemp = (float)player.score;

    while(scoreTemp >= 10) {
        scoreTemp /= 10;
        numDig++;
    }

    scoreTemp = (float)player.score;
    for(i = numDig-1; i >= 0; i--) {
        int dig = (int)(scoreTemp / pow(10, i));
        score[6+numDig-i] = dig + '0';
        scoreTemp -= dig*pow(10, i);
    }

    score[6+numDig+1] = '\0';

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
    (screenWidth-MeasureText(text, 35))/2, 620, 35, RAYWHITE);

    DrawText(score,
    (screenWidth-MeasureText(score, 20))/2, 660, 20, RAYWHITE);

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
