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

typedef struct
{
    clock_t comeco, fim;
    double duracao;
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
int copia_mapa (char mapa[LIN][COL], FILE *arq, char nome[]);
void exibe_mapa(PERSONAGEM *naruto, char mapa[LIN][COL], VETOR NINJA[], int *QtdNinjas, int *qtd_chaves);
void le_nome(FILE *arq, char nome[]);
void anda(PERSONAGEM *naruto, char ch, char mapa[LIN][COL], VETOR *pos_arm, int *chaves, int *qtd_chaves, int covarde);
void atira(VETOR *pos_shuriken, int *ch, char prox_ch, char mapa[LIN][COL], VETOR NINJA[], int ninja_morto[], int *matou_todos, int *i, int *atualiza_xys, int QtdNinjas, PERSONAGEM *naruto);
void anda_ninjas(VETOR NINJA[], char mapa[LIN][COL], int ninja_morto[], int QtdNinjas, PERSONAGEM naruto);
void recarrega_ammo(PERSONAGEM *naruto, TEMPO *t_ammo);
void set_clock(TEMPO *tempo);
void atira_ninja (int covarde, int dir_ninja[], char mapa[LIN][COL], PERSONAGEM *naruto, VETOR NINJA[], int ninja_morto[], TEMPO *tempo, int *flag_ninja, int *matou_todos, VETOR *pos_arm, int *chaves, int QtdNinjas, int tiro_ninja[], int atuliza_sn[]);
int mov_inteligentey(VETOR NINJA[], PERSONAGEM naruto, int n);

#endif // FUNC_H_INCLUDED
