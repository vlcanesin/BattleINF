#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "deflib.h"

void UpdateShots(Jogador *player) {

    int end, i, num;
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    if (player->dogtag != 100){
         num = EnemyShots(&player);
     }
    else
        num = 0;
    if (player->dogtag != 100){
        if(num == 1 && player->alinhado == 1){

            for(end = 0; end < QUANT_TIROS; end++) {
                if(player->tiros[end].naTela == 0) {
                    player->tiros[end].naTela = 1;
                    //player->tiros[end].origem = 'p';
                    break;
                }
            }

            if(end < QUANT_TIROS) {  // se foi possivel colocar mais um tiro na tela...

                if(player->r == 0){
                    player->tiros[end].Px = player->x + OFFSET_X;
                    player->tiros[end].Py = player->y;
                    player->tiros[end].Pr = player->r;
                } else if(player->r == 180){
                    player->tiros[end].Px = player->x + OFFSET_X;
                    player->tiros[end].Py = player->y + 2*OFFSET_Y;
                    player->tiros[end].Pr = player->r;
                } else if(player->r == 90){
                    player->tiros[end].Px = player->x + 2*OFFSET_X;
                    player->tiros[end].Py = player->y + OFFSET_Y;
                    player->tiros[end].Pr = player->r;
                } else if(player->r == 270){
                    player->tiros[end].Px = player->x;
                    player->tiros[end].Py = player->y + OFFSET_Y;
                    player->tiros[end].Pr = player->r;
                }

            }

        }
    }
    else{
            if(IsKeyPressed(KEY_SPACE)){

            for(end = 0; end < QUANT_TIROS; end++) {
                if(player->tiros[end].naTela == 0) {
                    player->tiros[end].naTela = 1;
                    //player->tiros[end].origem = 'p';
                    break;
                }
            }

            if(end < QUANT_TIROS) {  // se foi possivel colocar mais um tiro na tela...

                if(player->r == 0){
                    player->tiros[end].Px = player->x + OFFSET_X;
                    player->tiros[end].Py = player->y;
                    player->tiros[end].Pr = player->r;
                } else if(player->r == 180){
                    player->tiros[end].Px = player->x + OFFSET_X;
                    player->tiros[end].Py = player->y + 2*OFFSET_Y;
                    player->tiros[end].Pr = player->r;
                } else if(player->r == 90){
                    player->tiros[end].Px = player->x + 2*OFFSET_X;
                    player->tiros[end].Py = player->y + OFFSET_Y;
                    player->tiros[end].Pr = player->r;
                } else if(player->r == 270){
                    player->tiros[end].Px = player->x;
                    player->tiros[end].Py = player->y + OFFSET_Y;
                    player->tiros[end].Pr = player->r;
                }

            }

        }

    }

    for(i = 0; i < QUANT_TIROS; i++) {
        if(player->tiros[i].naTela == 1) {
            switch(player->tiros[i].Pr){
                case 0: player->tiros[i].Py -= player->tiros[i].vel;
                    break;
                case 180: player->tiros[i].Py += player->tiros[i].vel;
                    break;
                case 90: player->tiros[i].Px += player->tiros[i].vel;
                    break;
                case 270: player->tiros[i].Px -= player->tiros[i].vel;
                    break;
            }
        }
        if((player->tiros[i].Px < 0 || player->tiros[i].Px > screenWidth) ||
           (player->tiros[i].Py < 0 || player->tiros[i].Py > screenHeight-100)) player->tiros[i].naTela = 0;
    }

}

void BreakWalls(int wall[][N_COLUNAS], Jogador *player) {

    int i, lin, col;
    for(i = 0; i < QUANT_TIROS; i++) {
        for(lin = 0; lin < N_LINHAS; lin++) {
            for(col = 0; col < N_COLUNAS; col++) {
                if(player->tiros[i].naTela == 1 && wall[lin][col] == 1 &&
                   CheckCollisionCircleRec(
                        (Vector2){player->tiros[i].Px,player->tiros[i].Py}, 5,
                        (Rectangle){col*COL_SIZE, lin*LIN_SIZE, COL_SIZE, LIN_SIZE})) {
                    wall[lin][col] = 0;
                    player->tiros[i].naTela = 0;
                }
            }
        }
    }

}

void PlayerShot(Jogador *player, Jogador inimigo[]) {

    int i, j;
    for(i = 0; i < QUANT_TIROS; i++) {
        for(j = 0; j < QUANT_INIMIGOS; j++) {
            if(inimigo[j].naTela == 1) {
                if(inimigo[j].tiros[i].naTela == 1 &&
                   CheckCollisionCircleRec(
                        (Vector2){inimigo[j].tiros[i].Px,inimigo[j].tiros[i].Py}, 5,
                        (Rectangle){player->x, player->y, LARGURA_TANQUE, TAMANHO_TANQUE})) {
                    player->vidas--;
                    inimigo[j].tiros[i].naTela = 0;
                }
                if(player->tiros[i].naTela == 1 &&
                   CheckCollisionCircleRec(
                        (Vector2){player->tiros[i].Px,player->tiros[i].Py}, 5,
                        (Rectangle){inimigo[j].x, inimigo[j].y, LARGURA_TANQUE, TAMANHO_TANQUE})) {
                    inimigo[j].vidas--;
                    if(inimigo[j].vidas == 0) {
                        player->score += 800;
                    }
                    player->tiros[i].naTela = 0;
                }
            }
        }
    }

}
