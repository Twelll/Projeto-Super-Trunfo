# MakeFile
main: programaMain.o projeto.o
	@echo "Gerando arquivo executável"
	gcc programaMain.o projeto.o -o main -lws2_32 -lwinmm

programaMain.o: programaMain.c
	@echo "Compilando e gerando o objeto programaMain"
	gcc -c programaMain.c

projeto.o: projeto.c
	@echo "Compilando e gerando o objeto projeto"
	gcc -c projeto.c

clean:
	@echo "Apagando objetos e executáveis antigos..."
	del /F /Q *.o main.exe

run:
	main.exe