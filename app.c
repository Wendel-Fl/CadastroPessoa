#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avlTree.h"
#include "app.h"

No* LoadData(No* raiz, int ordenarPor){
   printf("Loading data...");
   FILE * input;
   input = fopen("input.txt", "r");
   char s1[15], s2[15], s3[15], completa[45], CPF[12], CEP[9];
   while(!feof(input)){
      fscanf(input, "%s %s %s %s %s",s1, s2, s3, CPF, CEP);
      memset(completa, 0, 45);
      joinstrings(s1, s2, s3, completa);
      raiz = inserir(raiz, completa, CPF, CEP, ordenarPor);
   }
   return raiz;
}

// Funcao que imprime o nome do App
void royalty(){
	printf("==============================\n\n\n");
	printf("     UM APP SEM NOME AINDA\n\n\n");
	printf("==============================\n\n\n");
}

// Funcao que roda o programa
void runApp(){
	royalty();
	printf("Desenvolvido por:\n");
	printf("              -  Carlos Eduardo\n");
	printf("              -  Gabrielle\n");
	printf("              -  João Victor\n");
	printf("              -  Robert Martins\n");
	printf("              -  Wendel Filho\n\n");
	printf("------------------------------\n\n\n");
}

int menuOrdenarPor(){
   int ordenarPor=3;
   runApp();
   while(ordenarPor!=0 && ordenarPor!=1 && ordenarPor!=2)  {
      printf("Digite a opcao na qual deseja ordenar os dados:\n");
      printf("0 - NOME\n1 - CPF\n2 - CEP\nSua opcao: ");
      scanf("%d", &ordenarPor);
      }
   return ordenarPor;
}

// Funcao que encerra o programa
void shutdown(){
	printf("Encerrando aplicativo...\n");
	exit(1);
}

// Função para escolher se vai imprimir em preorder, inorder ou posorder
void listDataMenu(No * raiz){
   int option;
   printf("\n\n\n\n   LISTAR CADASTROS\n\n");
   printf("1 - Listar em pre ordem\n");
   printf("2 - Listar em ordem\n");
   printf("3 - Listar em pos ordem\n");
   printf("\n\n\n");
   printf("9 - Voltar ao menu anterior\n");
   printf("0 - Encerrar\n");
   printf("\nDigite a opcao:\n");
   scanf("%d", &option);
   switch(option){
      case 1:
         preorder(raiz);
         break;
      case 2:
         inorder(raiz);
         break;
      case 3:
         posorder(raiz);
         break;
      case 9:
         checkDataMenu(raiz, 0);
         return;
      case 0:
         return;
      default:
         printf("Opcao invalida!\n");
         listDataMenu(raiz);
         break;
   }
}

// Funcao que dispoe menu de cadastros na arvore
void checkDataMenu(No * raiz, int ordenarPor){
   printf("\n\n1 - Buscar dados\n");
   printf("2 - Printar os dados\n");
   printf("Digite a opcao:\n");
   int option = 0;
   char target[60];
   char s1[20], s2[20], s3[20];
   memset(target, 0, 60);
   while(option != 1 && option != 2) scanf("%d", &option);
   if(option==1){
      if(ordenarPor==1) printf("Digite o CPF que deseja buscar:\n");
      else if(ordenarPor==2) printf("Digite o CEP que deseja buscar:\n");
      else printf("Digite o nome que deseja buscar:\n");
      if(ordenarPor==1 || ordenarPor==2) scanf("%s", target);
      else{
         scanf("%s %s %s", s1, s2, s3);
         joinstrings(s1, s2, s3, target);
      }
      search(raiz, target, ordenarPor);
   }
   if(option==2) listDataMenu(raiz);
   return;
}

// Funcao que dispoe o menu principal do programa
void mainMenu(No * raiz, int ordenarPor){
   int option;
   while(1){
      printf("\n\n\n\n   MENU PRINCIPAL\n\n");
      printf("1 - Verificar cadastros\n");
      printf("2 - Fazer novo cadastro\n");
      printf("\n\n\n");
      printf("0 - Encerrar\n");
      printf("\nDigite a opcao:\n");
      scanf("%d", &option);
      switch(option){
         case 1:
            checkDataMenu(raiz, ordenarPor);
            break;
         case 2:
            novoCadastro(raiz, ordenarPor);
            break;
         case 0:
            return;
         default:
            printf("Opcao invalida!\n");
            mainMenu(raiz, ordenarPor);
            break;
      }

   }
}

void novoCadastro(No * raiz, int ordenarPor){
   char s1[30], s2[30], s3[30], completa[90], CPF[12], CEP[9];
   memset(s1, 0, 30);
   memset(s2, 0, 30);
   memset(s3, 0, 30);
   memset(CPF, 0, 12);
   memset(CEP, 0, 9);
   memset(completa, 0, 90);
   printf("\nDigite seu primeiro nome: \n");
   scanf("%s", s1);
   printf("\nDigite seu primeiro sobrenome: \n");
   scanf("%s", s2);
   printf("\nDigite seu segundo sobrenome: \n");
   scanf("%s", s3);
   joinstrings(s1, s2, s3, completa);
   printf("\nDigite seu CPF (apenas os 11 digitos): ");
   scanf("%s", CPF);
   printf("\nDigite seu CEP (apenas os 8 digitos): ");
   scanf("%s", CEP);
   inserir(raiz, completa, CPF, CEP, ordenarPor);
}
