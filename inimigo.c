#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "deflib.h"

void sorteiaPosInimigo(Jogador inimigo[], int end, Jogador player, Rectangle wallRecs[][N_COLUNAS]) {

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    float randX, randY;
    int lin, col, ok, i, contador = 0;

    Rectangle randPos;

    do {
        contador ++;
        ok = 1;
        int shouldBreak = 0;

        randX = (float)((int)rand()%(screenWidth - inimigo[end].sizeX));
        randY = (float)((int)rand()%(screenHeight - inimigo[end].sizeY - 100));

        randPos = (Rectangle){randX, randY, inimigo[end].sizeX, inimigo[end].sizeY};

        int m = 100;  // margem de distância até o player
        if(CheckCollisionRecs(
           randPos, (Rectangle){player.x-m, player.y-m, player.sizeX+2*m, player.sizeY+2*m})){
           ok = 0;
        }

        // COLISÃO COM PAREDES
        for(lin = 0; lin < N_LINHAS; lin++) {
            for(col = 0; col < N_COLUNAS; col++) {
                if(CheckCollisionRecs(randPos, wallRecs[lin][col])) {
                    //printf("Entrei\n");
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
            if(inimigo[i].naTela == 1) {
                Rectangle inimigNaTela = {inimigo[i].x, inimigo[i].y,
                                   inimigo[i].sizeX, inimigo[i].sizeY};
                if(CheckCollisionRecs(randPos, inimigNaTela)) {
                    ok = 0;
                    break;
                }
            }
        }

        //printf("%d\n", ok);
    } while(ok == 0 && contador < 50);


    if (contador < 50){
        inimigo[end].x = randX;
        inimigo[end].y = randY;
        inimigo[end].pers = (Rectangle){randX+OFFSET_X, randY+OFFSET_Y, LARGURA_TANQUE, TAMANHO_TANQUE};
        //printf("'%c' RandX: %.2f RandY: %.2f\n", end+'0', randX, randY);
    } else {
        //printf("End '%c' nao foi incluido\n", end+'0');
        inimigo[end].naTela = 0;
    }

    //printf("inimigo pers : %f, %f, %f, %f \n",inimigo[end].pers.x,inimigo[end].pers.y,inimigo[end].pers.height,inimigo[end].pers.width);

}

void UpdateINIMIGO(Jogador inimigo[], int contFrames,
                   Jogador player, Rectangle wallRecs[][N_COLUNAS]) {

    int end, i, passou;

    if(sorteiaZero(contFrames) == 1){

        for(end = 0; end < QUANT_INIMIGOS; end++) {
            if(inimigo[end].naTela == 0) {
                for(i = 0; i < QUANT_TIROS; i++) {
                    passou = 1;
                    if(inimigo[end].tiros[i].naTela == 1) {
                        // NÃO COLOCA INIMIGO NA POSIÇÃO EM QUE AINDA POSSUI TIROS A SEREM RENDERIZADOS
                        passou = 0;
                        break;
                    }
                }
                if(passou) {
                    inimigo[end].naTela = 1;
                    inimigo[end].vidas = 1;
                    inimigo[end].sizeX = LARGURA_TANQUE;
                    inimigo[end].sizeY = TAMANHO_TANQUE;
                    break;
                }
            }
        }

        if(end < QUANT_INIMIGOS) {
            sorteiaPosInimigo(inimigo, end, player, wallRecs);
            //printf("End '%c': %.2f %.2f\n", end+'0', inimigo[end].x, inimigo[end].y);
        }

    }

    // DEIXA APENAS OS QUE ESTÃO VIVOS
    for(end = 0; end < QUANT_INIMIGOS; end++) {
        if(inimigo[end].naTela == 1 && inimigo[end].vidas <= 0) {
            inimigo[end].naTela = 0;
            inimigo[end].timer = 0;
            inimigo[end].sizeX = 0; // OBS: tamanho é zerado para não haver colisão com os tiros, já que naTela não é considerado nesse caso
            inimigo[end].sizeY = 0;
            //for(i = 0; i < QUANT_TIROS; i++) {
            //    inimigo[end].tiros[i].naTela = 0;
            //}
        }
    }

}

void Movimenta_Random (Jogador *inimigo){
    switch((int)inimigo->r){
    case 0: inimigo->y -= inimigo->vel;
            break;
    case 180: inimigo->y += inimigo->vel;
              break;
    case 90: inimigo->x += inimigo->vel;
             break;
    case 270: inimigo->x -= inimigo->vel;
              break;
    }
}
int sorteiaR(Jogador *inimigo){
    int vetorPosicao[4] = {0,90,180,270};
    int escolha = rand() %4;

    return ((int)inimigo->r+vetorPosicao[escolha])%360;
}

// DESCONTINUADA: Sorteia momento que o inimigo deve atirar
// Mentira, é melhor com ela
int EnemyShots(Jogador *inimigo){
    int info = 0;
    if (inimigo->dogtag != 100 && inimigo->alinhado == 1){
        info = rand()%80;
    }else
        info = 0;

    return info;
}
