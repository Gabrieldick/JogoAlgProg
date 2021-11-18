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

void exibe_mapa(PERSONAGEM *naruto, char mapa[LIN][COL], VETOR NINJA[], int *QtdNinjas, int *qtd_chaves)
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
             else if (mapa[i][j] == 'Z')
            {
                textbackground(GREEN);
                printf(" ");
            }
            else if (mapa[i][j] == 'C')
            {
                textbackground(BLUE);
                printf(" ");
                (*qtd_chaves)++;
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


    printf("\nSelecione o n�vel desejado para come�ar o jogo: ");
    gets(i);

    strcpy(nome, "mapa");
    strcat(nome, i);
    strcat(nome, ".txt");

}

char menu()
{
    char option;

    printf("Selecione uma das op��es: \n");
    printf("S - Selecionar n�vel: \n");
    printf("N - Novo jogo: \n");

    option = getch();

    return option;
}

void anda(PERSONAGEM *naruto, char ch, char mapa[LIN][COL], VETOR *pos_arm, int *chaves, int *qtd_chaves, int covarde)
{
    int andou = 0;
    switch ((ch))
    {
        case 97:
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

        case 100:
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

        case 115:
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

        case 119:
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
        if ((mapa[naruto->y - 1][naruto->x - 1] == 'X') && covarde == 0)
        {
            naruto->vidas = naruto->vidas - 1;
        }
        else if (mapa[naruto->y - 1][naruto->x - 1] == 'C')
        {
            naruto->pontos = naruto->pontos + 50;
            *chaves = *chaves + 1;
            (*qtd_chaves)--;
        }
        else if (mapa[naruto->y - 1][naruto->x - 1] == 'Z')
        {
            naruto->shurikens++;
        }
        mapa[naruto->y - 1][naruto->x - 1] = 'J';
    }
}

