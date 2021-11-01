#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED
#define LIN 23
#define COL 61

typedef struct
{
    clock_t comeco, fim;
    double duracao;
} TEMPO;
void flush_in();
void exibe_mapa(int *x, int *y, char mapa[LIN][COL], char nome[],  int NINJAx[], int NINJAy[]);
void le_nome(char nome[]);
void anda(int *x, int *y, char ch, char mapa[LIN][COL]);
void atira(int xb, int yb, char ch, char prox_ch, char mapa[LIN][COL], int *x, int *y, int NINJAx[], int NINJAy[], int ninja_morto[], TEMPO *tempo, int *flag_ninja, int *matou_todos);
void anda_ninjas(int NINJAx[], int NINJAy[],char mapa[LIN][COL], int ninja_morto[]);
void recarrega_ammo(int *shuriken, TEMPO *t_ammo);
void set_clock(TEMPO *tempo);
void atira_ninja (char ch, char prox_ch, char mapa[LIN][COL], int *x, int *y, int NINJAx[], int NINJAy[], int ninja_morto[], TEMPO *tempo, int *flag_ninja, int *matou_todos, int *vidas);

#endif // FUNC_H_INCLUDED
