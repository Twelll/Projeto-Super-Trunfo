# MakeFile
main: programaMain.o projeto.o
	@echo "Gerando arquivo executável"
	gcc programaMain.o projeto.o -o main

programaMain.o: programaMain.c
	@echo "Compilando e gerando o objeto programaMain"
	gcc -c programaMain.c

projeto.o: projeto.c
	@echo "Compilando e gerando o objeto projeto"
	gcc -c projeto.c

clean:
	@echo "Apagando objetos e executáveis antigos..."
	rm -f *.o main

run:
	./main
