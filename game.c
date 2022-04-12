#include "raylib.h"
#include <stdio.h>

#define GAME 2
#define PAUSE_GAME 8
#define SAVE_GAME 9

#define N_LINHAS 15
#define N_COLUNAS 40
struct Tiro {
    int Px;
    int Py;
    int Pr;
};
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

    int i, j,tiroTrig = 0;
    float x = 0, xAnt, y = 0, yAnt;
    float r = 0;
    int tamanho_t = 40;
    int largura_t = 40;
    float limitey = 0, limitex = 0;      // Texture loading

     struct Tiro tiroP;

    Texture2D tank = LoadTexture("resources/tanque_player.png");

    int wall[N_LINHAS][N_COLUNAS], quadSize[2] = {40, 25};
    Rectangle wallRecs[N_LINHAS][N_COLUNAS];

    initField(wall, wallRecs, &x, &y, 500, 500);

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        Vector2 origin = {tamanho_t/2,largura_t/2};
        Rectangle pers = {x+20,y+20,tamanho_t,largura_t};
        Rectangle tanque = {85,90,100,90};
        limitey = screenHeight - tamanho_t;
        limitex = screenWidth - largura_t;

        //----------------------------------------------------------------------------------
        xAnt = x;
        yAnt = y;

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
        if(IsKeyDown(KEY_SPACE)){
            tiroTrig = 1;
        }
        if(IsKeyDown(KEY_G)){
            tiroTrig = 0;
        }
        if(tiroTrig == 0 && r == 0){
        tiroP.Px = x + 20;
        tiroP.Py = y;
        tiroP.Pr = r;
        };
        if(tiroTrig == 0 && r == 180){
        tiroP.Px = x + 20;
        tiroP.Py = y + 40;
        tiroP.Pr = r;
        };
    if(tiroTrig == 0 && r == 90){
        tiroP.Px = x + 40;
        tiroP.Py = y + 20;
        tiroP.Pr = r;
        };
    if(tiroTrig == 0 && r == 270){
        tiroP.Px = x;
        tiroP.Py = y + 20;
        tiroP.Pr = r;
        };
        if(tiroTrig == 1){
            switch(tiroP.Pr){
            case 0: tiroP.Py -= 10;
                    break;
            case 180: tiroP.Py += 10;
                      break;
            case 90: tiroP.Px +=  10;
                     break;
            case 270: tiroP.Px -= 10;
                      break;

        }
    }

        UpdateWalls(wall, wallRecs, quadSize);
        AvoidColision(&xAnt, &yAnt, &x, &y, tamanho_t, largura_t,
                      wallRecs, limitex, limitey, quadSize);

        //---------------------------------------------------------------------------------


        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);
        //DrawRectangle(0,0,screenWidth,screenHeight,BLACK);
        //DrawRectangle(x,y,40,40,GREEN);
        //DrawTexture(tank,x,y,WHITE);
        if (tiroTrig ==1){
            DrawCircle(tiroP.Px,tiroP.Py,5,RAYWHITE);
        }
        for(i = 0; i < N_LINHAS; i++) {
            for(j = 0; j < N_COLUNAS; j++) {
                DrawRectangle(wallRecs[i][j].x, wallRecs[i][j].y,
                              wallRecs[i][j].width, wallRecs[i][j].height,
                              GREEN);
            }
        }
        DrawTexturePro(tank,tanque,pers,origin,r,RAYWHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(tank);       // Texture unloading
    *quit = 1;

}
