#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <time.h>
#include <windows.h>
#include <conio2.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define TIME_GAME 1
#define LIN 23
#define COL 61
#define C 50
#define INICIO 1
#define FIM 4
#define QtdNinjas 5

typedef struct
{
    clock_t comeco, fim;
    double duracao;
} TEMPO;
// Limpa o buffer do teclado
void flush_in()
{
    int ch;
    while ((ch = fgetc(stdin)) != EOF && ch != '\n')
    {
    }
}

void exibe_mapa(int *x, int *y, char mapa[LIN][COL], char nome[], int NINJAx[], int NINJAy[])
{
    int i, j, n = 0;
    FILE *arq;

    arq = fopen(nome, "r");

    printf("\n");
    gotoxy(*x - 1, *y - 1);
    for (i = 0; i < LIN; i++)
    {
        for (j = 0; j < COL; j++)
        {
            fscanf(arq, "%c", &mapa[i][j]);
            if (mapa[i][j] == '#')
            {
                textbackground(WHITE);
                printf(" ");
            }
            else if (mapa[i][j] == 'J')
            {
                textbackground(YELLOW);
                printf(" ");
            }
            else if (mapa[i][j] == 'N')
            {
                NINJAx[n] = wherex();
                NINJAy[n] = wherey();
                n++;
                textbackground(DARKGRAY);
                printf(" ");
            }
            else
            {
                textbackground(BLACK);
                printf("%c", mapa[i][j]); // testar se a impressão esta correta
            }
        }
    }

    printf("\n");

    fclose(arq); // fechar arquivo
}

void le_nome(char nome[])
{
    int i;
    do
    {
        printf("\nSelecione o nível desejado (1 ou 2) para começar o jogo: ");
        scanf("%d", &i);
        if ((i != 1 && i != 2))
            printf("\nDesculpe, não foi encontrado este nível, selecione níveis de 1 a 2\n");
    } while (i != 1 && i != 2);

    switch (i)
    {
        case 1:
            strcpy(nome, "mapa1.txt");
            break;
        case 2:
            strcpy(nome, "mapa2.txt");
            break;
    }
}

int menu()
{
    int option;

    printf("Selecione uma das opções: \n");
    printf("1 - Selecionar o mapa desejado: \n");

    printf("\nOpção selecionada: ");

    scanf("%d", &option);
    flush_in();

    return option;
}

void anda(int *x, int *y, char ch, char mapa[LIN][COL])
{
    switch (toupper(ch))
    {
        case 75:  // ArrowLeft
        case 'A': // a
            if (mapa[*y - 1][*x - 2] != '#')
            {
                gotoxy(*x, *y);
                textbackground(BLACK);
                printf(" ");
                *x = *x - 1;
                gotoxy(*x, *y);
                textbackground(YELLOW);
                printf(" ");
            }
            break;

        case 77:  // ArrowRight
        case 'D': // d
            if (mapa[*y - 1][*x] != '#')
            {
                gotoxy(*x, *y);
                textbackground(BLACK);
                printf(" ");
                *x = *x + 1;
                gotoxy(*x, *y);
                textbackground(YELLOW);
                printf(" ");
            }
            break;

        case 80:  // ArrowDown
        case 'S': // s
            if (mapa[*y][*x - 1] != '#')
            {
                gotoxy(*x, *y);
                textbackground(BLACK);
                printf(" ");
                *y = *y + 1;
                gotoxy(*x, *y);
                textbackground(YELLOW);
                printf(" ");
            }
            break;

        case 72:  // ArrowUp
        case 'W': // w
            if (mapa[*y - 2][*x - 1] != '#')
            {
                gotoxy(*x, *y);
                textbackground(BLACK);
                printf(" ");
                *y = *y - 1;
                gotoxy(*x, *y);
                textbackground(YELLOW);
                printf(" ");
            }
            break;

        case 27:
            puts("-- ESC!");
            puts("--- FIM!----");
            break;
    }
}

