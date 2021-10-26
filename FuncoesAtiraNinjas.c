void anda_ninjas(int NINJAx[], int NINJAy[], char mapa[LIN][COL], int ninja_morto[], int *x, int *y, int *flag_ninja, TEMPO tempo, int *vidas)
{
    int mov_ninja, valid_move, n = 0;
    for (n = 0; n < QtdNinjas; n++)
    {
        if (ninja_morto[n] == 0)
        {

                if(*y == NINJAy[n])
                {
                    if (flag_ninja==1)
                    {
                        tempo.comeco = clock();
                        flag_ninja = 0;
                    }


                    if(*x > NINJAx[n])
                    {
                        printf("%i", *vidas);
                        atira_ninjas(NINJAx[n], NINJAy[n], 32, 77, mapa, x, y, NINJAx, NINJAy, ninja_morto, &tempo, &flag_ninja, vidas);
                    }
                    else
                    {
                        printf("%i", *vidas);
                        atira_ninjas(NINJAx[n], NINJAy[n], 32, 75, mapa, x, y, NINJAx, NINJAy, ninja_morto, &tempo, &flag_ninja, vidas);
                    }

                }

            do
            {
                mov_ninja = round(1 + ((float)rand() / RAND_MAX) * (4 - 1));
                switch (mov_ninja)
                {
                    case 1: // a
                        if (mapa[NINJAy[n] - 1][NINJAx[n] - 2] != '#')
                        {
                            gotoxy(NINJAx[n], NINJAy[n]);
                            textbackground(BLACK);
                            printf(" ");
                            NINJAx[n] = NINJAx[n] - 1;
                            gotoxy(NINJAx[n], NINJAy[n]);
                            textbackground(DARKGRAY);
                            printf(" ");
                            valid_move = 1;
                        }
                        else
                            valid_move = 0;
                        break;

                    case 2: // d
                        if (mapa[NINJAy[n] - 1][NINJAx[n]] != '#')
                        {
                            gotoxy(NINJAx[n], NINJAy[n]);
                            textbackground(BLACK);
                            printf(" ");
                            NINJAx[n] = NINJAx[n] + 1;
                            gotoxy(NINJAx[n], NINJAy[n]);
                            textbackground(DARKGRAY);
                            printf(" ");
                            valid_move = 1;
                        }
                        else
                            valid_move = 0;
                        break;

                    case 3: // s
                        if (mapa[NINJAy[n]][NINJAx[n] - 1] != '#')
                        {
                            gotoxy(NINJAx[n], NINJAy[n]);
                            textbackground(BLACK);
                            printf(" ");
                            NINJAy[n] = NINJAy[n] + 1;
                            gotoxy(NINJAx[n], NINJAy[n]);
                            textbackground(DARKGRAY);
                            printf(" ");
                            valid_move = 1;
                        }
                        else
                            valid_move = 0;
                        break;

                    case 4: // w
                        if (mapa[NINJAy[n] - 2][NINJAx[n] - 1] != '#')
                        {
                            gotoxy(NINJAx[n], NINJAy[n]);
                            textbackground(BLACK);
                            printf(" ");
                            NINJAy[n] = NINJAy[n] - 1;
                            gotoxy(NINJAx[n], NINJAy[n]);
                            textbackground(DARKGRAY);
                            printf(" ");
                            valid_move = 1;
                        }
                        else
                            valid_move = 0;
                        break;

                    default:
                        valid_move = 0;
                        break;
                }
            } while (valid_move == 0);
        }
    }
}

void atira_ninjas(int xb, int yb, int ch, int prox_ch, char mapa[LIN][COL], int *x, int *y, int NINJAx[], int NINJAy[], int ninja_morto[], TEMPO *tempo, int *flag_ninja, int *vidas)
{
    int i, n;
    switch (toupper(prox_ch))
    {
        case 77: // ArrowLeft
        case 'D':
            for (i = 0; i <= 58; i++)
            {
                if (mapa[yb - 1][xb] != '#')
                {
                    gotoxy(xb + 1, yb);
                    textbackground(BLACK);
                    textcolor(LIGHTGRAY);
                    printf("x");
                    Sleep(25);
                    gotoxy(xb + 1, yb);
                    printf(" ");
                        if (xb == *x && yb == *y)
                        {

                            printf("%d", *vidas);

                        }
                    xb++;
                }
                tempo->fim = clock();
                tempo->duracao = (double)(tempo->fim - tempo->comeco) / CLOCKS_PER_SEC;
                if (tempo->duracao >= TIME_GAME)
                {

                    *flag_ninja = 1;
                    tempo->comeco = clock();
                }
                if (kbhit())
                {
                    ch = getch();
                    anda(x, y, ch, mapa);
                }
            }
            break;

        case 75: // ArrowLeft
        case 'A':
            for (i = 0; i <= 58; i++)
            {
                if (mapa[yb - 1][xb - 2] != '#')
                {
                    gotoxy(xb - 1, yb);
                    textbackground(BLACK);
                    textcolor(LIGHTGRAY);
                    printf("x");
                    Sleep(25);
                    gotoxy(xb - 1, yb);
                    printf(" ");
                        if (xb == *x && yb == *y)
                        {

                            printf("%d", *vidas);

                        }
                    xb--;
                }
                tempo->fim = clock();
                tempo->duracao = (double)(tempo->fim - tempo->comeco) / CLOCKS_PER_SEC;
                if (tempo->duracao >= TIME_GAME)
                {

                    *flag_ninja = 1;
                    tempo->comeco = clock();
                }
                if (kbhit())
                {
                    ch = getch();
                    anda(x, y, ch, mapa);
                }
            }
            break;
    }
}
