#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED


void flush_in();
void exibe_mapa(int *x, int *y, char mapa[LIN][COL], char nome[],  int NINJAx[], int NINJAy[]);
void le_nome(char nome[]);
void anda(int *x, int *y, char ch, char mapa[LIN][COL]);
void atira(int xb, int yb, int ch, int prox_ch, char mapa[LIN][COL], int *x, int *y, int NINJAx[], int NINJAy[], int ninja_morto[], TEMPO *tempo, int *flag_ninja);
void anda_ninjas(int NINJAx[], int NINJAy[],char mapa[LIN][COL], int ninja_morto[]);
void recarrega_ammo(int *shuriken, TEMPO *t_ammo);

#endif // FUNC_H_INCLUDED
