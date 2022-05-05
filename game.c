#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "deflib.h"

/*
- GAME:
  - Possui a fun��o que roda cada fase.
  - O Game, assim como o main, tamb�m gerencia
  algumas telas, sendo elas a principal (da fase),
  a de pause, e a de game over.
*/

void GameScreen(int *quit, int *return_to_menu, char path[16], char idNivel, int LOADED_OR_NOT, int *player_placar) {
    // Initialization
    //--------------------------------------------------------------------------------------

    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    int contFramesEnerg = 0, contFramesInimigo = 0;  // Usado para temporizar nascimentos aleat�rios
    int timerTiro = 1, timerLoucuraTotal = 0;
    // OBS: O timer loucura total est� desativado
    int spawnInimigo = 5;

    int i, j;
    int ALL_KILLED = 0;
    //int controle;
    //controle = LOADED_OR_NOT;

    int screen_game = GAME;

    float velIniP = 5;         // VELOCIDADES INICIAIS
    float velIniT = 10;
    float velIniP_inim = 2;
    float velIniT_inim = velIniP;

    Jogador inimigo[QUANT_INIMIGOS];
    Jogador player;

    float limitey = 0, limitex = 0;

    //Tiro tiros[quantTiros]; // FAZER PARA INIMIGOS TAMB�M
    for(i = 0; i < QUANT_TIROS; i++) {
        player.tiros[i].naTela = 0;
        player.tiros[i].vel = velIniT;
    }

    for(i = 0; i < QUANT_INIMIGOS; i++) {
        //inimigo[i].alinhado_vesgo = 0;
        for(j = 0; j < QUANT_TIROS; j++) {
            inimigo[i].tiros[j].naTela = 0;
            inimigo[i].tiros[j].vel = velIniT;
        }
    }

    Energia energCel[QUANT_ENERG];
    for(i = 0; i < QUANT_ENERG; i++) {
        energCel[i].naTela = 0;
        energCel[i].sizeX = 30;
        energCel[i].sizeY = 44;
    }

    Texture2D tankTexture = LoadTexture("resources/tanque_player.png");
    Texture2D wallTexture = LoadTexture("resources/brick_texture2.png");
    Texture2D enerTexture = LoadTexture("resources/energy_drop_cortado.png");
    Texture2D inimigoTexture = LoadTexture("resources/tanque_inimigo.png");
    Texture2D vida = LoadTexture("resources/vida.png");

    int wall[N_LINHAS][N_COLUNAS];
    Rectangle wallRecs[N_LINHAS][N_COLUNAS];

    if (LOADED_OR_NOT == CONTINUA_FASE_NORMAL || LOADED_OR_NOT == CONTINUA_FASE_CRIADA){
        //printf("Estou carregando a fase\n");
        BackTOSave(&player , inimigo);
        BackTOSaveParedinha (wall);
    } else {   // S� INICIALIZA VARI�VEIS CASO N�O SEJA PARA CARREGAR DO ARQUIVO SALVO
        player.x = 0;
        player.y = 0;
        player.r = 0;
        player.sizeX = LARGURA_TANQUE;
        player.sizeY = TAMANHO_TANQUE;
        player.dogtag = 100;
        player.vel = velIniP;
        player.vidas = 3;
        player.timer = 0;
        player.score = *player_placar;

        for(i = 0; i < QUANT_INIMIGOS; i++) {
            //printf("x e y de '%c': %.2f %.2f\n", i+'0',inimigo[i].x, inimigo[i].y);
            inimigo[i].naTela = 0;
            inimigo[i].sizeX = LARGURA_TANQUE;
            inimigo[i].sizeY = TAMANHO_TANQUE;
            inimigo[i].r = 0;
            inimigo[i].vel = velIniP_inim;
            inimigo[i].pers = (Rectangle){0,0,0,0};
            inimigo[i].vidas = 1;
            inimigo[i].dogtag = i;
            inimigo[i].timer = 0;
            inimigo[i].xAnt = 0;
            inimigo[i].yAnt = 0;
            inimigo[i].x = 0;
            inimigo[i].y = 0;
            inimigo[i].alinhado = 0;
            /*printf("\nMUDEI O INIMIGO\n");
            printf("\n%.2f x do inimigo %d", inimigo[i].x, i);
            printf("\n%.2f y do inimigo %d", inimigo[i].y, i);*/
            //printf("%d\n", inimigo[i].dogtag);
        }
    }

    initField(wall, wallRecs, &player, path, LOADED_OR_NOT);
    int end;

    // SPAWNA 3 TANQUES INICIAIS
    UpdateWalls(wall, wallRecs);
        if(LOADED_OR_NOT == INICIO_FASE_NORMAL || LOADED_OR_NOT == INICIO_FASE_CRIADA){
            for(i = 0; i < 3; i++) {
                for(end = 0; end < QUANT_INIMIGOS; end++) {
                    if(inimigo[end].naTela == 0) {
                        inimigo[end].naTela = 1;
                        inimigo[end].vidas = 1;
                        break;
                    }
                }
                if(end < QUANT_INIMIGOS) {
                sorteiaPosInimigo(inimigo, end, player, wallRecs);
                }

            }
        }

    int fimDeLOAD_MAP = 0;

    // Main game loop
    while (!WindowShouldClose() && !*return_to_menu && !ALL_KILLED && !fimDeLOAD_MAP) {

        CheckPause(&screen_game);
        CheckDEATH(&screen_game, &player);
        if (LOADED_OR_NOT == INICIO_FASE_NORMAL || LOADED_OR_NOT == CONTINUA_FASE_NORMAL) {
            ALL_KILLED = CheckCompletion(inimigo);
        }

        switch(screen_game) {

        case GAME:
            // Update
            Vector2 origin = {TAMANHO_TANQUE/2,LARGURA_TANQUE/2};
            player.pers = (Rectangle){player.x+OFFSET_X, player.y+OFFSET_Y, LARGURA_TANQUE, TAMANHO_TANQUE};
           // Rectangle inimigopers[] = {inimigo->x+offset_x, inimigo->y+offset_y, largura_t, tamanho_t};
            Rectangle tanque = {0,0,70,90};
            limitey = screenHeight - TAMANHO_TANQUE - 100; // 100px para menu
            limitex = screenWidth - LARGURA_TANQUE;

            //printf("%f %f %f %f\n", wallRecs[0][0].x, wallRecs[0][0].y, wallRecs[0][0].width, wallRecs[0][0].height);

            //----------------------------------------------------------------------------------
            player.xAnt = player.x;
            player.yAnt = player.y;

            for (i = 0; i < QUANT_INIMIGOS; i++){
                inimigo[i].xAnt = inimigo[i].x;
                inimigo[i].yAnt = inimigo[i].y;
            }

            // MOVIMENTA��O DO PLAYER
            if(IsKeyDown(KEY_UP)){
                player.y -= player.vel;
                player.r = 0;
            }

            if(IsKeyDown(KEY_DOWN)){
                player.y += player.vel;
                player.r = 180;
            }
            if(IsKeyDown(KEY_RIGHT)){
                player.x += player.vel;
                player.r = 90;
            }
            if(IsKeyDown(KEY_LEFT)){
                player.x -= player.vel;
                player.r = 270;
            }
            ////////////////////////////////////
             for(i = 0; i < QUANT_INIMIGOS; i++) {
                if(inimigo[i].naTela == 1) {
                    int m = 20;
                    //int m_vesgo = TAMANHO_TANQUE+10;
                    inimigo[i].alinhado = 0;
                    if(player.x-m < inimigo[i].x && inimigo[i].x < player.x+m){
                        if (inimigo[i].y > player.y)
                            inimigo[i].r = 0;
                        else
                            inimigo[i].r = 180;
                    }
                    if(player.y-m < inimigo[i].y && inimigo[i].y < player.y+m){
                        if (inimigo[i].x > player.x)
                            inimigo[i].r = 270;
                        else
                            inimigo[i].r = 90;
                    }
                    if((player.x-m < inimigo[i].x && inimigo[i].x < player.x+m) || (player.y-m < inimigo[i].y && inimigo[i].y < player.y+m))
                        inimigo[i].alinhado = 1;
                    else
                        inimigo[i].alinhado = 0;
                    /*if((player.x-m_vesgo < inimigo[i].x && inimigo[i].x < player.x+m_vesgo) || (player.y-m_vesgo < inimigo[i].y && inimigo[i].y < player.y+m_vesgo))
                        inimigo[i].alinhado_vesgo = 1;
                    else
                        inimigo[i].alinhado_vesgo = 0;*/

                    Movimenta_Random(&inimigo[i], player);


                }
                    UpdateShots(&inimigo[i], timerTiro);
                    BreakWalls(wall, &inimigo[i]);
                // NOTA: Quando o inimigo sai da tela, pode ser que ainda existam tiros dele
                // na tela. Optei por continuar simulando-os
              }

            ////////////////////////////////////

            UpdateShots(&player, timerTiro);
            BreakWalls(wall, &player);
            UpdateWalls(wall, wallRecs);

            PlayerShot(&player, inimigo);

            //Energia energCel[], int contFrames,
            //Jogador player, Rectangle wallRecs[][N_COLUNAS]
            UpdateINIMIGO(inimigo,contFramesInimigo,player,wallRecs);

            UpdateEnergCels(energCel, contFramesEnerg, player, wallRecs);

            AvoidColision(&player, inimigo,
                          wallRecs, limitex, limitey);
            for(i = 0; i<QUANT_INIMIGOS; i++){
                AvoidColision(&inimigo[i], inimigo,
                              wallRecs, limitex, limitey);
            }
            //---------------------------------------------------------------------------------


            //----------------------------------------------------------------------------------
            BeginDrawing();

            ClearBackground(BLACK);

            // DESENHA TEXTURA NA TELA INTEIRA
            DrawTextureTiled(
                wallTexture,
                (Rectangle){3, 3, 120, 120}, (Rectangle){0, 0, screenWidth, screenHeight},
                (Vector2){0, 0},
                0, 1, RAYWHITE
            );

            // COBRE TEXTURA PARA DELINEAR PAREDES
            for(i = 0; i < N_LINHAS; i++) {
                for(j = 0; j < N_COLUNAS; j++) {
                    if(wall[i][j] == 0) {  // se n�o tiver parede...
                        DrawRectangle(j*COL_SIZE, i*LIN_SIZE, COL_SIZE, LIN_SIZE, BLACK);
                    }
                }
            }

            // PRINTA ABA DE INFORMA��ES
            PrintTab(idNivel, player, vida, enerTexture);

            // DESENHA C�LULAS DE ENERGIA
            UseEnergCels(energCel, &player, velIniP, velIniT);
            for(i = 0; i < QUANT_INIMIGOS; i++) {
                UseEnergCels(energCel, &inimigo[i], velIniP_inim, velIniT_inim);
            }
            for(i = 0; i < QUANT_ENERG; i++) {
                if(energCel[i].naTela == 1) {
                    DrawTexture(enerTexture, energCel[i].Px, energCel[i].Py, RAYWHITE);
                }
            }

            // DESENHA TIROS
            for(i = 0; i < QUANT_TIROS; i++) {
                if(player.tiros[i].naTela == 1) {
                    DrawCircle(player.tiros[i].Px,player.tiros[i].Py,5,RAYWHITE);
                }
            }
            for(i = 0; i < QUANT_INIMIGOS; i++) {
                for (j = 0; j < QUANT_TIROS; j++){
                if(inimigo[i].tiros[j].naTela == 1) {
                    DrawCircle(inimigo[i].tiros[j].Px,inimigo[i].tiros[j].Py,5,RAYWHITE);
                    }
                }
            }
            // DESENHA INIMIGOS
             for(i = 0; i < QUANT_INIMIGOS; i++) {
                if(CheckCollisionRecs((Rectangle){inimigo[i].x, inimigo[i].y, inimigo[i].sizeX, inimigo[i].sizeY},
                                      (Rectangle){player.x, player.y, player.sizeX, player.sizeY})) {
                    inimigo[i].naTela = 0;
                }
                if(inimigo[i].naTela == 1) {
                    Rectangle inimigo_tanque = {inimigo[i].x + OFFSET_X, inimigo[i].y + OFFSET_Y,TAMANHO_TANQUE,LARGURA_TANQUE};
                    //DrawTexture(inimigoTexture, inimigo[i].pers.x,inimigo[i].pers.y, RAYWHITE);
                    //DrawRectangle(inimigo[i].x, inimigo[i].y,TAMANHO_TANQUE,LARGURA_TANQUE, GREEN);
                    DrawTexturePro(inimigoTexture,tanque,inimigo_tanque,origin,inimigo[i].r, RAYWHITE);
                    /*char id[2];
                    id[0] = i+'0';
                    id[1] = '\0';
                    DrawText(id, inimigo[i].x, inimigo[i].y, 20, RAYWHITE);*/
                }
            }

            // DESENHA TANQUE
            DrawTexturePro(tankTexture,tanque,player.pers,origin,player.r,RAYWHITE);

            //DrawTexturePro(inimigoTexture,tanque,pers,origin,player.r,RAYWHITE);
            //DrawRectangle(pers.x-largura_t/2, pers.y-tamanho_t/2, pers.height, pers.width, GREEN);

            // ATUALIZA VARI�VEIS DE TEMPO
            timerLoucuraTotal++;
            if(timerLoucuraTotal > 60*5) {
                timerLoucuraTotal = 0;
                if(spawnInimigo > 1) {
                    //spawnInimigo--;  // TIMER LOUCURA TOTAL EST� DESATIVADO
                }
            }
            velIniP_inim = 2 + (5-spawnInimigo)*0.1;
            velIniT_inim = velIniP + (5-spawnInimigo)*0.1;

            contFramesEnerg = (contFramesEnerg + 1) % 30;
            contFramesInimigo = (contFramesInimigo + 1) % spawnInimigo;
            timerTiro = (timerTiro + 1) % (60*3);
            if(player.timer > 0) {
                player.timer--;  // TIMER PARA C�LULA DE ENERGIA
            }
            for(i = 0; i < QUANT_INIMIGOS; i++) {
                if(inimigo[i].naTela == 1) {
                    inimigo[i].timer--;
                } else {
                    inimigo[i].timer = 0;
                }
            }

            EndDrawing();
            //----------------------------------------------------------------------------------
        break;

        case PAUSE:
            BeginDrawing();
            DrawText("PAUSED",
                    screenWidth-MeasureText("PAUSED", 20) - 25, N_LINHAS*LIN_SIZE + 25, 20, RAYWHITE);
            //if(LOADED_OR_NOT != 3) {   // IMPEDE QUE ELE VOLTE AO MENU QUANDO CARREGA A FASE X
            DrawText("RETURN TO MAIN MENU? S/N",
                    screenWidth-MeasureText("RETURN TO MAIN MENU? S/N", 20) - 25, N_LINHAS*LIN_SIZE + 50, 20, YELLOW);

            if(IsKeyPressed(KEY_S)) {
                Save(&player, inimigo, wall, idNivel);
                //printf("SALVEI!!\n");
                *return_to_menu = 1;
            }
            //}
            EndDrawing();
        break;
        case DEATH:
            // CASO O PLAYER MORRA EM UMA FASE NORMAL, MOSTRA TELA DE GAME OVER
            if(LOADED_OR_NOT == INICIO_FASE_NORMAL || LOADED_OR_NOT == CONTINUA_FASE_NORMAL) {
                char DEATHNAME[8] = "YOU DIED";
                //printf("EU MORRI");

                ClearBackground(BLACK);
                //printf("Entrei\n");
                BeginDrawing();
                DrawText(DEATHNAME,(screenWidth-MeasureText(DEATHNAME, 50))/2, 300, 50, RED);
                DrawText("APERTE ENTER PARA VOLTAR AO MENU",(screenWidth-MeasureText("APERTE ENTER PARA VOLTAR AO MENU", 15))/2, 360, 15, GRAY);
                if(IsKeyPressed(KEY_ENTER)){
                    //printf("\nVAZEI\n");
                    *return_to_menu = 1;
                    //return;
                }
                EndDrawing();

            // CASO O PLAYER MORRA EM UMA FASE CRIADA, FECHA O WHILE,
            // EM MAIN, VAI PARA TELA QUE MOSTRA APENAS O SCORE FINAL
            // DO PLAYER.
            } else {

                fimDeLOAD_MAP = 1;

            }

        break;

        }

    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(tankTexture);       // Texture unloading
    UnloadTexture(wallTexture);
    UnloadTexture(enerTexture);
    UnloadTexture(inimigoTexture);
    UnloadTexture(vida);

    // NOTA: mudar caso a condi��o do while mude
    if(player.vidas > 0 && !*return_to_menu && !ALL_KILLED && !fimDeLOAD_MAP) {
        *quit = 1;
        //printf("Entrei\n");
    }

    if(!*return_to_menu) {
        *player_placar += player.score;
    } else {
        *player_placar = player.score;
    }

}
