/**
 * @author Thiago Wesley Pasquim de Melo     (tmelo@alunos.utfpr.edu.br)
 * @author Lucas Gabriel Rodrigues de Moraes (lucasgabrielmoraes@alunos.utfpr.edu.br)
 * @author Vinicius Gabriel Giordani Barbosa (vinciusb.2024@alunos.utfpr.edu.br)
 * @brief
 * @version 2.0
 * @date 11-02-2024
 *
 * @copyright Copyright (c) 2025
 *
 */

// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <winsock2.h>
#include <windows.h>

// Variaveis Globais(Usadas Principalmente na LAN)
#define PORTA 8080
#define TAMANHO_BUFFER 1024
#define MAX_JOGADORES 8

/**
 * @brief Representa os atributos de uma carta no jogo
 *
 * Contem informacoes dos atributos
 * E usada dentro da Struct Cartas
 *
 */
typedef struct
{
    float potencia;
    float economia;
    int cilindros;
    float velocidadeMaxima;
    float quantidadeMacosCigarroPortamalas;
} Atributos;

/**
 * @brief Representa uma carta do jogo Super trunfo
 * Essa struct principal contem os dados das cartas
 */
typedef struct
{
    char nome[50];
    char letra;
    int numero;
    bool super_trunfo;
    Atributos end;
} Cartas;

/**
 * @brief Struct para conquistas, contem informacoes da conquista
 *
 */
typedef struct
{
    char nome[30];
    char descricao[100];
    int condicao;
    bool desbloqueada;
} Conquista;

/**
 * @brief Armazena o nome dos jogadores que estão jogando
 * e armazena as estatísticas dos jogadores
 */
typedef struct
{
    char nome[30];
    int partidasJogadas;
    int vitorias;
    float taxaVitoria;
    Conquista conquistas[4];
} Estatisticas;

/**
 * @brief Struct para Ranking, contem informacoes dos players no ranking
 *
 */
typedef struct
{
    char nome[30];
    int pontuacao;
} Ranking;

/**
 * @brief Struct para som
 *
 */
typedef struct
{
    char nome[50];
    char som[50];
} CartaSom;

// Preenchendo struct de som
CartaSom sons[] = {
    {"Fiat Uno C/Escada", "DUDUDUDU MAX VERSTAPPEN original.wav"},
    {"Peugeot 206", "tu-sai-de-problema.wav"},
    {"Fiat Marea Perua", "som-de-explosao.wav"},
    {"Gurgel BR-800", "seloco-nao-compensa.wav"}};

/**
 * @brief Escreve as informacoes das cartas no arquivo csv
 *
 * Salva dados das cartas no arquivo csv
 *
 * @param cartasFonte Ponteiro para struct
 * @param quantidadeCartas Quantidade de cartas no csv
 */
void ExportaCsv(Cartas *cartasFonte, int quantidadeCartas)
{
    FILE *arqCSV = fopen("Dados\\exporta_cartas.csv", "w");
    if (arqCSV == NULL)
    {
        perror("ERRO! Não foi possível abrir o arquivo .csv, para escrita");
        exit(1);
    } // if

    for (int i = 0; i < quantidadeCartas; i++)
    {
        fprintf(arqCSV, "%s,%c,%d,%s,%.2f,%.2f,%d,%.2f,%.2f\n",
                cartasFonte[i].nome,
                cartasFonte[i].letra,
                cartasFonte[i].numero,
                cartasFonte[i].super_trunfo ? "true" : "false",
                cartasFonte[i].end.potencia,
                cartasFonte[i].end.economia,
                cartasFonte[i].end.cilindros,
                cartasFonte[i].end.velocidadeMaxima,
                cartasFonte[i].end.quantidadeMacosCigarroPortamalas);
    } // for

    fclose(arqCSV);
} // ExportaCsv

/**
 * @brief Escreve as informacoes das cartas no arquivo csv
 *
 * Salva dados das cartas no arquivo csv
 *
 * @param cartasFonte Ponteiro para struct
 * @param quantidadeCartas Quantidade de cartas no csv
 */
void EscreverCsv(Cartas *cartasFonte, int quantidadeCartas)
{
    FILE *arqCSV = fopen("cartas.csv", "w");
    if (arqCSV == NULL)
    {
        perror("ERRO! Não foi possível abrir o arquivo .csv, para escrita");
        exit(1);
    } // if

    for (int i = 0; i < quantidadeCartas; i++)
    {
        fprintf(arqCSV, "%s,%c,%d,%s,%.2f,%.2f,%d,%.2f,%.2f\n",
                cartasFonte[i].nome,
                cartasFonte[i].letra,
                cartasFonte[i].numero,
                cartasFonte[i].super_trunfo ? "true" : "false",
                // cartasFonte[i].ID,
                cartasFonte[i].end.potencia,
                cartasFonte[i].end.economia,
                cartasFonte[i].end.cilindros,
                cartasFonte[i].end.velocidadeMaxima,
                cartasFonte[i].end.quantidadeMacosCigarroPortamalas);
    } // for

    fclose(arqCSV);
} // escreverCsv

/**
 * @brief  Conta o numeros de cartas no arquivo csv
 *
 * Le o arquivo csv e retorno o numeros de cartas no arquivo csv
 *
 * @return numeros de cartas no arquivo csv
 */
int ContarCartas()
{
    FILE *arqCsv = fopen("cartas.csv", "r");
    if (arqCsv == NULL)
    {
        perror("ERRO! Não foi possível abrir o arquivo .csv:\n");
        exit(1);
    } // if

    int contador = 0;
    char buffer[1024];

    // Conta as linhas com dados (cartas)
    while (fgets(buffer, sizeof(buffer), arqCsv))
    {
        // Se a linha não for vazia e tiver algum dado, conta como uma carta
        if (buffer[0] != '\n' && strlen(buffer) > 1)
        {
            contador++;
        } // if
    } // for

    fclose(arqCsv);
    return contador;
} // contarCartas

/**
 * @brief Insere cartas novas ao .csv
 *
 * O usuário digita os astributos de uma carta nova e atribui ao .csv
 *
 * @param cartas
 * @param quantidadeCartas
 */
void InserirCarta(Cartas **cartas, int *quantidadeCartas)
{
    int quantidadeAtual = *quantidadeCartas;
    int novaQuantidade = quantidadeAtual + 1;
    int cartaEncontrada = 0;
    char nomeCompara[20];

    // Realoca memória para a nova quantidade de cartas
    Cartas *novasCartas = (Cartas *)realloc(*cartas, novaQuantidade * sizeof(Cartas));
    if (novasCartas == NULL)
    {
        perror("ERRO! Não foi possível realocar memória\n");
        exit(1);
    } // if

    *cartas = novasCartas;

    Cartas *novaCarta = &(*cartas)[quantidadeAtual];

    printf("Digite as informaçãoes da carta nova...\n");

    do
    {
        setbuf(stdin, NULL);
        printf("Nome: ");
        Beep(800, 100);
        fgets(nomeCompara, 50, stdin);
        nomeCompara[strcspn(nomeCompara, "\n")] = '\0';

        cartaEncontrada = 0;
        for (int i = 0; i < *quantidadeCartas; i++)
        {
            if (strcasecmp(nomeCompara, (*cartas)[i].nome) == 0)
            {
                printf("Carta Encontrada %s\n", cartas[i]->nome);
                Beep(800, 100);
                cartaEncontrada = 1;
                break;
            } // if
        } // for
    } while (cartaEncontrada == 1);
    strcpy(novaCarta->nome, nomeCompara);

    do
    {
        printf("Letra (A - D): ");
        scanf(" %c", &novaCarta->letra);
        novaCarta->letra = toupper(novaCarta->letra);
        setbuf(stdin, NULL);
    } while (novaCarta->letra < 'A' || novaCarta->letra > 'D'); // do while para aceitar somente A ao D

    do
    {
        printf("Número (> 8): ");
        scanf("%d", &novaCarta->numero);
        setbuf(stdin, NULL);

    } while (novaCarta->numero <= 8); // do while que aceita numeros maiores que 8

    // Nao ira permitir outro super trunfo
    novaCarta->super_trunfo = false;

    do
    {
        printf("Potência: ");
        scanf("%f", &novaCarta->end.potencia);
        setbuf(stdin, NULL);
    } while (novaCarta->end.potencia < 0); // do while que aceita somente numeros maiores que 0

    do
    {
        printf("Economia: ");
        scanf("%f", &novaCarta->end.economia);
        setbuf(stdin, NULL);
    } while (novaCarta->end.economia < 0); // do while que aceita somente numeros maiores que 0

    do
    {
        printf("Maços de cigarro no porta-malas: ");
        scanf("%f", &novaCarta->end.quantidadeMacosCigarroPortamalas);
        setbuf(stdin, NULL);
    } while (novaCarta->end.quantidadeMacosCigarroPortamalas < 0); // do while que aceita somente numeros maiores que 0

    do
    {
        printf("Velocidade Máxima: ");
        scanf("%f", &novaCarta->end.velocidadeMaxima);
        setbuf(stdin, NULL);
    } while (novaCarta->end.velocidadeMaxima < 0); // do while que aceita somente numeros maiores que 0

    do
    {
        printf("Cilindros: ");
        scanf("%d", &novaCarta->end.cilindros);
        setbuf(stdin, NULL);
    } while (novaCarta->end.cilindros < 0); // do while que aceita somente numeros maiores que 0

    // Atualiza a quantidade de cartas
    *quantidadeCartas = novaQuantidade;

    // Abre o arquivo CSV em modo de adição
    FILE *filePointer = fopen("cartas.csv", "a");
    if (filePointer == NULL)
    {
        perror("ERRO! Nao foi foi abrir o arquivo .csv para escrita.\n");
        exit(1);
    } // if

    EscreverCsv(*cartas, *quantidadeCartas);
    printf("Carta adicionada com sucesso!\n");
    fclose(filePointer);
} // inserirCarta

/**
 * @brief Responsavel por alterar as informacoes das cartas no .csv
 *
 * Usuário digita o nome da carta, caso essa carta exista no .csv
 a função altera os atributos da carta no .csv
 *
 * @param cartasFonte
 * @param structTamanho
 */
