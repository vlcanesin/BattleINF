#ifndef DEFLIB_H
#define DEFLIB_H

#define MENU 1
#define GAME 2
#define LOADED_GAME 3
#define LOAD_MAP 4
#define RANKING 5
#define QUIT 6
#define ASK_NAME 7

#define N_LINHAS 15
#define N_COLUNAS 40

#define QUANT_TIROS 100
#define QUANT_ENERG 100
#define QUANT_INIMIGOS 50

#define  TAMANHO_TANQUE 60
#define  LARGURA_TANQUE 60

typedef struct Tiro {
    int Px;
    int Py;
    int Pr;
    int naTela;
    char origem;
    float vel;
} Tiro;

typedef struct Energia {
    int Px;
    int Py;
    int naTela;
    int sizeX;
    int sizeY;
} Energia;

typedef struct Jogador {
    float x;
    float y;
    float r;
    Rectangle pers;
    int sizeX;
    int sizeY;
    float vel;
    int vidas;
    int naTela;
    Tiro tiros[QUANT_TIROS];
} Jogador;

void MenuScreen(int *screen, int *menuOption);
void GameScreen(int *quit);

void UpdateShots(
    Jogador *player, int offset_x, int offset_y
);

void BreakWalls(
    int wall[][N_COLUNAS], Jogador *player, int quadSize[]
);

void initField(
    int wall[][N_COLUNAS], Rectangle wallRecs[][N_COLUNAS],
    float *x, float *y, float inix, float iniy
);

void UpdateWalls(
    int wall[][N_COLUNAS], Rectangle wallRecs[][N_COLUNAS],
    int quadSize[]
);

void AvoidColision(
    float *xTankAnt, float *yTankAnt, float *xTank, float *yTank,
    Rectangle wallRecs[][N_COLUNAS], float limitex, float limitey, int quadSize[]
);

void UpdateEnergCels(
    Energia energCel[], int contFrames,
    Jogador player, Rectangle wallRecs[][N_COLUNAS]
);

void UseEnergCels(
    Energia energCel[], Jogador *player, int *timer,
    float velIniP, float velIniT
);

#endif