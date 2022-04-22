#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N_LINHAS 15
#define N_COLUNAS 40

#define QUANT_TIROS 100
#define QUANT_ENERG 100

typedef struct Energia {
    int Px;
    int Py;
    int naTela;
    int sizeX;
    int sizeY;
} Energia;

typedef struct Tiro {
    int Px;
    int Py;
    int Pr;
    int naTela;
    char origem;
    float vel;
} Tiro;

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

int sorteiaZero(int contFrames) {

    int res = 0;

    if(contFrames == 0) {
        int random = rand()%17;
        if(random == 0) {
            res = 1;
        }
    }

    return res;

}

void sorteiaPos(Energia energCel[], int end, Jogador player, Rectangle wallRecs[][N_COLUNAS]) {

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int randX, randY;
    int lin, col, ok, i;

    do {

        ok = 1;
        int shouldBreak = 0;

        randX = (int)rand()%(screenWidth - energCel[end].sizeX);
        randY = (int)rand()%(screenHeight - energCel[end].sizeY - 100);

        Rectangle randPos = {randX, randY, energCel[end].sizeX, energCel[end].sizeY};

        if(CheckCollisionRecs(
           randPos, (Rectangle){player.x, player.y, player.sizeX, player.sizeY}) == 0) {

            // COLIS�O COM PAREDES
            for(lin = 0; lin < N_LINHAS; lin++) {
                for(col = 0; col < N_COLUNAS; col++) {
                    if(CheckCollisionRecs(randPos, wallRecs[lin][col])) {
                        ok = 0;
                        shouldBreak = 1;
                        break;
                    }
                }
                if(shouldBreak)
                    break;
            }

            // COLIS�O COM C�LULAS J� EXISTENTES
            for(i = 0; i <  QUANT_ENERG; i++) {
                if(energCel[i].naTela == 0)
                    continue;
                Rectangle celNaTela = {energCel[i].Px, energCel[i].Py,
                                       energCel[i].sizeX, energCel[i].sizeY};
                if(CheckCollisionRecs(randPos, celNaTela)) {
                    ok = 0;
                    break;
                }
            }

        }

    } while(ok == 0);

    energCel[end].Px = randX;
    energCel[end].Py = randY;

}

void UpdateEnergCels(Energia energCel[], int contFrames,
                     Jogador player, Rectangle wallRecs[][N_COLUNAS]) {

    int end;

    if(sorteiaZero(contFrames) == 1){

        for(end = 0; end < QUANT_ENERG; end++) {
            if(energCel[end].naTela == 0) {
                energCel[end].naTela = 1;
                break;
            }
        }

        if(end < QUANT_ENERG) {
            sorteiaPos(energCel, end, player, wallRecs);
        }

    }

}

// OBS: EST� PROGRAMADA PARA FUNCIONAR APENAS PARA O JOGADOR
// OBS2: N�O MAIS!!!
void UseEnergCels(Energia energCel[], Jogador *player, int *timer,
                  float velIniP, float velIniT) {

    int i;
    for(i = 0; i < QUANT_ENERG; i++) {
        if(energCel[i].naTela == 1) {
            if (CheckCollisionRecs(
                (Rectangle){energCel[i].Px, energCel[i].Py, energCel[i].sizeX, energCel[i].sizeY},
                (Rectangle){player->x, player->y, player->sizeX, player->sizeY})) {
                *timer = 5*60; // 5 segundos
                energCel[i].naTela = 0;
            }
        }
    }

    if(*timer > 0) {
        player->vel = 1.5*velIniP;
        for(i = 0; i < QUANT_TIROS; i++) {
            player->tiros[i].vel = 1.5*velIniT;
        }
    } else {
        player->vel = velIniP;
        for(i = 0; i < QUANT_TIROS; i++) {
            player->tiros[i].vel = velIniT;
        }
    }

}
