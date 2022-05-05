#include <stdio.h>
#include <math.h>
#include "raylib.h"
#include "deflib.h"

/*
- TAB:
  - Funções relativas à aba de informações da fase,
  como mostrar score, pausar e salvar e carregar fases.
*/

void PrintTab(char idNivel, Jogador player, Texture2D vida, Texture2D enerTexture) {

    const int screenHeight = GetScreenHeight();
    const int screenWidth = GetScreenWidth();
    int i;

    char text[7] = "Fase _ ";
    if(idNivel == 'x') {
        text[5] = 'x';
    } else {
        text[5] = idNivel + '0';
    }
    text[6] = '\0';

    char score[14] = "Score: ______ ";
    int numDig = 1;
    float scoreTemp = (float)player.score;

    while(scoreTemp >= 10) {
        scoreTemp /= 10;
        numDig++;
    }

    scoreTemp = (float)player.score;
    for(i = numDig-1; i >= 0; i--) {
        int dig = (int)(scoreTemp / pow(10, i));
        score[6+numDig-i] = dig + '0';
        scoreTemp -= dig*pow(10, i);
    }

    score[6+numDig+1] = '\0';

    DrawRectangle(0, N_LINHAS*LIN_SIZE,
                  screenWidth, screenHeight - N_LINHAS*LIN_SIZE,
                  GRAY);

    int spaceX = 25;
    for(i = 0; i < player.vidas; i++) {
        spaceX = i*(20);
        DrawTexture(vida, 25+spaceX, N_LINHAS*LIN_SIZE + 25, RAYWHITE);
    }

    if(player.timer > 0) {
        spaceX = 25 + spaceX + 50;
        DrawTexture(enerTexture, spaceX+25, N_LINHAS*LIN_SIZE + 25, RAYWHITE);
    }

    DrawText(text,
    (screenWidth-MeasureText(text, 35))/2, 620, 35, RAYWHITE);

    DrawText(score,
    (screenWidth-MeasureText(score, 20))/2, 660, 20, RAYWHITE);

}

void CheckPause(int *screen_game) {

    if(IsKeyPressed(KEY_P)) {
        if(*screen_game == GAME) {
            *screen_game = PAUSE;
        } else {
            *screen_game = GAME;
        }
    }

}

void CheckDEATH (int *screen_game, Jogador *player){
    if (player->vidas == 0){
        *screen_game = DEATH;
    }
     //if(IsKeyPressed(KEY_D)) {
       // if(*screen_game == GAME) {
         //   *screen_game = DEATH;
       // } else {
         //   *screen_game = GAME;
        //}
     //}
}

// SE TODOS OS INIMIGOS FORAM MATADOS, A FASE NORMAL FOI CONCLUIDA
int CheckCompletion (Jogador inimigo[]){
    int i, ALL_KILLED = 0, soma = 0;
    for(i = 0; i < QUANT_INIMIGOS; i++){
        if(inimigo[i].naTela == 0 ){
            soma ++;
        }
        //printf("SOMA : %d", soma);
    }
    if(soma == QUANT_INIMIGOS)
        ALL_KILLED = 1;
    else
        ALL_KILLED = 0;
    return ALL_KILLED;
}

