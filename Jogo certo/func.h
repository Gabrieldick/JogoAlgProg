#ifndef FUNC_H_INCLUDED //define que o arquivo é um cabeçalho para uso
#define FUNC_H_INCLUDED //define que o arquivo é um cabeçalho para uso
#define LIN 23 //define a quantidade máxima de linhas
#define COL 61 //define a quantidade máxima de colunas
#define QtdNinjasMAX 20 //define a quantidade máxima de ninjas que pode existir
#define TIME_GAME 1 //define a velocidade de movimentação para determinada quantidade de tempo
#define C 50 //define o tamanho máximo do nome do mapa
#define INICIO 1 //define quantidade inicial de possibilidades para movimento dos ninjas
#define FIM 4 //define a quantidade final de possibilidades para movimento dos ninjas
#define lvlMAX 99 //define a quantidade máxima de fases do jogo
#define Vidas_inicio 3 //define a quantidade inicial de vidas do personagem

typedef struct
{
    clock_t comeco, fim;
    float duracao;
} TEMPO; //estrutura para contagem dos tempos de jogo

typedef struct
{
    int x, y;
    int vidas, pontos, shurikens;
}PERSONAGEM; //estrutura para informações do personagem

typedef struct
{
    int x, y, Xs, Ys;
}VETOR; //estrutura para posições

//primeira chamada para declaração das funções
void flush_in();
void clearscreen();
int copia_mapa (char mapa[LIN][COL], FILE *arq, char nome[]);
void exibe_mapa(PERSONAGEM *naruto, char mapa[LIN][COL], VETOR NINJA[], int *QtdNinjas, int *qtd_chaves, int ninja_morto[], int carregando);
void anda(PERSONAGEM *naruto, char ch, char mapa[LIN][COL], int *chaves, int *qtd_chaves, int covarde);
void atira(VETOR *pos_shuriken, int *ch, char prox_ch, char mapa[LIN][COL], VETOR NINJA[], int ninja_morto[], int *matou_todos, int *i, int QtdNinjas, PERSONAGEM *naruto);
void anda_ninjas(VETOR NINJA[], char mapa[LIN][COL], int ninja_morto[], int QtdNinjas, PERSONAGEM naruto);
void set_clock(TEMPO *tempo);
void atira_ninja (int covarde, int dir_ninja[], char mapa[LIN][COL], PERSONAGEM *naruto, VETOR NINJA[], int ninja_morto[], int QtdNinjas, int tiro_ninja[], int atualiza_sn[]);
int mov_inteligente(VETOR NINJA[], PERSONAGEM naruto, int n);
void cheat(char ch, int *estado, int *covarde);
int salva(char mapa[LIN][COL], float duracao, int level, int vidas, int pontos, int chaves, int abatidos, int shurikens, VETOR pos_shuriken, int flag_tiro, char prox_ch, int QtdNinjas, int tiro_ninja[], int ninja_morto[], int dir_ninja[], int atualiza_sn[], VETOR ninja[]); //salva o estado atual do jogo
int carrega(FILE *arq, char nome_save[], char mapa[LIN][COL], float *duracao, int *level, int *vidas, int *pontos, int *chaves, int *abatidos, int *shurikens, VETOR *pos_shuriken, int *flag_tiro, char *prox_ch, int *QtdNinjas);
int carrega_ninja(FILE *arq, int QtdNinjas, int tiro_ninja[], int ninja_morto[], int dir_ninja[], int atualiza_sn[], VETOR NINJA[]); //carrega os objetos em movimento do jogo

#endif // FUNC_H_INCLUDED
