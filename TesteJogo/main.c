#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <time.h>
#include <windows.h>
#include <conio2.h>
#include <string.h>
#include <locale.h>
#include <math.h>
#include "func.h"
#define LIN 23
#define COL 61
#define C 50
#define QtdNinjas 5
#define TIME_GAME 1


int main()
{
    srand(time(NULL));
    setlocale(LC_CTYPE, "");
    int vidas = 3, option = 0;
    TEMPO tempo, t_ammo, tempo_game;
    char mapa[LIN][COL];
    char nome[C] = {"mapa1.txt"};
    char ch = 0, prox_ch = 'd';
    int x = 2, y = 2, shuriken = 5, n;
    int NINJAx[QtdNinjas], NINJAy[QtdNinjas], ninja_morto[QtdNinjas] = {0}, flag_ninja = 1, flag_ammo = 1, matou_todos = 0;

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

    tempo_game.comeco = clock();

    while (ch != 27 && matou_todos != QtdNinjas && vidas>0)
    {
        set_clock(&tempo_game);
        textbackground(BLACK);
        textcolor(WHITE);
        gotoxy(1, 25);
        printf("Tempo decorrido: %4.2lf\t", tempo_game.duracao);
        printf("Vidas restantes: %d\n", vidas);
        if (shuriken > 0)
        {
            printf("Shurikens restantes: %d                   \n", shuriken);
        }
        else
            printf("Shurikens restantes: recarregando...\n", shuriken);

        printf("Inimigos abatidos: %d", matou_todos);
        textcolor(BLACK);
        if (flag_ninja == 1)
        {
            tempo.comeco = clock();
            flag_ninja = 0;
        }
        if (flag_ammo == 1 && shuriken == 0)
        {
            t_ammo.comeco = clock();
            flag_ammo = 0;
        }
        set_clock(&tempo);
        set_clock(&t_ammo);
        if (kbhit())
        {
            ch = getch();
            switch (toupper(ch))
            {
                case 32:
                    if (shuriken > 0)
                    {
                        atira(x, y, ch, prox_ch, mapa, &x, &y, NINJAx, NINJAy, ninja_morto, &tempo, &flag_ninja, &matou_todos);
                        shuriken--;
                        textbackground(BLACK);
                        textcolor(WHITE);
                        gotoxy(1, 25);
                        printf("Shurikens restantes: %d", shuriken);
                        textcolor(BLACK);
                    }
                    break;

                default:
                    anda(&x, &y, ch, mapa);
                    ch = toupper(ch);
                    if (ch == 'A' || ch == 'D' || ch == 77 || ch == 75)
                        prox_ch = ch;
                    break;
            }
        }
        if (t_ammo.duracao >= 1.75 && flag_ammo != 1)
        {
            shuriken = 5;
            flag_ammo = 1;
        }
        if (tempo.duracao >= TIME_GAME && flag_ninja != 1)
        {
            anda_ninjas(NINJAx, NINJAy, mapa, ninja_morto);
            for (n=0; n<QtdNinjas; n++)
            {
                if (y == NINJAy[n])
                    atira_ninja(ch, prox_ch, mapa, &x, &y, NINJAx, NINJAy, ninja_morto, &tempo, &flag_ninja, &matou_todos, &vidas);
            }
            flag_ninja = 1;
        }
    }

    Sleep(2500);
    clrscr();
    gotoxy(20, 6);
    if (vidas<=0)
    {
        textbackground(LIGHTBLUE);
        textcolor(BLACK);
        printf("GAME OVER!!! ):");
    }
    else if (matou_todos == QtdNinjas)
    {
        textbackground(LIGHTBLUE);
        textcolor(BLACK);
        printf("LEVEL COMPLETO!!!");
    }
    textbackground(BLACK);
    printf("\t\t\t\t\t\t\t\\t\t");
    textcolor(WHITE);
    getch();
    return 0;
}