// SALVA OS ATRIBUTOS DO PLAYER E DOS INIMIGOS, AS PAREDES E O ID DO NIVEL SALVO
void Save (Jogador *player, Jogador inimigo[],int wall[][N_COLUNAS], int IdNivel){ //fiz de quase todos os parametros pq tada dando errado s� passando a struct
    int i = 0, j = 0;
    //printf(" O X E O Y DELE AGORA SAO: %.2f, %.2f", player->x, player->y);
    FILE *fjogo,*fw,*ff;
    fjogo = fopen("savedfiles/jogosalvo.bin", "wb");
    if (fjogo == NULL)
        printf("Deu algo errado em abrir.");

    if(fwrite(&player->x, sizeof(float), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fwrite(&player->y, sizeof(float), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fwrite(&player->r, sizeof(float), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fwrite(&player->alinhado, sizeof(int), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fwrite(&player->sizeX, sizeof(int), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fwrite(&player->sizeY, sizeof(int), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fwrite(&player->xAnt, sizeof(float), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fwrite(&player->yAnt, sizeof(float), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fwrite(&player->vel, sizeof(float), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fwrite(&player->dogtag, sizeof(int), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fwrite(&player->vidas, sizeof(int), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fwrite(&player->naTela, sizeof(int), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fwrite(&player->timer, sizeof(int), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fwrite(&player->score, sizeof(int), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fwrite(&player->pers, sizeof(Rectangle), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER RECTANGLE\n");

    for(i = 0; i< QUANT_INIMIGOS; i++){
        if(fwrite(&inimigo[i].x, sizeof(float), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fwrite(&inimigo[i].y, sizeof(float), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fwrite(&inimigo[i].r, sizeof(float), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fwrite(&inimigo[i].alinhado, sizeof(int), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fwrite(&inimigo[i].sizeX, sizeof(int), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fwrite(&inimigo[i].sizeY, sizeof(int), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fwrite(&inimigo[i].xAnt, sizeof(float), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fwrite(&inimigo[i].yAnt, sizeof(float), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fwrite(&inimigo[i].vel, sizeof(float), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fwrite(&inimigo[i].dogtag, sizeof(int), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fwrite(&inimigo[i].vidas, sizeof(int), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fwrite(&inimigo[i].naTela, sizeof(int), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fwrite(&inimigo[i].timer, sizeof(int), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fwrite(&inimigo[i].score, sizeof(int), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fwrite(&inimigo[i].pers, sizeof(Rectangle), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER RECTANGLE\n");
    }

       ///////////////////////////////////////


    fw = fopen("savedfiles/SaveW.bin", "wb");
    if (fw == NULL)
        printf("Erro ao criar save WALLS\n");
    ff = fopen("savedfiles/SaveF.bin", "wb");
    if (ff == NULL)
        printf("Erro ao criar save FASE\n");



    for(i = 0; i < N_LINHAS; i++) {
        for(j = 0; j < N_COLUNAS; j++){
            fwrite(&wall[i][j], sizeof(int), 1, fw);
        }
    }
    if(fwrite(&IdNivel, sizeof(int), 1, ff) != 1)
        printf("DEU MERDA COM A FASE\n");

    //printf("Tudo foi salvo no arquivo de save");

    fclose(fw);
    fclose(ff);
    fclose(fjogo);
}

// LE OS ATRIBUTOS DO PLAYER E DOS INIMIGOS
void BackTOSave (Jogador *player, Jogador inimigo[]){ //s� da read
    //////////////
    FILE *fjogo;
    int i = 0;
    //int j = 0;
    fjogo = fopen("savedfiles/jogosalvo.bin", "rb");
    if (fjogo == NULL)
        printf("Deu algo errado em abrir.");

    if(fread(&player->x, sizeof(float), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fread(&player->y, sizeof(float), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fread(&player->r, sizeof(float), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fread(&player->alinhado, sizeof(int), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fread(&player->sizeX, sizeof(int), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fread(&player->sizeY, sizeof(int), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fread(&player->xAnt, sizeof(float), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fread(&player->yAnt, sizeof(float), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fread(&player->vel, sizeof(float), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fread(&player->dogtag, sizeof(int), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fread(&player->vidas, sizeof(int), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fread(&player->naTela, sizeof(int), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
    if(fread(&player->timer, sizeof(int), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fread(&player->score, sizeof(int), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fread(&player->pers, sizeof(Rectangle), 1, fjogo) != 1)
        printf("DEU MERDA COM O PLAYER RECTANGLE\n");

    for(i = 0; i< QUANT_INIMIGOS; i++){
        if(fread(&inimigo[i].x, sizeof(float), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fread(&inimigo[i].y, sizeof(float), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fread(&inimigo[i].r, sizeof(float), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fread(&inimigo[i].alinhado, sizeof(int), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fread(&inimigo[i].sizeX, sizeof(int), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fread(&inimigo[i].sizeY, sizeof(int), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fread(&inimigo[i].xAnt, sizeof(float), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fread(&inimigo[i].yAnt, sizeof(float), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fread(&inimigo[i].vel, sizeof(float), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fread(&inimigo[i].dogtag, sizeof(int), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fread(&inimigo[i].vidas, sizeof(int), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fread(&inimigo[i].naTela, sizeof(int), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fread(&inimigo[i].timer, sizeof(int), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fread(&inimigo[i].score, sizeof(int), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fread(&inimigo[i].pers, sizeof(Rectangle), 1, fjogo) != 1)
            printf("DEU MERDA COM O PLAYER RECTANGLE\n");
    }

        /*
        player->sizeX = LARGURA_TANQUE;
        player->sizeY = TAMANHO_TANQUE;

        player->dogtag = dogtag;
        player->x = x;
        player->y = y;
        player->r = raio;
        player->vel = velocidade;
        player->vidas = hp;
        player->score = score;
        printf(" esse eh do player %f \n", player->x);
        printf(" do player %f \n", player->y);
        printf(" x eh: %f", x);
        printf(" y eh: %f", y);
        printf(" dogtag eh: %d", dogtag);
        printf(" raio eh: %f", raio);
        printf(" hp eh: %d", hp);
        printf(" score eh: %d", score);
        fclose(fdogtag);
        fclose(fpers_x);
        fclose(fpers_y);
        fclose(fr);
        fclose(fvel);
        fclose(fvidas);
        fclose(fscore);*/

       // player->x = TESTE.x;
        //player->y = TESTE.y;
        //player->r = TESTE.r;
       // player->dogtag = TESTE.dogtag;
        //player->score = TESTE.score;
        //player->vel= TESTE.vel;
        //player->vidas = TESTE.vidas;

        //printf("player.x em BackTOSave: %f\n", player->x);
        fclose(fjogo);
}

// LE AS PAREDINHAS
void BackTOSaveParedinha (int wall[][N_COLUNAS]){
    FILE *fw;
    int paredinha = 0, i,j;
    fw = fopen("savedfiles/SaveW.bin", "r");
    if (fw == NULL)
        printf("ERRO EM ABRIR ARQUIVO WALL\n");
    for(i = 0; i < N_LINHAS; i++){
        for(j = 0; j < N_COLUNAS; j++){
            fread(&paredinha,sizeof(int), 1, fw);
            wall[i][j] = paredinha;
            //printf("%d ", wall[i][j]);
            }
            //printf("\n");
        }
        fclose(fw);

}
