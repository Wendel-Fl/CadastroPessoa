#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct no No;

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
void preorder(No *raiz);
void inorder(No *raiz);
void posorder(No *raiz);
void search(No * raiz,char * target, int ordenarPor);

#endif // AVL_TREE_H