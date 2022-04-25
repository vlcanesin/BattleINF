#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "deflib.h"

void sorteiaPosInimigo(Jogador inimigo [], int end, Jogador player, Rectangle wallRecs[][N_COLUNAS]) {

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int randX, randY;
    int lin, col, ok, i, contador = 0;

    Rectangle randPos;

    do {
        contador ++;
        ok = 1;
        int shouldBreak = 0;

        randX = (int)rand()%(screenWidth - inimigo[end].sizeX);
        randY = (int)rand()%(screenHeight - inimigo[end].sizeY - 100);

        randPos = (Rectangle){randX, randY, inimigo[end].sizeX, inimigo[end].sizeY};

        if(CheckCollisionRecs(
           randPos, (Rectangle){player.x, player.y, player.sizeX, player.sizeY})){
           ok = 0;
        }

        // COLISÃO COM PAREDES
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

        // COLISÃO COM CÉLULAS JÁ EXISTENTES
        for(i = 0; i <  QUANT_INIMIGOS; i++) {
            if(inimigo[i].naTela == 0)
            continue;
            Rectangle inimigNaTela = {inimigo[i].x, inimigo[i].y,
                               inimigo[i].sizeX, inimigo[i].sizeY};
            if(CheckCollisionRecs(randPos, inimigNaTela)) {
                ok = 0;
                break;
            }
        }

    } while(ok == 0 && contador < 20);


    if (contador < 20){
        inimigo[end].x = randX;
        inimigo[end].y = randY;
        inimigo[end].pers = (Rectangle){randX+OFFSET_X, randY+OFFSET_Y, LARGURA_TANQUE, TAMANHO_TANQUE};
    } else {
        //printf("Nao foi incluido");
        inimigo[end].naTela = 0;
    }

    //printf("inimigo pers : %f, %f, %f, %f \n",inimigo[end].pers.x,inimigo[end].pers.y,inimigo[end].pers.height,inimigo[end].pers.width);

}

void UpdateINIMIGO(Jogador inimigo[], int contFrames,
                   Jogador player, Rectangle wallRecs[][N_COLUNAS]) {

    int end;

    if(sorteiaZero(contFrames) == 1){

        for(end = 0; end < QUANT_INIMIGOS; end++) {
            if(inimigo[end].naTela == 0) {
                inimigo[end].naTela = 1;
                inimigo[end].vidas = 1;
                break;
            }
        }

        if(end < QUANT_INIMIGOS) {
            sorteiaPosInimigo(inimigo, end, player, wallRecs);
        }

    }

    // VERIFICA QUAIS AINDA ESTÃO VIVOS
    for(end = 0; end < QUANT_INIMIGOS; end++) {
        if(inimigo[end].naTela == 1 && inimigo[end].vidas <= 0) {
            inimigo[end].naTela = 0;
        }
    }

}

void Movimenta_Random (Jogador inimigo[], int end){
}
