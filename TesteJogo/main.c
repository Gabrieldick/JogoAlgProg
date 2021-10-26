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
#define TIME_GAME 1

typedef struct
{
    clock_t comeco, fim;
    double duracao;
}TEMPO;

int main()
{
    srand(time(NULL));
    setlocale(LC_CTYPE, "");
    int option = 0;
    TEMPO tempo, t_ammo, tempo_game;
    char mapa[LIN][COL];
    char nome[C] = {"mapa1.txt"};
    char ch = 0, prox_ch='d';
    int x = 2, y = 2, shuriken=5;
    int NINJAx[QtdNinjas], NINJAy[QtdNinjas], ninja_morto[QtdNinjas]={0}, flag_ninja=1, flag_ammo=1;

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

    while (ch != 27)
    {
        tempo_game.fim= clock();
        tempo_game.duracao = (double)(tempo_game.fim - tempo_game.comeco)/CLOCKS_PER_SEC;
        textbackground(BLACK);
        textcolor(WHITE);
        gotoxy(1, 25);
        printf("Shurikens restantes: %d\n", shuriken);
        printf("Tempo decorrido: %4.2lf", tempo_game.duracao);
        textcolor(BLACK);
        if (flag_ninja==1)
        {
            tempo.comeco = clock();
            flag_ninja = 0;
        }
        if (flag_ammo==1 && shuriken==0)
        {
            t_ammo.comeco = clock();
            flag_ammo = 0;
        }
        tempo.fim = clock();
        t_ammo.fim = clock();
        t_ammo.duracao = (double)(t_ammo.fim - t_ammo.comeco)/CLOCKS_PER_SEC;
        tempo.duracao = (double)(tempo.fim - tempo.comeco)/CLOCKS_PER_SEC;
        if(kbhit())
            {
                ch = getch();
                switch (toupper(ch))
                {
                    case 32:
                        if (shuriken>0)
                        {
                            atira(x, y, ch, prox_ch, mapa, &x, &y, NINJAx, NINJAy, ninja_morto, &tempo, &flag_ninja);
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
                        if(ch=='A' || ch=='D' || ch==77 || ch==75) prox_ch = ch;
                        break;

                }
            }
        if (t_ammo.duracao>=1.75 && flag_ammo!=1)
        {
            shuriken=5;
            flag_ammo = 1;
        }
        if (tempo.duracao>=TIME_GAME && flag_ninja!=1)
        {
            anda_ninjas(NINJAx, NINJAy, mapa, ninja_morto);
            flag_ninja = 1;
        }

    }
    system("pause");

    return 0;
}
