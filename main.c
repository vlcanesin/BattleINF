#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deflib.h"

/*
- MAIN:
  - Gerencia telas principais por meio
  da variável screen, como o menu, o
  jogo e os highscores.
*/

int main(void) {

    srand(time(NULL));

    int LOADED_OR_NOT = 0;   // INDICA O MODO DE CARREGAMENTO DA FASE

    const int screenWidth = 1000;
    const int screenHeight = 700;
    int player_placar = 0;  // VARIÁVEL DO SCORE

    InitWindow(screenWidth, screenHeight, "BattleINF 1.0");
    SetTargetFPS(60);

    int menuOption = 0;
    // Option that is selected in menu
    int screen = MENU;
    // Determines what screen should be displayed

    // IMPORTANTE! i é inicializado aqui e não pode ser trocado
    // em nenhum for, já que ele significa o número da fase a ser mostrada
    int quit = 0, return_to_menu, i = 1, j;
    int entreiShowScore = 0;
    // Serve para impedir que o score seja colocado no ranking se o jogador acessou uma fase criada
    Highscore highscores[5];
    while (!WindowShouldClose() && !quit) {

    //------------- UPDATING --------------//
        switch(screen) {

        case MENU: MenuScreen(&screen, &menuOption);
        break;
        case GAME:
            player_placar = 0;
            entreiShowScore = 0;
            LOADED_OR_NOT = INICIO_FASE_NORMAL;  // ABRIR FASE INICIAL ORIGINAL

            for(i = 1; i <= N_FASES; i++) {
                if(quit) break;

                char path[17];
                snprintf(path, sizeof(path), "fases/nivel%c.txt", i+'0');

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

            entreiShowScore = 0;

            FILE *ff;
            ff = fopen("savedfiles/SaveF.bin", "r");
            if(ff == NULL){
                printf("Nao Carregou FASE.\n");
            }
            fread(&i, sizeof(int), 1 , ff);
            fclose(ff);
            //printf("%d", i);

            if(i == (int)'x') {

                LOADED_OR_NOT = CONTINUA_FASE_CRIADA;  // ABRIR FASE SALVA, QUE É DO MAPA CRIADO

                char path[16] = "fases/faseX.txt";
                ShowLevel('x', path);
                return_to_menu = 0;
                GameScreen(&quit, &return_to_menu, path, 'x', LOADED_OR_NOT, &player_placar);

                if(return_to_menu) {
                    screen = MENU;
                    entreiShowScore = 1;
                } else {
                    screen = SHOW_SCORE;
                }

            } else {

                LOADED_OR_NOT = CONTINUA_FASE_NORMAL;  // ABRIR FASE SALVA, QUE É DAS FASES PADRÕES

                for(; i <= N_FASES; i++) {
                    if(quit) break;

                    char path[17];
                    snprintf(path, sizeof(path), "fases/nivel%c.txt", i+'0');

                    ShowLevel((char)i, path);
                    return_to_menu = 0;
                    GameScreen(&quit, &return_to_menu, path, (char)i, LOADED_OR_NOT, &player_placar);

                    LOADED_OR_NOT = INICIO_FASE_NORMAL; // Já carregou a fase

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
            player_placar = 0;
            entreiShowScore = 0;
            LOADED_OR_NOT = INICIO_FASE_CRIADA;  // ABRIR FASE CRIADA

            char path[16] = "fases/faseX.txt";
            ShowLevel('x', path);
            return_to_menu = 0;
            GameScreen(&quit, &return_to_menu, path, 'x', LOADED_OR_NOT, &player_placar);

            if(return_to_menu) {
                screen = MENU;
                entreiShowScore = 1;
            } else {
                screen = SHOW_SCORE;
            }

        break;
        case RANKING:

            GetScores(highscores, 0);

            /*for(j = 0; j < 5; j++) {
                printf("Highscores[%d]: %s %d\n", j, highscores[j].nome, highscores[j].score);
            }*/

            int le_nome = 0;
            if(!entreiShowScore) {
                for(j = 0; j < 5; j++) {
                    if(player_placar > highscores[j].score) {
                        le_nome = 1;
                        break;
                    }
                }
            }

            if(le_nome == 1) {   // CASO PRECISE COLOCAR SCORE ATUAL NO RANKING

                char nome[MAX_INPUT_CHARS + 1];
                nome[0] = '\0';
                ReadName(&quit, nome);
                EscreveNome(nome, player_placar, highscores);

                player_placar = 0;  // Reseta placar quando coloca nome no ranking

            }

            screen = SHOW_HIGHSCORES;

        break;
        case SHOW_HIGHSCORES: ShowHighScores(&screen, highscores);
        break;
        case SHOW_SCORE:
            ShowScores(&screen, player_placar);
            entreiShowScore = 1;
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
