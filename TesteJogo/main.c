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
    clock_t comeco, fim;
    double duracao;
    int option = 0;
    char mapa[LIN][COL];
    char nome[C] = {"mapa1.txt"};
    char ch = 0;
    int x = 2, y = 2;
    int NINJAx[QtdNinjas], NINJAy[QtdNinjas], ninja_morto[QtdNinjas]={0}, flag_ninja=1;

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
        if (flag_ninja==1)
        {
            comeco = clock();
            flag_ninja = 0;
        }
        fim = clock();
        duracao = (double)(fim - comeco)/CLOCKS_PER_SEC;
        if(kbhit())
            {
                ch = getch();
                anda(&x, &y, ch, mapa);
                atira(x, y, ch, mapa, &x, &y, NINJAx, NINJAy, ninja_morto, duracao, &flag_ninja, fim, comeco);
            }

        if (duracao>=1 && flag_ninja!=1)
        {
            anda_ninjas(NINJAx, NINJAy, mapa, ninja_morto);
            flag_ninja = 1;
        }
    }
    system("pause");

    return 0;
}