void atira(int xb, int yb, char ch, char prox_ch, char mapa[LIN][COL], int *x, int *y, int NINJAx[], int NINJAy[], int ninja_morto[], TEMPO *tempo, int *flag_ninja, int *matou_todos)
{
    int i, n, matou=0;
    switch (toupper(prox_ch))
    {
        case 77: // ArrowRight
        case 'D':
            for (i = 0; i <= 58; i++)
            {
                if (mapa[yb - 1][xb] != '#')
                {
                    gotoxy(xb + 1, yb);
                    textbackground(BLACK);
                    textcolor(LIGHTGRAY);
                    printf("x");
                    Sleep(25);
                    gotoxy(xb + 1, yb);
                    printf(" ");
                    for (n = 0; n < QtdNinjas; n++)
                    {
                        if (xb == NINJAx[n] && yb == NINJAy[n])
                        {
                            ninja_morto[n] = 1;
                            *matou_todos = *matou_todos + 1;
                            matou = 1;
                        }
                        if (matou == 1)
                            i=58;
                    }
                    xb++;
                }
                tempo->fim = clock();
                tempo->duracao = (double)(tempo->fim - tempo->comeco) / CLOCKS_PER_SEC;
                if (tempo->duracao >= TIME_GAME)
                {
                    anda_ninjas(NINJAx, NINJAy, mapa, ninja_morto);
                    *flag_ninja = 1;
                    tempo->comeco = clock();
                }
                if (kbhit())
                {
                    ch = getch();
                    anda(x, y, ch, mapa);
                }
            }
            break;

        case 75: // ArrowLeft
        case 'A':
            for (i = 0; i <= 58; i++)
            {
                if (mapa[yb - 1][xb - 2] != '#')
                {
                    gotoxy(xb - 1, yb);
                    textbackground(BLACK);
                    textcolor(LIGHTGRAY);
                    printf("x");
                    Sleep(25);
                    gotoxy(xb - 1, yb);
                    printf(" ");
                    for (n = 0; n < QtdNinjas; n++)
                    {
                        if (xb == NINJAx[n] && yb == NINJAy[n])
                        {
                            ninja_morto[n] = 1;
                            *matou_todos = *matou_todos + 1;
                            matou = 1;
                        }
                        if (matou == 1)
                            i=58;
                    }
                    xb--;
                }
                if (kbhit())
                {
                    ch = getch();
                    anda(x, y, ch, mapa);
                }
            }
            break;
    }
}

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void anda_ninjas(int NINJAx[], int NINJAy[], char mapa[LIN][COL], int ninja_morto[])
{
    int mov_ninja, valid_move, n = 0;
    for (n = 0; n < QtdNinjas; n++)
    {
        if (ninja_morto[n] == 0)
        {

            do
            {
                mov_ninja = round(1 + ((float)rand() / RAND_MAX) * (4 - 1));
                switch (mov_ninja)
                {
                    case 1: // a
                        if (mapa[NINJAy[n] - 1][NINJAx[n] - 2] != '#')
                        {
                            gotoxy(NINJAx[n], NINJAy[n]);
                            textbackground(BLACK);
                            printf(" ");
                            NINJAx[n] = NINJAx[n] - 1;
                            gotoxy(NINJAx[n], NINJAy[n]);
                            textbackground(DARKGRAY);
                            printf(" ");
                            valid_move = 1;
                        }
                        else
                            valid_move = 0;
                        break;

                    case 2: // d
                        if (mapa[NINJAy[n] - 1][NINJAx[n]] != '#')
                        {
                            gotoxy(NINJAx[n], NINJAy[n]);
                            textbackground(BLACK);
                            printf(" ");
                            NINJAx[n] = NINJAx[n] + 1;
                            gotoxy(NINJAx[n], NINJAy[n]);
                            textbackground(DARKGRAY);
                            printf(" ");
                            valid_move = 1;
                        }
                        else
                            valid_move = 0;
                        break;

                    case 3: // s
                        if (mapa[NINJAy[n]][NINJAx[n] - 1] != '#')
                        {
                            gotoxy(NINJAx[n], NINJAy[n]);
                            textbackground(BLACK);
                            printf(" ");
                            NINJAy[n] = NINJAy[n] + 1;
                            gotoxy(NINJAx[n], NINJAy[n]);
                            textbackground(DARKGRAY);
                            printf(" ");
                            valid_move = 1;
                        }
                        else
                            valid_move = 0;
                        break;

                    case 4: // w
                        if (mapa[NINJAy[n] - 2][NINJAx[n] - 1] != '#')
                        {
                            gotoxy(NINJAx[n], NINJAy[n]);
                            textbackground(BLACK);
                            printf(" ");
                            NINJAy[n] = NINJAy[n] - 1;
                            gotoxy(NINJAx[n], NINJAy[n]);
                            textbackground(DARKGRAY);
                            printf(" ");
                            valid_move = 1;
                        }
                        else
                            valid_move = 0;
                        break;

                    default:
                        valid_move = 0;
                        break;
                }
            } while (valid_move == 0);
        }
    }
}

