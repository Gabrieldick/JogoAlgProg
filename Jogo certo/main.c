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
    srand(time(NULL)); //gera valores aleatorios para utilizar na movimeta��o dos inimigos
    setlocale(LC_CTYPE, ""); //muda o idioma de exibi��o para o padr�o atual do sistema
    int covarde = 0, estado=0, carregando = 0; //variaveis de controle do cheat e de loading do mapa
    TEMPO tempo, t_ammo, tempo_game, tiro_naruto; //variaveis para uso nos timers
    char mapa[LIN][COL], option, opt_menu; //copia do mapa da fase atual e variaveis de controle do menu
    char nome[C]; //string para o nome da fase atual
    char ch, prox_ch = 'd'; //variaveis de controle
    char ch_tiro; //variavel de controle dire��o da shuriken do personagem
    int  n, i, l, c; //varaveis para uso em for
    int ninja_morto[QtdNinjasMAX] = {0}, flag_ninja = 1, abatidos = 0, flag_tiro=0; //vetor com o estado dos ninjas, flag auxiliar para timing para movimenta��o do ninja, quantidade de inimigos abatidos
    FILE *arq; //ponteiro para o arquivo
    int chaves = 0, erro = 0, qtd_chaves = 0; //quantidade de chaves coletadas, flag de erro, quantidade total de erros
    int  QtdNinjas = 0, level = 1, qtd_level; //quantidade total de ninjas no mapa, level atual do mapa, quantidade total de mapas
    PERSONAGEM naruto; //struct com informa��es do personagem
    VETOR pos_shuriken, NINJA[QtdNinjasMAX]; //vetor com coordenadas da shuriken do ninja e estrutura com posi��o de cada ninja e posi��o da shuriken de cada
    int tiro_ninja[QtdNinjasMAX]; //vetor com flags de controle sobre o estado dos tiros de cada ninja
    int dir_ninja[QtdNinjasMAX]; //dire��o de movimento de cada ninja
    int atualiza_sn[QtdNinjasMAX]; //vetor para atualizar a posi��o da shuriken de cada ninja
    int level_inicial; //variavel com o level inicial ou level atual carregado
    float save_time=0; //variavel auxiliar para o tempo salvo de um jogo
    char nome_save[] = {"save.txt"}; //variavel auxiliar para abrir o save do jogo

    naruto.pontos = 0; //zera a quantidade inicial de pontos do personagem
    naruto.shurikens = 7; //quanitade inicial de shurikens disponiveis par ao usuario
    naruto.vidas = Vidas_inicio; //quantidade inicial de vidas do naruto

    hidecursor(); //fun��o para ocultar o cursor

    for (qtd_level = 1; qtd_level<lvlMAX; qtd_level++) //identifica a quantidade total de mapas na pasta onde est� o jogo
    {
            sprintf(nome, "mapa%d", qtd_level);
            strcat(nome, ".txt");
            arq = fopen(nome, "r");
            if(arq == NULL)
                  break;
    }

    fclose(arq); //fecha o arquivo aberto

    do //looping para execu��o do menu principal
    {
        option = menu(); //fun��o para exibir o menu principal

        switch (toupper(option))
        {
            case 'S': //op��o de salvar o jogo
                clearscreen(); //fun��o par alimpar a tela
                printf("Inicie um jogo para salvar!\n\n");
                erro = 1;
                break;

            case 'Q': //op��o para sair do jogo
                clearscreen(); //fun��o para limpar a tela
                printf("\n\n\n\n\n\n\n\n");
                printf("\t\t\t\t\tJogo encerrado\n\n\n\n\n");
                exit(0);
                break;

            case 'C': //op��o para carregar um jogo j� salvo
                clearscreen(); //fun��o para limpar a tela
                arq = fopen(nome_save, "r");
                if(carrega(arq, nome_save, mapa, &save_time, &level,  &naruto.vidas, &naruto.pontos, &chaves, &abatidos, &naruto.shurikens, &pos_shuriken, &flag_tiro, &ch_tiro, &QtdNinjas)) //carrega os dados b�sicos do jogo
                    printf("\nErro ao carregar jogo!\n");

                else if(carrega_ninja(arq, QtdNinjas, tiro_ninja, ninja_morto, dir_ninja, atualiza_sn, NINJA)) //Carrega os objetos em movimento do jogo
                    printf("\nErro ao carregar jogo!\n");

                else
                    {
                        fclose(arq); //fecha o arquivo aberto
                        carregando = 1; //sinaliza que foi carregado um jogo
                        erro = 0; //sem erros para carregar
                    }

                break;

            case 'N': //op��o para inicializar um novo jogo
                erro = 0;
                break;

            default: //caso alguma op��o diferente
                clearscreen();
                printf("Op��o invalida, digite novamente!");
                erro = 1;
        }

    }while (erro == 1); //permanece no menu enquanto n�o houver uma op��o v�lida

    tempo_game.comeco = clock(); //Come�a a contar o tempo de jogo

    level_inicial = level; //atribui o level inicial para o level 1 ou o carregado

    for(level = level_inicial; level<qtd_level && naruto.vidas>0; level++) //looping principal em que roda o jogo
    {
        qtd_chaves = 0; //redefine a quantidade de chaves do mapa para zero

        if(carregando == 0) //se n�o estiver carregando um save
        {
            QtdNinjas = 0;
            for(i = 0; i < QtdNinjasMAX; i++) //identifica a quantidade total de ninjas do mapa atual e redefine suas informa��es
            {
                ninja_morto[i] = 0;
                tiro_ninja[i] = 0;
                dir_ninja[i] = 0;
                atualiza_sn[i] = 1;
            }
        }

        // carrega o pr�ximo mapa
        sprintf(nome, "mapa%d", level);
        strcat(nome, ".txt");
        arq = fopen(nome, "r");

        if(carregando == 0) //se n�o estiver com um loading, copia o mapa da fase atual
            erro = copia_mapa(mapa, arq, nome);
        else
            erro = 0; //sem erros

        fclose(arq); //fecha o arquivo aberto
        printf("\n");
        if (erro == 0) //se n�o aconteceu erros, prepara exibi��o do mapa
        {
            clearscreen();
            textcolor(BLACK);
            exibe_mapa(&naruto, mapa, NINJA, &QtdNinjas, &qtd_chaves, ninja_morto, carregando);

            carregando = 0;
            printf("\n");
        }

        //loop em que o jogo funciona
        while (qtd_chaves>0 && naruto.vidas > 0 && carregando == 0)
        {
            for (l = 0; l < LIN; l++)
            {
                for (c = 0; c < COL; c++)
                {
                    if (mapa[l][c] == 'X') //n�o deixa as armadilhas sumirem
                    {
                        gotoxy(c+1, l+1);
                        textbackground(RED);
                        printf(" ");
                    }
                    else if (mapa[l][c] == 'C')//n�o deixa as chaves sumirem
                    {
                        gotoxy(c+1, l+1);
                        textbackground(BLUE);
                        printf(" ");
                    }
                    else if (mapa[l][c] == 'Z')//n�o deixa as shurikens sumirem
                    {
                        gotoxy(c+1, l+1);
                        textbackground(GREEN);
                        printf(" ");
                    }
                    else if (mapa[l][c] == '#')//evita quaisquer bugs com a parede
                    {
                        gotoxy(c+1, l+1);
                        textbackground(WHITE);
                        printf(" ");
                    }
                    else if (mapa[l][c] == 'J' && covarde == 1)//n�o deixa o jogador sumir quando covarde est� ativo
                    {
                        gotoxy(c+1, l+1);
                        textbackground(YELLOW);
                        printf(" ");
                    }

                }
            }
            for (n = 0; n<QtdNinjas; n++) //substitui o corpo do ninja morto
            {
                if (ninja_morto[n] == 0)
                {
                    gotoxy(NINJA[n].x, NINJA[n].y);
                    textbackground(DARKGRAY);
                    printf(" ");
                }
            }

            set_clock(&tempo_game); //prepara os timers para calculos durante o jogo
            textbackground(BLACK);
            textcolor(WHITE);
            gotoxy(65, 1); //troca a posi��o de origem para exibi��o
            printf("N�vel atual: %d\t", level);
            if(covarde) //se o cheat ativo, sinaliza
            {
                  gotoxy(65, 2);
                  textbackground(RED);
                  textcolor(BLACK);
                  printf("COVARDE!!!");
            }

            else //se o cheat desativado, exibi��o volta ao normal
            {
                  gotoxy(65, 2);
                  textbackground(BLACK);
                  printf("              ");
            }
            gotoxy(1, 24); //troca a posi��o de origem para exibi��o
            printf("Tempo decorrido: %4.2lf\t", (tempo_game.duracao + save_time)); //exibe o tempo atual do jogo
            printf("Vidas restantes: %d \n", naruto.vidas); //exibe a quantidade de vidas do naruto
            printf("Pontos: %d \n", naruto.pontos); //exibe a pontua��o atual
            printf("Chaves obtidas: %d  \n", chaves); //exibe a quantidade de chaves coletadas
            printf("Shurikens restantes: %d\n", naruto.shurikens); //exibe a quantidade de shurikens restantes
            printf("Inimigos abatidos: %d\n", abatidos); //exibe a quantidade de inimigos abatidos

            textcolor(BLACK);
            if (flag_ninja == 1) //inicializa o timer para movimenta��o do ninja
            {
                tempo.comeco = clock();
                flag_ninja = 0;
            }

            if (flag_tiro==0) //atualiza a posi��o de origem da shuriken do personagem
            {
                pos_shuriken.x = naruto.x;
                pos_shuriken.y = naruto.y;
            }
            for(i = 0; i < QtdNinjas; i++)
            {
                if(atualiza_sn[i] == 1) //atualiza as posi��es de origem das shurikens dos ninjas
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
                if(ch == 'l') //TIRAR!!!!!!!
                    qtd_chaves = 0;
                cheat(ch, &estado, &covarde);

                switch (ch)
                {
                    case 32: // espa�o
                    case 107: //k
                        if (naruto.shurikens > 0)
                        {
                            if(flag_tiro == 0)
                            {
                                if(!covarde)
                                    naruto.shurikens--;
                                ch_tiro = prox_ch;
                            }

                            flag_tiro = 1;

                            atira(&pos_shuriken, &flag_tiro, ch_tiro, mapa, NINJA, ninja_morto, &abatidos, &i, QtdNinjas, &naruto);
                        }
                        break;

                    case 9: //tab

                        do
                        {
                            gotoxy(1, 300);
                            textbackground(BLACK);
                            textcolor(WHITE);
                            opt_menu = menu();
                            switch (toupper(opt_menu))
                            {
                                case 'S':
                                    if(salva(mapa, tempo_game.duracao, level,  naruto.vidas, naruto.pontos, chaves, abatidos, naruto.shurikens, pos_shuriken, flag_tiro, ch_tiro, QtdNinjas, tiro_ninja, ninja_morto, dir_ninja, atualiza_sn, NINJA)) //salva o jogo
                                        printf("\nErro ao salvar jogo!\n");

                                    break;

                                case 'Q':
                                    clearscreen();
                                    printf("\n\n\n\n\n\n\n\n");
                                    printf("\t\t\t\t\tJogo encerrado\n\n\n\n\n");
                                    exit(0);
                                    break;

                                case 'C':
                                    clearscreen();
                                    arq = fopen(nome_save, "r");
                                    if(carrega(arq, nome_save, mapa, &save_time, &level,  &naruto.vidas, &naruto.pontos, &chaves, &abatidos, &naruto.shurikens, &pos_shuriken, &flag_tiro, &ch_tiro, &QtdNinjas)) //carrega os dados b�sicos do jogo
                                        printf("\nErro ao carregar jogo!\n");

                                    else if(carrega_ninja(arq, QtdNinjas, tiro_ninja, ninja_morto, dir_ninja, atualiza_sn, NINJA)) //Carrega os objetos em movimento do jogo
                                        printf("\nErro ao carregar jogo!\n");

                                    else
                                    {
                                        fclose(arq);
                                        tempo_game.comeco = clock(); //recome�a a contar o tempo de jogo
                                        carregando = 1;
                                        level --;
                                        erro = 0;
                                    }

                                    break;

                                case 'V':
                                    break;

                                case 'N': //reseta o jogo
                                    clearscreen();
                                    chaves = 0;
                                    qtd_chaves = 0;
                                    QtdNinjas = 0;
                                    naruto.pontos = 0;
                                    naruto.shurikens = 7;
                                    level = 1;
                                    covarde = 0;
                                    save_time = 0;
                                    abatidos = 0;
                                    flag_tiro = 0;
                                    naruto.vidas = Vidas_inicio;
                                    sprintf(nome, "mapa%d", level);
                                    strcat(nome, ".txt");
                                    arq = fopen(nome, "r");
                                    erro = copia_mapa(mapa, arq, nome);
                                    fclose(arq);
                                    printf("\n");
                                    if (erro == 0)
                                    {
                                        clearscreen();
                                        textcolor(BLACK);
                                        carregando = 0;
                                        exibe_mapa(&naruto, mapa, NINJA, &QtdNinjas, &qtd_chaves, ninja_morto, carregando);
                                        printf("\n");
                                    }
                                     for(i = 0; i < QtdNinjas; i++)
                                    {
                                        ninja_morto[i] = 0;
                                        tiro_ninja[i] = 0;
                                        dir_ninja[i] = 0;
                                        atualiza_sn[i] = 1;
                                    }
                                    tempo_game.comeco = clock(); //recome�a a contar o tempo de jogo
                                    break;

                                default:
                                    opt_menu = 'e';
                            }
                        }while(opt_menu == 'e');
                        break;

                    default:
                        anda(&naruto, ch, mapa, &chaves, &qtd_chaves, covarde);
                        ch = toupper(ch);
                        if (ch == 'A' || ch == 'D' || ch == 77 || ch == 75)
                            prox_ch = ch;
                        break;
                }

            }
            atira(&pos_shuriken, &flag_tiro, ch_tiro, mapa, NINJA, ninja_morto, &abatidos, &i, QtdNinjas, &naruto);

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
            atira_ninja(covarde, dir_ninja, mapa, &naruto, NINJA, ninja_morto, QtdNinjas, tiro_ninja, atualiza_sn);

        }

        clearscreen();
        gotoxy(20, 6);
        if (naruto.vidas==0)
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
            Sleep(2000);
            carregando = 0;
        }
        textbackground(BLACK);
        textcolor(WHITE);
    }

    if (level == qtd_level)
    {
        clearscreen();
        gotoxy(20, 6);
        textbackground(LIGHTBLUE);
        textcolor(BLACK);
        printf("JOGO COMPLETO!!!\n\n");
    }

    system("pause");
    return 0;
}
