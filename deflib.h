#ifndef DEFLIB_H
#define DEFLIB_H

#define MENU 1
#define GAME 2
#define LOADED_GAME 3
#define LOAD_MAP 4
#define RANKING 5
#define QUIT 6
#define ASK_NAME 7
#define PAUSE 8
#define DEATH 9
#define SHOW_SCORE 10
#define SHOW_HIGHSCORES 11

#define INICIO_FASE_NORMAL 0
#define CONTINUA_FASE_NORMAL 1
#define INICIO_FASE_CRIADA 2
#define CONTINUA_FASE_CRIADA 3

#define N_LINHAS 15
#define N_COLUNAS 40
#define N_FASES 4

#define QUANT_TIROS 100
#define QUANT_ENERG 100
#define QUANT_INIMIGOS  5
#define MAX_INPUT_CHARS 9

#define TAMANHO_TANQUE 60
#define LARGURA_TANQUE 60

#define OFFSET_X 30
#define OFFSET_Y 30

//const int quadSize[2] = {40, 25};
#define LIN_SIZE 40
#define COL_SIZE 25

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
    int alinhado;
    int sizeX;
    int sizeY;
    float xAnt;
    float yAnt;
    float vel;
    int dogtag;
    int vidas;
    int naTela;
    int timer;
    int score;
    Rectangle pers;
    Tiro tiros[QUANT_TIROS];
} Jogador;

typedef struct Highscore {
    char nome[MAX_INPUT_CHARS];
    int score;
} Highscore;

void MenuScreen(int *screen, int *menuOption);
void GameScreen(
    int *quit, int *return_to_menu, char path[16], char idNivel, int LOADED_OR_NOT, int *player_placar
);
void ShowLevel(char level, char path[16]);

void PrintTab(
    char idNivel, Jogador player, Texture2D vida, Texture2D enerTexture
);

void CheckPause(
    int *screen_game;
);

void UpdateShots(
    Jogador *player, int timerTiro
);

void BreakWalls(
    int wall[][N_COLUNAS], Jogador *player
);

void PlayerShot(
    Jogador *player, Jogador inimigo[]
);

void initField(
    int wall[][N_COLUNAS], Rectangle wallRecs[][N_COLUNAS],
    Jogador *player, char path[16], int LOADED_OR_NOT
);

void UpdateWalls(
    int wall[][N_COLUNAS], Rectangle wallRecs[][N_COLUNAS]
);

void AvoidColision(
    Jogador *player, Jogador inimigo[],
    Rectangle wallRecs[][N_COLUNAS], float limitex, float limitey
);

int sorteiaZero(int contFrames);

void UpdateEnergCels(
    Energia energCel[], int contFrames,
    Jogador player, Rectangle wallRecs[][N_COLUNAS]
);

void UseEnergCels(
    Energia energCel[], Jogador *player,
    float velIniP, float velIniT
);

void sorteiaPosInimigo(
    Jogador inimigo[], int end,
    Jogador player, Rectangle wallRecs[][N_COLUNAS]
);

void UpdateINIMIGO(
    Jogador inimigo[], int contFrames,
    Jogador player, Rectangle wallRecs[][N_COLUNAS]

);

int EnemyShots(Jogador *inimigo);

void Movimenta_Random (Jogador *inimigo, Jogador player);

int sorteiaR(Jogador *inimigo);

void CheckDEATH (int *screen_game, Jogador *player);

int CheckCompletion (Jogador inimigo[]);

void Save (Jogador *player, Jogador inimigo[],int wall[][N_COLUNAS], int IdNivel);

void BackTOSave (Jogador *player, Jogador inimigo[]);

void BackTOSaveParedinha (int wall[][N_COLUNAS]);

void GetScores(Highscore highScores[], int limpaArquivo);

void ReadName(int *quit, char name[]);

void EscreveNome(char nome[], int player_placar, Highscore highscores[]);

void ShowHighScores(int *screen, Highscore highscores[]);

void ShowScores (int *screen ,int player_placar);

#endif
