#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <time.h>
#include <windows.h>
#include <conio2.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "func.h"


void flush_in() // Limpa o buffer do teclado
{
    int ch;
    while ((ch = fgetc(stdin)) != EOF && ch != '\n')
    {
    }
}

void clearscreen() //limpa a tela
{
    #ifdef _WIN32
        system("cls");

    #elif _POSIX_C_SOURCE >= 199309L
        system("clear");

    #endif
}

int copia_mapa (char mapa[LIN][COL], FILE *arq, char nome[]) //Esta função copia o mapa com o nome da string para a matriz usada no programa
{
    int i, j;
    char cn[1] = { "\n" };
    if (arq == NULL)
    {
        printf("\nNível ainda não produzido!");
        return 1;
    }
    else
    {
        for (i = 0; i < LIN; i++)
        {
            for (j = 0; j < COL; j++)
            {
                if(i==(LIN-1) && j == (COL-1)) //evita sujeira no ultimo caractere que não existe no arquivo
                    {
                        mapa[i][j] = cn[0]; //armazena um \n no ultimo caractere do mapa
                    }

                else
                    fscanf(arq, "%c", &mapa[i][j]);
            }
        }
         return 0;
    }

}

void exibe_mapa(PERSONAGEM *naruto, char mapa[LIN][COL], VETOR NINJA[], int *QtdNinjas, int *qtd_chaves, int ninja_morto[], int carregando)
{
    int i, j, n = 0;

    gotoxy(1, 1); //Ajusta o cursor para a posição inicial
    for (i = 0; i < LIN; i++)
    {
        for (j = 0; j < COL; j++)
        {
            if (mapa[i][j] == '#') //printa as paredes
            {
                textbackground(WHITE);
                printf(" ");
            }
            else if (mapa[i][j] == 'J')//printa e define a posição do jogador
            {
                naruto->x = j+1;
                naruto->y = i+1;
                textbackground(YELLOW);
                printf(" ");
            }
            else if (mapa[i][j] == 'N' && carregando == 0)//printa e define as posições dos ninjas se o jogo não estiver sendo carregado
            {
                NINJA[n].x = wherex();
                NINJA[n].y = wherey();
                n++;
                textbackground(DARKGRAY);
                printf(" ");
                *QtdNinjas = *QtdNinjas + 1;
            }
            else if(i == (NINJA[n].y - 1) && j == (NINJA[n].x -1) && carregando == 1)//printa os ninjas em caso de jogo sendo carregado
            {

                if(ninja_morto[n] == 0)
                {
                    textbackground(DARKGRAY);
                    printf(" ");
                }
                n++;
            }
             else if (mapa[i][j] == 'Z')//printa e define as posições das shurikens adicionais
            {
                textbackground(GREEN);
                printf(" ");
            }
            else if (mapa[i][j] == 'C')//printa e define as posições das chaves
            {
                textbackground(BLUE);
                printf(" ");
                (*qtd_chaves)++;
            }
            else if (mapa[i][j] == 'X')//printa e define as posições das armadilhas
            {
                textbackground(RED);
                printf(" ");
            }
            else
            {
                textbackground(BLACK);
                printf("%c", mapa[i][j]); // printa os espaços sem nada
            }
        }
    }

    printf("\n");

}

char menu()// printa o menu do jogo
{
    char option;

    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t\tN - Novo jogo \n");
    printf("\t\t\t\t\t\tC - Carregar jogo \n");
    printf("\t\t\t\t\t\tS - Salvar jogo \n");
    printf("\t\t\t\t\t\tQ - Sair do jogo \n");
    printf("\t\t\t\t\t\tV - Voltar\n\n");
    printf("\t\t\t\t\t\tControles:\n");
    printf("\t\t\t\t\t\t-WASD ou SETAS (movimentação)\n");
    printf("\t\t\t\t\t\t-Espaço ou k (tiro)\n");
    printf("\t\t\t\t\t\t-TAB para pausar");
    printf("\n\n\n\n\n\n\n\n\n\n\n");

    option = getch(); //pega a opção sem printar ela na tela

    return option;
}

