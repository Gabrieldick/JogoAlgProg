#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <time.h>
#include <windows.h>
#include <conio2.h>
#include <string.h>
#include <ctype.h>
#define LIN 23
#define COL 61
#define C 50
#define INICIO 1
#define FIM 4
#define QtdNinjas 5

//Limpa o buffer do teclado
void flush_in()
{
      int ch;
      while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}

void exibe_mapa(int *x, int *y, char mapa[LIN][COL], char nome[],  int NINJAx[], int NINJAy[])
{
      int i, j, n=0;
      FILE *arq;

      arq=fopen(nome, "r");

      printf("\n");
      gotoxy(*x-1, *y-1);
      for(i=0; i<LIN; i++)
      {
            for(j=0; j<COL; j++)
            {
                  fscanf(arq,"%c", &mapa[i][j]);
                  if(mapa[i][j]=='#')
                    {
                      textbackground(WHITE);
                      printf(" ");
                    }
                  else if(mapa[i][j]=='J')
                    {
                        textbackground(YELLOW);
                        printf(" ");
                    }
                    else if(mapa[i][j]=='N')
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
                        printf("%c", mapa[i][j]); //testar se a impress�o esta correta
                    }

            }

      }

      printf("\n");

      fclose(arq); //fechar arquivo
}

void le_nome(char nome[])
{
    int i;
    do
    {
        printf("\nSelecione o n�vel desejado (1 ou 2) para come�ar o jogo: ");
        scanf("%d", &i);
        if ((i!=1 && i!=2)) printf("\nDesculpe, n�o foi encontrado este n�vel, selecione n�veis de 1 a 2\n");
    } while (i!=1 && i!=2);

    switch(i)
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

      printf("Selecione uma das op��es: \n");
      printf("1 - Selecionar o mapa desejado: \n");

      printf("\nOp��o selecionada: ");

      scanf("%d", &option);
      flush_in();

      return option;

}

void anda(int *x, int *y, char ch, char mapa[LIN][COL])
{
    switch(toupper(ch))
    {
        case 75: // ArrowLeft
        case 'A': //a
            if(mapa[*y-1][*x-2] != '#')
            {
                gotoxy(*x,*y);
                textbackground(BLACK);
                printf(" ");
                *x= *x - 1;
                gotoxy(*x,*y);
                textbackground(YELLOW);
                printf(" ");
            }
            break;

        case 77: // ArrowRight
        case 'D': //d
            if(mapa[*y-1][*x] != '#')
            {
                gotoxy(*x,*y);
                textbackground(BLACK);
                printf(" ");
                *x= *x + 1;
                gotoxy(*x,*y);
                textbackground(YELLOW);
                printf(" ");
            }
            break;

        case 80: // ArrowDown
        case 'S': //s
            if(mapa[*y][*x-1] != '#')
            {
                gotoxy(*x,*y);
                textbackground(BLACK);
                printf(" ");
                *y= *y + 1;
                gotoxy(*x,*y);
                textbackground(YELLOW);
                printf(" ");
            }
            break;

        case 72: // ArrowUp
        case 'W': //w
            if(mapa[*y-2][*x-1] != '#')
            {
                gotoxy(*x,*y);
                textbackground(BLACK);
                printf(" ");
                *y = *y - 1;
                gotoxy(*x,*y);
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


void atira(int xb, int yb, int ch, char mapa[LIN][COL], int *x, int *y, int NINJAx[], int NINJAy[], int ninja_morto[])
{
    int i, n;
    if(ch == 32)
    {
        for(i=0; i<=58; i++)
        {
            if(mapa[yb-1][xb] != '#')
                {
                    gotoxy(xb+1, yb);
                    textbackground(BLACK);
                    textcolor(LIGHTGRAY);
                    printf("x");
                    Sleep(25);
                    gotoxy(xb+1, yb);
                    printf(" ");
                    for(n=0; n<QtdNinjas; n++)
                    {
                        if(xb==NINJAx[n] && yb==NINJAy[n])
                        {
                            ninja_morto[n]=1;
                        }
                    }
                    xb++;
                }
            if(kbhit())
            {
                ch = getch();
                anda(&*x, &*y, ch, mapa);
            }
        }

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


void anda_ninjas(int NINJAx[], int NINJAy[],char mapa[LIN][COL], int ninja_morto[])
{
    int mov_ninja, valid_move, n=0;
    for(n=0; n<QtdNinjas; n++)
    {
        if (ninja_morto[n]!=1)
        {
            mov_ninja = round(1 + ( (float)rand() / RAND_MAX) * (4 - 1));
            do
            {
                switch(mov_ninja)
                {
                    case 1://a
                        if(mapa[NINJAy[n] -1][NINJAx[n] -2] != '#')
                        {
                            gotoxy(NINJAx[n] ,NINJAy[n]);
                            textbackground(BLACK);
                            printf(" ");
                            NINJAx[n] = NINJAx[n]  - 1;
                            gotoxy(NINJAx[n] ,NINJAy[n]);
                            textbackground(DARKGRAY);
                            printf(" ");
                            valid_move = 1;
                        }
                        break;

                    case 2://d
                        if(mapa[NINJAy[n]-1][NINJAx[n] ] != '#')
                        {
                            gotoxy(NINJAx[n] ,NINJAy[n]);
                            textbackground(BLACK);
                            printf(" ");
                            NINJAx[n] = NINJAx[n]  + 1;
                            gotoxy(NINJAx[n] ,NINJAy[n]);
                            textbackground(DARKGRAY);
                            printf(" ");
                            valid_move = 1;
                        }
                        break;

                    case 3://s
                        if(mapa[NINJAy[n]][NINJAx[n] -1] != '#')
                        {
                            gotoxy(NINJAx[n] ,NINJAy[n]);
                            textbackground(BLACK);
                            printf(" ");
                          NINJAy[n]= NINJAy[n] + 1;
                            gotoxy(NINJAx[n] ,NINJAy[n]);
                            textbackground(DARKGRAY);
                            printf(" ");
                            valid_move = 1;
                        }
                        break;

                    case 4://w
                        if(mapa[NINJAy[n]-2][NINJAx[n] -1] != '#')
                        {
                            gotoxy(NINJAx[n] ,NINJAy[n]);
                            textbackground(BLACK);
                            printf(" ");
                           NINJAy[n] = NINJAy[n] - 1;
                            gotoxy(NINJAx[n] ,NINJAy[n] );
                            textbackground(DARKGRAY);
                            printf(" ");
                            valid_move = 1;
                        }
                        break;

                    default:
                        valid_move = 0;
                        break;
                }
            }while(valid_move==0);
        }
    }
}
