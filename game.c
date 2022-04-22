#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define GAME 2
#define PAUSE_GAME 8
#define SAVE_GAME 9

#define N_LINHAS 15
#define N_COLUNAS 40

#define QUANT_TIROS 100
#define QUANT_ENERG 100

typedef struct Tiro {
    int Px;
    int Py;
    int Pr;
    int naTela;
    char origem;
    float vel;
} Tiro;

typedef struct Energia {
    int Px;
    int Py;
    int naTela;
    int sizeX;
    int sizeY;
} Energia;

typedef struct Jogador {
    float x;
    float y;
    float r;
    int sizeX;
    int sizeY;
    float vel;
    int vidas;
    Tiro tiros[QUANT_TIROS];
} Jogador;

void UpdateShots(
    Jogador *player, int offset_x, int offset_y
);

void BreakWalls(
    int wall[][N_COLUNAS], Jogador *player, int quadSize[]
);

void initField(
    int wall[][N_COLUNAS], Rectangle wallRecs[][N_COLUNAS],
    float *x, float *y, float inix, float iniy
);

void UpdateWalls(
    int wall[][N_COLUNAS], Rectangle wallRecs[][N_COLUNAS],
    int quadSize[]
);

void AvoidColision(
    float *xTankAnt, float *yTankAnt, float *xTank, float *yTank, int tamanho_t, int largura_t,
    Rectangle wallRecs[][N_COLUNAS], float limitex, float limitey, int quadSize[]
);

void UpdateEnergCels(
    Energia energCel[], int contFrames,
    Jogador player, Rectangle wallRecs[][N_COLUNAS]
);

void UseEnergCels(
    Energia energCel[], Jogador *player, int *timer,
    float velIniP, float velIniT
);

void GameScreen(int *quit) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    int contFrames = 0;  // Usado para contar os segundos
    int timer = 0;

    int i, j;

    float velIniP = 5;
    float velIniT = 10;

    Jogador player;
    player.x = 0;
    player.y = 0;
    player.r = 0;
    player.vel = velIniP;
    float xAnt, yAnt;

    int tamanho_t = 60;
    int largura_t = 60;
    player.sizeX = largura_t;
    player.sizeY = tamanho_t;

    int offset_x = 30, offset_y = 30;
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

    Texture2D tankTexture = LoadTexture("resources/tanque_player.png");
    Texture2D wallTexture = LoadTexture("resources/brick_texture2.png");
    Texture2D enerTexture = LoadTexture("resources/energy_drop_cortado.png");

    int wall[N_LINHAS][N_COLUNAS], quadSize[2] = {40, 25};
    Rectangle wallRecs[N_LINHAS][N_COLUNAS];

    initField(wall, wallRecs, &player.x, &player.y, 500, 500);

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        Vector2 origin = {tamanho_t/2,largura_t/2};
        Rectangle pers = {player.x+offset_x, player.y+offset_y, largura_t, tamanho_t};
        Rectangle tanque = {0,0,70,90};
        limitey = screenHeight - tamanho_t - 100; // 100px para menu
        limitex = screenWidth - largura_t;

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

        UpdateShots(&player, offset_x, offset_y);
        BreakWalls(wall, &player, quadSize);
        UpdateWalls(wall, wallRecs, quadSize);


        //Energia energCel[], int contFrames,
        //Jogador player, Rectangle wallRecs[][N_COLUNAS]
        UpdateEnergCels(energCel, contFrames, player, wallRecs);

        AvoidColision(&xAnt, &yAnt, &player.x, &player.y, tamanho_t, largura_t,
                      wallRecs, limitex, limitey, quadSize);

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
                    DrawRectangle(j*quadSize[1], i*quadSize[0], quadSize[1], quadSize[0], BLACK);
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

        // DESENHA TANQUE
        DrawTexturePro(tankTexture,tanque,pers,origin,player.r,RAYWHITE);
        //DrawRectangle(pers.x-largura_t/2, pers.y-tamanho_t/2, pers.height, pers.width, GREEN);

        // ATUALIZA VARIÁVEIS DE TEMPO
        contFrames = (contFrames + 1) % 60;
        if(timer > 0) timer--;

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(tankTexture);       // Texture unloading
    UnloadTexture(wallTexture);
    UnloadTexture(enerTexture);
    *quit = 1;

}