void anda(PERSONAGEM *naruto, char ch, char mapa[LIN][COL], int *chaves, int *qtd_chaves, int covarde) //mexe o personagem principal pelo mapa
{
    int andou = 0; //inicia uma flag como falsa para o movimento do personagem
    switch ((ch)) // sem o toupper para não dar conflito das setas com o "k" minúsculo utilizado no tiro
    {
        case 97:
        case 75:  // ArrowLeft
        case 'A': // a
            if (mapa[naruto->y - 1][naruto->x - 2] != '#')
            {
                mapa[naruto->y - 1][naruto->x - 1] = ' '; //limpa a posição anterior do naruto na matriz
                gotoxy(naruto->x, naruto->y);
                textbackground(BLACK);
                printf(" ");
                naruto->x = naruto->x - 1;
                gotoxy(naruto->x, naruto->y);
                textbackground(YELLOW);
                printf(" ");
                andou = 1;
            }
            break;

        case 100:
        case 77:  // ArrowRight
        case 'D': // d
            if (mapa[naruto->y - 1][naruto->x] != '#')
            {
                mapa[naruto->y - 1][naruto->x - 1] = ' ';//limpa a posição anterior do naruto na matriz
                gotoxy(naruto->x, naruto->y);
                textbackground(BLACK);
                printf(" ");
                naruto->x = naruto->x + 1;
                gotoxy(naruto->x, naruto->y);
                textbackground(YELLOW);
                printf(" ");
                andou = 1;
            }
            break;

        case 115:
        case 80:  // ArrowDown
        case 'S': // s
            if (mapa[naruto->y][naruto->x - 1] != '#')
            {
                mapa[naruto->y - 1][naruto->x - 1] = ' ';//limpa a posição anterior do naruto na matriz
                gotoxy(naruto->x, naruto->y);
                textbackground(BLACK);
                printf(" ");
                naruto->y = naruto->y + 1;
                gotoxy(naruto->x, naruto->y);
                textbackground(YELLOW);
                printf(" ");
                andou = 1;
            }
            break;

        case 119:
        case 72:  // ArrowUp
        case 'W': // w
            if (mapa[naruto->y - 2][naruto->x - 1] != '#')
            {
                mapa[naruto->y - 1][naruto->x - 1] = ' ';//limpa a posição anterior do naruto na matriz//limpa a posição anterior do naruto na matriz
                gotoxy(naruto->x, naruto->y);
                textbackground(BLACK);
                printf(" ");
                naruto->y = naruto->y - 1;
                gotoxy(naruto->x, naruto->y);
                textbackground(YELLOW);
                printf(" ");
                andou = 1;
            }
            break;
    }

    if(andou == 1)
    {
        if ((mapa[naruto->y - 1][naruto->x - 1] == 'X') && covarde == 0)
        {
            naruto->vidas = naruto->vidas - 1; //tira vida do naruto quando pisa numa armadilha
        }
        else if (mapa[naruto->y - 1][naruto->x - 1] == 'C')
        {
            naruto->pontos = naruto->pontos + 50; //adiciona os pontos caso pise em uma chave
            *chaves = *chaves + 1;
            (*qtd_chaves)--;//diminui a quantidade restantes de chaves no mapa
        }
        else if (mapa[naruto->y - 1][naruto->x - 1] == 'Z')
        {
            naruto->shurikens++;//incrementa a qtd de shurikens do personagem
        }
        mapa[naruto->y - 1][naruto->x - 1] = 'J';//Atualiza a posição do naruto na matriz, fazendo com que o personagem tenha sua posição salva diretamente na matriz
    }
}

