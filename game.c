#include "raylib.h"
#include <stdio.h>

#define GAME 2
#define PAUSE_GAME 8
#define SAVE_GAME 9

#define N_LINHAS 15
#define N_COLUNAS 40

void initField(
    int wall[][N_COLUNAS],
    float *x, float *y, float inix, float iniy
);
void UpdateWalls(
    int wall[][N_COLUNAS], Rectangle wallRecs[][N_COLUNAS],
    int quadSize[]
);

void AvoidColision(
    float *xTank, float *yTank, Rectangle wallRecs[][N_COLUNAS],
    float limitex, float limitey, int quadSize[]
);

void GameScreen(int *quit) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    int i, j;
    float x = 0, r = 0;
    float y = 0;
    int tamanho_t = 40;
    int largura_t = 40;
    float limitey = 0, limitex = 0;      // Texture loading

    Texture2D tank = LoadTexture("resources/oi.png");

    int wall[N_LINHAS][N_COLUNAS], quadSize[2] = {40, 25};
    Rectangle wallRecs[N_LINHAS][N_COLUNAS];

    initField(wall, &x, &y, 500, 500);

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        Vector2 origin = {tamanho_t/2,largura_t/2};
        Rectangle pers = {x+20,y+20,tamanho_t,largura_t};
        Rectangle tanque = {80,90,80,90};
        limitey = screenHeight - tamanho_t;
        limitex = screenWidth - largura_t;

        //----------------------------------------------------------------------------------
        if(IsKeyDown(KEY_UP)){
            y-= 10;
            r = 0;
        }
        if(IsKeyDown(KEY_DOWN)){
            y+= 10;
            r = 180;
        }
        if(IsKeyDown(KEY_RIGHT)){
            x+= 10;
            r = 90;
        }
        if(IsKeyDown(KEY_LEFT)){
            x-= 10;
            r = 270;
        }

        UpdateWalls(wall, wallRecs, quadSize);
        AvoidColision(&x, &y, wallRecs, limitex, limitey, quadSize);

        //---------------------------------------------------------------------------------


        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);
        //DrawRectangle(0,0,screenWidth,screenHeight,BLACK);
        //DrawRectangle(x,y,40,40,GREEN);
        //DrawTexture(tank,x,y,WHITE);
        for(i = 0; i < N_LINHAS; i++) {
            for(j = 0; j < N_COLUNAS; j++) {
                DrawRectangle(wallRecs[i][j].x, wallRecs[i][j].y,
                              wallRecs[i][j].width, wallRecs[i][j].height,
                              GREEN);
            }
        }
        DrawTexturePro(tank,tanque,pers,origin,r,RAYWHITE);

        Rectangle teste = (Rectangle){500, 500, 20, 20};
        DrawRectangle(teste.x, teste.y, teste.width, teste.height, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(tank);       // Texture unloading
    *quit = 1;

}