void AlterarCartas(Cartas *cartasFonte, int *structTamanho)
{
    char nomeCompara[50];
    int cartaEncontrada = 0;
    int salvaIndice;

    do
    {
        setbuf(stdin, NULL);
        printf("Digite o nome da carta que alterar: ");
        fgets(nomeCompara, 50, stdin);
        nomeCompara[strcspn(nomeCompara, "\n")] = '\0';
        Beep(800, 100);

        for (int i = 0; i < *structTamanho; i++)
        {
            if (strcasecmp(nomeCompara, cartasFonte[i].nome) == 0)
            {
                printf("Carta Encontrada %s\n", cartasFonte[i].nome);
                Beep(800, 100);
                cartaEncontrada = 1;
                salvaIndice = i;
                break;
            } // if para compara carta da fez com a qual procura

        } // for para passar por todas as cartas do deck

        if (!cartaEncontrada)
        {
            printf("A Carta %s NAO foi encontrada\n", nomeCompara);
            Beep(300, 200);
            Beep(200, 250);
            printf("Tente Novamente\n");
        } // if para quando a carta não for encontrada

    } while (!cartaEncontrada);

    // informacoes da carta
    printf("Agora digite as novas informacoes:\n");
    printf("Nome: ");
    fgets(cartasFonte[salvaIndice].nome, 50, stdin);
    cartasFonte[salvaIndice].nome[strcspn(cartasFonte[salvaIndice].nome, "\n")] = '\0';
    setbuf(stdin, NULL);

    for (int i = 0; i < *structTamanho; i++)
    {
        if (strcasecmp(nomeCompara, cartasFonte[i].nome) == 0)
        {
            printf("Ja existe uma carta com esse nome: "
                   "%s"
                   "\n",
                   cartasFonte[i].nome);
            Beep(300, 200);
            Beep(200, 250);
            cartaEncontrada = 1;
            break;
        } // if
    } // for

    do
    {
        printf("Potencia: ");
        scanf("%f", &cartasFonte[salvaIndice].end.potencia);
        setbuf(stdin, NULL);
        Beep(800, 100);
    } while (cartasFonte[salvaIndice].end.potencia < 0); // do while que aceita somente numeros maiores que 0

    do
    {

        printf("Economia: ");
        scanf("%f", &cartasFonte[salvaIndice].end.economia);
        setbuf(stdin, NULL);
        Beep(800, 100);
    } while (cartasFonte[salvaIndice].end.economia < 0); // do while que aceita somente numeros maiores que 0

    do
    {

        printf("cilindros: ");
        scanf("%d", &cartasFonte[salvaIndice].end.cilindros);
        setbuf(stdin, NULL);
        Beep(800, 100);
    } while (cartasFonte[salvaIndice].end.cilindros < 0); // do while que aceita somente numeros maiores que 0

    do
    {

        printf("Velocidade Maxima: ");
        scanf("%f", &cartasFonte[salvaIndice].end.velocidadeMaxima);
        setbuf(stdin, NULL);
        Beep(800, 100);
    } while (cartasFonte[salvaIndice].end.velocidadeMaxima < 0); // do while que aceita somente numeros maiores que 0

    do
    {

        printf("Quantidade de macos de cigarro no porta malas: ");
        scanf("%f", &cartasFonte[salvaIndice].end.quantidadeMacosCigarroPortamalas);
        setbuf(stdin, NULL);
        Beep(800, 100);
    } while (cartasFonte[salvaIndice].end.quantidadeMacosCigarroPortamalas < 0); // do while que aceita somente numeros maiores que 0

    EscreverCsv(cartasFonte, *structTamanho);

    // mensagem de exito
    printf("As informacoes foram atualizadas com sucesso\n");
    Beep(800, 200);
    Beep(1000, 200);
    Beep(1200, 200);
    Beep(1500, 300);

    return;
} // alternarCartas

/**
 * @brief Responsavel por Deletar cartas no .csv
 *
 * Usuário pode excluir uma carta do .csv desde que tenha mais 32 cartas no .csv
 *
 * @param cartas
 * @param quantidadeCartas
 */
void DeletarCartas(Cartas **cartas, int *quantidadeCartas)
{
    // so aceita remover cartas se o deck se estiver mais de 32
    if (*quantidadeCartas <= 32)
    {
        printf("Não é possível deletar mais cartas. O baralho deve ter pelo menos 32 cartas.\n");
        Beep(600, 300);
        Beep(400, 300);
        Beep(300, 300);
        Beep(200, 400);
        return;
    } // if

    printf("Escolha uma carta para deletar (por número):\n");
    for (int i = 0; i < *quantidadeCartas; i++)
    {
        printf("%d - %s\n", i + 1, (*cartas)[i].nome);
        Beep(800, 100);
    } // for para passar por todas as cartas do deck

    int indice;
    do
    {
        printf("Digite o número da carta que deseja deletar (1 a %d): ", *quantidadeCartas);
        scanf("%d", &indice);
        setbuf(stdin, NULL);
        Beep(800, 100);
    } while (indice < 1 || indice > *quantidadeCartas); // do while que aceita somente numeros maiores que 1 e menores que quantidade

    // Ajusta o índice para zero base
    indice--;

    // Move as cartas subsequentes para preencher o espaço da carta deletada
    for (int i = indice; i < *quantidadeCartas - 1; i++)
    {
        (*cartas)[i] = (*cartas)[i + 1];
    } // for

    // Realoca memória para ajustar o tamanho do vetor
    if (*quantidadeCartas - 1 > 0)
    {

        // Realoca a memória
        Cartas *temp = realloc(*cartas, (*quantidadeCartas - 1) * sizeof(Cartas));
        if (temp == NULL && *quantidadeCartas > 1)
        {
            perror("ERRO! Nao foi possivel realocar memória após deletar carta.\n");
            Beep(300, 200);
            Beep(200, 250);
            exit(1);
        } // if
        *cartas = temp;
    }
    (*quantidadeCartas)--;

    // Atualiza o arquivo CSV utilizando as funções de manipulação CSV
    EscreverCsv(*cartas, *quantidadeCartas);
    printf("Carta deletada com sucesso!\n");
    Beep(800, 100);

} // deletarCartas

/**
 * @brief Pesquisa uma carta buscando pelos atributos
 *
 * O usuário pode procurar uma carta digitando os atributos das cartas
 *
 * @param cartas
 * @param quantidadeCartas
 */
void PesquisaAtributos(Cartas cartas[], int quantidadeCartas)
{
    char nomeCompara[50];
    int encontrado = 0;
    int opcaoAtributoMenu1;
    char letraCompara[1];
    int numeroCompara;
    int cilindrosCompara;
    float cigarrosCompara;
    float velocidadeCompara;
    float economiaCompara;
    float potenciaCompara;

    printf("pesquisarAtributos\n");
    printf("\n");

    // Menu: 1 - Pesquisar por atributos
    printf("1 - Economia\n");
    printf("2 - Cilindros\n");
    printf("3 - VelocidadeMaxima\n");
    printf("4 - Quantidade macos de cigarro no porta-malas\n");
    // Informacoes Gerais da Carta
    printf("5 - Numero\n");
    printf("6 - Letra\n");
    printf("7 - Ver todos atributos de uma carta pelo nome\n");
    Beep(800, 100);

    do
    {
        setbuf(stdin, NULL);
        // Requisitando opcao
        printf("Digite sua opcao: ");
        scanf("%d", &opcaoAtributoMenu1);
        Beep(800, 100);
    } while (opcaoAtributoMenu1 < 1 || opcaoAtributoMenu1 > 7);

    // Switch Menor - Responsavel por Menu: 1 - Pesquisar por atributos
    switch (opcaoAtributoMenu1)
    {
    case 1: // Pesquisa Economia

        printf("Digite a Economia: ");
        scanf("%f", &economiaCompara);
        setbuf(stdin, NULL);
        Beep(800, 100);

        printf("Cartas com economia %f \n", economiaCompara);
        for (int i = 0; i < quantidadeCartas; i++)
        {
            if (economiaCompara == cartas[i].end.economia)
            {
                printf("%s: Economia %.2f\n", cartas[i].nome, cartas[i].end.economia);
            } // if comparar a economia escolhida com as cartas do deck
        } // for para passar por todas as cartas do deck
        break;

    case 2: // Pesquisa Cilindros

        printf("Digite a quantidade de cilindros: ");
        scanf("%d", &cilindrosCompara);
        setbuf(stdin, NULL);
        Beep(800, 100);

        printf("Cartas com %d cilindros\n", cilindrosCompara);
        for (int i = 0; i < quantidadeCartas; i++)
        {
            if (cilindrosCompara == cartas[i].end.cilindros)
            {
                printf("%s: Cilindros %d\n", cartas[i].nome, cartas[i].end.cilindros);
            } // if comparar o cilindros escolhidos com as cartas do deck
        } // for para passar por todas as cartas do deck
        break;

    case 3: // Pesquisa Velocidade Maxima

        printf("Digite a velocidade maxima: ");
        scanf("%f", &velocidadeCompara);
        setbuf(stdin, NULL);
        Beep(800, 100);

        printf("Cartas com velocidade maxima %f\n", velocidadeCompara);
        for (int i = 0; i < quantidadeCartas; i++)
        {
            if (velocidadeCompara == cartas[i].end.velocidadeMaxima)
            {
                printf("%s: Velocidade Maxima %.2ff\n", cartas[i].nome, cartas[i].end.quantidadeMacosCigarroPortamalas);
            } // if comparar a velocidade escolhida com as cartas do deck
        } // for para passar por todas as cartas do deck
        break;

    case 4: // Pesquisa Macos de cigarros no porta malas

        printf("Digite o macos de cigarros: ");
        scanf("%f", &cigarrosCompara);
        setbuf(stdin, NULL);
        Beep(800, 100);

        printf("Cartas com %f macos de cigarros no porta malas\n", cigarrosCompara);
        for (int i = 0; i < quantidadeCartas; i++)
        {
            if (cigarrosCompara == cartas[i].end.quantidadeMacosCigarroPortamalas)
            {
                printf("%s: Macos p/porta malas %.2f\n", cartas[i].nome, cartas[i].end.quantidadeMacosCigarroPortamalas);
            } // if comparar o macos de cigarros escolhida com as cartas do deck
        } // for para passar por todas as cartas do deck
        break;

    case 5: // Pesquisa Numero
        printf("Digite o numero: ");
        scanf("%d", &numeroCompara);
        setbuf(stdin, NULL);
        Beep(800, 100);

        printf("Cartas com numero %d\n", numeroCompara);
        for (int i = 0; i < quantidadeCartas; i++)
        {
            if (numeroCompara == cartas[i].numero)
            {
                printf("%s: Numero %d\n", cartas[i].nome, cartas[i].numero);
            } // if comparar a economia escolhida com as cartas do deck
        } // for para passar por todas as cartas do deck
        break;

    case 6: // Pesquisa Letra

        printf("Digite a letra: ");
        fgets(letraCompara, 1, stdin);
        letraCompara[strcspn(letraCompara, "\n")] = '\0';
        setbuf(stdin, NULL);
        Beep(800, 100);

        // printf("Cartas com a letra %c\n", letraCompara);
        for (int i = 0; i < quantidadeCartas; i++)
        {
            if (cartas[i].letra == letraCompara[0])
            {
                printf("%s : Letra %c\n", cartas[i].nome, cartas[i].letra);
            } // if comparar a letra escolhida com as cartas do deck
        } // for para passar por todas as cartas do deck
        break;

    case 7: // Pesquisa Nome

        printf("Digite o nome da carta que deseja pesquisar: ");
        fgets(nomeCompara, 50, stdin);
        nomeCompara[strcspn(nomeCompara, "\n")] = '\0';
        setbuf(stdin, NULL);
        Beep(800, 100);

        for (int i = 0; i < quantidadeCartas; i++)
        {
            if (strcasecmp(nomeCompara, cartas[i].nome) == 0)
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
                printf("Velocidade Max: %.2f Km/h\n", cartas[i].end.velocidadeMaxima);
                printf("Quantidade maxima de maços de cigarros no porta malas: %.2f\n", cartas[i].end.quantidadeMacosCigarroPortamalas);

                break; // carta encontrada, nao precisa continuar o loop
            } // if comparar o nome escolhido com as cartas do deck
        } //// for para passar por todas as cartas do deck

    case 8: // Pesquisa Potencia

        printf("Digite a potencia: ");
        scanf("%f", &potenciaCompara);
        setbuf(stdin, NULL);
        Beep(800, 100);

        printf("Cartas com potencia %f \n", potenciaCompara);
        for (int i = 0; i < quantidadeCartas; i++)
        {
            if (potenciaCompara == cartas[i].end.potencia)
            {
                printf("%s: Potencia %.2f\n", cartas[i].nome, cartas[i].end.potencia);
            } // if comparar a economia escolhida com as cartas do deck
        } // for para passar por todas as cartas do deck
        break;

        if (!encontrado)
        {
            perror("Carta não encontrada!\n");
            Beep(300, 200);
            Beep(200, 250);
            break;
        } // if

    default:

        perror("ERRO! Opcao invalida\n");
        Beep(300, 200);
        Beep(200, 250);
        break;

    } // Switch

    return;
} // Pesquisar_atributos