void atira(VETOR *pos_shuriken, int *flag_tiro, char prox_ch, char mapa[LIN][COL], VETOR NINJA[], int ninja_morto[], int *matou_todos, int *i, int QtdNinjas, PERSONAGEM *naruto)
{
    int n;

    switch (toupper(prox_ch)) // verifica o último caracter pressionado para direcionar o tiro
    {
        case 77: // ArrowRight
        case 'D':
            if (*flag_tiro == 1 ) //só roda o restante da função quando um tiro foi iniciado
            {
                if (mapa[pos_shuriken->y - 1][pos_shuriken->x] != '#') //verifica se a shuriken atingiu uma parede
                {
                    textbackground(BLACK);//background preto para "apagar" um caracter

                    if(pos_shuriken->x > naruto->x) //apaga a shuriken somente quando esta numa posição a frente do jogador (evita apagar o jogador do mapa)
                    {
                        gotoxy(pos_shuriken->x, pos_shuriken->y);
                        printf(" ");
                    }

                    gotoxy(pos_shuriken->x + 1, pos_shuriken->y); //printa a shuriken na posição seguinte
                    textcolor(YELLOW);
                    printf("x");



                    for (n = 0; n < QtdNinjas; n++)//faz uma varredura de todos os inimigos
                    {
                        if (pos_shuriken->x == NINJA[n].x && pos_shuriken->y == NINJA[n].y) //shuriken atingiu um inimigo
                        {
                            textbackground(BLACK); //apaga a shuriken
                            gotoxy(pos_shuriken->x + 1, pos_shuriken->y);
                            printf(" ");

                            gotoxy(NINJA[n].x, NINJA[n].y);//apaga o inimigo que foi morto
                            printf(" ");

                            ninja_morto[n] = 1;//declara o inimigo como morto(para de considerá-lo para as operações normais)

                            NINJA[n].x = 1; //coloca o ninja que foi morto em uma posição onde não pode ser alcançado
                            NINJA[n].y = 1;

                            *matou_todos = *matou_todos + 1;//incrementa a quantidade de inimigos abatidos

                           *flag_tiro = 0; //finaliza o tiro

                            naruto->pontos = naruto->pontos + 20;//incrementa pontuação
                        }
                    }
                    pos_shuriken->x = pos_shuriken->x + 1;//atualiza a posição da shuriken
                    *i = *i + 1;
                }
                else
                {
                    textbackground(BLACK); //caso o tiro encontre uma parede, finaliza o tiro e apaga a shuriken
                    gotoxy(pos_shuriken->x, pos_shuriken->y);
                    printf(" ");
                    *flag_tiro = 0;

                }
            }

            break;

        case 75: // ArrowLeft
        case 'A':
            if (*flag_tiro == 1) // procedimento igual ao anterior, só que atirando na outra direção
            {
                if (mapa[pos_shuriken->y - 1][pos_shuriken->x - 2] != '#')
                {

                    textbackground(BLACK);
                    if(pos_shuriken->x < naruto->x || (naruto->x == 2 && naruto->y == 2))
                    {
                        gotoxy(pos_shuriken->x, pos_shuriken->y);
                        printf(" ");
                    }

                    gotoxy(pos_shuriken->x - 1, pos_shuriken->y);

                    textcolor(YELLOW);
                    printf("x");


                    for (n = 0; n < QtdNinjas; n++)
                    {
                        if (pos_shuriken->x == NINJA[n].x && pos_shuriken->y == NINJA[n].y)
                        {
                            textbackground(BLACK);

                            gotoxy(pos_shuriken->x - 1, pos_shuriken->y);
                            printf(" ");

                            gotoxy(NINJA[n].x, NINJA[n].y);

                            printf(" ");
                            ninja_morto[n] = 1;

                            gotoxy(NINJA[n].Xs, NINJA[n].Ys);
                            printf(" ");

                            NINJA[n].x = 1;
                            NINJA[n].y = 1;
                            mapa[NINJA[n].y - 1][NINJA[n].x - 1] = ' ';
                            *matou_todos = *matou_todos + 1;
                            naruto->pontos = naruto->pontos + 20;
                        }
                    }
                    pos_shuriken->x = pos_shuriken->x - 1;
                }
                else
                {
                    textbackground(BLACK);
                    gotoxy(pos_shuriken->x, pos_shuriken->y);
                    printf(" ");
                    *flag_tiro = 0;

                }
            }

            break;
    }
}

