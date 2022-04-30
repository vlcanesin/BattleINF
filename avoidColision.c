#include "raylib.h"
#include "deflib.h"
#include <stdio.h>

void AvoidColision(
    Jogador *player, Jogador inimigo[],
    Rectangle wallRecs[][N_COLUNAS], float limitex, float limitey) {
    int i = 0;

    // COLISION WITH THE BOUNDARY
    //if(player->dogtag == 100){
     if(player->x > limitex || player->x < 0){
        player->x = player->xAnt;
        if(player->dogtag !=100)
        player->r = sorteiaR(&player);
    }
    if(player->y > limitey || player->y < 0){
        player->y = player->yAnt;
        if(player->dogtag !=100)
        player->r = sorteiaR(&player);
    }



    // COLISION WITH THE WALLS
    Rectangle tank = {player->x, player->y, TAMANHO_TANQUE, LARGURA_TANQUE};
    int lin, col;
    for(lin = 0; lin < N_LINHAS; lin++) {
        for(col = 0; col < N_COLUNAS; col++) {
            if(CheckCollisionRecs(tank, wallRecs[lin][col])) {
                player->x = player->xAnt;
                player->y = player->yAnt;
                if(player->dogtag != 100 && player->alinhado == 0)
                player->r = sorteiaR(&player);

            }
        }
    }

    //COLISION PLAYER WITH ENEMY TANKS
    if(player->dogtag == 100) {  // "player" jogador
        //Rectangle tank30 = {player->x, player->y, TAMANHO_TANQUE, LARGURA_TANQUE};
        for (i = 0; i < QUANT_INIMIGOS; i ++){
            Rectangle inimigo_tanque = {inimigo[i].x , inimigo[i].y, TAMANHO_TANQUE,LARGURA_TANQUE};
            if(CheckCollisionRecs(tank,inimigo_tanque) && inimigo[i].naTela == 1){
                player->x = player->xAnt;
                player->y = player->yAnt;
                inimigo[i].x = inimigo[i].xAnt;
                inimigo[i].y = inimigo[i].yAnt;
                //if(inimigo[i].alinhado == 0)
                //inimigo[i].r = sorteiaR(&inimigo[i]);
                //printf("Bati\n");
            }
        }
    }

    //COLISION BETWEEN ENEMY TANKS
    else {   // "player" inimigo
        //Rectangle tank30 = {player->x, player->y, TAMANHO_TANQUE, LARGURA_TANQUE};
        for (i = 0; i < QUANT_INIMIGOS; i ++){
            Rectangle inimigo_tanque = {inimigo[i].x , inimigo[i].y, TAMANHO_TANQUE,LARGURA_TANQUE};
            if(CheckCollisionRecs(tank,inimigo_tanque) && inimigo[i].naTela == 1 && player->dogtag != inimigo[i].dogtag){
                player->x = player->xAnt;
                player->y = player->yAnt;
                inimigo[i].x = inimigo[i].xAnt;
                inimigo[i].y = inimigo[i].yAnt;
                if(player->alinhado == 0)
                player->r = sorteiaR(&player);
                if(inimigo[i].alinhado == 0)
                inimigo[i].r = sorteiaR(&inimigo[i]);
            }
        }
    }

}