/**
 *
 * @brief Pesquisa os atributos de cada carta
 *
 * O usuario pode por Pesquisa os atributos de cilindro, cigarros, veolcidade maxima, economia e potencia por um intervalo queele desejar *
 *
 * @param cartas Struct de cartas
 * @param quantidadeCartas Quantidade de cartas
 */
void PesquisarAtributosMaiorMenor(Cartas cartas[], int quantidadeCartas)
{
    int maior, menor;
    char letraMenor, letraMaior;
    int opcaoAtributoMenu2;

    printf("\n");
    printf("Pesquisar_atributos_MaiorMenor\n");
    // Menu 2 - Pesquisar por atributos, dentro de um intervalo
    // Atributos da carta
    printf("1 - Economia\n");
    printf("2 - Cilindros\n");
    printf("3 - VelocidadeMaxima\n");
    printf("4 - Quantidade macos de cigarro no portamalas\n");
    // Informacoes Gerais da Carta
    printf("5 - Numero\n");
    printf("6 - Letra\n");
    Beep(800, 100);

    do
    {
        // Requisitando
        printf("Digite sua opcao: ");
        setbuf(stdin, NULL);
        scanf("%d", &opcaoAtributoMenu2);
    } while (opcaoAtributoMenu2 < 1 || opcaoAtributoMenu2 > 6); // do while para aceitar somente 1 ao 6

    if (opcaoAtributoMenu2 == 6)
    {
        printf("Letras Maiusculas, entre A - D\n");

        do
        {
            printf("Digite a letra de menor valor: ");
            scanf("%c", &letraMenor);
            setbuf(stdin, NULL);
            Beep(800, 100);
        } while (letraMenor < 'A' || letraMenor > 'D'); // do while para aceitar somente A ao D

        do
        {
            printf("Digite a letra de maior valor: ");
            scanf("%c", &letraMaior);
            setbuf(stdin, NULL);
            Beep(800, 100);
        } while (letraMenor < 'A' || letraMenor > 'D'); // do while para aceitar somente A ao D

        printf("\n");
        for (int i = 0; i < quantidadeCartas; i++)
        {
            {
                printf("%s: %c\n", cartas[i].nome, cartas[i].letra);

            } // if
        } // for
    }
    else
    {

        // Definindo intervalo
        printf("Escolha o intervalo que deseja\n");
        printf("Digite o limite inferior: ");
        scanf("%d", &menor);
        setbuf(stdin, NULL);
        Beep(800, 100);

        printf("Digite o limite superior: ");
        scanf("%d", &maior);
        setbuf(stdin, NULL);
        Beep(800, 100);

        // Menu 2: Pesquisar por atributos, dentro de um intervalo
        switch (opcaoAtributoMenu2)
        {

        case 1: // Economia
            for (int i = 0; i < quantidadeCartas; i++)
            {
                if (cartas[i].end.economia >= menor && cartas[i].end.economia <= maior)
                {
                    printf("%s: Economia %.2f", cartas[i].nome, cartas[i].end.economia);
                    printf("\n");
                } // if

            } // For
            break;

        case 2: // Cilindros
            for (int i = 0; i < quantidadeCartas; i++)
            {
                if (cartas[i].end.cilindros >= menor && cartas[i].end.cilindros <= maior)
                {
                    printf("%s: Cilidros %d", cartas[i].nome, cartas[i].end.cilindros);
                    printf("\n");
                } // if
            } // For
            break;

        case 3: // Velocidade Maxima
            for (int i = 0; i < quantidadeCartas; i++)
            {
                if (cartas[i].end.velocidadeMaxima >= menor && cartas[i].end.velocidadeMaxima <= maior)
                {
                    printf("%s: Velocidade %.2f", cartas[i].nome, cartas[i].end.velocidadeMaxima);
                    printf("\n");
                } // if
            } // for
            break;

        case 4: // Macos de cigarros no porta malas
            for (int i = 0; i < quantidadeCartas; i++)
            {
                if (cartas[i].end.quantidadeMacosCigarroPortamalas >= menor && cartas[i].end.quantidadeMacosCigarroPortamalas <= maior)
                {
                    printf("%s: Quantidade Max. de cigarros no porta malas %.2f", cartas[i].nome, cartas[i].end.quantidadeMacosCigarroPortamalas);
                    printf("\n");
                } // if
            } // For
            break;

        case 5: // Numero
            for (int i = 0; i < quantidadeCartas; i++)
            {
                if (cartas[i].numero >= menor && cartas[i].numero <= maior)
                {
                    printf("%s:  Numero %d", cartas[i].nome, cartas[i].numero);
                    printf("\n");
                } // if
            } // For
            break;

        default:
            printf("Erro\n");
            Beep(300, 200);
            Beep(200, 250);
            break;
        } // Switch

    } // else

} // Pesquisar_atributos_MaiorMemor

/**
 * @brief Exibe todas as cartas e seus atributos
 *
 * Navega entre todas as cartas
 *
 * @param cartas Struct de cartas
 * @param quantidadeCartas quantidade de cartas
 */
void NavTodasCartas(Cartas cartas[], int quantidadeCartas)
{
    printf("\n");
    for (int i = 0; i < quantidadeCartas; i++)
    {
        // Informacoes gerais da carta
        printf("Carta: %s\n", cartas[i].nome);
        printf("Categoria: %c\n", cartas[i].letra);
        printf("Numero: %d\n", cartas[i].numero);
        printf("Super Trunfo: %s\n", cartas[i].super_trunfo ? "Sim" : "Não");

        // Atributos
        printf("Potencia: %.2fCv\n", cartas[i].end.potencia);
        printf("Economia: %.2f Litro/Km\n", cartas[i].end.economia);
        printf("Cilindros: %d\n", cartas[i].end.cilindros);
        printf("Velocidade Max: %.2f Km/h\n", cartas[i].end.velocidadeMaxima);
        printf("Quantidade maxima de macos de cigarros no porta malas: %.2f\n", cartas[i].end.quantidadeMacosCigarroPortamalas);

        printf("\n\n");
    } // for

} // nav_todas_cartas

/**
 * @brief Menu para vizualizar as cartas
 *
 * Submenus: Pesquisar por atributo, Persquisar por atributos dentro de um intervalo e navegar entre todas as cartas
 *
 * @param cartas Struct de cartas
 * @param quantidadeCartas Quantidade de cartas
 */

void VizualizaCarta(Cartas cartas[], int quantidadeCartas)
{
    // Menu que exibe as opções
    int opcaoMenu;
    printf("\n");
    printf("Buscar/Vizualizar cartas\n");
    printf("1 - Pesquisar por atributos\n");
    printf("2 - Pesquisar por atributos, dentro de um intervalo:\n");
    printf("3 - Navegar por todas as cartas\n");
    Beep(800, 100);

    do
    {
        // Requisitando Opcao
        printf("Digite a opção: ");
        scanf("%d", &opcaoMenu);
        setbuf(stdin, NULL);

    } while (opcaoMenu < 1 || opcaoMenu > 3); // do while para aceitar somente 1 ao 3

    switch (opcaoMenu)
    {
    case 1:
        PesquisaAtributos(cartas, quantidadeCartas); // Chama a  função que pesquisa por atributos
        break;
    case 2:
        PesquisarAtributosMaiorMenor(cartas, quantidadeCartas); // Chama a função que pesquisa por atributos dentro de um intervalo
        break;
    case 3:
        NavTodasCartas(cartas, quantidadeCartas); // Chama a função que navega entre todas as cartas
        break;
    default:
        printf("Opcao invalida\n");
        Beep(300, 200);
        Beep(200, 250);
        break;
    } // switch
} // VizualizaCarta

/**
 * @brief Exibe as estatísticas dos jogadores
 *
 * @param estatistica
 * @param quantidadeJogadores
 */
void MostrarEstatistica(Estatisticas *estatistica, int quantidadeJogadores)
{
    for (int i = 0; i < quantidadeJogadores; i++)
    {
        printf("Estatisticas: %s\n", estatistica[i].nome);
        printf("Partidas jogadas: %d\n", estatistica[i].partidasJogadas);
        printf("Vitórias: %d\n", estatistica[i].vitorias);
        printf("Taxa de vitória: %.2f%%\n", estatistica[i].taxaVitoria);
    } // For
    Beep(800, 100);
} // MostrarEstatistica

void IniciaConquistas(Conquista *conquistas)
{
    strcpy(conquistas[0].nome, "Apenas começando...");
    strcpy(conquistas[0].descricao, "Jogue sua primeira partida.");
    conquistas[0].condicao = 1;
    conquistas[0].desbloqueada = false;

    strcpy(conquistas[1].nome, "O gostinho da vitória");
    strcpy(conquistas[1].descricao, "Vença sua primeira partida.");
    conquistas[1].condicao = 1;
    conquistas[1].desbloqueada = false;

    strcpy(conquistas[2].nome, "Veterano do Super Trunfo");
    strcpy(conquistas[2].descricao, "Jogue 10 partidas.");
    conquistas[2].condicao = 10;
    conquistas[2].desbloqueada = false;

    strcpy(conquistas[3].nome, "Mestre do Super Trunfo");
    strcpy(conquistas[3].descricao, "Vença 10 partidas.");
    conquistas[3].condicao = 10;
    conquistas[3].desbloqueada = false;
    Beep(800, 200);
    Beep(1000, 200);
    Beep(1200, 200);
    Beep(1500, 300);

} // IniciaConquistas

/**
 * @brief Lê o arquivo salvo no computado de estatísticas ou cria caso não existir e
 * carrega as estatísticas do jogar na struct "estatistica"
 *
 * @param estatistica
 * @param nomeJogador
 * @param quantidadeJogadores
 */