void hidecursor() //Função para esconder o indicador da posição do cursor implementada pelo professor
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void anda_ninjas(VETOR NINJA[], char mapa[LIN][COL], int ninja_morto[], int QtdNinjas, PERSONAGEM naruto)
{
    int mov_ninja, valid_move = 1, n = 0;
    for (n = 0; n < QtdNinjas; n++)//faz a varredura dos inimigos
    {
        if (ninja_morto[n] == 0) //só realiza as operações para os ninjas que ainda não foram eliminados
        {
            do
            {
                if (sqrt(pow((NINJA[n].x - naruto.x), 2)+pow((NINJA[n].y - naruto.y), 2))<25 && valid_move == 1)//aplica a movimentação inteligente para inimigos com até 25 casas de distancia do jogador
                    mov_ninja = mov_inteligente(NINJA, naruto, n);
                else
                {
                    mov_ninja = round(1 + ((float)rand() / RAND_MAX) * (4 - 1));//caso a movimentação inteligente não esteja habilitada ou não seja um movimento valido, seleciona uma direção aleatória
                    valid_move = 1;
                }


                switch (mov_ninja)
                {
                    case 1: // movimento para esquerda
                        if (mapa[NINJA[n].y - 1][NINJA[n].x - 2] != '#' && mapa[NINJA[n].y - 1][NINJA[n].x - 2] != 'J')//não realiza o movimento quando encontra uma posição vazia
                        {
                            gotoxy(NINJA[n].x, NINJA[n].y); //apaga o ninja de sua posição atual
                            textbackground(BLACK);
                            printf(" ");

                            NINJA[n].x = NINJA[n].x - 1;//printa o inimigo na nova posição
                            gotoxy(NINJA[n].x, NINJA[n].y);
                            textbackground(DARKGRAY);
                            printf(" ");

                            valid_move = 1;
                        }
                        else
                            valid_move = 0; // caso encontre uma parede ou o jogador, considera como movimento inválido
                        break;

                    case 2: // movimento para a direita
                        if (mapa[NINJA[n].y - 1][NINJA[n].x] != '#' && mapa[NINJA[n].y - 1][NINJA[n].x] != 'J')
                        {
                            gotoxy(NINJA[n].x, NINJA[n].y);
                            textbackground(BLACK);
                            printf(" ");

                            NINJA[n].x = NINJA[n].x + 1;

                            gotoxy(NINJA[n].x, NINJA[n].y);
                            textbackground(DARKGRAY);
                            printf(" ");
                            valid_move = 1;
                        }
                        else
                            valid_move = 0;
                        break;

                    case 3: // movimento para baixo
                        if (mapa[NINJA[n].y][NINJA[n].x - 1] != '#' && mapa[NINJA[n].y][NINJA[n].x - 1] != 'J')
                        {
                            gotoxy(NINJA[n].x, NINJA[n].y);
                            textbackground(BLACK);
                            printf(" ");

                            NINJA[n].y = NINJA[n].y + 1;

                            gotoxy(NINJA[n].x, NINJA[n].y);
                            textbackground(DARKGRAY);
                            printf(" ");
                            valid_move = 1;
                        }
                        else
                            valid_move = 0;
                        break;

                    case 4: // movimento para cima
                        if (mapa[NINJA[n].y - 2][NINJA[n].x - 1] != '#' && mapa[NINJA[n].y - 2][NINJA[n].x - 1] != 'J')
                        {
                            gotoxy(NINJA[n].x, NINJA[n].y);
                            textbackground(BLACK);
                            printf(" ");

                            NINJA[n].y = NINJA[n].y - 1;

                            gotoxy(NINJA[n].x, NINJA[n].y);
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
            } while (valid_move == 0); //fica "buscando" movimentos até encontrar um válido
        }
    }
}


void set_clock(TEMPO *tempo)//Deixa todos os cálculos prontos para a utilização de algum timer no jogo
{
    tempo->fim = clock();
    tempo->duracao = (double)(tempo->fim - tempo->comeco) / CLOCKS_PER_SEC;
}

void atira_ninja (int covarde, int dir_ninja[], char mapa[LIN][COL], PERSONAGEM *naruto, VETOR NINJA[], int ninja_morto[], int QtdNinjas, int tiro_ninja[], int atualiza_sn[])
{
    int i;
    for(i = 0; i < QtdNinjas; i++)
    {
        if (tiro_ninja[i] == 1)//funciona de maneira parecida com o tiro do jogador, porém é feita uma verificação separada para cada inimigo, pois todos podem atirar simultaneamente
        {
            switch (dir_ninja[i]) //é feita uma verificação na main para cada inimigo, localizando o jogador em relação a eles
            {
                case 1: // atira pra esquerda
                        if (mapa[NINJA[i].Ys - 1][NINJA[i].Xs - 2] != '#') //tiro similar ao do jogador, "calculado" para o ninja[i]
                        {
                            textbackground(BLACK);
                            //aqui não é feita a verificação para evitar apagar o inimigo como no jogador, pois a movimentação dos ninjas é computada rapidamente e, se for apagado, fica imperceptível
                            gotoxy(NINJA[i].Xs, NINJA[i].Ys);
                            printf(" ");


                            gotoxy(NINJA[i].Xs - 1, NINJA[i].Ys);

                            textcolor(LIGHTGRAY);
                            printf("x");

                            if (NINJA[i].Xs == naruto->x && NINJA[i].Ys == naruto->y && covarde == 0)//tiro encontrou o jogador
                            {
                                textbackground(BLACK);
                                gotoxy(NINJA[i].Xs - 1, NINJA[i].Ys);
                                printf(" "); // apaga a shuriken do ninja[i]

                                gotoxy(naruto->x, naruto->y);

                                printf(" "); // apaga o jogador

                                naruto->vidas = naruto->vidas - 1; //tira uma vida do jogador

                                tiro_ninja[i] = 0;//flags para finalizar o tiro e atualizar a posição das shurikens de cada inimigo
                                atualiza_sn[i] = 1;

                                naruto->x = 2;//retorna o jogador para o inicio
                                naruto->y = 2;
                                gotoxy(naruto->x, naruto->y);
                                textbackground(YELLOW);
                                printf(" ");
                            }

                            NINJA[i].Xs--; //move a shuriken do ninja[i] para a esquerda
                        }

                        else
                        {
                            //shuriken acertou a parede, mesmas operações de atualização de posições das shurikens
                            textbackground(BLACK);
                            gotoxy(NINJA[i].Xs, NINJA[i].Ys);
                            printf(" ");

                            tiro_ninja[i] = 0;
                            atualiza_sn[i] = 1;
                        }

                        break;

                case 0: //atira pra direita
                        if (mapa[NINJA[i].Ys - 1][NINJA[i].Xs] != '#')
                        {
                            textbackground(BLACK);

                            gotoxy(NINJA[i].Xs, NINJA[i].Ys);
                            printf(" ");


                            gotoxy(NINJA[i].Xs +1, NINJA[i].Ys);

                            textcolor(LIGHTGRAY);
                            printf("x");

                            if (NINJA[i].Xs == naruto->x && NINJA[i].Ys == naruto->y && covarde == 0)
                            {
                                textbackground(BLACK);
                                gotoxy(NINJA[i].Xs + 1, NINJA[i].Ys);
                                printf(" ");

                                gotoxy(naruto->x, naruto->y);

                                printf(" ");
                                naruto->vidas = naruto->vidas - 1;

                                tiro_ninja[i] = 0;
                                atualiza_sn[i] = 1;

                                naruto->x = 2;
                                naruto->y = 2;
                                gotoxy(naruto->x, naruto->y);
                                textbackground(YELLOW);
                                printf(" ");
                            }

                            NINJA[i].Xs++;
                        }

                        else
                        {
                            textbackground(BLACK);
                            gotoxy(NINJA[i].Xs, NINJA[i].Ys);
                            printf(" ");
                            tiro_ninja[i] = 0;
                            atualiza_sn[i] = 1;
                        }

                        break;
                }
            }
    }
}



int mov_inteligente(VETOR NINJA[], PERSONAGEM naruto, int n)
{
    int movimento;
    /*Esta movimentação faz com que o ninja a uma determinada distância do naruto sempre busque estar na mesma linha que ele, fazendo com que o ninja esteja mais
    propenso a realizar mais disparos. Além disso, quando ambos estão na mesma linha o ninja tenta se aproximar do personagem, tornando mais dificil a esquiva do projétil*/
    if((NINJA[n].y-naruto.y)>=1)
        movimento = 4; //W
    else if((NINJA[n].y-naruto.y)<=-1)
        movimento = 3; //S
    else if((NINJA[n].x-naruto.x)<=-1)
        movimento = 2; //D
    else movimento = 1; //A

    return movimento;
}

void cheat(char ch, int *estado, int *covarde) //Cria uma máquina de estados para implementação de cheats, apenas aceitando uma certa sequencia exata de caracteres para ativar ou desativar uma flag
{
      switch (ch) //verificação da máquina de estados
      {
            case 99: //c
            case 67: //C
                  *estado = 1; //sinaliza que esta ok e avança para o próximo estado
                  break;

            case 111: //o
            case 79: //O
                  if(*estado ==1) //condição para avançar para o proximo estado
                        *estado = 2; //sinaliza que esta ok e avança para o próximo estado

                  else
                        *estado = 0; //retorna para o estado inicial

                  break;

            case 118: //v
            case 86: //V
                  if(*estado == 2) //condição para avançar para o proximo estado
                        *estado = 3; //sinaliza que esta ok e avança para o próximo estado

                  else
                        *estado = 0; //retorna para o estado inicial

                  break;

            case 97: //a
            case 65: //A
                  if(*estado == 3) //condição para avançar para o proximo estado
                        *estado = 4; //sinaliza que esta ok e avança para o próximo estado

                  else
                        *estado = 0; //retorna para o estado inicial

                  break;

            case 114: //r
            case 82: //R
                  if(*estado == 4) //condição para avançar para o proximo estado
                        *estado = 5; //sinaliza que esta ok e avança para o próximo estado

                  else
                        *estado = 0; //retorna para o estado inicial

                  break;

            case 100: //d
            case 68: //D
                  if(*estado == 5) //condição para avançar para o proximo estado
                        *estado = 6; //sinaliza que esta ok e avança para o próximo estado

                  else
                        *estado = 0; //retorna para o estado inicial
                  break;

            case 101: //e
            case 69: //E
                  if(*estado == 6) //condição para avançar para o proximo estado
                        if(*covarde)
                              *covarde = 0; //se o cheat estiver ativo, desativa

                        else
                              *covarde = 1; //se o cheat estiver desativado, ativa

                  else
                        *estado = 0; //retorna para o estado inicial

                  break;

            default:
                  *estado = 0; //retorna para o estado inicial
                  break;
                }
}

int salva(char mapa[LIN][COL], float duracao, int level, int vidas, int pontos, int chaves, int abatidos, int shurikens, VETOR pos_shuriken, int flag_tiro, char prox_ch, int QtdNinjas, int tiro_ninja[], int ninja_morto[], int dir_ninja[], int atualiza_sn[], VETOR NINJA[])
{
    FILE *arq; //ponteiro para o arquivo aberto
    char nome[] = {"save.txt"}; //nome do arquivo contendo os dados salvos
    int i, j; //variaveis para uso no for
    char cn[1] = { "\n" }; //variavel auxiliar para sinalizar o fim de um dado salvo no arquivo para facilitar a leitura

    if( (arq = fopen(nome,"w")) == NULL) // abertura para escrita
        return 1; //retorna erro ao tentar salvar o arquivo

    else
    {
        for(i = 0; i < LIN; i++)
        {
            for(j = 0; j  < COL; j++)
            {
                fprintf(arq, "%c", mapa[i][j]); //salva o caractere atual da matriz do mapa no arquivo
            }

        }

        fprintf(arq, "%f",  duracao); //salva a duração atual do jogo
        fprintf(arq, "%c", cn[0]); //salva a sinaliação de término do dado
        fprintf(arq, "%d", level); //salva o level atual
        fprintf(arq, "%c", cn[0]); //salva a sinaliação de término do dado
        fprintf(arq, "%d", vidas); //salvaz a quantidade de vidas restantes
        fprintf(arq, "%c", cn[0]); //salva a sinaliação de término do dado
        fprintf(arq, "%d",  pontos); //salva a pontuação atual
        fprintf(arq, "%c", cn[0]); //salva a sinaliação de término do dado
        fprintf(arq, "%d", chaves); //salva a quantidade de chaves coletadas
        fprintf(arq, "%c", cn[0]); //salva a sinaliação de término do dado
        fprintf(arq, "%d", abatidos); //salva a quantidade de inimigos abatidos
        fprintf(arq, "%c", cn[0]); //salva a sinaliação de término do dado
        fprintf(arq, "%d", shurikens); //salva a quantidade de shurikens restantes do personagem
        fprintf(arq, "%c", cn[0]); //salva a sinaliação de término do dado
        fprintf(arq, "%d", pos_shuriken.x); //salva a posição atual da coordenada x da shuriken do ninja
        fprintf(arq, "%c", cn[0]); //salva a sinaliação de término do dado
        fprintf(arq, "%d", pos_shuriken.y); //salva a posição atual da coordenada y da shuriken do ninja
        fprintf(arq, "%c", cn[0]); //salva a sinaliação de término do dado
        fprintf(arq, "%d", flag_tiro); //salva se está ocorrendo um tiro do personagem
        fprintf(arq, "%c", cn[0]); //salva a sinaliação de término do dado
        fprintf(arq, "%c", prox_ch); //salva a direção do tiro do personagem
        fprintf(arq, "%c", cn[0]); //salva a sinaliação de término do dado
        fprintf(arq, "%d", QtdNinjas); //salva a quantidade total de ninjas daquele mapa
        fprintf(arq, "%c", cn[0]); //salva a sinaliação de término do dado


        for(i = 0; i < QtdNinjas; i++) //salva o estado dos tiros dos ninjas
        {
            fprintf(arq, "%d", tiro_ninja[i]);
            fprintf(arq, "%c", cn[0]); //salva a sinaliação de término do dado
        }

        for(i = 0; i < QtdNinjas; i++) //sava o estado dos ninjas se mortos ou vivos
        {
            fprintf(arq, "%d",ninja_morto[i]);
            fprintf(arq, "%c", cn[0]); //salva a sinaliação de término do dado
        }

        for(i = 0; i < QtdNinjas; i++) //salva a direção do movimento dos ninjas
        {
            fprintf(arq, "%d", dir_ninja[i]);
            fprintf(arq, "%c", cn[0]); //salva a sinaliação de término do dado
        }

        for(i = 0; i < QtdNinjas; i++) //salva as movimentações dos tiros dos ninjas
        {
            fprintf(arq, "%d", atualiza_sn[i]);
            fprintf(arq, "%c", cn[0]); //salva a sinaliação de término do dado
        }

        for(i = 0; i < QtdNinjas; i++) //salva todas informações de todos os ninjas existentes
        {
            fprintf(arq, "%d", NINJA[i].x); //salva as coordenadas x de cada ninja
            fprintf(arq, "%c", cn[0]); //salva a sinaliação de término do dado
            fprintf(arq, "%d", NINJA[i].y); //salva as coordenadas y de cada ninja
            fprintf(arq, "%c", cn[0]); //salva a sinaliação de término do dado
            fprintf(arq, "%d", NINJA[i].Xs); //salva as coordenadas x das shurikens da cada ninja
            fprintf(arq, "%c", cn[0]); //salva a sinaliação de término do dado
            fprintf(arq, "%d", NINJA[i].Ys); //salva as coordenadas y das shurikens de cada ninja
            fprintf(arq, "%c", cn[0]); //salva a sinaliação de término do dado
        }

        fclose(arq); //fecha o arquivo
        return 0;
    }

}

int carrega(FILE *arq, char nome_save[], char mapa[LIN][COL], float *duracao, int *level, int *vidas, int *pontos, int *chaves, int *abatidos, int *shurikens, VETOR *pos_shuriken, int *flag_tiro, char *prox_ch, int *QtdNinjas)
{
    char read[COL]; //tamanho auxiliar máximo a ser utilizado na leitura

    if (arq == NULL) // abertura para leitura
        return 1;   //retorna erro ao tentar carregar o arquivo

    else
    {
        copia_mapa(mapa, arq, nome_save);

        fgets(read, COL, arq); //ajusta a linha de leitura após a função copia mapa

        fgets(read, COL, arq); //coleta a string da linha atual
        *duracao = atof(read); //converte a string para float

        fgets(read, COL, arq); //coleta a string da linha atual
        *level = atoi(read); //converte a string para int

        fgets(read, COL, arq); //coleta a string da linha atual
        *vidas = atoi(read); //converte a string para int

        fgets(read, COL, arq); //coleta a string da linha atual
        *pontos = atoi(read); //converte a string para int

        fgets(read, COL, arq); //coleta a string da linha atual
        *chaves = atoi(read); //converte a string para int

        fgets(read, COL, arq); //coleta a string da linha atual
        *abatidos = atoi(read); //converte a string para int

        fgets(read, COL, arq); //coleta a string da linha atual
        *shurikens = atoi(read); //converte a string para int

        fgets(read, COL, arq); //coleta a string da linha atual
        pos_shuriken->x = atoi(read); //converte a string para int

        fgets(read, COL, arq); //coleta a string da linha atual
        pos_shuriken->y = atoi(read); //converte a string para int

        fgets(read, COL, arq); //coleta a string da linha atual
        *flag_tiro = atoi(read); //converte a string para int

        fgets(read, COL, arq); //coleta a string da linha atual
        *prox_ch = read[0]; //armazena a posição 0 pois prox_ch só tem 1 caractere

        fgets(read, COL, arq); //coleta a string da linha atual
        *QtdNinjas = atoi(read); //converte a string para int

        return 0;
    }

}

int carrega_ninja(FILE *arq, int QtdNinjas, int tiro_ninja[], int ninja_morto[], int dir_ninja[], int atualiza_sn[], VETOR NINJA[])
{
    int i;
    char read[COL]; //tamanho auxiliar máximo a ser utilizado na leitura

    if (arq == NULL) // abertura para leitura
        return 1; //retorna erro ao tentar carregar o arquivo

    else
    {
        for(i = 0; i < QtdNinjas; i++)
        {
            fgets(read, COL, arq); //coleta a string da linha atual
            tiro_ninja[i] = atoi(read); //converte a string para int;
        }

        for(i = 0; i < QtdNinjas; i++)
        {
            fgets(read, COL, arq); //coleta a string da linha atual
            ninja_morto[i] = atoi(read); //converte a string para int
        }

        for(i = 0; i < QtdNinjas; i++)
        {
            fgets(read, COL, arq); //coleta a string da linha atual
            dir_ninja[i] = atoi(read); //converte a string para int
        }

        for(i = 0; i < QtdNinjas; i++)
        {
            fgets(read, COL, arq); //coleta a string da linha atual
            atualiza_sn[i] = atoi(read); //converte a string para int
        }

        for(i = 0; i < QtdNinjas; i++)
        {
            fgets(read, COL, arq); //coleta a string da linha atual
            NINJA[i].x = atoi(read); //converte a string para int
            fgets(read, COL, arq); //coleta a string da linha atual
            NINJA[i].y = atoi(read); //converte a string para int
            fgets(read, COL, arq); //coleta a string da linha atual
            NINJA[i].Xs = atoi(read); //converte a string para int
            fgets(read, COL, arq); //coleta a string da linha atual
            NINJA[i].Ys = atoi(read); //converte a string para int
        }
        return 0;
    }
}
