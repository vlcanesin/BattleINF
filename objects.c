#include "raylib.h"
#include <stdlib.h>
#include <limits.h>
#include <time.h>

typedef struct Tiro {
    int Px;
    int Py;
    int Pr;
    int naTela;
}Tiro;

typedef struct Energia {
    int Px;
    int Py;
    int naTela;
}

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

void generateEnergCel(Energia energCel[], float x, float y, int quantEnerg, int contFrames) {

    if(sorteiaZero(contFrames) == 1) {

    }

}