void CarregaEstatistica(Estatisticas *estatistica, char nomeJogador[][50], int quantidadeJogadores)
{
    FILE *arquivo = fopen("estatisticas.dat", "rb"); // Abre o arquivo para leitura
    if (arquivo == NULL)
    {
        printf("\n");
        printf("\n");
        printf("Bem Vindo\n");
        printf("\n");
        printf("\n");
        printf("Arquivo de estatísticas não encontrado, criando arquivo...\n");

        arquivo = fopen("estatisticas.dat", "wb");    // Cria o arquivo para escrita
        for (int i = 0; i < quantidadeJogadores; i++) // Inicializa a struct com os valores padrão
        {
            strcpy(estatistica[i].nome, nomeJogador[i]);
            estatistica[i].partidasJogadas = 0;
            estatistica[i].vitorias = 0;
            estatistica[i].taxaVitoria = 0.0f;
            IniciaConquistas(estatistica[i].conquistas);
        } // For

        fwrite(estatistica, sizeof(Estatisticas), quantidadeJogadores, arquivo); // Escreve no arquivo binário caso já exista
        fclose(arquivo);
    }
    else
    {
        fread(estatistica, sizeof(Estatisticas), quantidadeJogadores, arquivo); // Lê o arquivo binário
        fclose(arquivo);

        for (int i = 0; i < quantidadeJogadores; i++)
        {
            strcpy(estatistica[i].nome, nomeJogador[i]);
        } // For
    } // If else
} // CarregaEstatistica

/**
 * @brief Salva as estatistica dos jogadores em um arquivo binário
 *
 * @param estatistica
 * @param quantidadeJogadores
 */
void SalvarEstatistica(Estatisticas *estatistica, int quantidadeJogadores)
{
    FILE *arquivo = fopen("estatisticas.dat", "wb");
    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo!");
        return;
    } // If

    fwrite(estatistica, sizeof(Estatisticas), quantidadeJogadores, arquivo);
    fclose(arquivo);
} // Salvar Estatistica

void MostrarRanking(Ranking *rank)
{
    printf("\n=== Ranking dos Jogadores ===\n");
    printf("----------------------------------------\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%2d. %-20s | Pontos: %5d\n", i + 1, rank[i].nome, rank[i].pontuacao);
    } // For

} // MostrarRanking

void CarregaRanking(Ranking *rank)
{
    FILE *arquivo = fopen("ranking.dat", "rb");

    // Se o arquivo não existe, cria um novo
    if (arquivo == NULL)
    {
        printf("Arquivo do ranking não encontrado, criando arquivo...\n");

        arquivo = fopen("ranking.dat", "wb");
        if (arquivo == NULL)
        {
            perror("Erro ao criar o arquivo!");
            return;
        } // if

        // Inicializa o ranking com valores padrão
        for (int i = 0; i < 10; i++)
        {
            strcpy(rank[i].nome, "Vazio");
            rank[i].pontuacao = 0;
        } // for

        fwrite(rank, sizeof(Ranking), 10, arquivo);
        fclose(arquivo);
    }
    else
    {

        fread(rank, sizeof(Ranking), 10, arquivo);
        fclose(arquivo);
    } // else
} // CarregaRanking

void SalvarRanking(Ranking *rank)
{
    FILE *arquivo = fopen("ranking.dat", "wb");
    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo!");
        Beep(300, 200);
        Beep(200, 250);
        return;
    } // If

    int gravados = fwrite(rank, sizeof(Ranking), 10, arquivo);
    fclose(arquivo);

    if (gravados != 10)
    {
        printf("Erro ao gravar o arquivo!\n");
    } // If
} // SalvarRanking

int AddJogadorRanking(Ranking *rank, char *nome, int pontuacao)
{
    if (pontuacao < 0)
        return -1;

    for (int i = 0; i < 10; i++)
    {
        if (strcmp(rank[i].nome, nome) == 0)
        {
            if (pontuacao > rank[i].pontuacao)
            {
                rank[i].pontuacao = pontuacao;
                while (i > 0 && rank[i].pontuacao > rank[i - 1].pontuacao)
                {
                    Ranking temp = rank[i];
                    rank[i] = rank[i - 1];
                    rank[i - 1] = temp;
                    i--;
                } // While
            } // If
            return i;
        } // If
    } // For

    Ranking novoJogador;
    strncpy(novoJogador.nome, nome, 29);
    novoJogador.nome[29] = '\0';
    novoJogador.pontuacao = pontuacao;

    int pos = 9;
    while (pos >= 0 && pontuacao > rank[pos].pontuacao)
    {
        rank[pos + 1] = rank[pos];
        pos--;
    } // While

    if (pos != 9)
    {
        rank[pos + 1] = novoJogador;
        return pos + 1;
    } // If
    return -1;
} // AddJogadorRanking

void VerificaConquistas(Estatisticas *estatistica)
{
    if (estatistica->partidasJogadas >= estatistica->conquistas[0].condicao &&
        !estatistica->conquistas[0].desbloqueada)
    {
        estatistica->conquistas[0].desbloqueada = true;
        printf("%s desbloqueou a conquista: %s!\n", estatistica->nome, estatistica->conquistas[0].nome);
        Beep(800, 100);
    } // if

    if (estatistica->vitorias >= estatistica->conquistas[1].condicao && !estatistica->conquistas[1].desbloqueada)
    {
        estatistica->conquistas[1].desbloqueada = true;
        printf("%s desbloqueou a conquista: %s!\n", estatistica->nome, estatistica->conquistas[1].nome);
        Beep(800, 100);
    } // if

    if (estatistica->partidasJogadas >= estatistica->conquistas[2].condicao && !estatistica->conquistas[2].desbloqueada)
    {
        estatistica->conquistas[2].desbloqueada = true;
        printf("%s desbloqueou a conquista: %s!\n", estatistica->nome, estatistica->conquistas[2].nome);
        Beep(800, 100);
    } // if

    if (estatistica->vitorias >= estatistica->conquistas[3].condicao && !estatistica->conquistas[3].desbloqueada)
    {
        estatistica->conquistas[3].desbloqueada = true;
        printf("%s desbloqueou a conquista: %s!\n", estatistica->nome, estatistica->conquistas[3].nome);
        Beep(800, 100);
    } // if
    return;
} // VerificaConquistas

/**
 * @brief salvaConquista
 *
 * @param conquistas
 */
void SalvarConquistas(Conquista *conquistas)
{
    FILE *arquivo = fopen("conquistas.dat", "wb");
    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo!");
        Beep(300, 200);
        Beep(200, 250);
        return;
    } // If

    fwrite(conquistas, sizeof(Conquista), 4, arquivo);
    fclose(arquivo);
    return;
} // SalvarConquistas

/**
 * @brief CarregaConquistas
 *
 * @param conquistas
 */
void CarregaConquistas(Conquista *conquistas)
{
    FILE *arquivo = fopen("conquistas.dat", "rb");

    // Se o arquivo não existe, cria um novo
    if (arquivo == NULL)
    {
        IniciaConquistas(conquistas);
        SalvarConquistas(conquistas);
        return;
    } // If
    fread(conquistas, sizeof(Conquista), 4, arquivo);
    fclose(arquivo);
    return;
} // CarregaConquistas

