#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#define TamX 11
#define TamY 11

void anda(int *x, int *y, int ch, char mapa[TamX][TamY])
{
    switch(ch)
    {
        case 97:
            clrscr();
            if(mapa[*x-1][*y] != '#')
            {
                mapa[*x][*y] =  ' ';
                *x= *x - 1;
                mapa[*x][*y] =  'O';
            }
            montaMapa(mapa);
            break;

        case 100:
            clrscr();
            if(mapa[*x+1][*y] != '#')
            {
                mapa[*x][*y] =  ' ';
                *x= *x + 1;
                mapa[*x][*y] =  'O';
            }
            montaMapa(mapa);
            break;

        case 115:
            clrscr();
            if(mapa[*x][*y+1] != '#')
            {
                mapa[*x][*y] =  ' ';
                *y= *y + 1;
                mapa[*x][*y] =  'O';
            }
            montaMapa(mapa);
            break;

        case 119:
            clrscr();
            if(mapa[*x][*y - 1] != '#')
            {
                mapa[*x][*y] =  ' ';
                *y = *y - 1;
                mapa[*x][*y] =  'O';
            }
            montaMapa(mapa);
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

void montaMapa(char mapa[TamX][TamY])
{
    int i, j;
    for(i = 0; i < TamX; i++)
    {
        for(j = 0; j < TamY; j++)
        {
            if(mapa[j][i] == '#')
                textbackground(WHITE);
            else
                textbackground(BLACK);

            printf(" %c ", mapa[j][i]);
        }
        printf("\n");
    }
}
