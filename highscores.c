#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "deflib.h"

/*
- HIGHSCORES:
  - Possui as funções que manipulam o arquivo binário
  de highscores
*/

void GetScores(Highscore highscores[], int limpaArquivo) {

    FILE *fp;

    if(!limpaArquivo) {
        fp = fopen("savedFiles/highscores.bin", "rb");

        // CRIA ARQUIVO CASO ELE AINDA NÃO EXISTA
        if(fp == NULL) {
            fp = fopen("savedFiles/highscores.bin", "wb");
            if(fp == NULL) {
                printf("Erro ao criar o arquivo de highscores!\n");
            } else {
                char dummyText[MAX_INPUT_CHARS+1] = "dummytext";
                dummyText[MAX_INPUT_CHARS] = '\0';
                int dummyValue = 0;

                //printf("dummytext: %s\n", dummyText);

                int i;
                for(i = 0; i < 5; i++) {
                    if(fputs(dummyText, fp) < 0) {
                        printf("Erro na escrita do nome do dummy!\n");
                    }
                    dummyValue = 5-i;
                    if(fwrite(&dummyValue, sizeof(dummyValue), 1, fp) != 1) {
                        printf("Erro na escrita do score do dummy!\n");
                    }
                }
                fclose(fp);
                fp = fopen("savedFiles/highscores.bin", "rb");
            }
        }
    } else {
        fp = fopen("savedFiles/highscores.bin", "wb+");

        char dummyText[MAX_INPUT_CHARS+1] = "dummytext";
        dummyText[MAX_INPUT_CHARS] = '\0';
        int dummyValue = 0;

        //printf("dummytext: %s\n", dummyText);

        int i;
        for(i = 0; i < 5; i++) {
            if(fputs(dummyText, fp) < 0) {
                printf("Erro na escrita do nome do dummy!\n");
            }
            dummyValue = 5-i;
            if(fwrite(&dummyValue, sizeof(dummyValue), 1, fp) != 1) {
                printf("Erro na escrita do score do dummy!\n");
            }
        }
    }

    // VERIFICA SE O ARQUIVO FOI CRIADO CORRETAMENTE
    if(fp != NULL) {

        int i = 0;
        fseek(fp, 0, SEEK_SET);

        while(fgets(highscores[i].nome, MAX_INPUT_CHARS+1, fp) != NULL) {
            if(fread(&highscores[i].score, sizeof(highscores[i].score), 1, fp) != 1) {
                printf("Erro na leitura da pontuacao em GetScores!\n");
            } else {
                //printf("em GetScores: highscores[%d].nome: %s\n", i, highscores[i].nome);
                //printf("em GetScores: highscores[%d].score: %d\n", i, highscores[i].score);
            }
            i++;

        }

        fclose(fp);

    } else {
        printf("Erro na leitura do arquivo de highscores!\n");
    }

}

void ReadName(int *quit, char name[]) {

    // Exemplo da raylib de leitura de caracteres:
    int screenWidth = GetScreenWidth();
    int letterCount = 0;

    Rectangle textBox = { screenWidth/2.0f - 110, 280, 225, 50 };

    int framesCounter = 0;

    while(!WindowShouldClose() && !IsKeyPressed(KEY_ENTER)) {

        // Get char pressed (unicode character) on the queue
        int key = GetCharPressed();

        // Check if more characters have been pressed on the same frame
        while (key > 0)
        {
            // NOTE: Only allow keys in range [32..125]
            if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
            {
                name[letterCount] = (char)key;
                name[letterCount+1] = '\0'; // Add null terminator at the end of the string.
                letterCount++;
            }

            key = GetCharPressed();  // Check next character in the queue
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            letterCount--;
            if (letterCount < 0) letterCount = 0;
            name[letterCount] = '\0';
        }


        framesCounter++;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("DIGITE O SEU NOME:",
                     (screenWidth - MeasureText("DIGITE O SEU NOME:", 20))/2, 240, 20, GRAY);

            DrawRectangleRec(textBox, LIGHTGRAY);
            DrawRectangleLines((int)textBox.x, (int
                                                )textBox.y, (int)textBox.width, (int)textBox.height, RED);

            DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

            DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS),
                     (screenWidth-MeasureText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 20))/2, 350, 20, DARKGRAY);

            if (letterCount < MAX_INPUT_CHARS) {
                // Draw blinking underscore char
                if (((framesCounter/20)%2) == 0)
                    DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
            }
            else DrawText("Press BACKSPACE to delete chars...",
                          (screenWidth - MeasureText("Press BACKSPACE to delete chars...", 20))/2, 400, 20, GRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------

    }

    // Mudar caso a condição do while mude
    if(!IsKeyPressed(KEY_ENTER)) {
        *quit = 1;
    }

}

