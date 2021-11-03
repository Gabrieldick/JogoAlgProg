#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <time.h>
#include <windows.h>
#include <conio2.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "func.h"


// Limpa o buffer do teclado
void flush_in()
{
    int ch;
    while ((ch = fgetc(stdin)) != EOF && ch != '\n')
    {
    }
}

int copia_mapa (char mapa[LIN][COL], FILE *arq, char nome[])
{
    int i, j, erro;

    arq = fopen(nome, "r");
    if (arq == NULL)
    {
        printf("\nN�vel ainda n�o produzido!");
        erro = 1;
    }
    else
    {
        erro = 0;
        for (i = 0; i < LIN; i++)
        {
            for (j = 0; j < COL; j++)
            {
                fscanf(arq, "%c", &mapa[i][j]);
            }
        }
    }
    fclose(arq);

    return erro;
}

void exibe_mapa(PERSONAGEM *naruto, char mapa[LIN][COL], VETOR NINJA[], int *QtdNinjas)
{
    int i, j, n = 0;

    printf("\n");
    gotoxy(1, 1);
    for (i = 0; i < LIN; i++)
    {
        for (j = 0; j < COL; j++)
        {
            if (mapa[i][j] == '#')
            {
                textbackground(WHITE);
                printf(" ");
            }
            else if (mapa[i][j] == 'J')
            {
                naruto->x = j+1;
                naruto->y = i+1;
                textbackground(YELLOW);
                printf(" ");
            }
            else if (mapa[i][j] == 'N')
            {
                NINJA[n].x = wherex();
                NINJA[n].y = wherey();
                n++;
                textbackground(DARKGRAY);
                printf(" ");
                *QtdNinjas = *QtdNinjas + 1;
            }
            else if (mapa[i][j] == 'C')
            {
                textbackground(BLUE);
                printf(" ");
            }
            else if (mapa[i][j] == 'X')
            {
                textbackground(RED);
                printf(" ");
            }
            else
            {
                textbackground(BLACK);
                printf("%c", mapa[i][j]); // testar se a impress�o esta correta
            }
        }
    }

    printf("\n");

}

void le_nome(FILE *arq, char nome[])
{
    char i[2];


    printf("\nSelecione o n�vel desejado (1 ou 2) para come�ar o jogo: ");
    gets(i);

    strcpy(nome, "mapa");
    strcat(nome, i);
    strcat(nome, ".txt");

}

char menu()
{
    char option;

    printf("Selecione uma das op��es: \n");
    printf("N - Novo jogo: \n");
    option = getch();

    return option;
}

void anda(PERSONAGEM *naruto, char ch, char mapa[LIN][COL], VETOR *pos_arm, int *chaves)
{
    int andou = 0;
    switch (toupper(ch))
    {
        case 75:  // ArrowLeft
        case 'A': // a
            if (mapa[naruto->y - 1][naruto->x - 2] != '#')
            {
                mapa[naruto->y - 1][naruto->x - 1] = ' ';
                gotoxy(naruto->x, naruto->y);
                textbackground(BLACK);
                printf(" ");
                naruto->x = naruto->x - 1;
                gotoxy(naruto->x, naruto->y);
                textbackground(YELLOW);
                printf(" ");
                andou = 1;
            }
            break;

        case 77:  // ArrowRight
        case 'D': // d
            if (mapa[naruto->y - 1][naruto->x] != '#')
            {
                mapa[naruto->y - 1][naruto->x - 1] = ' ';
                gotoxy(naruto->x, naruto->y);
                textbackground(BLACK);
                printf(" ");
                naruto->x = naruto->x + 1;
                gotoxy(naruto->x, naruto->y);
                textbackground(YELLOW);
                printf(" ");
                andou = 1;
            }
            break;

        case 80:  // ArrowDown
        case 'S': // s
            if (mapa[naruto->y][naruto->x - 1] != '#')
            {
                mapa[naruto->y - 1][naruto->x - 1] = ' ';
                gotoxy(naruto->x, naruto->y);
                textbackground(BLACK);
                printf(" ");
                naruto->y = naruto->y + 1;
                gotoxy(naruto->x, naruto->y);
                textbackground(YELLOW);
                printf(" ");
                andou = 1;
            }
            break;

        case 72:  // ArrowUp
        case 'W': // w
            if (mapa[naruto->y - 2][naruto->x - 1] != '#')
            {
                mapa[naruto->y - 1][naruto->x - 1] = ' ';
                gotoxy(naruto->x, naruto->y);
                textbackground(BLACK);
                printf(" ");
                naruto->y = naruto->y - 1;
                gotoxy(naruto->x, naruto->y);
                textbackground(YELLOW);
                printf(" ");
                andou = 1;
            }
            break;

        case 27:
            puts("-- ESC!");
            puts("--- FIM!----");
            break;
    }

    if(andou = 1)
    {
        if (mapa[naruto->y - 1][naruto->x - 1] == 'X')
        {
            naruto->vidas = naruto->vidas - 1;
        }
        if (mapa[naruto->y - 1][naruto->x - 1] == 'C')
        {
            naruto->pontos = naruto->pontos + 50;
            *chaves = *chaves + 1;
        }
        mapa[naruto->y - 1][naruto->x - 1] = 'J';
    }
}