void MostrarConquistas(Estatisticas *estatistica, int quantJogadores)
{
    char nomeBusca[30];
    int encontrado = 0;

    printf("Digite o nome do jogador: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    setbuf(stdin, NULL);
    Beep(800, 100);

    for (int i = 0; i < quantJogadores; i++)
    {
        if (strcmp(estatistica[i].nome, nomeBusca) == 0)
        {
            printf("\n=== Conquistas de %s ===\n", estatistica[i].nome);
            for (int l = 0; l < 4; l++)
            {
                printf("%s\n", estatistica[i].conquistas[l].nome);
                printf("Descrição: %s\n", estatistica[i].conquistas[l].descricao);
                printf("Status: %s\n", estatistica[i].conquistas[l].desbloqueada ? "Desbloqueada" : "Bloqueada");
                printf("\n");
            } // For
            encontrado = 1;
            break;
        } // If
    } // For

    if (!encontrado)
    {
        printf("Jogador não encontrado!\n");
    } // If
    return;
} // MostrarConquistas

/**
 * @brief Carrega as cartas do arquivo csv
 *
 * Le o arquivo 'cartas.csv'
 *
 * @param cartas  Ponteiro duplo para a Struct de cartas
 * @param quantidadeCartas Ponteiro para a quantidade de cartas
 */
void CarregarCartas(Cartas **cartas, int *quantidadeCartas)
{
    FILE *arquivoPointer = fopen("cartas.csv", "r"); // Abre o arquivo CSV para leitura
    if (arquivoPointer == NULL)
    {
        perror("Erro ao abrir o arquivo CSV para leitura.");
        Beep(300, 200);
        Beep(200, 250);
        exit(1);
    } // If

    // Conta o número de linhas no arquivo
    char buffer[1024];
    int linhas = 0;
    while (fgets(buffer, sizeof(buffer), arquivoPointer))
    {
        if (buffer[0] != '\n' && buffer[0] != '\0')
        {
            linhas++;
        } // If
    } // While

    rewind(arquivoPointer); // realoca o ponteiro para o inicio

    // Aloca memória para as cartas
    *cartas = malloc(linhas * sizeof(Cartas));
    if (*cartas == NULL)
    {
        perror("ERRO! Nao foi possivel alocar memória\n.");
        Beep(300, 200);
        Beep(200, 250);
        exit(1);
    } // if

    // Lê os dados do arquivo CSV
    *quantidadeCartas = 0;
    while (fgets(buffer, sizeof(buffer), arquivoPointer))
    {
        if (buffer[0] == '\n' || buffer[0] == '\0') // Ignora linhas em branco
        {
            continue;
        } // if

        Cartas *cartaAtual = &(*cartas)[*quantidadeCartas]; // Struct para a carta atual

        // Lê os dados da linha
        char superTrunfoTexto[6];
        sscanf(buffer, "%49[^,],%c,%d,%5[^,],%f,%f,%d,%f,%f",
               cartaAtual->nome,
               &cartaAtual->letra,
               &cartaAtual->numero,
               superTrunfoTexto,
               &cartaAtual->end.potencia,
               &cartaAtual->end.economia,
               &cartaAtual->end.cilindros,
               &cartaAtual->end.velocidadeMaxima,
               &cartaAtual->end.quantidadeMacosCigarroPortamalas);

        sscanf(buffer, "%49[^,],%c,%d,%5[^,],%f,%f,%d,%f,%f",
               cartaAtual->nome,
               &cartaAtual->letra,
               &cartaAtual->numero,
               superTrunfoTexto,
               &cartaAtual->end.potencia,
               &cartaAtual->end.economia,
               &cartaAtual->end.cilindros,
               &cartaAtual->end.velocidadeMaxima,
               &cartaAtual->end.quantidadeMacosCigarroPortamalas);

        // Converte "true"/"false" para booleano
        if (strcmp(superTrunfoTexto, "true") == 0)
        {
            cartaAtual->super_trunfo = true;
        } // else
        else if (strcmp(superTrunfoTexto, "false") == 0)
        {
            cartaAtual->super_trunfo = false;
        } // else
        else
        {
            fprintf(stderr, "Erro: valor inválido para super_trunfo: %s\n", superTrunfoTexto);
            Beep(300, 200);
            Beep(200, 250);
            exit(1);
        } // else

        (*quantidadeCartas)++;
    } // while

    fclose(arquivoPointer);
    return;
} // carregarCartas

/**
 * @brief Menu para gerenciamento das cartas
 *
 * Submenus: inserir, alterar e deletar cartas
 *
 * @param cartas Struct de cartas
 * @param quantidadeCartas Numero total de cartas
 */
void SubMenuGerenciaCartas(Cartas cartas[], int quantidadeCartas)
{
    int subOpcao; // Opção do submenu
    do
    {
        printf("Gerenciar Cartas:\n");
        printf("1 - Inserir Carta\n");
        printf("2 - Alterar Carta\n");
        printf("3 - Deletar Carta\n");
        printf("4 - Sair\n");

        printf("Escolha uma opção: ");
        scanf("%d", &subOpcao);
        Beep(800, 100);

        switch (subOpcao)
        {
        case 1:
            InserirCarta(&cartas, &quantidadeCartas); // Chama a função de inserir carta
            break;
        case 2:
            AlterarCartas(cartas, &quantidadeCartas); // Chama a função de alterar carta
            break;
        case 3:
            DeletarCartas(&cartas, &quantidadeCartas); // Chama a função de deletar carta
            break;
        case 4:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao Invalida\n");
        } // Switch

    } while (subOpcao != 4); // do while para aceitar somente 4 opções

    return;
} // Sub Menu Gererencir cartas

/**
 * @brief Escreve as informacoes das cartas no arquivo csv
 *
 * Salva dados das cartas no arquivo csv
 *
 * @param cartasFonte Ponteiro para struct
 * @param quantidadeCartas Quantidade de cartas no csv
 */
void SorteiaNumeros(int quantJogadores, int quantCartasJogador, int **cartasSorteadas)
{
    int quantidadeCartas = quantCartasJogador * quantJogadores;
    int *sorteadas = calloc(quantidadeCartas, sizeof(int)); // Aloca e inicializa com 0
    if (sorteadas == NULL)
    {
        perror("ERRO! Não foi possível alocar memória para sorteadas.\n");
        Beep(300, 200);
        Beep(200, 250);
        exit(1);
    } // if

    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    for (int jogador = 0; jogador < quantJogadores; jogador++)
    {
        for (int carta = 0; carta < quantCartasJogador; carta++)
        {
            int numero;
            do
            {
                numero = (rand() % quantidadeCartas); // Sorteia um número entre 0 e quantidadeCartas - 1
            } while (sorteadas[numero]); // Verifica se a carta já foi sorteada

            cartasSorteadas[jogador][carta] = numero; // Atribui a carta ao jogador
            sorteadas[numero] = 1;                    // Marca a carta como sorteada
        } // For menor
    } // For maior
    free(sorteadas);
    return;
} // SorteiaNumeros

/**
 * @brief Toca os efeitos sonoros durante a gameplay
 *
 * @param cartas Struct de cartas
 * @param cartaAtual Indice da carta
 */
void tocaEfeitoSonoros(Cartas cartas[], int cartaAtual)
{

    for (int i = 0; i < 3; i++)
    {
        if (strcasecmp(cartas[cartaAtual].nome, sons[i].nome) == 0)
        {
            PlaySound(sons[i].som, NULL, SND_FILENAME | SND_ASYNC);
            break;
        } // if
    } // for
    return;
} // tocaEfeitoSonoros

/**
 * @brief  Gameplay, umas das funcoes principais do programa, responsavel pela gameplay em local
 *
 * @param quantJogadores
 * @param cartas
 * @param quantidadeCartas
 * @param nomesJogadores
 * @param estatistica
 * @param rank
 */
void Gameplay(int quantJogadores, Cartas cartas[], int quantidadeCartas, char nomesJogadores[][50], Estatisticas *estatistica, Ranking *rank)
{
    float maiorValor = -1;
    int vencedorRodada = -1;
    char atributoEscolhido[50];
    int cartasPorJogador = quantidadeCartas / quantJogadores;

    int **cartasSorteadas = (int **)calloc(quantJogadores, sizeof(int *));
    for (int l = 0; l < quantJogadores; l++)
    {
        cartasSorteadas[l] = (int *)calloc(quantidadeCartas, sizeof(int));
    } // For

    Conquista conquistas[4];
    CarregaConquistas(conquistas);
    SorteiaNumeros(quantJogadores, cartasPorJogador, cartasSorteadas);

    printf("\nInício do jogo com %d jogadores e %d cartas por jogador.\n", quantJogadores, cartasPorJogador);
    Beep(800, 100);
    // Loop do jogo principal
    bool jogoAtivo = true;
    int jogadorAtual = 0;
    int *cartasPorJogadorAtual = (int *)calloc(quantJogadores, sizeof(int));
    for (int i = 0; i < quantJogadores; i++)
    {
        cartasPorJogadorAtual[i] = cartasPorJogador;
    } // For

    while (jogoAtivo)
    {
        maiorValor = -1;
        vencedorRodada = 1;
        bool empate;
        do
        {
            empate = false;

            printf("\n=== Rodada do Jogador %s ===\n", nomesJogadores[jogadorAtual]);

            // Mostrar as cartas da vez de todos os jogadores
            printf("Cartas da vez:\n");
            for (int i = 0; i < quantJogadores; i++)
            {
                if (cartasPorJogadorAtual[i] > 0)
                {
                    int cartaAtual = cartasSorteadas[i][0];
                    printf("Jogador %s:\n", nomesJogadores[i]);
                    printf(" Nome: %s\n", cartas[cartaAtual].nome);
                    printf(" Potência: %.2f Cv \n", cartas[cartaAtual].end.potencia);
                    printf(" Economia: %.2f Litros/km\n", cartas[cartaAtual].end.economia);
                    printf(" Cilindros: %d\n", cartas[cartaAtual].end.cilindros);
                    printf(" Velocidade Máxima: %.2f km/h\n", cartas[cartaAtual].end.velocidadeMaxima);
                    printf(" Cigarros no Porta-malas: %.2f\n\n", cartas[cartaAtual].end.quantidadeMacosCigarroPortamalas);
                    tocaEfeitoSonoros(cartas, cartaAtual);
                }
                else
                {
                    printf("Jogador %s: Sem cartas!\n", nomesJogadores[i]);
                }
            } // f

            setbuf(stdin, NULL);
            printf("Escolha um atributo: (potencia, economia, cilindros, velocidade, cigarros): ");
            fgets(atributoEscolhido, sizeof(atributoEscolhido), stdin);
            atributoEscolhido[strcspn(atributoEscolhido, "\n")] = '\0';
            Beep(800, 100);

            maiorValor = -1;
            vencedorRodada = -1;

            // Comparar o atributo escolhido entre os jogadores
            for (int i = 0; i < quantJogadores; i++)
            {
                int cartaAtual = cartasSorteadas[i][0]; // Sempre comparar a primeira carta de cada jogador
                float valorAtributo = 0;

                // Cheat
                //  Se o jogador digitou o cheat, processa-o imediatamente
                if (strcmp(atributoEscolhido, "ganhou") == 0)
                {
                    vencedorRodada = jogadorAtual;
                    empate = false;
                    jogoAtivo = false;
                    break; // Sai do loop for imediatamente
                }
                // Fim cheat

                if (strcmp(atributoEscolhido, "potencia") == 0)
                {
                    valorAtributo = cartas[cartaAtual].end.potencia;
                } // if
                else if (strcmp(atributoEscolhido, "economia") == 0)
                {
                    valorAtributo = cartas[cartaAtual].end.economia;
                } // else if
                else if (strcmp(atributoEscolhido, "cilindros") == 0)
                {
                    valorAtributo = cartas[cartaAtual].end.cilindros;
                } // else if
                else if (strcmp(atributoEscolhido, "velocidade") == 0)
                {
                    valorAtributo = cartas[cartaAtual].end.velocidadeMaxima;
                } // else if
                else if (strcmp(atributoEscolhido, "cigarros") == 0)
                {
                    valorAtributo = cartas[cartaAtual].end.quantidadeMacosCigarroPortamalas;
                } // else if
                else
                {
                    printf("Atributo inválido! Escolha novamente.\n");
                    Beep(300, 200);
                    Beep(200, 250);
                    empate = true;
                    break;
                } // else

                if (valorAtributo > maiorValor)
                {
                    maiorValor = valorAtributo;
                    vencedorRodada = i;
                    empate = false;
                } // if
                else if (valorAtributo == maiorValor)
                {
                    empate = true;
                    printf("EMPATE! ESCOLHA OUTRO ATRIBUTO\n");
                    Beep(300, 200);
                    Beep(200, 250);
                    break;
                } // else if
            } // for
        } while (empate);

        if (vencedorRodada != -1)
        {
            printf("\nJogador %s venceu a rodada com o maior %s (%.2f)!\n", nomesJogadores[vencedorRodada], atributoEscolhido, maiorValor);
            Beep(800, 200);
            Beep(1000, 200);
            Beep(1200, 200);
            Beep(1500, 300);

            // Transferir cartas para o vencedor
            for (int i = 0; i < quantJogadores; i++)
            {
                if (i != vencedorRodada && cartasPorJogadorAtual[i] > 0)
                {
                    // Transferir a carta do perdedor para o vencedor
                    cartasSorteadas[vencedorRodada][cartasPorJogadorAtual[vencedorRodada]] = cartasSorteadas[i][0];
                    cartasPorJogadorAtual[vencedorRodada]++;
                } // if
            } // for

            // Remover a carta usada de cada jogador
            for (int i = 0; i < quantJogadores; i++)
            {
                if (i != vencedorRodada) // Apenas para os perdedores
                {
                    // Desloca as cartas para a esquerda, removendo a carta usada
                    for (int j = 0; j < cartasPorJogadorAtual[i] - 1; j++)
                    {
                        cartasSorteadas[i][j] = cartasSorteadas[i][j + 1];
                    } // for
                    cartasPorJogadorAtual[i]--; // Atualiza o número de cartas do perdedor
                } // if
            } // for

            // Mover a carta do vencedor para o final do deck
            int cartaVencedor = cartasSorteadas[vencedorRodada][0]; // Guarda a carta usada pelo vencedor
            for (int j = 0; j < cartasPorJogadorAtual[vencedorRodada] - 1; j++)
            {
                cartasSorteadas[vencedorRodada][j] = cartasSorteadas[vencedorRodada][j + 1];
            } // for
            cartasSorteadas[vencedorRodada][cartasPorJogadorAtual[vencedorRodada] - 1] = cartaVencedor; // Coloca no final

            // Verificar condição de vitória
            if (cartasPorJogadorAtual[vencedorRodada] == quantidadeCartas)
            {
                printf("\nParabéns, %s! Você venceu o jogo!\n", nomesJogadores[vencedorRodada]);
                Beep(800, 200);
                Beep(1000, 200);
                Beep(1200, 200);
                Beep(1500, 300);
                estatistica[vencedorRodada].vitorias++;

                for (int i = 0; i < quantJogadores; i++)
                {
                    estatistica[i].partidasJogadas++;
                } // For

                for (int i = 0; i < quantJogadores; i++)
                {
                    if (estatistica[i].partidasJogadas > 0)
                    {
                        estatistica[i].taxaVitoria =
                            ((float)estatistica[i].vitorias / estatistica[i].partidasJogadas) * 100;
                    } // if
                    else
                    {
                        estatistica[i].taxaVitoria = 0.0f;
                    } // else
                } // For
                jogoAtivo = false;
            } // If

        } // if maior

    } // while principal

    for (int i = 0; i < quantJogadores; i++)
    {
        VerificaConquistas(&estatistica[i]);
    } // For

    SalvarEstatistica(estatistica, quantJogadores);
    SalvarConquistas(conquistas);

    for (int i = 0; i < quantJogadores; i++)
    {
        AddJogadorRanking(rank, nomesJogadores[vencedorRodada], estatistica[vencedorRodada].vitorias);
    } // For

    SalvarRanking(rank);

    // Free
    for (int i = 0; i < quantJogadores; i++)
    {
        free(cartasSorteadas[i]);
    }
    free(cartasSorteadas);
    free(cartasPorJogadorAtual);

    return;

} // while

/**
 * @brief Retorna uma escolha aleatoria do bot
 * 
 * @return char* 
 */
char *AtributoBot()
{
    static char atributo[50];
    // Inicializa o gerador de números aleatórios com a semente baseada no tempo atual
    srand(time(NULL));

    // Gera um número aleatório entre 1 e 5
    int numAleatorio = (rand() % 5) + 1;

    if (numAleatorio == 1)
    {
        strcpy(atributo, "potencia"); // potencia, economia, cilindros, velocidade, cigarros
    }
    else if (numAleatorio == 2)
    {
        strcpy(atributo, "economia");
    }
    else if (numAleatorio == 3)
    {
        strcpy(atributo, "cilindros");
    }
    else if (numAleatorio == 4)
    {
        strcpy(atributo, "velocidade");
    }
    else if (numAleatorio == 5)
    {
        strcpy(atributo, "cigarros");
    }
    printf("bot escolhe atributo: %s\n", atributo);
    return atributo;
} // GameplayBot

/**
 * @brief  GameplayBot, umas das funcoes principais do programa, responsavel pela gameplay com o bot
 *
 * @param quantJogadores
 * @param cartas
 * @param quantidadeCartas
 * @param nomesJogadores
 * @param estatistica
 * @param rank
 */
void GameplayBot(int quantJogadores, Cartas cartas[], int quantidadeCartas, char nomesJogadores[][50], Estatisticas *estatistica, Ranking *rank)
{
    float maiorValor = -1;
    int vencedorRodada = -1;
    char atributoEscolhido[50];
    int cartasPorJogador = quantidadeCartas / 2;
    int numrodada = 1;

    int **cartasSorteadas = (int **)calloc(quantJogadores, sizeof(int *));
    for (int l = 0; l < quantJogadores; l++)
    {
        cartasSorteadas[l] = (int *)calloc(quantidadeCartas, sizeof(int));
    } // For

    Conquista conquistas[4];
    CarregaConquistas(conquistas);
    SorteiaNumeros(quantJogadores, cartasPorJogador, cartasSorteadas);

    printf("\nInício do jogo com o BOT e %d cartas por jogador.\n", cartasPorJogador);
    Beep(800, 100);
    // Loop do jogo principal
    bool jogoAtivo = true;
    int jogadorAtual = 0;
    int *cartasPorJogadorAtual = (int *)calloc(quantJogadores, sizeof(int));
    for (int i = 0; i < quantJogadores; i++)
    {
        cartasPorJogadorAtual[i] = cartasPorJogador;
    } // For

    while (jogoAtivo)
    {
        maiorValor = -1;
        vencedorRodada = 1;
        bool empate;
        do
        {
            empate = false;

            printf("\n=== Rodada %d do Jogador %s ===\n", numrodada, nomesJogadores[jogadorAtual]);

            // Mostrar as cartas da vez de todos os jogadores
            printf("Cartas da vez:\n");
            for (int i = 0; i < quantJogadores; i++)
            {
                if (cartasPorJogadorAtual[i] > 0)
                {
                    int cartaAtual = cartasSorteadas[i][0];
                    printf("Jogador %s:\n", nomesJogadores[i]);
                    printf(" Nome: %s\n", cartas[cartaAtual].nome);
                    printf(" Potência: %.2f Cv \n", cartas[cartaAtual].end.potencia);
                    printf(" Economia: %.2f Litros/km\n", cartas[cartaAtual].end.economia);
                    printf(" Cilindros: %d\n", cartas[cartaAtual].end.cilindros);
                    printf(" Velocidade Máxima: %.2f km/h\n", cartas[cartaAtual].end.velocidadeMaxima);
                    printf(" Cigarros no Porta-malas: %.2f\n\n", cartas[cartaAtual].end.quantidadeMacosCigarroPortamalas);
                    tocaEfeitoSonoros(cartas, cartaAtual);
                }
                else
                {
                    printf("Jogador %s: Sem cartas!\n", nomesJogadores[i]);
                }
            } // fpr


            if (strcmp(nomesJogadores[jogadorAtual], nomesJogadores[0]) == 0)
            {
                printf("Jogador vai escolher...\n");
                setbuf(stdin, NULL);
                printf("Escolha um atributo: (potencia, economia, cilindros, velocidade e cigarros): ");
                fgets(atributoEscolhido, sizeof(atributoEscolhido), stdin);
                atributoEscolhido[strcspn(atributoEscolhido, "\n")] = '\0';
                Beep(800, 100);
                // else(

                // else(strcmp(nomesJogadores[jogadorAtual], nomesJogadores[0]) == 0)
            }
            else 
            {
                printf("Bot vai escolher...\n");
                Sleep(2000);  // Espera 3 segundo
                strncpy(atributoEscolhido, AtributoBot(), sizeof(atributoEscolhido) - 1);
                atributoEscolhido[sizeof(atributoEscolhido) - 1] = '\0'; // Garante terminação da string
                printf("Atributo: %s\n", atributoEscolhido);
                Sleep(2000);
            }

            maiorValor = -1;
            vencedorRodada = -1;
            // Comparar o atributo escolhido entre os jogadores
            for (int i = 0; i < quantJogadores; i++)
            {
                int cartaAtual = cartasSorteadas[i][0]; // Sempre comparar a primeira carta de cada jogador
                float valorAtributo = 0;

                // Cheat
                //  Se o jogador digitou o cheat, processa-o imediatamente
                if (strcmp(atributoEscolhido, "ganhou") == 0)
                {
                    vencedorRodada = jogadorAtual;
                    empate = false;
                    jogoAtivo = false;
                    break; // Sai do loop for imediatamente
                }
                // Fim cheat
                if (strcmp(atributoEscolhido, "potencia") == 0)
                {
                    valorAtributo = cartas[cartaAtual].end.potencia;
                } // if
                else if (strcmp(atributoEscolhido, "economia") == 0)
                {
                    valorAtributo = cartas[cartaAtual].end.economia;
                } // else if
                else if (strcmp(atributoEscolhido, "cilindros") == 0)
                {
                    valorAtributo = cartas[cartaAtual].end.cilindros;
                } // else if
                else if (strcmp(atributoEscolhido, "velocidade") == 0)
                {
                    valorAtributo = cartas[cartaAtual].end.velocidadeMaxima;
                } // else if
                else if (strcmp(atributoEscolhido, "cigarros") == 0)
                {
                    valorAtributo = cartas[cartaAtual].end.quantidadeMacosCigarroPortamalas;
                } // else if
                else
                {
                    printf("Atributo inválido! Escolha novamente.\n");
                    Beep(300, 200);
                    Beep(200, 250);
                    empate = true;
                    break;
                } // else
                if (valorAtributo > maiorValor)
                {
                    maiorValor = valorAtributo;
                    vencedorRodada = i;
                    empate = false;
                } // if
                else if (valorAtributo == maiorValor)
                {
                    empate = true;
                    printf("EMPATE! ESCOLHA OUTRO ATRIBUTO\n");
                    Beep(300, 200);
                    Beep(200, 250);
                    break;
                } // else if
            } // for
            numrodada++;
        } while (empate);
        if (vencedorRodada != -1)
        {
            printf("\nJogador %s venceu a rodada com o maior %s (%.2f)!\n", nomesJogadores[vencedorRodada], atributoEscolhido, maiorValor);
            Beep(800, 200);
            Beep(1000, 200);
            Beep(1200, 200);
            Beep(1500, 300);

            // Transferir cartas para o vencedor
            for (int i = 0; i < quantJogadores; i++)
            {
                if (i != vencedorRodada && cartasPorJogadorAtual[i] > 0)
                {
                    // Transferir a carta do perdedor para o vencedor
                    cartasSorteadas[vencedorRodada][cartasPorJogadorAtual[vencedorRodada]] = cartasSorteadas[i][0];
                    cartasPorJogadorAtual[vencedorRodada]++;
                } // if
            } // for
            // Remover a carta usada de cada jogador
            for (int i = 0; i < quantJogadores; i++)
            {
                if (i != vencedorRodada) // Apenas para os perdedores
                {
                    // Desloca as cartas para a esquerda, removendo a carta usada
                    for (int j = 0; j < cartasPorJogadorAtual[i] - 1; j++)
                    {
                        cartasSorteadas[i][j] = cartasSorteadas[i][j + 1];
                    } // for
                    cartasPorJogadorAtual[i]--; // Atualiza o número de cartas do perdedor
                } // if
            } // for
            // Mover a carta do vencedor para o final do deck
            int cartaVencedor = cartasSorteadas[vencedorRodada][0]; // Guarda a carta usada pelo vencedor
            for (int j = 0; j < cartasPorJogadorAtual[vencedorRodada] - 1; j++)
            {
                cartasSorteadas[vencedorRodada][j] = cartasSorteadas[vencedorRodada][j + 1];
            } // for
            cartasSorteadas[vencedorRodada][cartasPorJogadorAtual[vencedorRodada] - 1] = cartaVencedor; // Coloca no final

            // Verificar condição de vitória
            if (cartasPorJogadorAtual[vencedorRodada] == quantidadeCartas)
            {
                printf("\nParabéns, %s! Você venceu o jogo!\n", nomesJogadores[vencedorRodada]);
                
                Beep(800, 200);
                Beep(1000, 200);
                Beep(1200, 200);
                Beep(1500, 300);
                estatistica[vencedorRodada].vitorias++;
                printf("nome atual %s\n", nomesJogadores[jogadorAtual]);
                for (int i = 0; i < quantJogadores; i++)
                {
                    estatistica[i].partidasJogadas++;
                } // For

                for (int i = 0; i < quantJogadores; i++)
                {
                    if (estatistica[i].partidasJogadas > 0)
                    {
                        estatistica[i].taxaVitoria =
                            ((float)estatistica[i].vitorias / estatistica[i].partidasJogadas) * 100;
                    } // if
                    else
                    {
                        estatistica[i].taxaVitoria = 0.0f;
                    } // else
                } // For
                jogoAtivo = false;
            } // If
           if (jogoAtivo)
           {
            jogadorAtual = vencedorRodada;
           }
           
        } // if maior
    } // while principal

    for (int i = 0; i < quantJogadores; i++)
    {
        VerificaConquistas(&estatistica[i]);
    } // For

    SalvarEstatistica(estatistica, quantJogadores);
    SalvarConquistas(conquistas);

    for (int i = 0; i < quantJogadores; i++)
    {
        AddJogadorRanking(rank, nomesJogadores[vencedorRodada], estatistica[vencedorRodada].vitorias);
    } // For

    SalvarRanking(rank);

    // Free
    for (int i = 0; i < quantJogadores; i++)
    {
        free(cartasSorteadas[i]);
    }
    free(cartasSorteadas);
    free(cartasPorJogadorAtual);

    return;

} // while

void jogarServidor(SOCKET socketClientes[], int numJogadores, Cartas cartas[], int quantidadeCartas, Estatisticas *estatistica, Ranking *rank)
{
    int rodada = 1;
    char nomesJogadores[numJogadores][50]; // Nome dos jogadores
    int cartasPorJogador = quantidadeCartas / numJogadores;
    char buffer_atributo[TAMANHO_BUFFER];

    // Receber os nomes dos jogadores
    for (int i = 0; i < numJogadores; i++)
    {
        if (recv(socketClientes[i], nomesJogadores[i], sizeof(nomesJogadores[i]), 0) <= 0)
        {
            printf("Erro ao receber nome do jogador %d\n", i + 1);
            return;
        } // if
        printf("Jogador %d conectado: %s\n", i + 1, nomesJogadores[i]);
        Beep(800, 100);
    } // for

    // Inicializa as estatísticas dos jogadores
    for (int i = 0; i < numJogadores; i++)
    {
        strcpy(estatistica[i].nome, nomesJogadores[i]);
    } // for

    // Sorteia as cartas para cada jogador
    int **cartasSorteadas = (int **)calloc(numJogadores, sizeof(int *));
    for (int l = 0; l < numJogadores; l++)
    {
        cartasSorteadas[l] = (int *)calloc(quantidadeCartas + 1, sizeof(int)); // Alocar espaço para todas as cartas
    } // for

    Conquista conquistas[4];
    CarregaConquistas(conquistas);

    // Sorteia as cartas para cada jogador
    SorteiaNumeros(numJogadores, cartasPorJogador, cartasSorteadas);

    // Aloca e inicializa o número de cartas por jogador
    int *cartasPorJogadorAtual = (int *)calloc(numJogadores, sizeof(int));
    for (int i = 0; i < numJogadores; i++)
    {
        cartasPorJogadorAtual[i] = cartasPorJogador;
    }

    // Loop do jogo principal
    bool jogoAtivo = true;
    int jogadorAtual = 0;
    int vencedorRodada = -1;
    char nomeJogadorVez[50];
    int jogadoresAtivos = numJogadores;
    //bool empate = false;

    while (jogoAtivo)
    {
       // empate = false;
        int maiorValor = -1;

        // Enviar o jogador da vez para todos os clientes ativos
        for (int i = 0; i < numJogadores; i++)
        {
            if (socketClientes[i] != INVALID_SOCKET)
            {
                if (send(socketClientes[i], (char *)&jogadorAtual, sizeof(int), 0) <= 0)
                {
                    printf("Erro ao enviar o jogador atual para o jogador %d\n", i + 1);
                    Beep(300, 200);
                    Beep(200, 250);
                    return;
                } // if

                strncpy(nomeJogadorVez, nomesJogadores[jogadorAtual], sizeof(nomeJogadorVez) - 1);
                nomeJogadorVez[sizeof(nomeJogadorVez) - 1] = '\0';
                if (send(socketClientes[i], nomeJogadorVez, sizeof(nomeJogadorVez), 0) <= 0)
                {
                    printf("Erro ao enviar o nome do jogador atual para o jogador %d\n", i + 1);
                    Beep(300, 200);
                    Beep(200, 250);
                    return;
                } // if
                printf("[Servidor] Enviando jogador atual: %d, nome: %s\n", jogadorAtual, nomeJogadorVez);
                Beep(800, 100);
            } // if
        } // for

        // Enviar o número de cartas para cada jogador
        for (int i = 0; i < numJogadores; i++)
        {
            if (socketClientes[i] != INVALID_SOCKET)
            {
                if (send(socketClientes[i], (char *)&cartasPorJogadorAtual[i], sizeof(int), 0) <= 0)
                {
                    printf("Erro ao enviar o número de cartas para o jogador %d\n", i + 1);
                    Beep(300, 200);
                    Beep(200, 250);
                    return;
                } // if
            } // for
        } // for

        // Enviar as cartas para cada jogador
        for (int i = 0; i < numJogadores; i++)
        {
            if (socketClientes[i] != INVALID_SOCKET)
            {
                for (int j = 0; j < cartasPorJogadorAtual[i]; j++)
                {
                    int cartaAtual = cartasSorteadas[i][j];
                    if (send(socketClientes[i], (char *)&cartas[cartaAtual], sizeof(Cartas), 0) <= 0)
                    {
                        printf("Erro ao enviar a carta %d para o jogador %d\n", j + 1, i + 1);
                        Beep(300, 200);
                        Beep(200, 250);
                        return;
                    } // if
                } // for
            } // if
        } // for

        // Receber a escolha de atributo do jogador atual
        if (recv(socketClientes[jogadorAtual], buffer_atributo, sizeof(buffer_atributo), 0) <= 0)
        {
            printf("Erro ao receber atributo do jogador %d\n", jogadorAtual + 1);
            return;
        } // if
        buffer_atributo[strcspn(buffer_atributo, "\n")] = '\0';

        printf("\n=== Rodada %d ===\n", rodada);
        printf("Jogador %d escolheu o atributo: %s\n", jogadorAtual + 1, buffer_atributo);
        Beep(800, 100);

        // Comparar o atributo escolhido entre os jogadores
        vencedorRodada = -1;
        maiorValor = -1;
        // empate = false;
        int countMax = 0;

        for (int i = 0; i < numJogadores; i++)
        {
            if (cartasPorJogadorAtual[i] > 0)
            {
                int cartaAtual = cartasSorteadas[i][0];
                float valorAtributo = 0;

                if (strcmp(buffer_atributo, "potencia") == 0)
                {
                    valorAtributo = cartas[cartaAtual].end.potencia;
                } // if
                else if (strcmp(buffer_atributo, "economia") == 0)
                {
                    valorAtributo = cartas[cartaAtual].end.economia;
                } // else if
                else if (strcmp(buffer_atributo, "cilindros") == 0)
                {
                    valorAtributo = cartas[cartaAtual].end.cilindros;
                } // else if
                else if (strcmp(buffer_atributo, "velocidade") == 0)
                {
                    valorAtributo = cartas[cartaAtual].end.velocidadeMaxima;
                } // else if
                else if (strcmp(buffer_atributo, "cigarros") == 0)
                {
                    valorAtributo = cartas[cartaAtual].end.quantidadeMacosCigarroPortamalas;
                } // else if
                else
                {
                    printf("Atributo inválido!\n");
                   // empate = true;
                    break;
                } // else if

                if (valorAtributo > maiorValor)
                {
                    maiorValor = valorAtributo;
                    vencedorRodada = i;
                    //empate = false;
                    countMax = 1;
                } // if
                else if (valorAtributo == maiorValor)
                {
                    countMax++;
                } // else if
            } // if maior
        } // for maior

        if (countMax > 1)
        {
            //empate = true;
            printf("Empate! Escolha outro atributo.\n");
            Beep(300, 200);
            Beep(200, 250);
            continue;
        } // if

        // Enviar o vencedor da rodada para todos os clientes
        for (int i = 0; i < numJogadores; i++)
        {
            if (socketClientes[i] != INVALID_SOCKET)
            {
                if (send(socketClientes[i], (char *)&vencedorRodada, sizeof(int), 0) <= 0)
                {
                    printf("Erro ao enviar o vencedor da rodada para o jogador %d\n", i + 1);
                    Beep(300, 200);
                    Beep(200, 250);
                    return;
                } // if
            } // if
        } // for

        // Transferir cartas para o vencedor
        if (vencedorRodada != -1)
        {
            // Coletar as cartas do topo de cada jogador ativo
            int cartasColetadas[MAX_JOGADORES];
            int numCartasColetadas = 0;
            for (int i = 0; i < numJogadores; i++)
            {
                if (cartasPorJogadorAtual[i] > 0)
                {
                    cartasColetadas[numCartasColetadas++] = cartasSorteadas[i][0];
                } // for
            } // for

            // Remover a carta do topo de cada jogador ativo
            for (int i = 0; i < numJogadores; i++)
            {
                if (cartasPorJogadorAtual[i] > 0)
                {
                    for (int j = 0; j < cartasPorJogadorAtual[i] - 1; j++)
                    {
                        cartasSorteadas[i][j] = cartasSorteadas[i][j + 1];
                    } // for
                    cartasPorJogadorAtual[i]--;
                } // if
            } // for

            // Transferir as cartas coletadas para o vencedor
            for (int i = 0; i < numCartasColetadas; i++)
            {
                if (cartasPorJogadorAtual[vencedorRodada] < quantidadeCartas)
                {
                    cartasSorteadas[vencedorRodada][cartasPorJogadorAtual[vencedorRodada]++] = cartasColetadas[i];
                } // if
                else
                {
                    printf("Erro: sem espaço para adicionar mais cartas ao jogador %d\n", vencedorRodada);
                    Beep(300, 200);
                    Beep(200, 250);
                    break;
                } // else
            } // for

            // Verificar jogadores ativos
            for (int i = 0; i < numJogadores; i++)
            {
                if (cartasPorJogadorAtual[i] == 0)
                {
                    printf("Jogador %d (%s) eliminado!\n", i + 1, nomesJogadores[i]);
                    Beep(600, 300);
                    Beep(400, 300);
                    Beep(300, 300);
                    Beep(200, 400);
                    closesocket(socketClientes[i]);
                    socketClientes[i] = INVALID_SOCKET;
                    jogadoresAtivos--;
                } // if
                else
                {
                    printf("Jogador %d (%s) ainda na partida!\n", i + 1, nomesJogadores[i]);
                } // else
            } // for
        } // if maior

        // Verificar condição de vitória
        if (cartasPorJogadorAtual[vencedorRodada] == quantidadeCartas)
        {
            printf("\nParabéns, %s! Você venceu o jogo!\n", nomesJogadores[vencedorRodada]);
            Beep(800, 200);
            Beep(1000, 200);
            Beep(1200, 200);
            Beep(1500, 300);
            estatistica[vencedorRodada].vitorias++;

            for (int i = 0; i < numJogadores; i++)
            {
                estatistica[i].partidasJogadas++;
            } // For

            for (int i = 0; i < numJogadores; i++)
            {
                if (estatistica[i].partidasJogadas > 0)
                {
                    estatistica[i].taxaVitoria =
                        ((float)estatistica[i].vitorias / estatistica[i].partidasJogadas) * 100;
                } // if
                else
                {
                    estatistica[i].taxaVitoria = 0.0f;
                } // If else
            } // For

            jogoAtivo = false;
            char statusMsg[] = "FIM";
            for (int i = 0; i < numJogadores; i++)
            {
                if (socketClientes[i] != INVALID_SOCKET)
                {
                    if (send(socketClientes[i], statusMsg, sizeof(statusMsg), 0) <= 0)
                    {
                        printf("Erro ao enviar mensagem de fim de jogo para o jogador %d\n", i + 1);
                        Beep(300, 200);
                        Beep(200, 250);
                        return;
                    } // if
                } // if
            } // for
            break;
        }
        else
        {
            char statusMsg[] = "CON";
            for (int i = 0; i < numJogadores; i++)
            {
                if (socketClientes[i] != INVALID_SOCKET)
                {
                    if (send(socketClientes[i], statusMsg, sizeof(statusMsg), 0) <= 0)
                    {
                        printf("Erro ao enviar mensagem de continuação de jogo para o jogador %d\n", i + 1);
                        Beep(300, 200);
                        Beep(200, 250);
                        return;
                    } // if
                } // if
            } // for
        } // else

        jogadorAtual = vencedorRodada;
        rodada++;
    } // while maior

    for (int i = 0; i < numJogadores; i++)
    {
        VerificaConquistas(&estatistica[i]);
    } // For

    // Salvar as estatísticas e o ranking
    SalvarEstatistica(estatistica, numJogadores);
    SalvarConquistas(conquistas);

    for (int i = 0; i < numJogadores; i++)
    {
        AddJogadorRanking(rank, nomesJogadores[vencedorRodada], estatistica[vencedorRodada].vitorias);
    } // For

    SalvarRanking(rank);

    // Liberar a memória alocada
    for (int l = 0; l < numJogadores; l++)
    {
        free(cartasSorteadas[l]);
    } // for
    free(cartasSorteadas);
    free(cartasPorJogadorAtual);
} // jogarServidor

/**
 * @brief  iniciarServidor, Funcao responsavel por Iniciar o servidor e efetuar a conexao dos clientes
 *
 * @param quantJogadores
 * @param cartas
 * @param quantidadeCartas
 * @param estatistica
 * @param rank
 */
void iniciarServidor(int quantJogadores, Cartas cartas[], int quantidadeCartas, Estatisticas *estatistica, Ranking *rank)
{
    WSADATA wsa;
    SOCKET servidor, clientes[quantJogadores];
    struct sockaddr_in enderecoServidor, enderecoCliente;
    int tamanhoEnderecoCliente, numClientes = 0;

    printf("Inicializando Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Erro ao inicializar o Winsock: %d\n", WSAGetLastError());
        Beep(300, 200);
        Beep(200, 250);
        return;
    } // if

    servidor = socket(AF_INET, SOCK_STREAM, 0);
    if (servidor == INVALID_SOCKET)
    {
        printf("Erro ao criar socket: %d\n", WSAGetLastError());
        Beep(300, 200);
        Beep(200, 250);
        return;
    } // if
    printf("Socket criado.\n");

    enderecoServidor.sin_family = AF_INET;
    enderecoServidor.sin_addr.s_addr = INADDR_ANY;
    enderecoServidor.sin_port = htons(PORTA);

    if (bind(servidor, (struct sockaddr *)&enderecoServidor, sizeof(enderecoServidor)) == SOCKET_ERROR)
    {
        printf("Erro no bind: %d\n", WSAGetLastError());
        return;
    } // if
    printf("Bind realizado.\n");

    listen(servidor, quantJogadores);
    printf("Aguardando conexoes na porta %d...\n", PORTA);
    printf("quant Jogadores: %d\n", quantJogadores);

    while (numClientes < quantJogadores)
    {
        tamanhoEnderecoCliente = sizeof(struct sockaddr_in);
        clientes[numClientes] = accept(servidor, (struct sockaddr *)&enderecoCliente, &tamanhoEnderecoCliente);
        if (clientes[numClientes] == INVALID_SOCKET)
        {
            printf("Falha ao aceitar conexao: %d\n", WSAGetLastError());
            Beep(300, 200);
            Beep(200, 250);
            return;
        } // if
        printf("Jogador %d conectado.\n", numClientes + 1);
        Beep(800, 100);
        numClientes++;
    } // while

    printf("Todos os jogadores conectados. Iniciando jogo...\n");

    jogarServidor(clientes, numClientes, cartas, quantidadeCartas, estatistica, rank);

    for (int i = 0; i < numClientes; i++)
    {
        closesocket(clientes[i]);
    } // for
    closesocket(servidor);
    WSACleanup();
} // iniciarServidor

