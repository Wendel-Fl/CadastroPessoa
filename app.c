#include <stdio.h>
#include <stdlib.h>

#include "tests.c"
#include "avlTree.c"
#include "person.c"

//Ponteiro para a raiz da arvore
No *root;

void royalty();
void shutdown();
void listDataMenu();
void checkDataMenu();
void mainMenu();
void runApp();

// Funcao que imprime o nome do App
void royalty(){
	system("cls");
	printf("==============================\n\n\n");
	printf("     UM APP SEM NOME AINDA\n\n\n");
	printf("==============================\n\n\n");
}

// Funcao que encerra o programa
void shutdown(){
	printf("Encerrando aplicativo...\n");
	exit(1);
}

// Funcao que dispoe menu de print de ordens da arvore
void listDataMenu(){
	royalty();
	int option;
	printf("   VERIFICAR CADASTROS\n\n");
	printf("1 - Listar em pre ordem\n");
	printf("2 - Listar em ordem\n");
	printf("3 - Listar em pos ordem\n");
	printf("4 - Listar em ordem nivelada\n");
	printf("\n\n\n");
	printf("9 - Voltar ao menu anterior\n");
	printf("0 - Encerrar\n");
	printf("\nDigite a opcao:\n");
	scanf("%d", &option);
	switch(option){
		case 1:
			printf("Nao implementado");
			system("PAUSE");
			listDataMenu();
			break;
		case 2:
			printf("Nao implementado");
			system("PAUSE");
			listDataMenu();
			break;
		case 3:
			printf("Nao implementado");
			system("PAUSE");
			listDataMenu();
		case 4:
			printf("Nao implementado");
			system("PAUSE");
			listDataMenu();
			break;
		case 9:
			checkDataMenu();
			break;
		case 0:
			shutdown();
			break;
		default:
			printf("Opcao invalida!\n");
			listDataMenu();
			break;
	}
}

// Funcao que dispoe menu de cadastros na arvore
void checkDataMenu(){
	royalty();
	int option;
	printf("   VERIFICAR CADASTROS\n\n");
	printf("1 - Listar cadastros\n");
	printf("2 - Total de cadastros\n");
	printf("3 - Atualizar cadastro\n");
	printf("\n\n\n");
	printf("9 - Voltar ao menu principal\n");
	printf("0 - Encerrar\n");
	printf("\nDigite a opcao:\n");
	scanf("%d", &option);
	switch(option){
		case 1:
			listDataMenu();
			break;
		case 2:
			printf("Nao implementado");
			system("PAUSE");
			checkDataMenu();
			break;
		case 3:
			printf("Nao implementado");
			system("PAUSE");
			checkDataMenu();
			break;
		case 9:
			mainMenu();
			break;
		case 0:
			shutdown();
			break;
		default:
			printf("Opcao invalida!\n");
			checkDataMenu();
			break;
	}
}

// Funcao que dispoe o menu principal do programa
void mainMenu(){
	royalty();
	int option;
	printf("   MENU PRINCIPAL\n\n");
	printf("1 - Verificar cadastros\n");
	printf("2 - Novo cadastro\n");
	printf("\n\n\n");
	printf("0 - Encerrar\n");
	printf("\nDigite a opcao:\n");
	scanf("%d", &option);
	switch(option){
		case 1:
			checkDataMenu();
			break;
		case 2:
			printf("Nao implementado");
			system("PAUSE");
			mainMenu();
			break;
		case 0:
			shutdown();
			break;
		default:
			printf("Opcao invalida!\n");
			mainMenu();
			break;
	}
}

// Funcao que roda o programa
void runApp(){
	char option;
	royalty();
	printf("Desenvolvido por:\n");
	printf("              -  Carlos Eduardo\n");
	printf("              -  Gabrielle\n");
	printf("              -  João Victor\n");
	printf("              -  Robert Martins\n");
	printf("              -  Wendel Filho\n\n");
	printf("------------------------------\n\n\n");
	printf("\n Pressione alguma tecla para continuar");
	scanf("%c", &option);
	if(option == 't')
		runTests();
	else
		mainMenu();
}
