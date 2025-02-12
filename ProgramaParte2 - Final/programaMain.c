#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <winsock2.h>
#include "projeto.h"
#include <windows.h>

#define PORTA 8080
#define TAMANHO_BUFFER 1024

int main()
{
    printf("*   #####   ##   ##  ######   #######  ######            ######   ######   ##   ##  ##   ##  #######   ##### *\n");
    printf("*  ##   ##  ##   ##   ##  ##   ##   #   ##  ##           # ## #    ##  ##  ##   ##  ###  ##   ##   #  ##   ## *\n");
    printf("*  #        ##   ##   ##  ##   ## #     ##  ##             ##      ##  ##  ##   ##  #### ##   ## #    ##   ## *\n");
    printf("*   #####   ##   ##   #####    ####     #####              ##      #####   ##   ##  ## ####   ####    ##   ## *\n");
    printf("*       ##  ##   ##   ##       ## #     ## ##              ##      ## ##   ##   ##  ##  ###   ## #    ##   ## *\n");
    printf("*  ##   ##  ##   ##   ##       ##   #   ##  ##             ##      ##  ##  ##   ##  ##   ##   ##      ##   ## *\n");
    printf("*   #####    #####   ####     #######  #### ##            ####    #### ##   #####   ##   ##  ####      ##### *\n");
    printf("\n");

    int opcao = 0;
    int quantJogadores = 0;
    char enderecoServidor[50];
    int quantidadeCartas = ContarCartas();

    if (mciSendString("open \"fundo do super trunfo.wav\" type waveaudio alias audio1", NULL, 0, NULL) != 0)
    {
        printf("Erro ao abrir audio menu\n");
        return 1;
    } // abre o arquivo de audio.wav

    if (mciSendString("play audio1", NULL, 0, NULL) != 0)
    {
        printf("Erro ao reproduzir audio menu\n");
        return 1;
    } // Inicia a reproduçao

    // Alocando Espaco para structs
    Cartas *cartas = (Cartas *)malloc((quantidadeCartas * sizeof(Cartas)));
    if (cartas == NULL)
    {
        printf("ERRO! Nao foi possivel alocar memória\n");
        exit(1);
    } // if

    // Alocando Espaco para structs
    Estatisticas *estatistica = (Estatisticas *)malloc((8 * sizeof(Estatisticas)));
    if (estatistica == NULL)
    {
        printf("ERRO! Não foi possível alocar memória\n");
        exit(1);
    } // if

    Ranking *rank = (Ranking *)malloc((10 * sizeof(Ranking)));
    if (rank == NULL)
    {
        printf("ERRO! Não foi possível alocar memória\n");
        exit(1);
    } // if

    Conquista *conquistas = (Conquista *)malloc((4 * sizeof(Conquista)));
    if (conquistas == NULL)
    {
        printf("ERRO! Não foi possível alocar memória\n");
        exit(1);
    } // if

    // Coloca as cartas do .csv na struct
    CarregarCartas(&cartas, &quantidadeCartas);

    char nomesJogadores[8][50];

    // Loop menu principal do jogo
    while (opcao != 7)
    {
        CarregaEstatistica(estatistica, nomesJogadores, quantJogadores);
        CarregaRanking(rank);
        CarregaConquistas(conquistas);

        printf("\n");
        printf("----------MENU----------\n");
        printf("1 - Jogar\n");
        printf("2 - Buscar/Vizualizar Cartas\n");
        printf("3 - Estatisticas e Rankings\n");
        printf("4 - Conquistas\n");
        printf("5 - Gerenciar Cartas\n");
        printf("6 - Exportar CSV\n");
        printf("7 - Sair\n");
        do
        {
            printf("Digite sua opcao: ");
            scanf("%d", &opcao);
            getchar();
            Beep(800, 100);
        } while (opcao < 1 || opcao > 7);

        // Switch com as opcoes do menu
        switch (opcao)
        {

        // Opcao Menu: Jogar
        case 1:

            do
            {

                // Submenu
                opcao = 0;
                printf("Escolha o modo de jogo:\n");
                printf("1 - Iniciar como Servidor\n");
                printf("2 - Conectar como Cliente\n");
                printf("3 - Local\n");
                printf("4 - Contra o computador\n");
                scanf("%d", &opcao);
                getchar();
                Beep(800, 100);

            } while (opcao < 1 || opcao > 4);
            // Opcao submenu: Servidor
            if (opcao == 1)
            {
                quantJogadores = 0;
                do
                {
                    printf("Digite a quantidade de jogadores(MIN: 2 | MAX 8): ");
                    scanf("%d", &quantJogadores);
                    getchar();
                } while (quantJogadores < 1 || quantJogadores > 8);

                printf("quant Jogadores: %d\n", quantJogadores);
                iniciarServidor(quantJogadores, cartas, quantidadeCartas, estatistica, rank);
            } // if

            // Opcao submenu: Cliente
            else if (opcao == 2)
            {
                printf("Digite o IP do servidor: ");
                fgets(enderecoServidor, sizeof(enderecoServidor), stdin);
                enderecoServidor[strcspn(enderecoServidor, "\n")] = '\0';
                iniciarCliente(enderecoServidor);

            } // else if
            // Opcao submenu: Local
            else if (opcao == 3)
            {
                do
                {
                    printf("Digite a quantidade de jogadores(MIN: 2 | MAX 8): ");
                    scanf("%d", &quantJogadores);
                    getchar();
                } while (quantJogadores < 2 || quantJogadores > 8);

                for (int i = 0; i < quantJogadores; i++)
                {
                    printf("Jogador %d, insira seu nome: ", i + 1);
                    fgets(nomesJogadores[i], 50, stdin);
                    nomesJogadores[i][strcspn(nomesJogadores[i], "\n")] = '\0';
                } // for
                Gameplay(quantJogadores, cartas, quantidadeCartas, nomesJogadores, estatistica, rank);

            } // else if
            else if (opcao == 4)
            {
                quantJogadores = 2;
                
                printf("Jogador, insira seu nome: ");
                fgets(nomesJogadores[0], 50, stdin);
                nomesJogadores[0][strcspn(nomesJogadores[0], "\n")] = '\0';

                strcpy(nomesJogadores[1], "Bot");

                GameplayBot(quantJogadores,cartas, quantidadeCartas, nomesJogadores, estatistica, rank);
            }

            // Nenhuma opcao submenu
            else
            {
                printf("Opcao invalida!\n");
                break;
            } // else
            break;

        // Opcao Menu: Buscar/Vizualizar Cartas
        case 2:
            VizualizaCarta(cartas, quantidadeCartas);
            break;

        // Opcao Menu: Estatisticas e Rankings
        case 3:
            // Atualiza estatisticas
            CarregaEstatistica(estatistica, nomesJogadores, quantJogadores);
            CarregaRanking(rank);

            // Opcoes do menu
            do
            {
                printf("Opcoes\n");
                printf("1 - Mostrar Estatisticas\n");
                printf("2 - Rankings\n");
                printf("Digite sua opção: ");
                scanf("%d", &opcao);
                setbuf(stdin, NULL);
            } while (opcao < 1 || opcao > 2);

            // Switch com as opcoes do menu
            if (opcao == 1) // Opcao Menu: Mostrar Estatisticas
            {
                MostrarEstatistica(estatistica, quantJogadores);
            }
            else if (opcao == 2) // Opcao Menu: Rankings
            {
                MostrarRanking(rank);
            } // If else
            else // Opcao Menu: Erro
            {
                printf("Opcao invalida\n");
                break;
            } // If else
            break;
        // Opcao Menu: Conquistas
        case 4:
            MostrarConquistas(estatistica, quantJogadores);
            break;

        // Opcao Menu: Gerenciar Cartas
        case 5:
            SubMenuGerenciaCartas(cartas, quantidadeCartas);
            break;

        // Opcao Menu: Exportar CSV
        case 6:
            ExportaCsv(cartas, quantidadeCartas);
            printf("Arquivo criado com sucesso\n");
            break;

        // Opcao Menu: Sair
        case 7:
            printf("O Programa sera encerrado\n");
            break;

        // Opcao Menu: Erro
        default:
            perror("ERRO\n");
            break;

        } // Switch
    } // While

    // Liberando memoria alocada
    free(cartas);
    free(estatistica);
    free(rank);
    free(conquistas);

    return 0;
} // main