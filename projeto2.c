/**
 * @author Thiago Pasquim (tmelo@alunos.utfpr.edu.br)
 * @brief
 * @version 0.1
 * @date 2024-11-20
 *
 * @copyright Copyright (c) 2024
 *
 */

// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// Enum para letra das cartas: Usado para comparar os valores das letras.
// Ex: a > b? -> 4 > 1 ? -> sim, logo a vence
typedef enum
{
    A = 4,
    B = 3,
    C = 2,
    D = 1
} Letra_Para_Numero;

// Enum para Switchs
typedef enum
{
    OPCAO_PESQUISAR_ATRIBUTOS = 1,
    OPCAO_PESQUISAR_ATRIBUTOS_MAIOR_MENOR,
    OPCAO_TODAS_CARTAS
} OPCAO_SWITCH;

// Enum para ID das cartas
typedef enum
{
    CARTA1 = 1,
    CARTA2,
    CARTA3,
    CARTA4,
    CARTA5,
    CARTA6,
    CARTA7,
    CARTA8,
    CARTA9,
    CARTA10,
    CARTA11,
    CARTA12,
    CARTA13,
    CARTA14,
    CARTA15,
    CARTA16,
    CARTA17,
    CARTA18,
    CARTA19,
    CARTA20,
    CARTA21,
    CARTA22,
    CARTA23,
    CARTA24,
    CARTA25,
    CARTA26,
    CARTA27,
    CARTA28,
    CARTA29,
    CARTA30,
    CARTA31,
    CARTA32
} Cartas_enum;

// Struct atributos das cartas
typedef struct
{
    float potencia;
    float economia;
    int cilindros;
    float velocidade_maxima;
    float quantidade_macos_cigarro_portamalas;
} Atributos;

// Struct de todas as informacoes das cartas
typedef struct
{
    char nome[50];
    char letra;
    int numero;
    bool super_trunfo;
    Letra_Para_Numero letras_numero;
    Cartas_enum ID;
    Atributos end;
} Cartas;

