all: Projeto

Projeto: app.h avlTree.h avlTree.c app.c main.c
	gcc -o Projeto avlTree.c app.c main.c

run: Projeto
	./Projeto