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

typedef struct Tiro {
    int Px;
    int Py;
    int Pr;
    int naTela;
    char origem;
    float vel;
}Tiro;

typedef struct Energia {
    int Px;
    int Py;
    int naTela;
} Energia;

typedef struct Jogador {
    float x;
    float y;
    float r;
    int sizeX;
    int sizeY;
    float vel;
    int vidas;
} Jogador;

void UpdateShots(
    Tiro tiros[], float x, float y, float r, int quantTiros,
    int offset_x, int offset_y
);

void BreakWalls(
    int wall[][N_COLUNAS], Tiro tiros[],
    int quantTiros, int quadSize[]
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

void GameScreen(int *quit) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    int contFrames = 0;
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

    const int quantTiros = 1000;
    Tiro tiros[quantTiros];
    for(i = 0; i < quantTiros; i++) {
        tiros[i].naTela = 0;
        tiros[i].vel = velIniT;
    }

    const int quantEnerg = 100;
    Energia energCel[quantEnerg];
    for(i = 0; i < quantEnerg; i++) energCel[i].naTela = 0;

    srand(time(NULL));

    Texture2D tankTexture = LoadTexture("resources/tanque_player.png");
    Texture2D wallTexture = LoadTexture("resources/brick_texture2.png");

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

        printf("%f %f\n", player.x, player.y);

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

        UpdateShots(tiros, player.x, player.y, player.r, quantTiros, offset_x, offset_y);
        BreakWalls(wall, tiros, quantTiros, quadSize);

        UpdateWalls(wall, wallRecs, quadSize);

        AvoidColision(&xAnt, &yAnt, &player.x, &player.y, tamanho_t, largura_t,
                      wallRecs, limitex, limitey, quadSize);

        //---------------------------------------------------------------------------------


        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        DrawTexturePro(wallTexture,tanque,pers,origin,player.r,RAYWHITE);
        DrawTextureTiled(
            wallTexture,
            (Rectangle){3, 3, 120, 120}, (Rectangle){0, 0, screenWidth, screenHeight},
            (Vector2){0, 0},
            0, 1, RAYWHITE
        );

        for(i = 0; i < N_LINHAS; i++) {
            for(j = 0; j < N_COLUNAS; j++) {
                if(wall[i][j] == 0) {
                    DrawRectangle(j*quadSize[1], i*quadSize[0], quadSize[1], quadSize[0], BLACK);
                }
            }
        }

        for(i = 0; i < quantTiros; i++) {
            if(tiros[i].naTela == 1) {
                DrawCircle(tiros[i].Px,tiros[i].Py,5,RAYWHITE);
            }
        }

        DrawTexturePro(tankTexture,tanque,pers,origin,player.r,RAYWHITE);
        //DrawRectangle(pers.x-largura_t/2, pers.y-tamanho_t/2, pers.height, pers.width, GREEN);

        contFrames = (contFrames + 1) % 60;
        if(timer > 0) timer--;

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(tankTexture);       // Texture unloading
    UnloadTexture(wallTexture);
    *quit = 1;

}