void Inicializar_Struct(Cartas cartas[])
{ // Por enquanto, preenchido com informacoes aleatorias
    // nome, letra, numero, super_trunfo?/ ID, letra para numero, potencia, economia, cilindros, velocidade_maxima, quantidade_maxima_de_macos_de_cigarros_no_porta_malas
    cartas[0] = (Cartas){"Fiat Uno Mille", 'A', 1, true, CARTA1, A, {66, 10, 4, 299792458, 2900}}; // super trunfo
    cartas[1] = (Cartas){"Chevrolet Opala", 'B', 2, false, CARTA2, B, {98, 8, 6, 180, 2}};
    cartas[2] = (Cartas){"Volkswagen Fuscão Preto", 'C', 3, false, CARTA3, C, {50, 12, 4, 130, 5}};
    cartas[3] = (Cartas){"Toyota Corolla", 'D', 4, false, CARTA4, D, {144, 15, 4, 210, 4}};
    cartas[4] = (Cartas){"Volkswagen Gol GTI Rebaixado", 'E', 5, false, CARTA5, A, {112, 10, 4, 190, 3}};
    cartas[5] = (Cartas){"Ford Maverick", 'F', 6, false, CARTA6, B, {140, 7, 8, 200, 2}};
    cartas[6] = (Cartas){"Chevrolet Corsa", 'G', 7, false, CARTA7, C, {78, 16, 4, 160, 3}};
    cartas[7] = (Cartas){"Renault Kwid", 'H', 8, false, CARTA8, D, {70, 20, 3, 150, 4}};
    cartas[8] = (Cartas){"Jeep Renegade", 'I', 9, false, CARTA9, A, {130, 10, 4, 180, 3}};
    cartas[9] = (Cartas){"Chevrolet Monza", 'J', 10, false, CARTA10, B, {110, 12, 4, 170, 300}};
    cartas[10] = (Cartas){"Volkswagen Kombi", 'K', 11, false, CARTA11, C, {80, 10, 4, 120, 8}};
    cartas[11] = (Cartas){"Fiat Palio", 'L', 12, false, CARTA12, D, {85, 13, 4, 160, 3}};
    cartas[12] = (Cartas){"Honda Civic", 'M', 13, false, CARTA13, A, {150, 14, 4, 220, 4}};
    cartas[13] = (Cartas){"Chevrolet Camaro", 'N', 14, false, CARTA14, B, {455, 7, 8, 290, 2}};
    cartas[14] = (Cartas){"Volkswagen Santana", 'O', 15, false, CARTA15, C, {116, 12, 4, 180, 3}};
    cartas[15] = (Cartas){"Ford EcoSport", 'P', 16, false, CARTA16, D, {137, 10, 4, 170, 4}};
    cartas[16] = (Cartas){"Renault Sandero", 'Q', 17, false, CARTA17, A, {82, 13, 4, 165, 4}};
    cartas[17] = (Cartas){"Volkswagen Saveiro", 'R', 18, false, CARTA18, B, {104, 12, 4, 175, 4}};
    cartas[18] = (Cartas){"Chevrolet Onix", 'S', 19, false, CARTA19, C, {116, 15, 3, 185, 4}};
    cartas[19] = (Cartas){"Fiat Toro", 'T', 20, false, CARTA20, D, {139, 11, 4, 190, 5}};
    cartas[20] = (Cartas){"Ford Ka", 'U', 21, false, CARTA21, A, {85, 14, 3, 170, 4}};
    cartas[21] = (Cartas){"Hyundai HB20", 'V', 22, false, CARTA22, B, {116, 14, 4, 190, 4}};
    cartas[22] = (Cartas){"Toyota Hilux", 'W', 23, false, CARTA23, C, {204, 9, 4, 200, 6}};
    cartas[23] = (Cartas){"Fiat Strada", 'X', 24, false, CARTA24, D, {109, 12, 4, 180, 5}};
    cartas[24] = (Cartas){"Volkswagen T-Cross", 'Y', 25, false, CARTA25, A, {128, 13, 4, 190, 4}};
    cartas[25] = (Cartas){"Chevrolet Tracker", 'Z', 26, false, CARTA26, B, {133, 14, 4, 200, 4}};
    cartas[26] = (Cartas){"GURGEL BR-800", 'A', 27, false, CARTA27, C, {180, 10, 4, 210, 4}};
    cartas[27] = (Cartas){"Ford Ranger", 'B', 28, false, CARTA28, D, {200, 8, 4, 200, 5}};
    cartas[28] = (Cartas){"Nissan Kicks", 'C', 29, false, CARTA29, A, {114, 15, 4, 180, 4}};
    cartas[29] = (Cartas){"Volkswagen Amarok", 'D', 30, false, CARTA30, B, {225, 9, 6, 210, 6}};
    cartas[30] = (Cartas){"Fiat Mobi", 'E', 31, false, CARTA31, C, {74, 16, 3, 150, 3}};
    cartas[31] = (Cartas){"Chevrolet Spin", 'F', 32, false, CARTA32, D, {108, 11, 4, 160, 6}};

    return;
} // Inicializar_Struct

// Em desenvolvimento
void Gameplay(int quant_jogadores)
{

    printf("Voce selecionou %d jogadores\n", quant_jogadores);

    return;
} // Gameplay

