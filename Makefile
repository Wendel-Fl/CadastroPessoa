all: Projeto

Projeto: app.h avlTree.h avlTree.c app.c main.c
	gcc avlTree.c app.c main.c -o Projeto

run: Projeto
	./Projeto

clean:
	rm -f Projeto