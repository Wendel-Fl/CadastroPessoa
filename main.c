#include <locale.h>

#include "avlTree.h"
#include "app.h"

int main(){
   int ordenarPor = 0;
   ordenarPor = menuOrdenarPor();

   setlocale(LC_ALL, "Portuguese");
   No *raiz = NULL;
   raiz = LoadData(raiz, ordenarPor);

   mainMenu(raiz, ordenarPor);

   return 1;
}