// Buscando as cartas para visualizar por atributos, maior e menor
void VizualizaCarta(Cartas cartas[])
{

    char nome_compara[50];
    int encontrado = 0;
    int opcao_menu, opcao_atributo_menu1, opcao_atributo_menu2;
    int maior, menor, letra_menor, letra_maior;

    // Menu que exibe as opções
    printf("\n");
    printf("Buscar/Vizualizar cartas\n");
    printf("1 - Pesquisar por atributos\n");
    printf("2 - Pesquisar por atributos, dentro de um intervalo:\n");
    printf("3 - Navegar por todas as cartas\n");

    do
    {
        // Requisitando Opcao
        printf("Digite a opção: ");
        scanf("%d", &opcao_menu);
        setbuf(stdin, NULL);

    } while (opcao_menu < 0 || opcao_menu > 3);

    // Switch Maior - Responsavel Pelos Menus
    switch (opcao_menu)
    {

    // Menu 1
    case OPCAO_PESQUISAR_ATRIBUTOS:
        printf("\n");

        // Menu: 1 - Pesquisar por atributos
        printf("1 - Economia\n");
        printf("2 - Cilindros\n");
        printf("3 - Velocidade_maxima\n");
        printf("4 - Quantidade macos de cigarro no porta-malas\n");
        // Informacoes Gerais da Carta
        printf("5 - Numero\n");
        printf("6 - Letra\n");
        printf("7 - Ver todos atributos de uma carta pelo nome\n");

        do
        {
            // Requisitando opcao
            printf("Digite sua opcao: ");
            scanf("%d", &opcao_atributo_menu1);
            setbuf(stdin, NULL);
        } while (opcao_atributo_menu1 < 1 || opcao_atributo_menu1 > 7);

        // Switch Menor - Responsavel por Menu: 1 - Pesquisar por atributos
        switch (opcao_atributo_menu1)
        {
        case 1: // Economia
            for (int i = 0; i < 32; i++)
            {
                printf("%s: Economia %.2f L/Km", cartas[i].nome, cartas[i].end.economia);
                printf("\n");
            } // For
            break;

        case 2: // Cilindros
            for (int i = 0; i < 32; i++)
            {
                printf("%s: Cilindros %d", cartas[i].nome, cartas[i].end.cilindros);
                printf("\n");
            } // For
            break;

        case 3: // Velocidade Maxima
            for (int i = 0; i < 32; i++)
            {
                printf("%s: Velocidade Maxima %.2f", cartas[i].nome, cartas[i].end.velocidade_maxima);
                printf("\n");
            } // For
            break;

        case 4: // Macos de cigarros no porta malas
            for (int i = 0; i < 32; i++)
            {
                printf("%s: Quantidade Max. de cigarros no porta malas %.2f", cartas[i].nome, cartas[i].end.quantidade_macos_cigarro_portamalas);
                printf("\n");
            } // For
            break;

        case 5: // Numero
            for (int i = 0; i < 32; i++)
            {
                printf("%s: Numero %d", cartas[i].nome, cartas[i].numero);
                printf("\n");
            } // For
            break;

        case 6: // Letra
            for (int i = 0; i < 32; i++)
            {
                printf("%s: Letra %c", cartas[i].nome, cartas[i].letra);
                printf("\n");
            } // For
            break;

        case 7: // Nome

            printf("Digite o nome da carta que deseja pesquisar: ");
            fgets(nome_compara, 50, stdin);
            nome_compara[strcspn(nome_compara, "\n")] = '\0';
            setbuf(stdin, NULL);

            for (int i = 0; i < 32; i++)
            {
                if (strcmp(nome_compara, cartas[i].nome) == 0)
                {

                    // Informacoes gerais da carta
                    printf("Carta: %s\n", cartas[i].nome);
                    printf("Categoria: %c\n", cartas[i].letra);
                    printf("Numero: %d\n", cartas[i].numero);
                    printf("Super Trunfo: %s\n", cartas[i].super_trunfo ? "Sim" : "Não");

                    // Atributos
                    printf("Economia: %.2f Litro/Km\n", cartas[i].end.economia);
                    printf("Potencia: %.2fCv\n", cartas[i].end.potencia);
                    printf("Cilindros: %d\n", cartas[i].end.cilindros);
                    printf("Velocidade Max: %.2f Km/h\n", cartas[i].end.velocidade_maxima);
                    printf("Quantidade maxima de maços de cigarros no porta malas: %.2f\n", cartas[i].end.quantidade_macos_cigarro_portamalas);

                    break; // carta encontrada, nao precisa continuar o loop
                } // if
            } // for

            if (!encontrado)
            {
                printf("\nCarta '%s' não encontrada!\n", nome_compara);
            } // if

            return;
        } // BuscaCartas

    default:
        printf("Erro\n");
        break;
    } // Switch Menor - Responsavel por Menu: 1 - Pesquisar por atributos

    // Menu 2
    switch (opcao_menu)
    {

    case OPCAO_PESQUISAR_ATRIBUTOS_MAIOR_MENOR:
        printf("\n");
        // Menu 2 - Pesquisar por atributos, dentro de um intervalo
        //  Atributos da carta
        printf("1 - Economia\n");
        printf("2 - Cilindros\n");
        printf("3 - Velocidade_maxima\n");
        printf("4 - Quantidade macos de cigarro no portamalas\n");
        // Informacoes Gerais da Carta
        printf("5 - Numero\n");
        printf("6 - Letra\n");

        do
        {
            // Requisitando
            printf("Digite sua opcao: ");
            scanf("%d", &opcao_atributo_menu2);
            setbuf(stdin, NULL);
        } while (opcao_atributo_menu2 < 1 || opcao_atributo_menu2 > 6);

        // If para opcao 6: pois se trata de um caso especial
        /*if (opcao_atributo_menu1 != 6)
        {
            printf("Opcoes\n");
            printf("4 = A\n");
            printf("3 = B\n");
            printf("2 = C\n");
            printf("1 = D\n");

            printf("Digite a letra de menor valor: ");
            scanf("%d", &letra_menor);
            setbuf(stdin, NULL);

            printf("Digite a letra de maior valor: ");
            scanf("%d", &letra_maior);
            setbuf(stdin, NULL);

            for (int i = 0; i < 32; i++)
            {
                if ((unsigned int)cartas[i].letras_numero >= (unsigned int)letra_maior && (unsigned int)cartas[i].letras_numero <= (unsigned int)letra_menor)
                {
                    printf("%s: %c", cartas[i].nome, cartas[i].letra);
                    printf("\n");

                } // if

            } // for
        }
        else
        {
        */

        // Definindo intervalo
        printf("Escolha o intervalo que deseja\n");
        printf("Valores menores ou iguais que: ");
        scanf("%d", &menor);
        setbuf(stdin, NULL);

        printf("Valores maiores ou iguais que: ");
        scanf("%d", &maior);
        setbuf(stdin, NULL);

        // Switch Menor - Responsavel por Menu 2: Pesquisar por atributos, dentro de um intervalo
        switch (opcao_atributo_menu2)
        {

        case 1: // Economia
            for (int i = 0; i < 32; i++)
            {
                if (cartas[i].end.economia >= maior && cartas[i].end.economia <= menor)
                {
                    printf("%s: Economia %.2f", cartas[i].nome, cartas[i].end.economia);
                    printf("\n");
                }

            } // For
            break;

        case 2: // Cilindros
            for (int i = 0; i < 32; i++)
            {
                if (cartas[i].end.cilindros >= maior && cartas[i].end.cilindros <= menor)
                {
                    printf("%s: Cilidros %d", cartas[i].nome, cartas[i].end.cilindros);
                    printf("\n");
                }
            } // For
            break;

        case 3: // Velocidade Maxima
            for (int i = 0; i < 32; i++)
            {
                if (cartas[i].end.velocidade_maxima >= maior && cartas[i].end.velocidade_maxima <= menor)
                {
                    printf("%s: Velocidade %.2f", cartas[i].nome, cartas[i].end.velocidade_maxima);
                    printf("\n");
                }
            }
            break;

        case 4: // Macos de cigarros no porta malas
            for (int i = 0; i < 32; i++)
            {
                if (cartas[i].end.quantidade_macos_cigarro_portamalas >= maior && cartas[i].end.quantidade_macos_cigarro_portamalas <= menor)
                {
                    printf("%s: Quantidade Max. de cigarros no porta malas %.2f", cartas[i].nome, cartas[i].end.quantidade_macos_cigarro_portamalas);
                    printf("\n");
                }
            } // For
            break;

        case 5: // Numero
            for (int i = 0; i < 32; i++)
            {
                if (cartas[i].numero >= maior && cartas[i].numero <= menor)
                {
                    printf("%s:  Numero %d", cartas[i].nome, cartas[i].numero);
                    printf("\n");
                }
            } // For
            break;

        // Em aprimoramento
        case 6:
            printf("Opcoes\n");
            printf("1 = A\n");
            printf("2 = B\n");
            printf("3 = C\n");
            printf("4 = D\n");

            printf("Digite a letra de menor valor: ");
            scanf("%d", &letra_menor);
            setbuf(stdin, NULL);

            printf("Digite a letra de maior valor: ");
            scanf("%d", &letra_maior);
            setbuf(stdin, NULL);

            for (int i = 0; i < 32; i++)
            {
                if ((unsigned int)cartas[i].letras_numero >= (unsigned int)letra_maior && (unsigned int)cartas[i].letras_numero <= (unsigned int)letra_menor)
                {
                    printf("%s: %c", cartas[i].nome, cartas[i].letra);
                    printf("\n");

                } // For

            } // i
            break;

        default:
            printf("Erro\n");
            break;
        } // Switch Menor - Responsavel por Menu 2: Pesquisar por atributos, dentro de um intervalo

    } //  Switch Maior - Responsavel Pelos Menus
    return;
} // Função

