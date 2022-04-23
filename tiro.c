#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "deflib.h"

void UpdateShots(Jogador *player, int offset_x, int offset_y) {

    int end, i;
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    if(IsKeyPressed(KEY_SPACE)){

        for(end = 0; end < QUANT_TIROS; end++) {
            if(player->tiros[end].naTela == 0) {
                player->tiros[end].naTela = 1;
                //player->tiros[end].origem = 'p';
                break;
            }
        }

        if(end < QUANT_TIROS) {  // se foi possível colocar mais um tiro na tela...

            if(player->r == 0){
                player->tiros[end].Px = player->x + offset_x;
                player->tiros[end].Py = player->y;
                player->tiros[end].Pr = player->r;
            } else if(player->r == 180){
                player->tiros[end].Px = player->x + offset_x;
                player->tiros[end].Py = player->y + 2*offset_y;
                player->tiros[end].Pr = player->r;
            } else if(player->r == 90){
                player->tiros[end].Px = player->x + 2*offset_x;
                player->tiros[end].Py = player->y + offset_y;
                player->tiros[end].Pr = player->r;
            } else if(player->r == 270){
                player->tiros[end].Px = player->x;
                player->tiros[end].Py = player->y + offset_y;
                player->tiros[end].Pr = player->r;
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

void BreakWalls(int wall[][N_COLUNAS], Jogador *player, int quadSize[]) {

    int i, lin, col;
    for(i = 0; i < QUANT_TIROS; i++) {
        for(lin = 0; lin < N_LINHAS; lin++) {
            for(col = 0; col < N_COLUNAS; col++) {
                if(player->tiros[i].naTela == 1 && wall[lin][col] == 1 &&
                   CheckCollisionCircleRec(
                        (Vector2){player->tiros[i].Px,player->tiros[i].Py}, 5,
                        (Rectangle){col*quadSize[1], lin*quadSize[0], quadSize[1], quadSize[0]})) {
                    wall[lin][col] = 0;
                    player->tiros[i].naTela = 0;
                }
            }
        }
    }

}

