#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "projeto.h"

/**
 * @brief Funcao main
 * 
 * funcao principal do codigo
 * 
 * @return int 
 */
int main()
{
    
    int opcao = 0;
    int salvaContador = 0;
    int quantidadeCartasOriginal = 32;

    Cartas *cartas = (Cartas *)malloc((quantidadeCartasOriginal * sizeof(Cartas)));
    if (cartas == NULL)
    {
        printf("ERRO! Nao foi possivel alocar memória\n");
        exit(1);
    } // If

    CarregarCartas(&cartas, &quantidadeCartasOriginal);

    while (1)
    {

        salvaContador = ContarCartas();
        // MENU
        setbuf(stdin, NULL);
        printf("MENU\n");

        printf("1 - Jogar\n");
        printf("2 - Buscar/Vizualizar Cartas\n");
        printf("3 - Estatisticas e Rankings\n");
        printf("4 - Conquistas\n");
        printf("5 - Gerenciar Cartas\n");
        printf("6 - para sair\n");
        setbuf(stdin, NULL);
        do
        {
            // Requisitando opcao
            printf("Digite sua opcao: ");
            scanf("%d", &opcao);
            setbuf(stdin, NULL);

        } while (opcao < 1 || opcao > 6);

        // Switch - Menu
        switch (opcao)
        {

        // JOGAR
        case 1:
            printf("Voce escoleheu gameplay\n"); // apenas demonstrativo
            break;

        // BUSCAR/VIZUALIZAR CARTAS
        case 2:
            VizualizaCarta(cartas, salvaContador);
            break;

        // ESTATISTICAS E RANKINGS
        case 3:
            printf("Voce escolheu Estatisticas e Rankings\n"); // apenas demonstrativo
            // Funcao
            break;

        // CONQUISTAS
        case 4:
            printf("Voce escolheu Conquistas\n"); // apenas demostrativo
            // Funcao
            break;
        case 5:
            SubMenuGerenciaCartas(cartas, salvaContador);
            break;

            // Funcao
        case 6:
            printf("O Programa sera encerrado\n");
            return 1;
            break;

        // NENHUMA OPCAO
        default:
            perror("ERRO\n");
            break;
        } // Switch

    } // while

    free(cartas);

    return 0;

} // main