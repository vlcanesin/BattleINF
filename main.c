#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deflib.h"

int main(void) {

    srand(time(NULL));

    const int screenWidth = 1000;
    const int screenHeight = 700;

    InitWindow(screenWidth, screenHeight, "BattleINF 1.0");
    SetTargetFPS(60);

    int menuOption = 0;
    // Option that is selected in menu
    int screen = MENU;
    // Determines what screen should be displayed

    int quit = 0, i;

    while (!WindowShouldClose() && !quit) {

    //------------- UPDATING --------------//
        switch(screen) {

        case MENU: MenuScreen(&screen, &menuOption);
        break;
        case GAME:

            for(i = 1; i <= N_FASES; i++) {
                if(quit) break;

                char path[16];
                snprintf(path, sizeof(path), "fases/fase%c.txt", i+'0');

                ShowLevel(i, path);
                GameScreen(&quit, path);

            }

            quit = 1;

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