/**
 * @brief JogarCliente, Funcao responsavel por gameplay do cliente, recebe variaveis do servidor etc
 *
 * @param socketServidor
 */
void jogarCliente(SOCKET socketServidor)
{
    int vencedorRodada;
    int jogadorAtual = 0;
    char nomeJogador[50];
    size_t bytesRecebidos = 0;
    char buffer[TAMANHO_BUFFER];
    char *recvBuffer = (char *)&jogadorAtual;

    // Requisitando nome do jogador
    printf("Digite seu nome: ");
    fgets(nomeJogador, sizeof(nomeJogador), stdin);
    nomeJogador[strcspn(nomeJogador, "\n")] = '\0';

    // Envia o nome do jogador para o servidor
    if (send(socketServidor, nomeJogador, strlen(nomeJogador) + 1, 0) <= 0)
    {
        printf("Erro ao enviar nome do jogador.\n");
        Beep(300, 200);
        Beep(200, 250);
        return;
    } // if

    // Loop do jogo
    bool jogoAtivo = true;
    while (jogoAtivo)
    {
        jogadorAtual = 0;
        char nomeJogadorVez[50] = {0};

        // Receber o jogador da vez
        while (bytesRecebidos < sizeof(int))
        {
            int result = recv(socketServidor, recvBuffer + bytesRecebidos, sizeof(int) - bytesRecebidos, 0);
            if (result <= 0)
            {
                printf("Erro ao receber jogador da vez.\n");
                Beep(300, 200);
                Beep(200, 250);
                return;
            } // if
            bytesRecebidos += result;
        } // while
        bytesRecebidos = 0;

        // Receber o nome do jogador da vez
        while (bytesRecebidos < sizeof(nomeJogadorVez))
        {
            int result = recv(socketServidor, nomeJogadorVez + bytesRecebidos, sizeof(nomeJogadorVez) - bytesRecebidos, 0);
            if (result <= 0)
            {
                printf("Erro ao receber nome do jogador da vez.\n");
                Beep(300, 200);
                Beep(200, 250);
                return;
            } // if
            bytesRecebidos += result;
        } // while
        bytesRecebidos = 0;

        // Receber o número de cartas
        int numCartas;
        while (bytesRecebidos < sizeof(int))
        {
            int result = recv(socketServidor, (char *)&numCartas + bytesRecebidos, sizeof(int) - bytesRecebidos, 0);
            if (result <= 0)
            {
                printf("Erro ao receber número de cartas.\n");
                Beep(300, 200);
                Beep(200, 250);
                return;
            } // if
            bytesRecebidos += result;
        } // while
        bytesRecebidos = 0;

        // Receber as cartas
        Cartas *minhasCartas = (Cartas *)calloc(numCartas, sizeof(Cartas));
        for (int i = 0; i < numCartas; i++)
        {
            if (recv(socketServidor, (char *)&minhasCartas[i], sizeof(Cartas), 0) <= 0)
            {
                printf("Erro ao receber carta.\n");
                Beep(300, 200);
                Beep(200, 250);
                free(minhasCartas);
                return;
            } // if
        } // for

        // Verificar se o jogador foi eliminado
        if (numCartas == 0)
        {
            printf("Você foi eliminado!\n");
            Beep(600, 300);
            Beep(400, 300);
            Beep(300, 300);
            Beep(200, 400);
            jogoAtivo = false;
            free(minhasCartas);
            break;
        } // if

        // Mostrar a carta do topo
        printf("\n--- Sua Carta ---\n");
        printf("Nome: %s\n", minhasCartas[0].nome);
        printf("Potência: %.2f\n", minhasCartas[0].end.potencia);
        printf("Economia: %.2f\n", minhasCartas[0].end.economia);
        printf("Cilindros: %d\n", minhasCartas[0].end.cilindros);
        printf("Velocidade Máxima: %.2f\n", minhasCartas[0].end.velocidadeMaxima);
        printf("Cigarros no Porta-malas: %.2f\n", minhasCartas[0].end.quantidadeMacosCigarroPortamalas);
        tocaEfeitoSonoros(minhasCartas, 0);

        // Verificar se é a vez do jogador
        if (strcmp(nomeJogador, nomeJogadorVez) == 0)
        {
            printf("Escolha um atributo: ");
            Beep(800, 100);
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            if (send(socketServidor, buffer, sizeof(buffer), 0) <= 0)
            {
                printf("Erro ao enviar atributo escolhido.\n");
                Beep(300, 200);
                Beep(200, 250);
                free(minhasCartas);
                return;
            } // if
        }
        else
        {
            printf("Aguardando jogador %d (%s) escolher o atributo...\n", jogadorAtual + 1, nomeJogadorVez);
        } // if

        // Receber o vencedor da rodada
        if (recv(socketServidor, (char *)&vencedorRodada, sizeof(int), 0) <= 0)
        {
            printf("Erro ao receber vencedor da rodada.\n");
            Beep(300, 200);
            Beep(200, 250);
            free(minhasCartas);
            return;
        } // if

        // Receber o status do jogo (FIM ou CON)
        char statusMsg[4];
        if (recv(socketServidor, statusMsg, sizeof(statusMsg), 0) <= 0)
        {
            printf("Erro ao receber status do jogo.\n");
            Beep(300, 200);
            Beep(200, 250);
            free(minhasCartas);
            return;
        } // if

        // Verificar se o jogo terminou
        if (strcmp(statusMsg, "FIM") == 0)
        {
            printf("Fim de jogo!\n");
            Beep(300, 200);
            Beep(200, 250);
            jogoAtivo = false;
        } // if
        else if (strcmp(statusMsg, "CON") == 0)
        {
            printf("Continuando o jogo...\n");
            Beep(800, 100);
        } // else if

        // Liberar a memória alocada para as cartas
        free(minhasCartas);
    } // Fim do loop do jogo
    return;
} // Fim da função jogarCliente

