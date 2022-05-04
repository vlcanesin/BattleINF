#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deflib.h"

int main(void) {

    srand(time(NULL));

    int LOADED_OR_NOT = 0;

    const int screenWidth = 1000;
    const int screenHeight = 700;
    int player_placar = 0;

    InitWindow(screenWidth, screenHeight, "BattleINF 1.0");
    SetTargetFPS(60);

    int menuOption = 0;
    // Option that is selected in menu
    int screen = MENU;
    // Determines what screen should be displayed

    // IMPORTANTE! i � inicializado aqui e n�o pode ser trocado
    // em nenhum for, j� que ele significa o n�mero da fase a ser mostrada
    int quit = 0, return_to_menu, i = 1, j;
    Highscore highscores[5];
    while (!WindowShouldClose() && !quit) {

    //------------- UPDATING --------------//
        switch(screen) {

        case MENU: MenuScreen(&screen, &menuOption);
        break;
        case GAME:
            player_placar = 0;

            for(i = 1; i <= N_FASES; i++) {
                if(quit) break;

                char path[16];
                snprintf(path, sizeof(path), "fases/fase%c.txt", i+'0');

                ShowLevel((char)i, path);
                return_to_menu = 0;
                GameScreen(&quit, &return_to_menu, path, (char)i, LOADED_OR_NOT, &player_placar);

                if(return_to_menu) {
                    screen = MENU;
                    break;
                }
            }

            if(i > N_FASES) {
                screen = RANKING;
            }

        break;
        case LOADED_GAME:
            if(LOADED_OR_NOT != 3)
                LOADED_OR_NOT = 1;
            FILE *ff;
            ff = fopen("savedfiles/SaveF.bin", "r");
            if(ff == NULL){
                printf("Nao Carregou FASE.\n");
            }
            fread(&i, sizeof(int), 1 , ff);
            fclose(ff);
            printf("%d", i);

            if(i == (int)'x') {
                screen = LOAD_MAP;
            } else {

                for(; i <= N_FASES; i++) {
                    if(quit) break;

                    char path[16];
                    snprintf(path, sizeof(path), "fases/fase%c.txt", i+'0');

                    ShowLevel((char)i, path);
                    return_to_menu = 0;
                    GameScreen(&quit, &return_to_menu, path, (char)i, LOADED_OR_NOT, &player_placar);
                    LOADED_OR_NOT++;

                    if(return_to_menu) {
                        screen = MENU;
                        break;
                    }
                }

                if(i > N_FASES) {
                    screen = RANKING;
                }

            }

        break;
        case LOAD_MAP:
            LOADED_OR_NOT = 3;
            player_placar = 0;
            char path[16] = "fases/faseX.txt";
            ShowLevel('x', path);
            return_to_menu = 0;
            GameScreen(&quit, &return_to_menu, path, 'x', LOADED_OR_NOT, &player_placar);

            if(return_to_menu) {
                screen = MENU;
                break;
            }

            screen = SHOW_SCORE;

        break;
        case RANKING:
            GetScores(highscores, 0);

            for(j = 0; j < 5; j++) {
                printf("Highscores[%d]: %s %d\n", j, highscores[j].nome, highscores[j].score);
            }

            int le_nome = 0;
            for(j = 0; j < 5; j++) {
                if(player_placar > highscores[j].score) {
                    le_nome = 1;
                    break;
                }
            }

            if(le_nome == 1) {

                char nome[MAX_INPUT_CHARS + 1];
                nome[0] = '\0';
                ReadName(&quit, nome);
                EscreveNome(nome, player_placar, highscores);

            }

            screen = SHOW_HIGHSCORES;
        break;
        case SHOW_HIGHSCORES: ShowHighScores(&screen, highscores);
        break;
        case SHOW_SCORE: ShowScores(&screen, highscores);
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
