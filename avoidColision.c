#include "raylib.h"
#include "deflib.h"

void AvoidColision(
    float *xTankAnt, float *yTankAnt, float *xTank, float *yTank,
    Rectangle wallRecs[][N_COLUNAS], float limitex, float limitey) {

    // COLISION WITH THE BOUNDARY
    if(*xTank > limitex || *xTank < 0){
        *xTank = *xTankAnt;
    }
    if(*yTank > limitey || *yTank < 0){
        *yTank = *yTankAnt;
    }

    // COLISION WITH THE WALLS
    Rectangle tank = {*xTank, *yTank, TAMANHO_TANQUE, LARGURA_TANQUE};
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


