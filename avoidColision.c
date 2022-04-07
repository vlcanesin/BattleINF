#include "raylib.h"

#define N_COLUNAS 40

void AvoidColision(
    float *xTank, float *yTank, Rectangle wallRecs[][N_COLUNAS],
    float limitex, float limitey, int quadSize[]) {

    int x = *xTank;
    int y = *yTank;

    // COLISION WITH THE BOUNDARY
    if(x > limitex){
        *xTank = limitex;
    }
    if(x < 0){
        *xTank = 0;
    }
    if(y > limitey){
        *yTank = limitey;
    }
    if(y < 0){
        *yTank = 0;
    }

    // COLISION WITH THE WALLS


}
