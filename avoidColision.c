#include "raylib.h"
#include "deflib.h"

void AvoidColision(
    Jogador *player, Jogador inimigo[],
    Rectangle wallRecs[][N_COLUNAS], float limitex, float limitey) {
    int i = 0;
    float x, y;

    // COLISION WITH THE BOUNDARY
    //if(player->dogtag == 100){
    if(player->x > limitex || player->x < 0){
        player->x = player->xAnt;
    }
    if(player->y > limitey || player->y < 0){
        player->y = player->yAnt;
    }

    // COLISION WITH THE WALLS
    Rectangle tank = {player->x, player->y, TAMANHO_TANQUE, LARGURA_TANQUE};
    int lin, col;
    for(lin = 0; lin < N_LINHAS; lin++) {
        for(col = 0; col < N_COLUNAS; col++) {
            if(CheckCollisionRecs(tank, wallRecs[lin][col])) {
                player->x = player->xAnt;
                player->y = player->yAnt;
                }
            }
        }

//}

    //COLISION PLAYER WITH ENEMY TANKS
        if(player->dogtag == 100){
        Rectangle tank30 = {player->x, player->y, TAMANHO_TANQUE, LARGURA_TANQUE};
        for (i = 0; i < QUANT_INIMIGOS; i ++){
        Rectangle inimigo_tanque = {inimigo[i].x , inimigo[i].y, TAMANHO_TANQUE,LARGURA_TANQUE};
        if(CheckCollisionRecs(tank,inimigo_tanque) && inimigo[i].naTela == 1){
                player->x = player->xAnt;
                player->y = player->yAnt;
                inimigo[i].x = inimigo[i].xAnt;
                inimigo[i].y = inimigo[i].yAnt;
                }
            }
        }
        //COLISION BETWEEN ENEMY TANKS
        if(player->dogtag != 100){
        Rectangle tank30 = {player->x, player->y, TAMANHO_TANQUE, LARGURA_TANQUE};
        for (i = 0; i < QUANT_INIMIGOS; i ++){
        Rectangle inimigo_tanque = {inimigo[i].x , inimigo[i].y, TAMANHO_TANQUE,LARGURA_TANQUE};
        if(CheckCollisionRecs(tank,inimigo_tanque) && inimigo[i].naTela == 1 && player->dogtag != inimigo[i].dogtag){
                player->x = player->xAnt;
                player->y = player->yAnt;
                inimigo[i].x = inimigo[i].xAnt;
                inimigo[i].y = inimigo[i].yAnt;
                }
            }
        }

    }
    /*else{
        if(&inimigo->pers->x > limitex || player.pers->x < 0){
        player->pers->x = player->pers->xAnt;
    }
    if(player->pers->y > limitey || player->y < 0){
        player->y = player->yAnt;
    }

    // COLISION WITH THE WALLS
    Rectangle tank = inimigo.pers;
    int lin, col;
    for(lin = 0; lin < N_LINHAS; lin++) {
        for(col = 0; col < N_COLUNAS; col++) {
            if(CheckCollisionRecs(tank, wallRecs[lin][col])) {
                player->x = player->xAnt;
                player->y = player->yAnt;
            }
        }
    }
    }

}*/