int main()
{

    int opcao = 0;
    int quant_jogadores;
    Cartas cartas[32];
    Inicializar_Struct(cartas);

    while (opcao == !5)
    {
        // MENU
        printf("MENU\n");
        printf("1 - Jogar\n");
        printf("2 - Buscar/Vizualizar Cartas\n");
        printf("3 - Estatisticas e Rankings\n");
        printf("4 - Conquistas\n");
        printf("5 - para sair\n");

        do
        {
            // Requisitando opcao
            printf("Digite sua opcao: ");
            scanf("%d", &opcao);
            setbuf(stdin, NULL);

        } while (opcao < 1 || opcao > 5);

        // Switch - Menu
        switch (opcao)
        {

        // JOGAR
        case 1:
            do
            {
                printf("Digite a quantidade de jogadores(MIN: 2 | MAX 8): ");
                scanf("%d", &quant_jogadores);
            } while (quant_jogadores < 2 || quant_jogadores > 8);

            Gameplay(quant_jogadores);
            break;

        // BUSCAR/VIZUALIZAR CARTAS
        case 2:
            VizualizaCarta(cartas);
            break;

        // ESTATISTICAS E RANKINGS
        case 3:
            printf("Voce escolheu Estatisticas e Rankings\n"); // Apenas Testes
            // Funcao
            break;

        // CONQUISTAS
        case 4:
            printf("Voce escolheu Conquistas\n"); // Apenas Testes
            // Funcao
            break;
        case 5:
            printf("O Programa sera encerrado\n");
            return 0;

        // NENHUMA OPCAO
        default:
            printf("Erro\n");
            break;
        } // Switch

        return 0;
    } // while
} // main

    /*
    ADICIONADO:
    filtros em todas as entradas
    correcao nos indices do vetor da struct cartas - acompanhado com o "for" correto
    correcao dos parametros de todos "if" em Atributos maiores ou menores
    funcao while na main
    correcao de pequenos erros

    PENDENCIAS:
    Adicionar corretamente a case 6 de atributos maior e menor
    Implementacao do resto do projeto
    */