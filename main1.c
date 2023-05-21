//cmd /c '.\main.exe < input.txt > output.txt'


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct no {
   char * name;
   struct no *esquerda, *direita;
   char CPF[12];
   char CEP[9];
   int altura;
} No;

No* LoadData(No* raiz, int ordenarPor);
No* novoNo(char * name, char CPF[12], char CEP[9]);
int maior(int a, int b);
int noAltura(No *no);
int fatorBl(No *no);
No* rotacaoEsquerda(No* raiz);
No* rotacaoDireita(No* raiz);
No* rotacaoDireitaEsquerda(No *raiz);
No* rotacaoEsquerdaDireita(No *raiz);
No* balancear(No *raiz);
No* inserir(No *raiz, char * nome, char * CPF, char * CEP, int ordenarPor);
void joinstrings(char * s1, char * s2, char * s3, char * result);
void inorder(No *raiz);
void imprimir(No *raiz, int nivel);
void search(No * raiz,char * target, int ordenarPor);

void mainMenu(No * raiz, int ordenarPor);
void novoCadastro(No * raiz, int ordenarPor);
void checkDataMenu(No * raiz, int ordenarPor);
int menuOrdenarPor();

int main(){
   int ordenarPor = 0;
   ordenarPor = menuOrdenarPor();

   setlocale(LC_ALL, "Portuguese");
   No *raiz = NULL;
   raiz = LoadData(raiz, ordenarPor);
   //inorder(raiz);

   mainMenu(raiz, ordenarPor);

   return 1;
}

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

/**
 * Função que cria um novo nó
 * valor -> valor a ser inserido no nó
 * Retorna: o endereço do nó criado
*/
No* novoNo(char * name, char CPF[12], char CEP[9]) {
   No *novo = malloc(sizeof(No));
   novo->name = (char *) malloc(strlen(name)+1);
   if (novo) {
      strcpy(novo->name, name);
      strcpy(novo->CEP, CEP);
      strcpy(novo->CPF, CPF);
      novo->esquerda = NULL;
      novo->direita = NULL;
      novo->altura = 0;
   } else {
      printf("Erro ao alocar memória!\n");
   }
   
   return novo;
}

/**
 * Retorna o maior dentre dois valores
 * a, b -> altura de dois nós da árvore
*/
int maior(int a, int b) {
   // if ternário -> (condição) ? verdadeiro : falso
   return (a > b) ? a : b;
}

// Retorna a altura de um nó ou -1 caso ele seja null
int noAltura(No *no) {
   if (no == NULL) {
      return -1;
   } else {
      return no->altura;
   }
}

// Calcula e retorna o fator de balanceamento de um nó
int fatorBl(No *noArv) {
   if (noArv) {
      return noAltura(noArv->esquerda) - noAltura(noArv->direita);
   } else { 
      return 0;
   }
}

// Função para a rotação à esquerda
No* rotacaoEsquerda(No* raiz) {
   No *aux, *filho; 
   
   aux = raiz->direita;
   filho = aux->esquerda;

   aux->esquerda = raiz;
   raiz->direita = filho;

   raiz->altura = maior(noAltura(raiz->esquerda), noAltura(raiz->direita)) + 1;
   aux->altura = maior(noAltura(aux->esquerda), noAltura(aux->direita)) + 1;

   // retorna a nova raiz
   return aux;
}

// Função para a rotação à direita
No* rotacaoDireita(No* raiz) {
   No *aux, *filho; 
   
   aux = raiz->esquerda;
   filho = aux->direita;

   aux->direita = raiz;
   raiz->esquerda = filho;

   raiz->altura = maior(noAltura(raiz->esquerda), noAltura(raiz->direita)) + 1;
   aux->altura = maior(noAltura(aux->esquerda), noAltura(aux->direita)) + 1;

   // retorna a nova raiz
   return aux;
}

// Função para rotação Direita Esquerda
No* rotacaoDireitaEsquerda(No *raiz) {
   raiz->direita = rotacaoDireita(raiz->direita);
   return rotacaoEsquerda(raiz);
}

// Função para rotação Esquerda Direita
No* rotacaoEsquerdaDireita(No *raiz) {
   raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
   return rotacaoDireita(raiz);
}

/**
 * Função para realizar o balanceamento da árvore após uma inserção ou remoção
 * Recebe o nó que está desbalanceado e retorna a nova raiz após o balanceamento
*/
No* balancear(No *raiz) {
   int fb = fatorBl(raiz);

   // Rotação à esquerda
   if (fb < -1 && fatorBl(raiz->direita) <= 0)
      raiz = rotacaoEsquerda(raiz);
   
   // Rotação à direita
   else if (fb > 1 && fatorBl(raiz->esquerda) >= 0)
      raiz = rotacaoDireita(raiz);
   
   // Rotação dupla à esquerda
   else if (fb > 1 && fatorBl(raiz->esquerda) < 0)
      raiz = rotacaoEsquerdaDireita(raiz);
   
   // Rotação dupla à direita
   else if (fb < -1 && fatorBl(raiz->direita) > 0)
      raiz = rotacaoDireitaEsquerda(raiz);

   return raiz;
}


/**
 * @brief Inserir um novo nó na árvore
 * 
 * @param raiz raiz da árvore em que o nó será inserido
 * @param nome nome da pessoa
 * @param CPF cpf da pessoa
 * @param CEP cep da pessoa
 * @param ordenarPor Fator que decidirá como ordenaremos a árvore. Qualquer int diferente de 1 e 2: NOME. 1: CPF. 2: CEP
 * @return No* 
 */
