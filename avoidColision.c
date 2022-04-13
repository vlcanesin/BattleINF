#include "raylib.h"

#define N_LINHAS 15
#define N_COLUNAS 40

typedef struct Tiro {
    int Px;
    int Py;
    int Pr;
    int naTela;
}Tiro;

void UpdateShots(Tiro tiros[], float x, float y, float r, int quantTiros, int offset_x, int offset_y) {

    int end, i;
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    if(IsKeyPressed(KEY_SPACE)){

        for(end = 0; end < quantTiros; end++) {
            if(tiros[end].naTela == 0) {
                tiros[end].naTela = 1;
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




