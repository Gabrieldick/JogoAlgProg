#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED
#define LIN 23
#define COL 61
#define QtdNinjasMAX 20
#define TIME_GAME 1
#define C 50
#define INICIO 1
#define FIM 4
#define lvlMAX 99
#define Vidas_inicio 3

typedef struct
{
    clock_t comeco, fim;
    float duracao;
} TEMPO;

typedef struct
{
    int x, y;
    int vidas, pontos, shurikens;
}PERSONAGEM;

typedef struct
{
    int x, y, Xs, Ys;
}VETOR;

void flush_in();
void clearscreen();
int copia_mapa (char mapa[LIN][COL], FILE *arq, char nome[]);
void exibe_mapa(PERSONAGEM *naruto, char mapa[LIN][COL], VETOR NINJA[], int *QtdNinjas, int *qtd_chaves, int ninja_morto[], int carregando);
void le_nome(FILE *arq, char nome[]);
void anda(PERSONAGEM *naruto, char ch, char mapa[LIN][COL], VETOR *pos_arm, int *chaves, int *qtd_chaves, int covarde);
void atira(VETOR *pos_shuriken, int *ch, char prox_ch, char mapa[LIN][COL], VETOR NINJA[], int ninja_morto[], int *matou_todos, int *i, int *atualiza_xys, int QtdNinjas, PERSONAGEM *naruto);
void anda_ninjas(VETOR NINJA[], char mapa[LIN][COL], int ninja_morto[], int QtdNinjas, PERSONAGEM naruto);
void recarrega_ammo(PERSONAGEM *naruto, TEMPO *t_ammo);
void set_clock(TEMPO *tempo);
void atira_ninja (int covarde, int dir_ninja[], char mapa[LIN][COL], PERSONAGEM *naruto, VETOR NINJA[], int ninja_morto[], int QtdNinjas, int tiro_ninja[], int atualiza_sn[]);
int mov_inteligente(VETOR NINJA[], PERSONAGEM naruto, int n);
void cheat(char ch, int *estado, int *covarde);
int salva(char mapa[LIN][COL], float duracao, int level, int vidas, int pontos, int chaves, int abatidos, int shurikens, VETOR pos_shuriken, int flag_tiro, char prox_ch, int QtdNinjas, int tiro_ninja[], int ninja_morto[], int dir_ninja[], int atualiza_sn[], VETOR ninja[]); //salva o estado atual do jogo
int carrega(FILE *arq, char nome_save[], char mapa[LIN][COL], float *duracao, int *level, int *vidas, int *pontos, int *chaves, int *abatidos, int *shurikens, VETOR *pos_shuriken, int *flag_tiro, char *prox_ch, int *QtdNinjas);
int carrega_ninja(FILE *arq, int QtdNinjas, int tiro_ninja[], int ninja_morto[], int dir_ninja[], int atualiza_sn[], VETOR NINJA[]); //carrega os objetos em movimento do jogo

#endif // FUNC_H_INCLUDED
