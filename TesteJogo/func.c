#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <time.h>
#include <windows.h>
#include <conio2.h>
#include <string.h>
#define LIN 23
#define COL 61
#define C 50

//Limpa o buffer do teclado
void flush_in()
{
      int ch;
      while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}

void exibe_mapa(int *x, int *y, char mapa[LIN][COL], char nome[])
{
      int i, j;
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
                  else
                    {
                        textbackground(BLACK);
                        printf("%c", mapa[i][j]); //testar se a impressão esta correta
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
        printf("\nSelecione o nível desejado (1 ou 2) para começar o jogo: ");
        scanf("%d", &i);
        if ((i!=1 && i!=2)) printf("\nDesculpe, não foi encontrado este nível, selecione níveis de 1 a 2\n");
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

      printf("\nSelecione uma das opções: \n");
      printf("1 - Selecionar o mapa desejado: \n");

      printf("\nOpção selecionada: ");

      scanf("%d", &option);
      flush_in();

      return option;

}

void anda(int *x, int *y, int ch, char mapa[LIN][COL])
{
    switch(ch)
    {
        case 97: //a
            if(mapa[*y-1][*x-2] != '#')
            {
                gotoxy(*x,*y);
                textbackground(BLACK);
                printf(" ");
                *x= *x - 1;
                gotoxy(*x,*y);
                textbackground(BLUE);
                printf(" ");
            }
            break;

        case 100: //d
            if(mapa[*y-1][*x] != '#')
            {
                gotoxy(*x,*y);
                textbackground(BLACK);
                printf(" ");
                *x= *x + 1;
                gotoxy(*x,*y);
                textbackground(BLUE);
                printf(" ");
            }
            break;

        case 115: //s
            if(mapa[*y][*x-1] != '#')
            {
                gotoxy(*x,*y);
                textbackground(BLACK);
                printf(" ");
                *y= *y + 1;
                gotoxy(*x,*y);
                textbackground(BLUE);
                printf(" ");
            }
            break;

        case 119: //w
            if(mapa[*y-2][*x-1] != '#')
            {
                gotoxy(*x,*y);
                textbackground(BLACK);
                printf(" ");
                *y = *y - 1;
                gotoxy(*x,*y);
                textbackground(BLUE);
                printf(" ");

            }
            break;

        case 27:
            puts("-- ESC!");
            puts("--- FIM!----");
            break;

    }
}


void atira(int xb, int yb, int ch, char mapa[LIN][COL], int *x, int *y)
{
    int i;
    if(ch == 32)
    {
        for(i=0; i<=58; i++)
        {
            if(mapa[yb-1][xb] != '#')
                {
                    gotoxy(xb+1, yb);
                    textbackground(BLACK);
                    printf("x");
                    Sleep(25);
                    gotoxy(xb+1, yb);
                    printf(" ");
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

