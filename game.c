#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "deflib.h"

void GameScreen(int *quit, char path[16]) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    int contFramesEnerg = 0, contFramesInimigo = 0;  // Usado para temporizar nascimentos aleatórios
    int timer = 0;

    int i, j;

    float velIniP = 5;
    float velIniT = 10;

    Jogador player;
    player.x = 0;
    player.y = 0;
    player.r = 0;
    player.vel = velIniP;
    player.vidas = 3;
    float xAnt, yAnt;

    //int tamanho_t = 60;
    //int largura_t = 60;
    player.sizeX = LARGURA_TANQUE;
    player.sizeY = TAMANHO_TANQUE;

    float limitey = 0, limitex = 0;

    //Tiro tiros[quantTiros]; // FAZER PARA INIMIGOS TAMBÉM
    for(i = 0; i < QUANT_TIROS; i++) {
        player.tiros[i].naTela = 0;
        player.tiros[i].vel = velIniT;
    }

    Energia energCel[QUANT_ENERG];
    for(i = 0; i < QUANT_ENERG; i++) {
        energCel[i].naTela = 0;
        energCel[i].sizeX = 30;
        energCel[i].sizeY = 44;
    }
    Jogador inimigo[QUANT_INIMIGOS];
    for(i = 0; i < QUANT_INIMIGOS; i++) {
        inimigo[i].naTela = 0;
        inimigo[i].sizeX = LARGURA_TANQUE;
        inimigo[i].sizeY = TAMANHO_TANQUE;
        inimigo[i].r = 0;
        inimigo[i].pers = (Rectangle){0,0,0,0};
        inimigo[i].vidas = 1;
    }

    Texture2D tankTexture = LoadTexture("resources/tanque_player.png");
    Texture2D wallTexture = LoadTexture("resources/brick_texture2.png");
    Texture2D enerTexture = LoadTexture("resources/energy_drop_cortado.png");
    Texture2D inimigoTexture = LoadTexture("resources/tanque_inimigo.png");

    int wall[N_LINHAS][N_COLUNAS];
    Rectangle wallRecs[N_LINHAS][N_COLUNAS];

    initField(wall, wallRecs, &player, path);

    int end;

    // SPAWNA 3 TANQUES INICIAIS
    UpdateWalls(wall, wallRecs);
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

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        Vector2 origin = {TAMANHO_TANQUE/2,LARGURA_TANQUE/2};
        player.pers = (Rectangle){player.x+OFFSET_X, player.y+OFFSET_Y, LARGURA_TANQUE, TAMANHO_TANQUE};
       // Rectangle inimigopers[] = {inimigo->x+offset_x, inimigo->y+offset_y, largura_t, tamanho_t};
        Rectangle tanque = {0,0,70,90};
        limitey = screenHeight - TAMANHO_TANQUE - 100; // 100px para menu
        limitex = screenWidth - LARGURA_TANQUE;

        //printf("%f %f %f %f\n", wallRecs[0][0].x, wallRecs[0][0].y, wallRecs[0][0].width, wallRecs[0][0].height);

        //----------------------------------------------------------------------------------
        xAnt = player.x;
        yAnt = player.y;

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

        UpdateShots(&player);
        BreakWalls(wall, &player);
        UpdateWalls(wall, wallRecs);

        PlayerShot(&player, inimigo);

        //Energia energCel[], int contFrames,
        //Jogador player, Rectangle wallRecs[][N_COLUNAS]
        UpdateINIMIGO(inimigo,contFramesInimigo,player,wallRecs);
        UpdateEnergCels(energCel, contFramesEnerg, player, wallRecs);
        AvoidColision(&xAnt, &yAnt, &player.x, &player.y,
                      wallRecs, limitex, limitey);

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
                if(wall[i][j] == 0) {  // se não tiver parede...
                    DrawRectangle(j*COL_SIZE, i*LIN_SIZE, COL_SIZE, LIN_SIZE, BLACK);
                }
            }
        }

        // DESENHA CÉLULAS DE ENERGIA
        UseEnergCels(energCel, &player, &timer, velIniP, velIniT);
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
        // DESENHA INIMIGOS
         for(i = 0; i < QUANT_INIMIGOS; i++) {
            if(inimigo[i].naTela == 1) {
                //DrawTexture(inimigoTexture, inimigo[i].pers.x,inimigo[i].pers.y, RAYWHITE);
                DrawTexturePro(inimigoTexture,tanque,inimigo[i].pers,origin,inimigo[i].r,RAYWHITE);
                //DrawRectangle(inimigo[i].x,inimigo[i].y,inimigo[i].pers.width,inimigo[i].pers.height, GREEN);
            }
        }

        // DESENHA TANQUE
        DrawTexturePro(tankTexture,tanque,player.pers,origin,player.r,RAYWHITE);

        //DrawTexturePro(inimigoTexture,tanque,pers,origin,player.r,RAYWHITE);
        //DrawRectangle(pers.x-largura_t/2, pers.y-tamanho_t/2, pers.height, pers.width, GREEN);

        // ATUALIZA VARIÁVEIS DE TEMPO
        contFramesEnerg = (contFramesEnerg + 1) % 60;
        contFramesInimigo = (contFramesInimigo + 1) % 1;
        if(timer > 0) timer--;

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(tankTexture);       // Texture unloading
    UnloadTexture(wallTexture);
    UnloadTexture(enerTexture);
    UnloadTexture(inimigoTexture);
    //*quit = 1;

}
