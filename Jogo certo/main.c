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
    srand(time(NULL)); //gera valores aleatorios para utilizar na movimetação dos inimigos
    setlocale(LC_CTYPE, ""); //muda o idioma de exibição para o padrão atual do sistema
    int covarde = 0, estado=0, carregando = 0; //variaveis de controle do cheat e de loading do mapa
    TEMPO tempo, tempo_game; //variaveis para uso nos timers
    char mapa[LIN][COL], option, opt_menu; //copia do mapa da fase atual e variaveis de controle do menu
    char nome[C]; //string para o nome da fase atual
    char ch, prox_ch = 'd'; //variaveis de controle
    char ch_tiro; //variavel de controle direção da shuriken do personagem
    int  n, i, l, c; //varaveis para uso em for
    int ninja_morto[QtdNinjasMAX] = {0}, flag_ninja = 1, abatidos = 0, flag_tiro=0; //vetor com o estado dos ninjas, flag auxiliar para timing para movimentação do ninja, quantidade de inimigos abatidos
    FILE *arq; //ponteiro para o arquivo
    int chaves = 0, erro = 0, qtd_chaves = 0; //quantidade de chaves coletadas, flag de erro, quantidade total de erros
    int  QtdNinjas = 0, level = 1, qtd_level; //quantidade total de ninjas no mapa, level atual do mapa, quantidade total de mapas
    PERSONAGEM naruto; //struct com informações do personagem
    VETOR pos_shuriken, NINJA[QtdNinjasMAX]; //vetor com coordenadas da shuriken do ninja e estrutura com posição de cada ninja e posição da shuriken de cada
    int tiro_ninja[QtdNinjasMAX]; //vetor com flags de controle sobre o estado dos tiros de cada ninja
    int dir_ninja[QtdNinjasMAX]; //direção de movimento de cada ninja
    int atualiza_sn[QtdNinjasMAX]; //vetor para atualizar a posição da shuriken de cada ninja
    int level_inicial; //variavel com o level inicial ou level atual carregado
    float save_time=0; //variavel auxiliar para o tempo salvo de um jogo
    char nome_save[] = {"save.txt"}; //variavel auxiliar para abrir o save do jogo

    naruto.pontos = 0; //zera a quantidade inicial de pontos do personagem
    naruto.shurikens = 7; //quanitade inicial de shurikens disponiveis par ao usuario
    naruto.vidas = Vidas_inicio; //quantidade inicial de vidas do naruto

    hidecursor(); //função para ocultar o cursor

    for (qtd_level = 1; qtd_level<lvlMAX; qtd_level++) //identifica a quantidade total de mapas na pasta onde está o jogo
    {
            sprintf(nome, "mapa%d", qtd_level);
            strcat(nome, ".txt");
            arq = fopen(nome, "r");
            if(arq == NULL)
                  break;
    }

    fclose(arq); //fecha o arquivo aberto

    do //looping para execução do menu principal
    {
        option = menu(); //função para exibir o menu principal

        switch (toupper(option))
        {
            case 'S': //opção de salvar o jogo
                clearscreen(); //função par alimpar a tela
                printf("Inicie um jogo para salvar!\n\n");
                erro = 1;
                break;

            case 'Q': //opção para sair do jogo
                clearscreen(); //função para limpar a tela
                printf("\n\n\n\n\n\n\n\n");
                printf("\t\t\t\t\tJogo encerrado\n\n\n\n\n");
                exit(0);
                break;

            case 'C': //opção para carregar um jogo já salvo
                clearscreen(); //função para limpar a tela
                arq = fopen(nome_save, "r");
                if(carrega(arq, nome_save, mapa, &save_time, &level,  &naruto.vidas, &naruto.pontos, &chaves, &abatidos, &naruto.shurikens, &pos_shuriken, &flag_tiro, &ch_tiro, &QtdNinjas)) //carrega os dados básicos do jogo
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

            case 'N': //opção para inicializar um novo jogo
                erro = 0;
                break;

            default: //caso alguma opção diferente
                clearscreen();
                printf("Opção invalida, digite novamente!");
                erro = 1;
        }

    }while (erro == 1); //permanece no menu enquanto não houver uma opção válida

    tempo_game.comeco = clock(); //Começa a contar o tempo de jogo

    level_inicial = level; //atribui o level inicial para o level 1 ou o carregado

    for(level = level_inicial; level<qtd_level && naruto.vidas>0; level++) //looping principal em que roda o jogo
    {
        qtd_chaves = 0; //redefine a quantidade de chaves do mapa para zero

        if(carregando == 0) //se não estiver carregando um save
        {
            QtdNinjas = 0;
            for(i = 0; i < QtdNinjasMAX; i++) //identifica a quantidade total de ninjas do mapa atual e redefine suas informações
            {
                ninja_morto[i] = 0;
                tiro_ninja[i] = 0;
                dir_ninja[i] = 0;
                atualiza_sn[i] = 1;
            }
        }

        // carrega o próximo mapa
        sprintf(nome, "mapa%d", level);
        strcat(nome, ".txt");
        arq = fopen(nome, "r");

        if(carregando == 0) //se não estiver com um loading, copia o mapa da fase atual
            erro = copia_mapa(mapa, arq, nome);
        else
            erro = 0; //sem erros

        fclose(arq); //fecha o arquivo aberto
        printf("\n");
        if (erro == 0) //se não aconteceu erros, prepara exibição do mapa
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
                    if (mapa[l][c] == 'X') //não deixa as armadilhas sumirem
                    {
                        gotoxy(c+1, l+1);
                        textbackground(RED);
                        printf(" ");
                    }
                    else if (mapa[l][c] == 'C')//não deixa as chaves sumirem
                    {
                        gotoxy(c+1, l+1);
                        textbackground(BLUE);
                        printf(" ");
                    }
                    else if (mapa[l][c] == 'Z')//não deixa as shurikens sumirem
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
                    else if (mapa[l][c] == 'J' && covarde == 1)//não deixa o jogador sumir quando covarde está ativo
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
            gotoxy(65, 1); //troca a posição de origem para exibição
            printf("Nível atual: %d\t", level);
            if(covarde) //se o cheat ativo, sinaliza
            {
                  gotoxy(65, 2);
                  textbackground(RED);
                  textcolor(BLACK);
                  printf("COVARDE!!!");
            }

            else //se o cheat desativado, exibição volta ao normal
            {
                  gotoxy(65, 2);
                  textbackground(BLACK);
                  printf("              ");
            }
            gotoxy(1, 24); //troca a posição de origem para exibição
            printf("Tempo decorrido: %4.2lf\t", (tempo_game.duracao + save_time)); //exibe o tempo atual do jogo
            printf("Vidas restantes: %d \n", naruto.vidas); //exibe a quantidade de vidas do naruto
            printf("Pontos: %d \n", naruto.pontos); //exibe a pontuação atual
            printf("Chaves obtidas: %d  \n", chaves); //exibe a quantidade de chaves coletadas
            printf("Shurikens restantes: %d\n", naruto.shurikens); //exibe a quantidade de shurikens restantes
            printf("Inimigos abatidos: %d\n", abatidos); //exibe a quantidade de inimigos abatidos

            textcolor(BLACK);
            if (flag_ninja == 1) //inicializa o timer para movimentação do ninja
            {
                tempo.comeco = clock();
                flag_ninja = 0;
            }

            if (flag_tiro==0) //atualiza a posição de origem da shuriken do personagem
            {
                pos_shuriken.x = naruto.x;
                pos_shuriken.y = naruto.y;
            }
            for(i = 0; i < QtdNinjas; i++)
            {
                if(atualiza_sn[i] == 1) //atualiza as posições de origem das shurikens dos ninjas
                {
                    NINJA[i].Xs = NINJA[i].x + 1;
                    NINJA[i].Ys = NINJA[i].y;
                }
            }

            if (kbhit()) //função para keyboard hit, detecta se foi pressionada alguma tecla
            {
                ch = getch(); //armazena a tecla pressionada
                if(ch == 'l') //TIRAR!!!!!!!
                    qtd_chaves = 0;
                cheat(ch, &estado, &covarde); //chama a função para verificar o cheat

                switch (ch)
                {
                    case 32: // espaço
                    case 107: //k
                        if (naruto.shurikens > 0)
                        {
                            if(flag_tiro == 0)
                            {
                                if(!covarde)
                                    naruto.shurikens--; //decrementa a quantidade de shurikens do personagem
                                ch_tiro = prox_ch; //direção atual do tiro
                            }

                            flag_tiro = 1; //tiro em andamento

                            atira(&pos_shuriken, &flag_tiro, ch_tiro, mapa, NINJA, ninja_morto, &abatidos, &i, QtdNinjas, &naruto); //chama função do tiro
                        }
                        break;

                    case 9: //tab

                        do
                        {
                            gotoxy(1, 300);
                            textbackground(BLACK);
                            textcolor(WHITE);
                            opt_menu = menu(); //chama o menu principal
                            switch (toupper(opt_menu)) //testa a opção
                            {
                                case 'S': //opção para salvar o jogo atual
                                    if(salva(mapa, tempo_game.duracao, level,  naruto.vidas, naruto.pontos, chaves, abatidos, naruto.shurikens, pos_shuriken, flag_tiro, ch_tiro, QtdNinjas, tiro_ninja, ninja_morto, dir_ninja, atualiza_sn, NINJA)) //salva o jogo
                                        printf("\nErro ao salvar jogo!\n");

                                    break;

                                case 'Q': //opção para sair do jogo
                                    clearscreen();
                                    printf("\n\n\n\n\n\n\n\n");
                                    printf("\t\t\t\t\tJogo encerrado\n\n\n\n\n");
                                    exit(0);
                                    break;

                                case 'C': //opção para carregar um jogo existente
                                    clearscreen();
                                    arq = fopen(nome_save, "r");
                                    if(carrega(arq, nome_save, mapa, &save_time, &level,  &naruto.vidas, &naruto.pontos, &chaves, &abatidos, &naruto.shurikens, &pos_shuriken, &flag_tiro, &ch_tiro, &QtdNinjas)) //carrega os dados básicos do jogo
                                        printf("\nErro ao carregar jogo!\n");

                                    else if(carrega_ninja(arq, QtdNinjas, tiro_ninja, ninja_morto, dir_ninja, atualiza_sn, NINJA)) //Carrega os objetos em movimento do jogo
                                        printf("\nErro ao carregar jogo!\n");

                                    else
                                    {
                                        fclose(arq); //fecha o arquivo do save
                                        tempo_game.comeco = clock(); //recomeça a contar o tempo de jogo
                                        carregando = 1; //sinaliza que foi carregado um save
                                        level --; //ajusta o level de exibição para a próxima execução
                                        erro = 0; //sem erros
                                    }

                                    break;

                                case 'V': //volta para o jogo em andamento
                                    break;

                                case 'N': //inicia um jogo novo do zero e reseta as informações
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
                                     for(i = 0; i < QtdNinjas; i++) //reseta informações dos ninjas
                                    {
                                        ninja_morto[i] = 0;
                                        tiro_ninja[i] = 0;
                                        dir_ninja[i] = 0;
                                        atualiza_sn[i] = 1;
                                    }
                                    tempo_game.comeco = clock(); //recomeça a contar o tempo de jogo
                                    break;

                                default:
                                    opt_menu = 'e';
                            }
                        }while(opt_menu == 'e');
                        break;

                    default: //caso alguma opção diferente
                        anda(&naruto, ch, mapa, &chaves, &qtd_chaves, covarde); //chama a função para movimento do personagem
                        ch = toupper(ch);
                        if (ch == 'A' || ch == 'D' || ch == 77 || ch == 75) //salva a direção da shuriken a ser atirada
                            prox_ch = ch;
                        break;
                }

            }
            atira(&pos_shuriken, &flag_tiro, ch_tiro, mapa, NINJA, ninja_morto, &abatidos, &i, QtdNinjas, &naruto); //continua o movimento do tiro

            if (tempo.duracao >= TIME_GAME && flag_ninja != 1)
            {
                anda_ninjas(NINJA, mapa, ninja_morto, QtdNinjas, naruto); //função para movimentação dos ninjas
                
                for (n=0; n<QtdNinjas; n++)
                {
                    if (naruto.y == NINJA[n].y && tiro_ninja[n] != 1) //verifica se o ninja e o naruto estão na mesma linha e inicializa o tiro do ninja
                    {
                        atualiza_sn[n] = 0;
                        tiro_ninja[n] = 1;
                        textbackground(BLACK);
                        printf(" ");
                        if(naruto.x < NINJA[n].x)
                        {
                            dir_ninja[n] = 1; //direção do tiro do ninja
                        }
                        else
                            dir_ninja[n] = 0; //direção do tiro do ninja

                    }

                }

                flag_ninja = 1; //sinaliza que os ninjas realizaram um movimento
            }
            atira_ninja(covarde, dir_ninja, mapa, &naruto, NINJA, ninja_morto, QtdNinjas, tiro_ninja, atualiza_sn); //continua o tiro do ninja

        }

        clearscreen();
        gotoxy(20, 6); //muda a coordenada para exibição
        if (naruto.vidas==0) //caso acabe as vidas do personagem
        {
            textbackground(LIGHTBLUE);
            textcolor(BLACK);
            printf("GAME OVER!!! ):"); //mostra que acabou o jogo
        }
        else if (qtd_chaves == 0) //caso colete todas chaves do mapa atual
        {
            textbackground(LIGHTBLUE);
            textcolor(BLACK);
            printf("LEVEL COMPLETO!!!\n\n"); //sinaliza que o nivel foi completo
            Sleep(2000); //tempo para ficar exibindo a informação
            carregando = 0; //sinaliza que não está sendo carregado um save
        }
        textbackground(BLACK);
        textcolor(WHITE);
    }

    if (level == qtd_level) //se chegou no maximo de mapas existentes
    {
        clearscreen();
        gotoxy(20, 6);
        textbackground(LIGHTBLUE);
        textcolor(BLACK);
        printf("JOGO COMPLETO!!!\n\n"); //sinaliza que o jogo foi completo
    }

    system("pause");
    return 0; //encera o programa
}
