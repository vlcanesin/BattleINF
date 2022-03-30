#include "raylib.h"
#include <stdio.h>

#define MENU 1
#define GAME 2
#define LOADED_GAME 3
#define LOAD_MAP 4
#define RANKING 5
#define QUIT 6
#define ASK_NAME 7

void MenuScreen(int *screen, int *menuOption) {

    //------------- UPDATING --------------//
    int screenWidth = GetScreenWidth();
    //int screenHeight = GetScreenHeight();

    int i, options = 5;
    Color colors[options];

    if(IsKeyPressed(KEY_DOWN))
        *menuOption = (*menuOption + 1) % options;
    if(IsKeyPressed(KEY_UP))
        *menuOption = (*menuOption + options - 1) % options;

    for(i = 0; i < options; i++) {
        if(i == *menuOption) colors[i] = BLACK;
        else colors[i] = GRAY;
    }

    if(IsKeyPressed(KEY_ENTER)) {

        switch(*menuOption) {

        case 0: *screen = GAME;  // GameScreen
        break;
        case 1: *screen = LOADED_GAME;  // LoadedGameScreen
        break;
        case 2: *screen = LOAD_MAP;  // LoadMapScreen
        break;
        case 3: *screen = RANKING;  // RankingScreen
        break;
        case 4: *screen = QUIT;  // QuitScreen
        break;

        }

    }

    //-------------- DRAWING --------------//
    BeginDrawing();
    ClearBackground(RAYWHITE);
    // Title
    DrawText("BattleINF v1.0",
             (screenWidth-MeasureText("BattleINF v1.0", 62))/2, 150, 62, RED);

    // Options
    DrawText("Novo Jogo",
             (screenWidth-MeasureText("Novo Jogo", 20))/2, 270, 20, colors[0]);
    DrawText("Continuar",
             (screenWidth-MeasureText("Continuar", 20))/2, 320, 20, colors[1]);
    DrawText("Carregar mapa",
             (screenWidth-MeasureText("Carregar mapa", 20))/2, 370, 20, colors[2]);
    DrawText("Ranking",
             (screenWidth-MeasureText("Ranking", 20))/2, 420, 20, colors[3]);
    DrawText("Sair",
             (screenWidth-MeasureText("Sair", 20))/2, 470, 20, colors[4]);

    EndDrawing();

}
