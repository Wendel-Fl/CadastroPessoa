//cmd /c '.\main.exe < COMPLETO.txt >resultado.txt' 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
   char * name;
   struct no *esq, *dir;
   int altura;
} No;

No* novoNo(char * name);
int maior(int a, int b);
int alturaNo(No *no);
int fatorBalanceamento(No *no);
No* rotacaoEsquerda(No* raiz);
No* rotacaoDireita(No* raiz);
No* rotacaoDireitaEsquerda(No *raiz);
No* rotacaoEsquerdaDireita(No *raiz);
No* balancear(No *raiz);
No* inserir(No *raiz, char * name);
void joinstrings(char * s1, char * s2, char * s3, char * result);

void inorder(No *raiz);
void imprimir(No *raiz, int nivel);


int main() {
   char s1[15], s2[15], s3[15], completa[45];
   
   No *raiz = NULL;
   while(scanf("%s %s %s", &s1, &s2, &s3) != EOF){
    memset(completa, 0, 45);
    joinstrings(s1, s2, s3, completa);
    raiz = inserir(raiz, completa);
   }
    inorder(raiz);
         
}

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
      novo->esq = NULL;
      novo->dir = NULL;
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
int alturaNo(No *no) {
   if (no == NULL) {
      return -1;
   } else {
      return no->altura;
   }
}

// Calcula e retorna o fator de balanceamento de um nó
int fatorBalanceamento(No *no) {
   if (no) {
      return alturaNo(no->esq) - alturaNo(no->dir);
   } else {
      return 0;
   }
}

// Função para a rotação à esquerda
No* rotacaoEsquerda(No* raiz) {
   No *aux, *filho; 
   
   aux = raiz->dir;
   filho = aux->esq;

   aux->esq = raiz;
   raiz->dir = filho;

   raiz->altura = maior(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;
   aux->altura = maior(alturaNo(aux->esq), alturaNo(aux->dir)) + 1;

   // retorna a nova raiz
   return aux;
}

// Função para a rotação à direita
No* rotacaoDireita(No* raiz) {
   No *aux, *filho; 
   
   aux = raiz->esq;
   filho = aux->dir;

   aux->dir = raiz;
   raiz->esq = filho;

   raiz->altura = maior(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;
   aux->altura = maior(alturaNo(aux->esq), alturaNo(aux->dir)) + 1;

   // retorna a nova raiz
   return aux;
}

// Função para rotação Direita Esquerda
No* rotacaoDireitaEsquerda(No *raiz) {
   raiz->dir = rotacaoDireita(raiz->dir);
   return rotacaoEsquerda(raiz);
}

// Função para rotação Esquerda Direita
No* rotacaoEsquerdaDireita(No *raiz) {
   raiz->esq = rotacaoEsquerda(raiz->esq);
   return rotacaoDireita(raiz);
}

/**
 * Função para realizar o balanceamento da árvore após uma inserção ou remoção
 * Recebe o nó que está desbalanceado e retorna a nova raiz após o balanceamento
*/
No* balancear(No *raiz) {
   int fb = fatorBalanceamento(raiz);

   // Rotação à esquerda
   if (fb < -1 && fatorBalanceamento(raiz->dir) <= 0)
      raiz = rotacaoEsquerda(raiz);
   
   // Rotação à direita
   else if (fb > 1 && fatorBalanceamento(raiz->esq) >= 0)
      raiz = rotacaoDireita(raiz);
   
   // Rotação dupla à esquerda
   else if (fb > 1 && fatorBalanceamento(raiz->esq) < 0)
      raiz = rotacaoEsquerdaDireita(raiz);
   
   // Rotação dupla à direita
   else if (fb < -1 && fatorBalanceamento(raiz->dir) > 0)
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
        raiz->esq = inserir(raiz->esq, nome);
    } else if (strcmp(raiz->name, nome) < 0) {
        raiz->dir = inserir(raiz->dir, nome);
    } else {
        printf("\nInsercao nao realizada\nO elemento %s ja existe na arvore\n", nome);
    
   }

   // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
   raiz->altura = maior(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;

   // Verifica a necessidade de rebalancear a árvore
   raiz = balancear(raiz);

   return raiz;
}


void inorder(No *raiz) {
   if (raiz) {
      inorder(raiz->esq);
      printf("%s\n", raiz->name);
      inorder(raiz->dir);
   }
}


void imprimir(No *raiz, int nivel) {
   int i;
   
   if (raiz) {
      imprimir(raiz->dir, nivel + 1);
      printf("\n\n");
      
      for (i = 0; i < nivel; i++) {
         printf("\t");
      }
      
      printf("%s\n", raiz->name);
      imprimir(raiz->esq, nivel + 1);
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