void atira(VETOR *pos_shuriken, char ch, char prox_ch, char mapa[LIN][COL], VETOR NINJA[], int ninja_morto[], int *matou_todos, int *i, int *atualiza_xys, int QtdNinjas)
{
    int n, matou=0;
    switch (toupper(prox_ch))
    {
        case 77: // ArrowRight
        case 'D':
            if (i <= 58)
            {
                if (mapa[pos_shuriken->y - 1][pos_shuriken->x] != '#')
                {
                    gotoxy(pos_shuriken->x + 1, pos_shuriken->y);
                    textbackground(BLACK);
                    textcolor(LIGHTGRAY);
                    printf("x");
                    Sleep(25);
                    gotoxy(pos_shuriken->x + 1, pos_shuriken->y);
                    printf(" ");
                    for (n = 0; n < QtdNinjas; n++)
                    {
                        if (pos_shuriken->x == NINJA[n].x && pos_shuriken->y == NINJA[n].y)
                        {
                            ninja_morto[n] = 1;
                            NINJA[n].x = 1;
                            NINJA[n].y = 1;
                            *matou_todos = *matou_todos + 1;
                            matou = 1;
                        }
                        if (matou == 1)
                            *i=59;
                    }
                    pos_shuriken->x = pos_shuriken->x + 1;
                    *i = *i + 1;
                }
            }
            else
            {
                *i=0;
                *atualiza_xys = 1;
            }
            break;

        case 75: // ArrowLeft
        case 'A':
            if (*i <= 58)
            {
                if (mapa[pos_shuriken->y - 1][pos_shuriken->x - 2] != '#')
                {
                    gotoxy(pos_shuriken->x - 1, pos_shuriken->y);
                    textbackground(BLACK);
                    textcolor(LIGHTGRAY);
                    printf("x");
                    Sleep(25);
                    gotoxy(pos_shuriken->x - 1, pos_shuriken->y);
                    printf(" ");
                    for (n = 0; n < QtdNinjas; n++)
                    {
                        if (pos_shuriken->x == NINJA[n].x && pos_shuriken->y == NINJA[n].y)
                        {
                            ninja_morto[n] = 1;
                            *matou_todos = *matou_todos + 1;
                            matou = 1;
                        }
                        if (matou == 1)
                            i=58;
                    }
                    pos_shuriken->x = pos_shuriken->x - 1;
                    *i = *i + 1;
                }
            }
            else
            {
                *i=0;
                *atualiza_xys = 1;
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

void anda_ninjas(VETOR NINJA[], char mapa[LIN][COL], int ninja_morto[], int QtdNinjas, PERSONAGEM naruto)
{
    int mov_ninja, valid_move = 1, n = 0, andou = 0;
    for (n = 0; n < QtdNinjas; n++)
    {
        if (ninja_morto[n] == 0)
        {
            do
            {
                if (sqrt(pow((NINJA[n].x - naruto.x), 2)+pow((NINJA[n].y - naruto.y), 2))<25 && valid_move == 1)
                    mov_ninja = mov_inteligente(NINJA, naruto, n);
                else
                {
                    mov_ninja = round(1 + ((float)rand() / RAND_MAX) * (4 - 1));
                    valid_move = 1;
                }


                switch (mov_ninja)
                {
                    case 1: // a
                        if (mapa[NINJA[n].y - 1][NINJA[n].x - 2] != '#' && mapa[NINJA[n].y - 1][NINJA[n].x - 2] != 'X' && mapa[NINJA[n].y - 1][NINJA[n].x - 2] != 'J')
                        {
                            gotoxy(NINJA[n].x, NINJA[n].y);
                            textbackground(BLACK);
                            printf(" ");
                            NINJA[n].x = NINJA[n].x - 1;
                            gotoxy(NINJA[n].x, NINJA[n].y);
                            textbackground(DARKGRAY);
                            printf(" ");
                            valid_move = 1;
                        }
                        else
                            valid_move = 0;
                        break;

                    case 2: // d
                        if (mapa[NINJA[n].y - 1][NINJA[n].x] != '#' && mapa[NINJA[n].y - 1][NINJA[n].x] != 'X' && mapa[NINJA[n].y - 1][NINJA[n].x] != 'J')
                        {
                            gotoxy(NINJA[n].x, NINJA[n].y);
                            textbackground(BLACK);
                            printf(" ");
                            NINJA[n].x = NINJA[n].x + 1;
                            gotoxy(NINJA[n].x, NINJA[n].y);
                            textbackground(DARKGRAY);
                            printf(" ");
                            valid_move = 1;
                        }
                        else
                            valid_move = 0;
                        break;

                    case 3: // s
                        if (mapa[NINJA[n].y][NINJA[n].x - 1] != '#' && mapa[NINJA[n].y][NINJA[n].x - 1] != 'X' && mapa[NINJA[n].y][NINJA[n].x - 1] != 'J')
                        {
                            gotoxy(NINJA[n].x, NINJA[n].y);
                            textbackground(BLACK);
                            printf(" ");
                            NINJA[n].y = NINJA[n].y + 1;
                            gotoxy(NINJA[n].x, NINJA[n].y);
                            textbackground(DARKGRAY);
                            printf(" ");
                            valid_move = 1;
                        }
                        else
                            valid_move = 0;
                        break;

                    case 4: // w
                        if (mapa[NINJA[n].y - 2][NINJA[n].x - 1] != '#' && mapa[NINJA[n].y - 2][NINJA[n].x - 1] != 'X' && mapa[NINJA[n].y - 2][NINJA[n].x - 1] != 'J')
                        {
                            gotoxy(NINJA[n].x, NINJA[n].y);
                            textbackground(BLACK);
                            printf(" ");
                            NINJA[n].y = NINJA[n].y - 1;
                            gotoxy(NINJA[n].x, NINJA[n].y);
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

void recarrega_ammo(PERSONAGEM *naruto, TEMPO *t_ammo)
{
    t_ammo->comeco = clock();
    t_ammo->duracao = 0;
    if (t_ammo->duracao < 1.75)
    {
        t_ammo->fim = clock();
        t_ammo->duracao = (double)(t_ammo->fim - t_ammo->comeco) / CLOCKS_PER_SEC;
    }
    naruto->shurikens = 5;
}

void set_clock(TEMPO *tempo)
{
    tempo->fim = clock();
    tempo->duracao = (double)(tempo->fim - tempo->comeco) / CLOCKS_PER_SEC;
}

void atira_ninja (char ch, char prox_ch, char mapa[LIN][COL], PERSONAGEM *naruto, VETOR NINJA[], int ninja_morto[], TEMPO *tempo, int *flag_ninja, int *matou_todos, VETOR *pos_arm, int *chaves, int QtdNinjas)
{
    int difx, dify, i, j, dif, xb, yb, matou;
    for(j=0; j<QtdNinjas; j++)
    {
            xb = NINJA[j].x;
            yb = NINJA[j].y;
            difx = NINJA[j].x - naruto->x; //positivo significa que ninja est� mais � direita
            dify = NINJA[j].y - naruto->y;
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
                                if (xb == naruto->x && yb == naruto->y)
                                {
                                    naruto->vidas = naruto->vidas - 1;
                                    matou = 1;
                                    naruto->x = 2;
                                    naruto->y = 2;
                                    gotoxy(naruto->x, naruto->y);
                                    textbackground(YELLOW);
                                    printf(" ");
                                }
                                xb--;
                                if (matou == 1)
                                    i=58;
                            }
                            tempo->fim = clock();
                            tempo->duracao = (double)(tempo->fim - tempo->comeco) / CLOCKS_PER_SEC;
                            if (tempo->duracao >= TIME_GAME)
                            {
                                anda_ninjas(NINJA, mapa, ninja_morto, QtdNinjas, *naruto);
                                *flag_ninja = 1;
                                tempo->comeco = clock();
                            }
                            if (kbhit())
                            {
                                ch = getch();
                                anda(naruto, ch, mapa, pos_arm, chaves);
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
                                if (xb == naruto->x && yb == naruto->y)
                                {
                                    naruto->vidas = naruto->vidas - 1;
                                    matou = 1;
                                    naruto->x = 2;
                                    naruto->y = 2;
                                    gotoxy(naruto->x, naruto->y);
                                    textbackground(YELLOW);
                                    printf(" ");
                                }
                                if (matou == 1)
                                    i=58;
                                xb++;
                            }
                            tempo->fim = clock();
                            tempo->duracao = (double)(tempo->fim - tempo->comeco) / CLOCKS_PER_SEC;
                            if (tempo->duracao >= TIME_GAME)
                            {
                                anda_ninjas(NINJA, mapa, ninja_morto, QtdNinjas, *naruto);
                                *flag_ninja = 1;
                                tempo->comeco = clock();
                            }
                            if (kbhit())
                            {
                                ch = getch();
                                anda(naruto, ch, mapa, pos_arm, chaves);
                            }
                        }
                        break;
                }
            }
    }



}

int mov_inteligente(VETOR NINJA[], PERSONAGEM naruto, int n)
{
    int movimento;
    //1a2d3s4w
    if((NINJA[n].y-naruto.y)>=1)
        movimento = 4; //W
    else if((NINJA[n].y-naruto.y)<=-1)
        movimento = 3; //S
    else if((NINJA[n].x-naruto.x)<=-1)
        movimento = 2; //D
    else movimento = 1; //A

    return movimento;
}
