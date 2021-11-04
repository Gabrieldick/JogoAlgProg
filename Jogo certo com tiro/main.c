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


int main()
{
    srand(time(NULL));
    setlocale(LC_CTYPE, "");
    int vidas = 3, covarde = 0;
    TEMPO tempo, t_ammo, tempo_game, tiro_naruto;
    char mapa[LIN][COL], option;
    char nome[C];
    char ch = 0, prox_ch = 'd';
    char ch_tiro = 0;
    int  n, i, l, c;
    int NINJAx[QtdNinjasMAX], NINJAy[QtdNinjasMAX], ninja_morto[QtdNinjasMAX] = {0}, flag_ninja = 1, flag_ammo = 1, matou_todos = 0, flag_tiro=1, atualiza_xys=1;
    FILE *arq;
    int pontos = 0, chaves = 0, erro = 0, QtdNinjas = 0;
    PERSONAGEM naruto;
    VETOR pos_arm, pos_shuriken, NINJA[QtdNinjasMAX];

    pos_arm.x = 1;
    pos_arm.y = 1;
    naruto.pontos = 0;
    naruto.shurikens = 5;
    naruto.vidas = 5;

    hidecursor();
    do
    {
        option = menu();

        switch (toupper(option))
        {
            case 'N':
                le_nome(arq, nome);
                erro = copia_mapa(mapa, arq, nome);
                printf("\n");
                if (erro == 0)
                {
                    Sleep(1000);
                    clrscr();
                    textcolor(BLACK);
                    exibe_mapa(&naruto, mapa, NINJA, &QtdNinjas);

                    printf("\n");
                }
                break;

            case 0:
                break;

            default:
                printf("\nOpção invalida, digite novamente!\n\n");
        }

    }while ((option != 'N' && option != 'n') || erro ==1);



    int tiro_ninja[QtdNinjas];
    int dir_ninja[QtdNinjas];
    int atualiza_sn[QtdNinjas];
    for(i = 0; i < QtdNinjas; i++)
    {
        tiro_ninja[i] = 0;
        dir_ninja[i] = 0;
        atualiza_sn[i] = 1;

    }

    tempo_game.comeco = clock();

    while (ch != 27 && matou_todos != QtdNinjas && naruto.vidas > 0)
    {
        set_clock(&tempo_game);
        textbackground(BLACK);
        textcolor(WHITE);
        gotoxy(1, 25);
        printf("Tempo decorrido: %4.2lf\t", tempo_game.duracao);
        printf("Vidas restantes: %d \n", naruto.vidas);
        printf("Pontos: %d \n", naruto.pontos);
        printf("Chaves obtidas: %d  \n", chaves);
        if (naruto.shurikens > 0)
        {
            printf("Shurikens restantes: %d                   \n", naruto.shurikens);
        }
        else
            printf("Shurikens restantes: recarregando...\n", naruto.shurikens);

        printf("Inimigos abatidos: %d", matou_todos);
        textcolor(BLACK);
        if (flag_ninja == 1)
        {
            tempo.comeco = clock();
            flag_ninja = 0;
        }
        if (flag_ammo == 1 && naruto.shurikens == 0)
        {
            t_ammo.comeco = clock();
            flag_ammo = 0;
        }
        //if (flag_tiro == 1)
       // {
        //    tiro_naruto.comeco = clock();
         //   flag_tiro = 0;
        //}
        if (atualiza_xys==1)
        {
            pos_shuriken.x = naruto.x;
            pos_shuriken.y = naruto.y;
        }
        for(i = 0; i < QtdNinjas; i++)
        {
            if(atualiza_sn[i] == 1)
            {
                NINJA[i].Xs = NINJA[i].x;
                NINJA[i].Ys = NINJA[i].y;
            }
        }

        set_clock(&tempo);
        set_clock(&t_ammo);
        set_clock(&tiro_naruto);
        if (kbhit())
        {
            ch = getch();
            switch (toupper(ch))
            {
                case 32:
                    tiro_naruto.comeco = clock();
                    if (naruto.shurikens > 0 && tiro_naruto.duracao>=0.25)
                    {
                        atualiza_xys = 0;
                        flag_tiro = 1;
                        ch_tiro = prox_ch;
                        atira(&pos_shuriken, &flag_tiro, ch_tiro, mapa, NINJA, ninja_morto, &matou_todos, &i, &atualiza_xys, QtdNinjas);

                        naruto.shurikens--;
                    }
                    break;

                default:
                    anda(&naruto, ch, mapa, &pos_arm, &chaves);
                    ch = toupper(ch);
                    if (ch == 'A' || ch == 'D' || ch == 77 || ch == 75)
                        prox_ch = ch;
                    break;
            }
        }
        atira(&pos_shuriken, &flag_tiro, ch_tiro, mapa, NINJA, ninja_morto, &matou_todos, &i, &atualiza_xys, QtdNinjas);
        if (t_ammo.duracao >= 1.75 && flag_ammo != 1)
        {
            naruto.shurikens = 5;
            flag_ammo = 1;
        }
        if (tempo.duracao >= TIME_GAME && flag_ninja != 1)
        {

            anda_ninjas(NINJA, mapa, ninja_morto, QtdNinjas, naruto);
            for (n=0; n<QtdNinjas; n++)
            {
                if (naruto.y == NINJA[n].y && tiro_ninja[n] != 1)
                {
                    atualiza_sn[n] = 0;
                    tiro_ninja[n] = 1;
                    printf(" ");
                    if(naruto.x < NINJA[n].x)
                    {
                        dir_ninja[n] = 1;
                    }
                    else
                        dir_ninja[n] = 0;

                }

            }


            flag_ninja = 1;
        }
        atira_ninja(covarde, dir_ninja, mapa, &naruto, NINJA, ninja_morto, &tempo, &flag_ninja, &matou_todos, &pos_arm, &chaves, QtdNinjas, tiro_ninja, atualiza_sn);

        for (l = 0; l < LIN; l++)
        {
            for (c = 0; c < COL; c++)
            {
                if (mapa[l][c] == 'X')
                {
                    gotoxy(c+1, l+1);
                    textbackground(RED);
                    printf(" ");
                }
                else if (mapa[l][c] == 'C')
                {
                    gotoxy(c+1, l+1);
                    textbackground(BLUE);
                    printf(" ");
                }
            }
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
