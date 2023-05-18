//cmd /c '.\main.exe < COMPLETO.txt >resultado.txt' 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avlTree.c"


int runTests() {
   char s1[15], s2[15], s3[15], completa[45];
   
   No *raiz = NULL;
   while(scanf("%s %s %s", &s1, &s2, &s3) != EOF){
    memset(completa, 0, 45);
    joinstrings(s1, s2, s3, completa);
    raiz = inserir(raiz, completa);
   }
    inorder(raiz);
}
