#include "raylib.h"
#include <stdio.h>

int menuOption = 0;
// Option that is selected in menu

void MenuScreen(int *screen) {

    //------------- UPDATING --------------//
    int screenWidth = GetScreenWidth();
    //int screenHeight = GetScreenHeight();

    int i, options = 5;
    Color colors[options];

    if(IsKeyPressed(KEY_DOWN))
        menuOption = (menuOption + 1) % options;
    if(IsKeyPressed(KEY_UP))
        menuOption = (menuOption + options - 1) % options;

    for(i = 0; i < options; i++) {
        if(i == menuOption) colors[i] = BLACK;
        else colors[i] = GRAY;
    }

    if(IsKeyPressed(KEY_ENTER)) {

        switch(menuOption) {

        case 0: *screen = 2;  // GameScreen
        break;
        case 1: *screen = 3;  // LoadedGameScreen
        break;
        case 2: *screen = 4;  // LoadMapScreen
        break;
        case 3: *screen = 5;  // RankingScreen
        break;
        case 4: *screen = 6;  // QuitScreen
        break;

        }

    }

    //-------------- DRAWING --------------//
    BeginDrawing();
    ClearBackground(RAYWHITE);
    // Title
    DrawText("BattleINF v1.0",
             (screenWidth-MeasureText("BattleINF v1.0", 62))/2, 100, 62, RED);

    // Options
    DrawText("Novo Jogo",
             (screenWidth-MeasureText("Novo Jogo", 20))/2, 220, 20, colors[0]);
    DrawText("Continuar",
             (screenWidth-MeasureText("Continuar", 20))/2, 270, 20, colors[1]);
    DrawText("Carregar mapa",
             (screenWidth-MeasureText("Carregar mapa", 20))/2, 320, 20, colors[2]);
    DrawText("Ranking",
             (screenWidth-MeasureText("Ranking", 20))/2, 370, 20, colors[3]);
    DrawText("Sair",
             (screenWidth-MeasureText("Sair", 20))/2, 420, 20, colors[4]);

    EndDrawing();

}
