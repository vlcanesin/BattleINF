#include "raylib.h"
#include <stdlib.h>
#include <limits.h>
#include <time.h>

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
    float Px;
    float Py;
    int sizeX;
    int sizeY;
    int naTela;
}Energia;

typedef struct Jogador {
    float x;
    float y;
    float r;
    int sizeX;
    int sizeY;
    float vel;
    int vidas;
} Jogador;

void UpdateShots(Tiro tiros[], float x, float y, float r, int quantTiros, int offset_x, int offset_y) {

    int end, i;
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    if(IsKeyPressed(KEY_SPACE)){

        for(end = 0; end < quantTiros; end++) {
            if(tiros[end].naTela == 0) {
                tiros[end].naTela = 1;
                tiros[end].origem = 'p';
                break;
            }
        }

        if(r == 0){
            tiros[end].Px = x + offset_x;
            tiros[end].Py = y;
            tiros[end].Pr = r;
        } else if(r == 180){
            tiros[end].Px = x + offset_x;
            tiros[end].Py = y + 2*offset_y;
            tiros[end].Pr = r;
        } else if(r == 90){
            tiros[end].Px = x + 2*offset_x;
            tiros[end].Py = y + offset_y;
            tiros[end].Pr = r;
        } else if(r == 270){
            tiros[end].Px = x;
            tiros[end].Py = y + offset_y;
            tiros[end].Pr = r;
        }

    }

    for(i = 0; i < quantTiros; i++) {
        if(tiros[i].naTela == 1) {
            switch(tiros[i].Pr){
                case 0: tiros[i].Py -= 10;
                    break;
                case 180: tiros[i].Py += 10;
                    break;
                case 90: tiros[i].Px +=  10;
                    break;
                case 270: tiros[i].Px -= 10;
                    break;
            }
        }
        if((tiros[i].Px < 0 || tiros[i].Px > screenWidth) ||
           (tiros[i].Py < 0 || tiros[i].Py > screenHeight)) tiros[i].naTela = 0;
    }

}

void BreakWalls(int wall[][N_COLUNAS], Tiro tiros[], int quantTiros, int quadSize[]) {

    int i, lin, col;
    for(i = 0; i < quantTiros; i++) {
        for(lin = 0; lin < N_LINHAS; lin++) {
            for(col = 0; col < N_COLUNAS; col++) {
                if(tiros[i].naTela == 1 && wall[lin][col] == 1 &&
                   CheckCollisionCircleRec(
                        (Vector2){tiros[i].Px,tiros[i].Py}, 5,
                        (Rectangle){col*quadSize[1], lin*quadSize[0], quadSize[1], quadSize[0]})) {
                    wall[lin][col] = 0;
                    tiros[i].naTela = 0;
                }
            }
        }
    }

}

//=============================================================================================================//

int sorteiaZero(int contFrames) {

    int res = 0;

    if(contFrames == 0) {
        int random = (int)((float)rand()/INT_MAX) * 16;
        if(random == 0) {
            res = 1;
        }
    }

    return res;

}

void sorteiaPos(Energia *energCel, Jogador player, Rectangle wallRecs[][N_COLUNAS]) {

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    float randX, randY;
    int i, j, ok;

    do {

        ok = 0;
        randX = ((float)rand()/INT_MAX) * screenWidth;
        randY = ((float)rand()/INT_MAX) * screenHeight;

        if(CheckCollisionRecs(
           (Rectangle){energCel->Px, energCel->Py, energCel->sizeX, energCel->sizeY},
           (Rectangle){player.x, player.y, player.sizeX, player.sizeY}) == 0) {
            for(i = 0; i < N_LINHAS; i++) {
                for(j = 0; j < N_COLUNAS; j++) {
                    if(CheckCollisionRecs(
                       (Rectangle){energCel->Px, energCel->Py, energCel->sizeX, energCel->sizeY},
                       wallRecs[i][j]) == 0) {
                        ok = 1;
                    }
                }
            }
        }

    } while(ok == 0);

    energCel->Px = randX;
    energCel->Py = randY;

}

void UpdateEnergCels(Energia energCel[], int quantEnerg, int contFrames,
                     Jogador player, Rectangle wallRecs[][N_COLUNAS]) {

    int end;
    //const int screenWidth = GetScreenWidth();
    //const int screenHeight = GetScreenHeight();

    if(sorteiaZero(contFrames) == 1){

        for(end = 0; end < quantEnerg; end++) {
            if(energCel[end].naTela == 0) {
                energCel[end].naTela = 1;
                break;
            }
        }

        sorteiaPos(&energCel[end], player, wallRecs);

    }

}

// OBS: ESTÁ PROGRAMADA PARA FUNCIONAR APENAS PARA O JOGADOR
void UseEnergCels(Energia energCel[], int quantEnerg, Tiro tiros[], int quantTiros,
                  int sizeEnergCelX, int sizeEnergCelY, Jogador player, int timer,
                  float velIniP, float velIniT) {

    int i;
    for(i = 0; i < quantEnerg; i++) {
        if(energCel[i].naTela == 1) {
            if (CheckCollisionRecs(
                (Rectangle){energCel[i].Px, energCel[i].Py, sizeEnergCelX, sizeEnergCelY},
                (Rectangle){player.x, player.y, player.sizeX, player.sizeY})) {
                timer = 5*60; // 5 segundos
                energCel[i].naTela = 0;
            }
        }
    }

    if(timer > 0) {
        player.vel = 1.5*player.vel;
        for(i = 0; i < quantTiros; i++) {
            if(tiros[i].origem == 'p') {
                tiros[i].vel = 1.5*tiros[i].vel;
            }
        }
    } else {
        player.vel = velIniP;
        for(i = 0; i < quantTiros; i++) {
            if(tiros[i].origem == 'p') {
                tiros[i].vel = velIniT;
            }
        }
    }

}

