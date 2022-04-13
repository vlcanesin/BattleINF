#include "raylib.h"
#include <stdio.h>

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
}Tiro;

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

    int i, j;
    float x = 0, xAnt, y = 0, yAnt;
    float r = 0;
    int tamanho_t = 60;
    int largura_t = 60;
    int offset_x = 30, offset_y = 30;
    float limitey = 0, limitex = 0;      // Texture loading

    const int quantTiros = 1000;
    Tiro tiros[quantTiros];
    for(i = 0; i < quantTiros; i++) tiros[i].naTela = 0;

    Texture2D tankTexture = LoadTexture("resources/tanque_player.png");
    Texture2D wallTexture = LoadTexture("resources/brick_texture2.png");

    int wall[N_LINHAS][N_COLUNAS], quadSize[2] = {40, 25};
    Rectangle wallRecs[N_LINHAS][N_COLUNAS];

    initField(wall, wallRecs, &x, &y, 500, 500);

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        Vector2 origin = {tamanho_t/2,largura_t/2};
        Rectangle pers = {x+offset_x,y+offset_y,tamanho_t,largura_t};
        Rectangle tanque = {0,0,70,90};
        limitey = screenHeight - tamanho_t;
        limitex = screenWidth - largura_t;

        //----------------------------------------------------------------------------------
        xAnt = x;
        yAnt = y;

        if(IsKeyDown(KEY_UP)){
            y-= 5;
            r = 0;
        }
        if(IsKeyDown(KEY_DOWN)){
            y+= 5;
            r = 180;
        }
        if(IsKeyDown(KEY_RIGHT)){
            x+= 5;
            r = 90;
        }
        if(IsKeyDown(KEY_LEFT)){
            x-= 5;
            r = 270;
        }

        UpdateShots(tiros, x, y, r, quantTiros, offset_x, offset_y);
        BreakWalls(wall, tiros, quantTiros, quadSize);

        UpdateWalls(wall, wallRecs, quadSize);

        AvoidColision(&xAnt, &yAnt, &x, &y, tamanho_t, largura_t,
                      wallRecs, limitex, limitey, quadSize);

        //---------------------------------------------------------------------------------


        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        DrawTexturePro(wallTexture,tanque,pers,origin,r,RAYWHITE);
        DrawTextureTiled(
            wallTexture,
            (Rectangle){0, 0, 120, 120}, (Rectangle){0, 0, screenWidth, screenHeight},
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

        DrawTexturePro(tankTexture,tanque,pers,origin,r,RAYWHITE);
        //DrawRectangle(pers.x-largura_t/2, pers.y-tamanho_t/2, pers.height, pers.width, GREEN);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(tankTexture);       // Texture unloading
    UnloadTexture(wallTexture);
    *quit = 1;

}
