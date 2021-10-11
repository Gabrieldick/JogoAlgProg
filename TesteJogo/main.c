#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#define TamX 11
#define TamY 11


int main(void)
{
    char mapa[TamX][TamY] =
    {
        {"##########"},
        {"#O      I#"},
        {"# ###### #"},
        {"# ###### #"},
        {"#  I#S## #"},
        {"### #I   #"},
        {"### #### #"},
        {"### ####I#"},
        {"#SI    IT#"},
        {"##########"}
    };


    int ch = 0;
    int x = 1, y = 1;

    textcolor(WHITE);
    montaMapa(mapa);

    while (ch != 27)
    {
        ch = getch();
        anda(&x, &y, ch, &mapa);
        //atira(x, y, ch);
    }
    system("pause");
}
