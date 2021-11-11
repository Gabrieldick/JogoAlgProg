#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <time.h>
#include <windows.h>
#include <conio2.h>
#include <string.h>
#include <locale.h>
#include <math.h>
#include <ctype.h>
#include "func.h"


int main()
{
    srand(time(NULL));
    setlocale(LC_CTYPE, "");
    int vidas = 3, covarde = 0, estado=0;
    TEMPO tempo, t_ammo, tempo_game, tiro_naruto;
    char mapa[LIN][COL], option;
    char nome[C];
    char ch = 0, prox_ch = 'd';
    char ch_tiro =0;
    int  n, i, l, c;
    int ninja_morto[QtdNinjasMAX] = {0}, flag_ninja = 1, flag_ammo = 1, matou_todos = 0, flag_tiro=1, atualiza_xys=1;
    FILE *arq;
    int chaves = 0, erro = 0, qtd_chaves = 0;
    int  QtdNinjas = 0, level = 1, qtd_level;
    PERSONAGEM naruto;
    VETOR pos_arm, pos_shuriken, NINJA[QtdNinjasMAX];
    int tiro_ninja[QtdNinjasMAX];
    int dir_ninja[QtdNinjasMAX];
    int atualiza_sn[QtdNinjasMAX];

    pos_arm.x = 1;
    pos_arm.y = 1;
    naruto.pontos = 0;
    naruto.shurikens = 5;
    naruto.vidas = 5;

    hidecursor();

    for (qtd_level = 1; qtd_level<lvlMAX; qtd_level++)
    {
            sprintf(nome, "mapa%d", qtd_level);
            strcat(nome, ".txt");
            arq = fopen(nome, "r");
            if(arq == NULL)
                  break;
    }

    do
    {
        option = menu();

        switch (toupper(option))
        {
            case 'S':
                le_nome(arq, nome);
                erro = copia_mapa(mapa, arq, nome);
                printf("\n");
                if (erro == 0)
                {
                    Sleep(1000);
                    clrscr();
                    textcolor(BLACK);
                    exibe_mapa(&naruto, mapa, NINJA, &QtdNinjas, &qtd_chaves);

                    printf("\n");
                }
                break;

            case 'N':
                break;

            case 0:
                break;

            default:
                printf("\nOpção invalida, digite novamente!\n\n");
        }

    }while ((option != 'N' && option != 'n') || erro ==1);


    tempo_game.comeco = clock();

    for(level = 1; level<qtd_level; level++)
    {
        //reseta_contadores(&qtd_chaves, &ninja_morto, &QtdNinjas);
        qtd_chaves = 0;
        QtdNinjas = 0;
        if (option == 'N' || option == 'n')
        {
            sprintf(nome, "mapa%d", level);
            strcat(nome, ".txt");
            erro = copia_mapa(mapa, arq, nome);
            printf("\n");
            if (erro == 0)
            {
                Sleep(1000);
                clrscr();
                textcolor(BLACK);
                exibe_mapa(&naruto, mapa, NINJA, &QtdNinjas, &qtd_chaves);
                printf("\n");
            }
        }

         for(i = 0; i < QtdNinjas; i++)
        {
            ninja_morto[i] = 0;
            tiro_ninja[i] = 0;
            dir_ninja[i] = 0;
            atualiza_sn[i] = 1;

        }



        while (ch != 27 && qtd_chaves>0 && naruto.vidas > 0)
        {
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
                    else if (mapa[l][c] == 'Z')
                    {
                        gotoxy(c+1, l+1);
                        textbackground(GREEN);
                        printf(" ");
                    }
                    else if (mapa[l][c] == '#')
                    {
                        gotoxy(c+1, l+1);
                        textbackground(WHITE);
                        printf(" ");
                    }
                }
            }
            for (n = 0; n<QtdNinjas; n++)
            {
                if (ninja_morto[n] == 0)
                {
                    gotoxy(NINJA[n].x, NINJA[n].y);
                    textbackground(DARKGRAY);
                    printf(" ");
                }
            }

            set_clock(&tempo_game);
            textbackground(BLACK);
            textcolor(WHITE);
            gotoxy(65, 1);
            printf("Nível atual: %d\t", level);
            if(covarde)
            {
                  gotoxy(65, 2);
                  textbackground(RED);
                  textcolor(BLACK);
                  printf("COVARDE!!!");
            }

            else
            {
                  gotoxy(65, 2);
                  textbackground(BLACK);
                  printf("              ");
            }
            gotoxy(1, 25);
            printf("Tempo decorrido: %4.2lf\t", tempo_game.duracao);
            printf("Vidas restantes: %d \n", naruto.vidas);
            printf("Pontos: %d \n", naruto.pontos);
            printf("Chaves obtidas: %d  \n", chaves);
            if (naruto.shurikens > 0)
            {
                printf("Shurikens restantes: %d                                                        \n", naruto.shurikens);
            }
            else
                printf("Shurikens restantes: Sem shurikens restantes\n");

            printf("Inimigos abatidos: %d", matou_todos);
            textcolor(BLACK);
            if (flag_ninja == 1)
            {
                tempo.comeco = clock();
                flag_ninja = 0;
            }

            if (atualiza_xys==1)
            {
                pos_shuriken.x = naruto.x;
                pos_shuriken.y = naruto.y;
            }
            for(i = 0; i < QtdNinjas; i++)
            {
                if(atualiza_sn[i] == 1)
                {
                    NINJA[i].Xs = NINJA[i].x + 1;
                    NINJA[i].Ys = NINJA[i].y;
                }
            }

            set_clock(&tempo);
            set_clock(&t_ammo);
            set_clock(&tiro_naruto);

            if (kbhit())
            {
                ch = getch();

                cheat(ch, &estado, &covarde);

                switch (ch)
                {
                    case 32: // espaço
                    case 107: //k
                        if (naruto.shurikens > 0)
                        {
                            if(atualiza_xys == 1)
                            {
                                naruto.shurikens--;
                                ch_tiro = prox_ch;
                            }
                            atualiza_xys = 0;
                            flag_tiro = 1;

                            atira(&pos_shuriken, &flag_tiro, ch_tiro, mapa, NINJA, ninja_morto, &matou_todos, &i, &atualiza_xys, QtdNinjas, &naruto);
                        }
                        break;

                    default:
                        anda(&naruto, ch, mapa, &pos_arm, &chaves, &qtd_chaves, covarde);
                        ch = toupper(ch);
                        if (ch == 'A' || ch == 'D' || ch == 77 || ch == 75)
                            prox_ch = ch;
                        break;
                }

            }
            atira(&pos_shuriken, &flag_tiro, ch_tiro, mapa, NINJA, ninja_morto, &matou_todos, &i, &atualiza_xys, QtdNinjas, &naruto);

            if (tempo.duracao >= TIME_GAME && flag_ninja != 1)
            {
                anda_ninjas(NINJA, mapa, ninja_morto, QtdNinjas, naruto);
                for (n=0; n<QtdNinjas; n++)
                {
                    if (naruto.y == NINJA[n].y && tiro_ninja[n] != 1)
                    {
                        atualiza_sn[n] = 0;
                        tiro_ninja[n] = 1;
                        textbackground(BLACK);
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
        else if (qtd_chaves == 0)
        {
            textbackground(LIGHTBLUE);
            textcolor(BLACK);
            printf("LEVEL COMPLETO!!!\n\n");
        }
        textbackground(BLACK);
        textcolor(WHITE);
    }
    system("pause");
    return 0;
}