void recarrega_ammo(int *shuriken, TEMPO *t_ammo)
{
    t_ammo->comeco = clock();
    t_ammo->duracao = 0;
    if (t_ammo->duracao < 1.75)
    {
        t_ammo->fim = clock();
        t_ammo->duracao = (double)(t_ammo->fim - t_ammo->comeco) / CLOCKS_PER_SEC;
    }
    *shuriken = 5;
}

void set_clock(TEMPO *tempo)
{
    tempo->fim = clock();
    tempo->duracao = (double)(tempo->fim - tempo->comeco) / CLOCKS_PER_SEC;
}

void atira_ninja (char ch, char prox_ch, char mapa[LIN][COL], int *x, int *y, int NINJAx[], int NINJAy[], int ninja_morto[], TEMPO *tempo, int *flag_ninja, int *matou_todos, int *vidas)
{
    int difx, dify, i, j, dif, xb, yb, matou;
    for(j=0; j<QtdNinjas; j++)
    {
            xb = NINJAx[j];
            yb = NINJAy[j];
            difx = NINJAx[j] - *x; //positivo significa que ninja está mais à direita
            dify = NINJAy[j] - *y;
            if (difx>0)
                dif = 1;
            else dif = 0;
            if (dify==0 && ninja_morto[j]==0)
            {
                switch (dif)
                {
                    case 1: // atira pra esquerda
                        for (i = 0; i <= 58; i++)
                        {
                            if (mapa[yb - 1][xb - 2] != '#')
                            {
                                gotoxy(xb - 1, yb);
                                textbackground(BLACK);
                                textcolor(LIGHTGRAY);
                                printf("x");
                                Sleep(25);
                                gotoxy(xb - 1, yb);
                                printf(" ");
                                if (xb == *x && yb == *y)
                                {
                                    *vidas = *vidas - 1;
                                    matou = 1;
                                }
                                xb--;
                                if (matou == 1)
                                    i=58;
                            }
                            tempo->fim = clock();
                            tempo->duracao = (double)(tempo->fim - tempo->comeco) / CLOCKS_PER_SEC;
                            if (tempo->duracao >= TIME_GAME)
                            {
                                anda_ninjas(NINJAx, NINJAy, mapa, ninja_morto);
                                *flag_ninja = 1;
                                tempo->comeco = clock();
                            }
                            if (kbhit())
                            {
                                ch = getch();
                                anda(x, y, ch, mapa);
                            }
                        }
                        break;

                    case 0: //atira pra direita
                        for (i = 0; i <= 58; i++)
                            {
                                if (mapa[yb - 1][xb] != '#')
                            {
                                gotoxy(xb + 1, yb);
                                textbackground(BLACK);
                                textcolor(LIGHTGRAY);
                                printf("x");
                                Sleep(25);
                                gotoxy(xb + 1, yb);
                                printf(" ");
                                if (xb == *x && yb == *y)
                                {
                                    *vidas--;
                                }
                                xb++;
                            }
                            tempo->fim = clock();
                            tempo->duracao = (double)(tempo->fim - tempo->comeco) / CLOCKS_PER_SEC;
                            if (tempo->duracao >= TIME_GAME)
                            {
                                anda_ninjas(NINJAx, NINJAy, mapa, ninja_morto);
                                *flag_ninja = 1;
                                tempo->comeco = clock();
                            }
                            if (kbhit())
                            {
                                ch = getch();
                                anda(x, y, ch, mapa);
                            }
                        }
                        break;
                }
            }
    }



}