/**
 * @brief Iniciar Cliente, funcao responsavel por inicializar o cliente e efetuar a conexao
 *
 * @param enderecoIP
 */
void iniciarCliente(const char *enderecoIP)
{
    WSADATA wsa;
    SOCKET cliente;
    struct sockaddr_in enderecoServidor;

    printf("Inicializando Winsock...\n");
    Beep(800, 100);
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Erro ao inicializar Winsock: %d\n", WSAGetLastError());
        Beep(300, 200);
        Beep(200, 250);
        exit(1);
    } // if

    cliente = socket(AF_INET, SOCK_STREAM, 0);
    if (cliente == INVALID_SOCKET)
    {
        printf("Erro ao criar socket: %d\n", WSAGetLastError());
        Beep(800, 100);
        exit(1);
    } // If
    printf("Socket criado.\n");
    Beep(800, 100);

    enderecoServidor.sin_family = AF_INET;
    enderecoServidor.sin_addr.s_addr = inet_addr(enderecoIP);
    enderecoServidor.sin_port = htons(PORTA);

    if (connect(cliente, (struct sockaddr *)&enderecoServidor, sizeof(enderecoServidor)) < 0)
    {
        printf("Erro ao conectar ao servidor.\n");
        Beep(300, 200);
        Beep(200, 250);
        exit(1);
    } // If
    printf("Conectado ao servidor!\n");
    Beep(800, 100);

    // tocaEfeitoSonoros();

    // jogarCliente(cliente, quantidadeCartas, maxJogadores, cartas);
    jogarCliente(cliente);
    closesocket(cliente);
    WSACleanup();

    return;
} // iniciarCliente