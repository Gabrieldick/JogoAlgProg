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
        case 97:
            if(mapa[*x-1][*y] != '#')
            {
                gotoxy(*x,*y);
                printf(" ");
                *x= *x - 1;
                gotoxy(*x,*y);
                printf("O");
            }
            break;

        case 100:
            if(mapa[*x+1][*y] != '#')
            {
                gotoxy(*x,*y);
                printf(" ");
                *x= *x + 1;
                gotoxy(*x,*y);
                printf("O");
            }
            break;

        case 115:
            if(mapa[*x][*y+1] != '#')
            {
                gotoxy(*x,*y);
                printf(" ");
                *y= *y + 1;
                gotoxy(*x,*y);
                printf("O");
            }
            break;

        case 119:
            if(mapa[*x][*y - 1] != '#')
            {
                gotoxy(*x,*y);
                printf(" ");
                *y = *y - 1;
                gotoxy(*x,*y);
                printf("O");
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

int main(void)
{
    char mapa[TamX][TamY] =
    {
        {"###########"},
        {"###########"},
        {"##O      I#"},
        {"## ###### #"},
        {"## ###### #"},
        {"##  I#S## #"},
        {"#### #I   #"},
        {"#### #### #"},
        {"#### ####I#"},
        {"##SI    IT#"},
        {"###########"}
    };


    int ch = 0;
    int x = 2, y = 2;

    textcolor(WHITE);
    montaMapa(&mapa);

    while (ch != 27)
    {
        ch = getch();
        anda(&x, &y, ch, &mapa);
        //atira(x, y, ch);
    }
    system("pause");
}
