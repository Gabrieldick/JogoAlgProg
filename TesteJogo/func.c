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
      printf("Digite o nome do arquivo com extensao: ");
      fgets(nome, C, stdin);
      nome[strcspn(nome, "\n")] = 0;

}

int menu()
{
      int option;

      printf("Selecione uma das opções: \n");
      printf("1 - Digitar o nome do mapa a ser aberto\n");
      printf("2 - Exibir o mapa selecionado e começar o jogo\n");

      printf("\nOpção selecionada: ");

      scanf("%d", &option);
      flush_in();

      return option;

}
void cria_mapa()
{

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


void atira(int x, int y, int ch)
{
    if(ch == 32)
    {
        int i;
        for(i = 1; i < 21; i++)
        {
            clrscr();
            gotoxy(x, y);
            puts("O");
            gotoxy(x, y +i);
            puts(".");
            Sleep(1);
        }
        clrscr();
        gotoxy(x, y);
        puts("O");
    }

}

