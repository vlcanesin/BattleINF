#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deflib.h"

int main(void) {

    srand(time(NULL));

    int LOADED_OR_NOT = 1;

    const int screenWidth = 1000;
    const int screenHeight = 700;
    int player_placar = 0;

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
                GameScreen(&quit, path, i, 0, player_placar);
                player_placar+= GameScreen(&quit, path, i, 0, player_placar);

            }

            quit = 1;

        break;
        case LOADED_GAME:




                if(LOADED_OR_NOT == 1){
                    FILE *ff;
                    ff = fopen("savedfiles/SaveF.bin", "r");
                    if(ff == NULL){
                        printf("Nao Carregou FASE.\n");
                    }
                    fread(&i, sizeof(int), 1 , ff);
                    fclose(ff);
                }
                printf("%d", i);
                for(i ; i <= N_FASES; i++) {
                if(quit) break;

                char path[16];
                snprintf(path, sizeof(path), "fases/fase%c.txt", i+'0');

                ShowLevel(i, path);
                player_placar = GameScreen(&quit, path, i, LOADED_OR_NOT, player_placar);
                LOADED_OR_NOT++;


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
