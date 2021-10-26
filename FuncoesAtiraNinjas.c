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
                            *vidas--;
                            printf("teste");
                        }
                    xb++;
                }
                tempo->fim = clock();
                tempo->duracao = (double)(tempo->fim - tempo->comeco) / CLOCKS_PER_SEC;
                if (tempo->duracao >= TIME_GAME)
                {
                    anda_ninjas(NINJAx, NINJAy, mapa, ninja_morto);
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
                            *vidas--;
                            printf("teste");
                        }
                    xb--;
                }
                tempo->fim = clock();
                tempo->duracao = (double)(tempo->fim - tempo->comeco) / CLOCKS_PER_SEC;
                if (tempo->duracao >= TIME_GAME)
                {
                    anda_ninjas(NINJAx, NINJAy, mapa, ninja_morto);
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
