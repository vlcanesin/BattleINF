#include <stdio.h>
#include <math.h>
#include "raylib.h"
#include "deflib.h"

void PrintTab(int idNivel, Jogador player, Texture2D vida, Texture2D enerTexture) {

    const int screenHeight = GetScreenHeight();
    const int screenWidth = GetScreenWidth();
    int i;

    char text[7] = "Fase _ ";
    text[5] = idNivel + '0';
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

void Save (Jogador *player, Jogador inimigo[],int wall[][N_COLUNAS], int IdNivel){ //fiz de quase todos os parametros pq tada dando errado só passando a struct
    int i = 0, j = 0;
    printf(" O X E O Y DELE AGORA SAO: %.2f, %.2f", player->x, player->y);
    FILE *fdogtag,*fpers_x,*fpers_y,*fr,*fvel,*fvidas,*fi,*fw,*ff, *fscore;
    fdogtag = fopen("savedfiles/SaveDOGTAG.bin", "w");
    if (fdogtag == NULL)
        printf("Erro ao criar save PLAYER\n");
    fpers_x = fopen("savedfiles/SavePERSx.bin", "w");
    if (fpers_x == NULL)
        printf("Erro ao criar save PLAYER\n");
    fpers_y = fopen("savedfiles/SavePERSy.bin", "w");
    if (fpers_y == NULL)
        printf("Erro ao criar save PLAYER\n");
    fr = fopen("savedfiles/SaveORIENTA.bin", "w");
    if (fr == NULL)
        printf("Erro ao criar save PLAYER\n");
    fvel = fopen("savedfiles/SaveVEL.bin", "w");
    if (fvel == NULL)
        printf("Erro ao criar save PLAYER\n");
    fvidas = fopen("savedfiles/SaveVIDAS.bin", "w");
    if (fvidas == NULL)
        printf("Erro ao criar save PLAYER\n");
    fi = fopen("savedfiles/SaveI.bin", "w");
    if (fi == NULL)
        printf("Erro ao criar save Inimigo\n");
    fw = fopen("savedfiles/SaveW.bin", "w");
    if (fw == NULL)
        printf("Erro ao criar save WALLS\n");
    ff = fopen("savedfiles/SaveF.bin", "w");
    if (ff == NULL)
        printf("Erro ao criar save FASE\n");
    fscore = fopen("savedfiles/SaveSCORE.bin", "w");
    if (fscore == NULL)
        printf("Erro ao criar save SCORE\n");
    if(fwrite(&player->dogtag, sizeof(int), 1, fdogtag) != 1)
        printf("DEU MERDA COM O PLAYER\n");
     if(fwrite(&player->x, sizeof(float), 1, fpers_x) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fwrite(&player->y, sizeof(float), 1, fpers_y) != 1)
        printf("DEU MERDA COM O PLAYER\n");
     if(fwrite(&player->r, sizeof(float), 1, fr) != 1)
        printf("DEU MERDA COM O PLAYER\n");
     if(fwrite(&player->vel, sizeof(float), 1, fvel) != 1)
        printf("DEU MERDA COM O PLAYER\n");
     if(fwrite(&player->vidas, sizeof(int), 1, fvidas) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    if(fwrite(&player->score, sizeof(int), 1, fscore) != 1)
        printf("DEU MERDA COM O PLAYER\n");
    for (i = 0; i < QUANT_INIMIGOS; i++){
    if(fwrite(&inimigo[i], sizeof(Jogador), 1, fi) != 1)
        printf("DEU MERDA COM O INIMIGO\n");
    }
    for(i = 0; i < N_LINHAS; i++) {
        for(j = 0; j < N_COLUNAS; j++){
            fwrite(&wall[i][j], sizeof(int), 1, fw);
        }
    }
    if(fwrite(&IdNivel, sizeof(int), 1, ff) != 1)
        printf("DEU MERDA COM A FASE\n");

    printf("Tudo foi salvo no arquivo de save");
    fclose(fdogtag);
    fclose(fpers_x);
    fclose(fpers_y);
    fclose(fr);
    fclose(fvel);
    fclose(fvidas);
    fclose(fi);
    fclose(fw);
    fclose(ff);
    fclose(fscore);
}

void BackTOSavePlayer (Jogador *player){ //só da read
    FILE *fdogtag,*fpers_x,*fpers_y,*fr,*fvel,*fvidas,*fscore;
        fdogtag = fopen("savedfiles/SaveDOGTAG.bin", "r");
        fscore = fopen("savedfiles/SaveSCORE.bin", "r");
        fpers_x = fopen("savedfiles/SavePERSx.bin", "r");
        fpers_y = fopen("savedfiles/SavePERSy.bin", "r");
        fr = fopen("savedfiles/SaveORIENTA.bin", "r");
        fvel = fopen("savedfiles/SaveVEL.bin", "r");
        fvidas = fopen("savedfiles/SaveVIDAS.bin", "r");
        int dogtag = 0, hp = 0 ,score = 0;
        float x = 0, y = 0;
        float raio = 0, velocidade = 0;
        if(fread(&dogtag, sizeof(int), 1, fdogtag) != 1)
            printf("DEU MERDA COM O PLAYER\n");
         if(fread(&x, sizeof(float), 1, fpers_x) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fread(&y, sizeof(float), 1, fpers_y) != 1)
            printf("DEU MERDA COM O PLAYER\n");
         if(fread(&raio, sizeof(float), 1, fr) != 1)
            printf("DEU MERDA COM O PLAYER\n");
         if(fread(&velocidade, sizeof(float), 1, fvel) != 1)
            printf("DEU MERDA COM O PLAYER\n");
         if(fread(&hp, sizeof(int), 1, fvidas) != 1)
            printf("DEU MERDA COM O PLAYER\n");
        if(fread(&score, sizeof(int), 1, fscore) != 1)
            printf("DEU MERDA COM O PLAYER\n");

        player->sizeX = LARGURA_TANQUE;
        player->sizeY = TAMANHO_TANQUE;

        player->dogtag = dogtag;
        player->x = x;
        player->y = y;
        player->r = raio;
        player->vel = velocidade;
        player->vidas = hp;
        player->score = score;
        printf(" esse eh do player %.2f \n", player->x);
        printf(" do player %.2f \n", player->y);
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
        /*fclose(fscore);*/
}

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
