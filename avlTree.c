#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "person.c"

typedef struct no {
   char * name;
   struct no *esquerda, *direita;
   int altura;
} No;

No* novoNo(char * name);
int maior(int a, int b);
int noAltura(No *no);
int fatorBl(No *no);
No* rotacaoEsquerda(No* raiz);
No* rotacaoDireita(No* raiz);
No* rotacaoDireitaEsquerda(No *raiz);
No* rotacaoEsquerdaDireita(No *raiz);
No* balancear(No *raiz);
No* inserir(No *raiz, char * name);
void joinstrings(char * s1, char * s2, char * s3, char * result);

void inorder(No *raiz);
void imprimir(No *raiz, int nivel);

/**
 * Função que cria um novo nó
 * valor -> valor a ser inserido no nó
 * Retorna: o endereço do nó criado
*/
No* novoNo(char * name) {
   No *novo = malloc(sizeof(No));
   novo->name = (char *) malloc(strlen(name)+1);
   if (novo) {
      strcpy(novo->name, name);
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
 * Insere um novo nó na árvore
 * raiz -> raiz da árvore
 * x -> valor a ser inserido
 * Retorno: endereço do novo nó ou nova raiz após o balanceamento
*/
No* inserir(No *raiz, char * nome){
    
   if (raiz == NULL) {
      return novoNo(nome);

   }
   
    if (strcmp(raiz->name, nome) > 0) {
        raiz->esquerda = inserir(raiz->esquerda, nome);
    } else if (strcmp(raiz->name, nome) < 0) {
        raiz->direita = inserir(raiz->direita, nome);
    } else {
        printf("\nInsercao nao realizada\nO elemento %s ja existe na arvore\n", nome);
    
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
      printf("%s\n", raiz->name);
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
