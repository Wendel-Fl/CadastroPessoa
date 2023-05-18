#include <locale.h>

#include "app.c"

int main(){
    setlocale(LC_ALL, "Portuguese");
	runApp();
	return 0;
}
