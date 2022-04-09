#include "raylib.h"

#define N_LINHAS 15
#define N_COLUNAS 40

void AvoidColision(
    float *xTankAnt, float *yTankAnt, float *xTank, float *yTank, int tamanho_t, int largura_t,
    Rectangle wallRecs[][N_COLUNAS], float limitex, float limitey, int quadSize[]) {

    // COLISION WITH THE BOUNDARY
    if(*xTank > limitex || *xTank < 0){
        *xTank = *xTankAnt;
    }
    if(*yTank > limitey || *yTank < 0){
        *yTank = *yTankAnt;
    }

    // COLISION WITH THE WALLS
    Rectangle tank = {*xTank, *yTank, tamanho_t, largura_t};
    int lin, col;
    for(lin = 0; lin < N_LINHAS; lin++) {
        for(col = 0; col < N_COLUNAS; col++) {
            if(CheckCollisionRecs(tank, wallRecs[lin][col])) {
                *xTank = *xTankAnt;
                *yTank = *yTankAnt;
            }
        }
    }

}