No* inserir(No *raiz, char * nome, char * CPF, char * CEP, int ordenarPor){
   if(ordenarPor == 1){
      if (raiz == NULL) {
         return novoNo(nome, CPF, CEP);
      }
      if (strcmp(raiz->CPF, CPF) > 0) {
         raiz->esquerda = inserir(raiz->esquerda, nome, CPF, CEP, ordenarPor);
      } else if (strcmp(raiz->CPF, CPF) < 0) {
         raiz->direita = inserir(raiz->direita, nome, CPF, CEP, ordenarPor);
      } else {
         strcpy(raiz->name, nome);
         strcpy(raiz->CEP, CEP);
         strcpy(raiz->CPF, CPF);
      
      }

   }
   else if(ordenarPor == 2){
      if (raiz == NULL) {
         return novoNo(nome, CPF, CEP);
      }
      if (strcmp(raiz->CEP, CEP) > 0) {
         raiz->esquerda = inserir(raiz->esquerda, nome, CPF, CEP, ordenarPor);
      } else if (strcmp(raiz->CEP, CEP) < 0) {
         raiz->direita = inserir(raiz->direita, nome, CPF, CEP, ordenarPor);
      } else {
         strcpy(raiz->name, nome);
         strcpy(raiz->CEP, CEP);
         strcpy(raiz->CPF, CPF);
      }
   }
   else{
      if (raiz == NULL) {
         return novoNo(nome, CPF, CEP);
      }
      if (strcmp(raiz->name, nome) > 0) {
         raiz->esquerda = inserir(raiz->esquerda, nome, CPF, CEP, ordenarPor);
      } else if (strcmp(raiz->name, nome) < 0) {
         raiz->direita = inserir(raiz->direita, nome, CPF, CEP, ordenarPor);
      } else {
         strcpy(raiz->name, nome);
         strcpy(raiz->CEP, CEP);
         strcpy(raiz->CPF, CPF);
      }
   }

   // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
   raiz->altura = maior(noAltura(raiz->esquerda), noAltura(raiz->direita)) + 1;

   // Verifica a necessidade de rebalancear a árvore
   raiz = balancear(raiz);

   return raiz;
}


void inorder(No *raiz) {
   if (raiz) {
      inorder(raiz->esquerda);
      printf("Nome: %s CEP: %s CPF: %s\n", raiz->name, raiz->CEP, raiz->CPF);
      inorder(raiz->direita);
   }
}


void imprimir(No *raiz, int nivel) {
   int i;
   
   if (raiz) {
      imprimir(raiz->direita, nivel + 1);
      printf("\n\n");
      
      for (i = 0; i < nivel; i++) {
         printf("\t");
      }
      
      printf("%s\n", raiz->name);
      imprimir(raiz->esquerda, nivel + 1);
   }
}

void joinstrings(char * s1, char * s2, char * s3, char * result){
    int i;
    for(i=0; i<strlen(s1);i++){
        memset(&result[i], s1[i], 1);
    }
    for(i=0; i<strlen(s2);i++){
        memset(&result[i+strlen(s1)], s2[i], 1);
    }
    for(i=0; i<strlen(s3);i++){
        memset(&result[i+strlen(s1)+strlen(s2)], s3[i], 1);
    }
}

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

void checkDataMenu(No * raiz, int ordenarPor){
   printf("\n\n1 - Buscar dados\n");
   printf("2 - Printar os dados\n");
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
   if(option==2) inorder(raiz);
   return;
}

int menuOrdenarPor(){
   int ordenarPor=3;
   while(ordenarPor!=0 && ordenarPor!=1 && ordenarPor!=2)  {
      printf("Digite a opcao na qual deseja ordenar os dados:\n");
      printf("0 - NOME\n1 - CPF\n2 - CEP\nSua opcao: ");
      scanf("%d", &ordenarPor);
      }
   return ordenarPor;
}

void search(No * raiz,char * target, int ordenarPor){
   if (raiz == NULL) {
      printf("Nao foi possivel achar a chave %s.\n", target);
      checkDataMenu(raiz, ordenarPor);
   }
   
   if(ordenarPor == 1){
      if (strcmp(raiz->CPF, target) > 0) {
         search(raiz->esquerda, target, ordenarPor);
      } else if (strcmp(raiz->CPF, target) < 0) {
         search(raiz->direita, target, ordenarPor);
      } else {
         printf("\n%s:\n", target);
         printf(" Nome: %s\n CPF: %s\n CEP: %s\n", raiz->name, raiz->CPF, raiz->CEP);
         return;
      }
   }
   else if(ordenarPor == 2){
      if (strcmp(raiz->CEP, target) > 0) {
         search(raiz->esquerda, target, ordenarPor);
      } else if (strcmp(raiz->CEP, target) < 0) {
         search(raiz->direita, target, ordenarPor);
      } else {
         printf("\n%s:\n", target);
         printf(" Nome: %s\n CPF: %s\n CEP: %s\n", raiz->name, raiz->CPF, raiz->CEP);
         return;
      }
   }
   else{
      if (strcmp(raiz->name, target) > 0) {
         search(raiz->esquerda, target, ordenarPor);
      } else if (strcmp(raiz->name, target) < 0) {
         search(raiz->direita, target, ordenarPor);
      } else {
         printf("\n%s:\n", target);
         printf(" Nome: %s\n CPF: %s\n CEP: %s\n", raiz->name, raiz->CPF, raiz->CEP);
         return;
      }
   } 
}
