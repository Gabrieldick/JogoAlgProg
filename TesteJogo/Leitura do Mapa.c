#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <string.h>

#define LIN 23
#define COL 61
#define C 50

//Limpa o buffer do teclado
void flush_in()
{
      int ch;
      while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}

void exibe_mapa(char nome[])
{
      int i, j;
      char mapa[LIN][COL];
      FILE *arq;

      arq=fopen(nome, "r");

      printf("\n");

      for(i=0; i<LIN; i++)
      {
            for(j=0; j<COL; j++)
            {
                  fscanf(arq,"%c", &mapa[i][j]);
                  printf("%c", mapa[i][j]); //testar se a impressão esta correta
            }

      }

      printf("\n");

      fclose(arq); //fechar arquivo
}

void le_nome(char nome[])
{
      printf("Digite o nome do arquivo com extensao: ");
      fgets(nome, C, stdin);
      nome[strcspn(nome, "\n")] = 0;

}

int menu()
{
      int option;

      printf("Selecione uma das opcoes: \n");
      printf("1 - Digitar o nome do mapa a ser aberto\n");
      printf("2 - Exibir o mapa selecionado\n");
      printf("0 - Encerra o programa\n");

      printf("\nOpcao selecionada: ");

      scanf("%d", &option);
      flush_in();

      return option;

}
void cria_mapa()
{

}

int main()
{
      int option;
      char nome[C] = {"mapa1.txt"};

      while(1)
      {
            option = menu();

            switch(option)
            {
                  case 1:
                        le_nome(nome);
                        printf("\n");
                        break;

                  case 2:
                        exibe_mapa(nome);
                        printf("\n");
                        break;

                  case 0:
                        return 0;
                        break;

                  default:
                        printf("\nopcao invalida, digite novamente!\n");
            }
      }
}