void atira(VETOR *pos_shuriken, int *flag_tiro, char prox_ch, char mapa[LIN][COL], VETOR NINJA[], int ninja_morto[], int *matou_todos, int *i, int *atualiza_xys, int QtdNinjas, PERSONAGEM *naruto)
{
    int n, matou=0;
    switch (toupper(prox_ch))
    {
        case 77: // ArrowRight
        case 'D':
            if (*flag_tiro == 1)
            {
                if (mapa[pos_shuriken->y - 1][pos_shuriken->x] != '#')
                {

                    gotoxy(pos_shuriken->x + 1, pos_shuriken->y);
                    textbackground(BLACK);
                    textcolor(YELLOW);
                    printf("x");
                    Sleep(10);
                    gotoxy(pos_shuriken->x + 1, pos_shuriken->y);
                    printf(" ");

                    for (n = 0; n < QtdNinjas; n++)
                    {
                        if (pos_shuriken->x == NINJA[n].x && pos_shuriken->y == NINJA[n].y)
                        {
                            gotoxy(NINJA[n].x, NINJA[n].y);
                            textbackground(BLACK);
                            printf(" ");
                            ninja_morto[n] = 1;
                            NINJA[n].x = 1;
                            NINJA[n].y = 1;
                            mapa[NINJA[n].y - 1][NINJA[n].x - 1] = ' ';
                            *matou_todos = *matou_todos + 1;
                            matou = 1;
                            naruto->pontos = naruto->pontos + 20;
                        }
                        if (matou == 1)
                        {
                            *atualiza_xys = 1;
                            *flag_tiro = 0;
                        }

                    }
                    pos_shuriken->x = pos_shuriken->x + 1;
                    *i = *i + 1;
                }
                else
                {
                    *flag_tiro = 0;
                    *atualiza_xys = 1;
                }
            }
            else
            {
                *atualiza_xys = 1;
            }
            break;

        case 75: // ArrowLeft
        case 'A':
            if (*flag_tiro == 1)
            {
                if (mapa[pos_shuriken->y - 1][pos_shuriken->x - 2] != '#')
                {
                    gotoxy(pos_shuriken->x - 1, pos_shuriken->y);
                    textbackground(BLACK);
                    textcolor(YELLOW);
                    printf("x");
                    Sleep(10);
                    gotoxy(pos_shuriken->x - 1, pos_shuriken->y);
                    printf(" ");
                    for (n = 0; n < QtdNinjas; n++)
                    {
                        if (pos_shuriken->x == NINJA[n].x && pos_shuriken->y == NINJA[n].y)
                        {
                            gotoxy(NINJA[n].x, NINJA[n].y);
                            textbackground(BLACK);
                            printf(" ");
                            ninja_morto[n] = 1;
                            NINJA[n].x = 1;
                            NINJA[n].y = 1;
                            mapa[NINJA[n].y - 1][NINJA[n].x - 1] = ' ';
                            *matou_todos = *matou_todos + 1;
                            matou = 1;
                            naruto->pontos = naruto->pontos + 20;
                        }
                        if (matou == 1)
                        {
                            *flag_tiro = 0;
                            *atualiza_xys = 1;
                        }
                    }
                    pos_shuriken->x = pos_shuriken->x - 1;
                }
                else
                {
                    *flag_tiro = 0;
                    *atualiza_xys = 1;
                }
            }
            else
            {
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
                if (sqrt(pow((NINJA[n].x - naruto.x), 2)+pow((NINJA[n].y - naruto.y), 2))<500 && valid_move == 1)
                    mov_ninja = mov_inteligente(NINJA, naruto, n);
                else
                {
                    mov_ninja = round(1 + ((float)rand() / RAND_MAX) * (4 - 1));
                    valid_move = 1;
                }


                switch (mov_ninja)
                {
                    case 1: // a
                        if (mapa[NINJA[n].y - 1][NINJA[n].x - 2] != '#' && mapa[NINJA[n].y - 1][NINJA[n].x - 2] != 'J' && mapa[NINJA[n].y - 1][NINJA[n].x - 2] != 'Z' && mapa[NINJA[n].y - 1][NINJA[n].x - 2] != 'C' )
                        {
                            gotoxy(NINJA[n].x, NINJA[n].y);
                            textbackground(BLACK);
                            printf(" ");
                            mapa[NINJA[n].y - 1][NINJA[n].x - 1] = ' ';
                            NINJA[n].x = NINJA[n].x - 1;
                            mapa[NINJA[n].y - 1][NINJA[n].x - 1] = 'N';
                            gotoxy(NINJA[n].x, NINJA[n].y);
                            textbackground(DARKGRAY);
                            printf(" ");
                            valid_move = 1;
                        }
                        else
                            valid_move = 0;
                        break;

                    case 2: // d
                        if (mapa[NINJA[n].y - 1][NINJA[n].x] != '#' && mapa[NINJA[n].y - 1][NINJA[n].x] != 'J' && mapa[NINJA[n].y - 1][NINJA[n].x] != 'C' && mapa[NINJA[n].y - 1][NINJA[n].x] != 'Z')
                        {
                            gotoxy(NINJA[n].x, NINJA[n].y);
                            textbackground(BLACK);
                            printf(" ");
                            mapa[NINJA[n].y - 1][NINJA[n].x - 1] = ' ';
                            NINJA[n].x = NINJA[n].x + 1;
                            mapa[NINJA[n].y - 1][NINJA[n].x - 1] = 'N';
                            gotoxy(NINJA[n].x, NINJA[n].y);
                            textbackground(DARKGRAY);
                            printf(" ");
                            valid_move = 1;
                        }
                        else
                            valid_move = 0;
                        break;

                    case 3: // s
                        if (mapa[NINJA[n].y][NINJA[n].x - 1] != '#' && mapa[NINJA[n].y][NINJA[n].x - 1] != 'J' && mapa[NINJA[n].y][NINJA[n].x - 1] != 'Z' && mapa[NINJA[n].y][NINJA[n].x - 1] != 'C')
                        {
                            gotoxy(NINJA[n].x, NINJA[n].y);
                            textbackground(BLACK);
                            printf(" ");
                            mapa[NINJA[n].y - 1][NINJA[n].x - 1] = ' ';
                            NINJA[n].y = NINJA[n].y + 1;
                            mapa[NINJA[n].y - 1][NINJA[n].x - 1] = 'N';
                            gotoxy(NINJA[n].x, NINJA[n].y);
                            textbackground(DARKGRAY);
                            printf(" ");
                            valid_move = 1;
                        }
                        else
                            valid_move = 0;
                        break;

                    case 4: // w
                        if (mapa[NINJA[n].y - 2][NINJA[n].x - 1] != '#' && mapa[NINJA[n].y - 2][NINJA[n].x - 1] != 'J' && mapa[NINJA[n].y - 2][NINJA[n].x - 1] != 'C' && mapa[NINJA[n].y - 2][NINJA[n].x - 1] != 'Z')
                        {
                            gotoxy(NINJA[n].x, NINJA[n].y);
                            textbackground(BLACK);
                            printf(" ");
                            mapa[NINJA[n].y - 1][NINJA[n].x - 1] = ' ';
                            NINJA[n].y = NINJA[n].y - 1;
                            mapa[NINJA[n].y - 1][NINJA[n].x - 1] = 'N';
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

void atira_ninja (int covarde, int dir_ninja[], char mapa[LIN][COL], PERSONAGEM *naruto, VETOR NINJA[], int ninja_morto[], int QtdNinjas, int tiro_ninja[], int atualiza_sn[])
{
    int i, matou = 0;
    for(i = 0; i < QtdNinjas; i++)
    {

            if (tiro_ninja[i] == 1 && ninja_morto[i]==0)
            {
                switch (dir_ninja[i])
                {
                    case 1: // atira pra esquerda
                            if (mapa[NINJA[i].Ys - 1][NINJA[i].Xs - 2] != '#')
                            {
                                gotoxy(NINJA[i].Xs - 1, NINJA[i].Ys);
                                textbackground(BLACK);
                                textcolor(LIGHTGRAY);
                                printf("x");
                                Sleep(5);
                                gotoxy(NINJA[i].Xs - 1, NINJA[i].Ys);
                                printf(" ");
                                if (NINJA[i].Xs == naruto->x && NINJA[i].Ys == naruto->y && covarde == 0)
                                {
                                    gotoxy(naruto->x, naruto->y);
                                    textbackground(BLACK);
                                    printf(" ");
                                    naruto->vidas = naruto->vidas - 1;
                                    matou = 1;
                                    naruto->x = 2;
                                    naruto->y = 2;
                                    gotoxy(naruto->x, naruto->y);
                                    textbackground(YELLOW);
                                    printf(" ");
                                }
                                NINJA[i].Xs--;
                                if (matou == 1)
                                {
                                    tiro_ninja[i] = 0;
                                    atualiza_sn[i] = 1;
                                }
                            }
                            else
                            {
                                tiro_ninja[i] = 0;
                                atualiza_sn[i] = 1;
                            }
                        break;

                    case 0: //atira pra direita
                                if (mapa[NINJA[i].Ys - 1][NINJA[i].Xs] != '#')
                                {
                                    gotoxy(NINJA[i].Xs + 1, NINJA[i].Ys);
                                    textbackground(BLACK);
                                    textcolor(LIGHTGRAY);
                                    printf("x");
                                    Sleep(5);
                                    gotoxy(NINJA[i].Xs + 1, NINJA[i].Ys);
                                    printf(" ");
                                    if (NINJA[i].Xs == naruto->x && NINJA[i].Ys == naruto->y && covarde == 0)
                                    {
                                        gotoxy(naruto->x, naruto->y);
                                        textbackground(BLACK);
                                        printf(" ");
                                        naruto->vidas = naruto->vidas - 1;
                                        matou = 1;
                                        naruto->x = 2;
                                        naruto->y = 2;
                                        gotoxy(naruto->x, naruto->y);
                                        textbackground(YELLOW);
                                        printf(" ");
                                    }
                                    if (matou == 1)
                                    {
                                        tiro_ninja[i] = 0;
                                        atualiza_sn[i] = 1;
                                    }
                                    NINJA[i].Xs++;
                                }
                                else
                                {
                                    tiro_ninja[i] = 0;
                                    atualiza_sn[i] = 1;
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

void cheat(char ch, int *estado, int *covarde)
{
      switch (ch)
      {
            case 99: //c
            case 67: //C
                  *estado = 1;
                  break;

            case 111: //o
            case 79: //O
                  if(*estado ==1)
                        *estado = 2;

                  else
                        *estado = 0;

                  break;

            case 118: //v
            case 86: //V
                  if(*estado == 2)
                        *estado = 3;

                  else
                        *estado = 0;

                  break;

            case 97: //a
            case 65: //A
                  if(*estado == 3)
                        *estado = 4;

                  else
                        *estado = 0;

                  break;

            case 114: //r
            case 82: //R
                  if(*estado == 4)
                        *estado = 5;

                  else
                        *estado = 0;

                  break;

            case 100: //d
            case 68: //D
                  if(*estado == 5)
                        *estado = 6;

                  else
                        *estado = 0;
                  break;

            case 101: //e
            case 69: //E
                  if(*estado == 6)
                        if(*covarde)
                              *covarde = 0;

                        else
                              *covarde = 1;

                  else
                        *estado = 0;

                  break;

            default:
                  *estado = 0;
                  break;
                }
}
