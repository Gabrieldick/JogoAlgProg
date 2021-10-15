#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <time.h>
#include <windows.h>
#include <conio2.h>
#include <string.h>
#include <locale.h>
#define LIN 23
#define COL 61
#define C 50

int main(void)
{
    setlocale(LC_CTYPE, "");
    int option = 0;
    char mapa[LIN][COL];
    char nome[C] = {"mapa1.txt"};
    int ch = 0;
    int x = 2, y = 2;

    while (option != 1)
    {
        option = menu();

        switch (option)
        {
            case 1:
                le_nome(nome);
                printf("\n");
                Sleep(1000);
                clrscr();
                exibe_mapa(&x, &y, mapa, nome);
                printf("\n");
                break;

            case 0:
                break;

            default:
                printf("\nOpção invalida, digite novamente!\n");
        }
    }

    textcolor(WHITE);

    while (ch != 27)
    {

        if(kbhit())
            {
                ch = getch();
                anda(&x, &y, ch, mapa);
                atira(x, y, ch, mapa, &x, &y);
            }
    }
    system("pause");

    return 0;
}
