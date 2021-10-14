#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#define TamX 12
#define TamY 12

void anda(int *x, int *y, int ch, char mapa[TamX][TamY])
{
    switch(ch)
    {
        case 97: //a
            if(mapa[*x-1][*y] != '#')
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
            if(mapa[*x+1][*y] != '#')
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
            if(mapa[*x][*y+1] != '#')
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
            if(mapa[*x][*y - 1] != '#')
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

void montaMapa(char mapa[TamX][TamY])
{
    int i, j;
    for(i = 0; i < TamX; i++)
    {
        for(j = 0; j < TamY; j++)
        {
            if(mapa[i][j] == '#')
                textbackground(WHITE);
            else
                textbackground(BLACK);
            gotoxy(i, j);
            printf("%c", mapa[i][j]);
        }
        printf("\n");
    }
}
