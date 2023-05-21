STD = -std=c99
# -std=c99: padrao C99 da linguagem C
# -ansi:    padrao C90 da linguagem C

OPTIONS = -Wall -Wpedantic -Wno-unused-result -O0 -g
# -O0: nao otimiza o codigo ao compilar
# -g:  prepara o terreno para que o gdb possa encontrar bugs

all: projeto

projeto: app.h avlTree.h avlTree.c app.c main.c
	gcc $(STD) $(OPTIONS) avlTree.c app.c main.c -o projeto

clean:
	rm -f projeto