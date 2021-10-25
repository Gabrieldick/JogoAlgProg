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
#define QtdNinjas 5

int main(void)
{
     srand(time(NULL));
    setlocale(LC_CTYPE, "");
    int option = 0;
    char mapa[LIN][COL];
    char nome[C] = {"mapa1.txt"};
    char ch = 0;
    int x = 2, y = 2;
    int NINJAx[QtdNinjas], NINJAy[QtdNinjas], ninja_morto[QtdNinjas]={0};

    hidecursor();
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
                textcolor(BLACK);
                exibe_mapa(&x, &y, mapa, nome, NINJAx, NINJAy);
                printf("\n");
                break;

            case 0:
                break;

            default:
                printf("\nOpção invalida, digite novamente!\n\n");
        }
    }

    while (ch != 27)
    {

        if(kbhit())
            {
                ch = getch();
                anda(&x, &y, ch, mapa);
                anda_ninjas(NINJAx, NINJAy, mapa, ninja_morto);
                atira(x, y, ch, mapa, &x, &y, NINJAx, NINJAy, ninja_morto);
            }
    }
    system("pause");

    return 0;
}