void DeslocaFiles(FILE *fp, int limite) {

    //fseek(fp, 0, SEEK_END);

    int i;
    Highscore temp;
    for(i = 4; i > limite; i--) {
        //fseek(fp, -2 * (sizeof(temp.nome) + sizeof(temp.score)), SEEK_CUR);
        fseek(fp, (i-1) * (sizeof(temp.nome) + sizeof(temp.score)), SEEK_SET);

        if(fgets(temp.nome, MAX_INPUT_CHARS+1, fp) == NULL) {
            printf("Erro na leitura do nome em DeslocaFiles!\n");
        }
        if(fread(&temp.score, sizeof(temp.score), 1, fp) != 1) {
            printf("Erro na leitura do score em DeslocaFiles!\n");
        }
        /*if(fwrite(&temp.nome, sizeof(temp.nome), 1, fp) != 1) {
            printf("Erro na escrita do nome em DeslocaFiles!\n");
        }*/
        //printf("em DeslocaFiles: nome: %s score: %d\n", temp.nome, temp.score);
        fseek(fp, (i) * (sizeof(temp.nome) + sizeof(temp.score)), SEEK_SET);
        fputs(temp.nome, fp);
        if(fwrite(&temp.score, sizeof(temp.score), 1, fp) != 1) {
            printf("Erro na escrita do score em DeslocaFiles!\n");
        }

        //fseek(fp, -1 * (sizeof(temp.nome) + sizeof(temp.score)), SEEK_CUR);
    }

}

void EscreveNome(char nome[], int player_placar, Highscore highscores[]) {

    FILE *fp = fopen("savedFiles/highscores.bin", "rb+");

    int i = 0, j;
    for(i = 0; i < 5; i++) {
       if(player_placar > highscores[i].score) {
            int stringJaAcabou = 0;
            for(j = 0; j < MAX_INPUT_CHARS; j++) {
                if(nome[j] != '\0' && !stringJaAcabou) {
                    highscores[i].nome[j] = nome[j];
                } else {
                    stringJaAcabou = 1;
                    highscores[i].nome[j] = ' ';  // Faz com que todas as strings sempre tenham o tamanho máximo
                }
            }
            highscores[i].nome[j] = '\0';
            highscores[i].score = player_placar;

            //printf("highscores[i]: nome %s score %d\n", highscores[i].nome, highscores[i].score);

            DeslocaFiles(fp, i);
            /*if(fwrite(&nome, sizeof(*nome), 1, fp) != 1) {
                printf("Erro na escrita do nome em EscreveNome!\n");
            }*/
            fseek(fp, (i)*(sizeof(highscores[i].nome) + sizeof(highscores[i].score)), SEEK_SET);
            fputs(highscores[i].nome, fp);
            if(fwrite(&highscores[i].score, sizeof(highscores[i].score), 1, fp) != 1) {
                printf("Erro na escrita do score em EscreveNome!\n");
            }

            // ATUALIZA HIGHSCORES (VETOR)
            int i = 0;
            fseek(fp, 0, SEEK_SET);
            while(fgets(highscores[i].nome, MAX_INPUT_CHARS+1, fp) != NULL) {
                if(fread(&highscores[i].score, sizeof(highscores[i].score), 1, fp) != 1) {
                    printf("Erro na leitura da pontuacao em GetScores!\n");
                } else {
                    //printf("em EscreveNome: highscores[%d].nome: %s\n", i, highscores[i].nome);
                    //printf("em EscreveNome: highscores[%d].score: %d\n", i, highscores[i].score);
                }
                i++;

            }
            break;
        }
    }

    fclose(fp);

}

void ShowHighScores(int *screen, Highscore highscores[]) {

    int screenWidth = GetScreenWidth();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Highscores",
             (screenWidth-MeasureText("Highscores", 62))/2, 80, 62, RED);

    int i;
    for(i = 0; i < 5; i++) {
        DrawText(highscores[i].nome, 350, 75*i + 200, 30, BLACK);
        DrawText(TextFormat("%d", highscores[i].score),
                 screenWidth - 350 - MeasureText(TextFormat("%d", highscores[i].score), 30),
                 75*i + 200, 30, GRAY);
    }

    DrawText("Deseja voltar ao menu? (S/N)",
             (screenWidth - MeasureText("Deseja voltar ao menu? (S/N)", 20))/2, 75*i + 220, 20, RED);

    if(IsKeyPressed(KEY_S)) {
        *screen = MENU;
    }

    EndDrawing();

}

void ShowScores (int *screen ,int player_placar){
    int screenWidth = GetScreenWidth();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Highscore",
             (screenWidth-MeasureText("Highscore", 62))/2, 80, 62, RED);


        DrawText(TextFormat("%d", player_placar), 650, 275, 30, BLACK);
        DrawText("SEU SCORE FOI:", (screenWidth - MeasureText(TextFormat("%d", player_placar), 30) - 500)/2,275,30,RED);


    DrawText("Deseja voltar ao menu? (S/N)",
             (screenWidth - MeasureText("Deseja voltar ao menu? (S/N)", 20))/2, 600, 20, RED);

    if(IsKeyPressed(KEY_S)) {
        *screen = MENU;
    }

    EndDrawing();
}

