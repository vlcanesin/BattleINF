#include "raylib.h"
#include <stdio.h>

const int screenWidth = 1200;
const int screenHeight = 600;

void MenuScreen();

int main(void) {

    InitWindow(screenWidth, screenHeight, "BattleINF 1.0");
    SetTargetFPS(60);

    int screen = 1;
    // Determines what screen should be displayed
    /*
        SCREEN TABLE:
        - 1: MenuScreen
        - 2: GameScreen
        - 3: LoadedGameScreen
        - 4: LoadMapScreen
        - 5: RankingScreen
        - 6: QuitScreen - might not be an actual screen
    */
    int quit = 0;

    while (!WindowShouldClose() && !quit) {

    //------------- UPDATING --------------//
        switch(screen) {

        case 1: MenuScreen(&screen); // MenuScreen() returns the next screen to be displayed
        break;
        default: quit = 1; // MenuScreen() returned QuitScreen, so program should quit
        break;

        }

    //-------------- DRAWING --------------//
        //BeginDrawing();

        //EndDrawing();

    }
    // Fecha a janela
    CloseWindow();
    return 0;
}
