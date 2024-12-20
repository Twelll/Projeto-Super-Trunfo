/**
 * @author Thiago Wesley Pasquim de Melo     (tmelo@alunos.utfpr.edu.br)
 * @author Lucas Gabriel Rodrigues de Moraes (lucasgabrielmoraes@alunos.utfpr.edu.br)
 * @author Vinicius Gabriel Giordani Barbosa (vinciusb.2024@alunos.utfpr.edu.br)
 * @brief
 * @version 1.0
 * @date 20-12-2024
 *
 * @copyright Copyright (c) 2024
 *
 */

// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/* Sera util para funcao gameplay
// Enum para ID das cartas
typedef enum
{
    CARTA1 = 1,CARTA2, CARTA3, CARTA4, CARTA5, CARTA6, CARTA7, CARTA8, CARTA9, CARTA10, CARTA11, CARTA12,
    CARTA13, CARTA14, CARTA15, CARTA16, CARTA17, CARTA18, CARTA19, CARTA20, CARTA21, CARTA22, CARTA23, CARTA24,
    CARTA25, CARTA26, CARTA27,  CARTA28,  CARTA29, CARTA30, CARTA31, CARTA32
} Cartas_enum;
*/

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
        fprintf(arqCSV, "%s,%c,%d,%s,%.2f,%.2f,%.2f,%.2f,%d\n",
                cartasFonte[i].nome,
                cartasFonte[i].letra,
                cartasFonte[i].numero,
                cartasFonte[i].super_trunfo ? "true" : "false",
                // cartasFonte[i].ID,
                cartasFonte[i].end.potencia,
                cartasFonte[i].end.economia,
                cartasFonte[i].end.quantidadeMacosCigarroPortamalas,
                cartasFonte[i].end.velocidadeMaxima,
                cartasFonte[i].end.cilindros);
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
   // int salvaIndice;
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

    printf("Digite...\n");

    do
    {
        setbuf(stdin, NULL);
        printf("Nome: ");
        fgets(nomeCompara, 50, stdin);
        nomeCompara[strcspn(nomeCompara, "\n")] = '\0';
        
        cartaEncontrada = 0;
        for (int i = 0; i < *quantidadeCartas; i++)
        {
            if (strcasecmp(nomeCompara, (*cartas)[i].nome) == 0)
            {
                printf("Carta Encontrada %s\n", cartas[i]->nome);
                cartaEncontrada = 1;
                //salvaIndice = i;
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
    } while (novaCarta->letra < 'A' || novaCarta->letra > 'D');// && (novaCarta->letra < 'a' || novaCarta->letra > 'd')); // do while para aceitar somente A ao D

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

        for (int i = 0; i < *structTamanho; i++)
        {
            if (strcasecmp(nomeCompara, cartasFonte[i].nome) == 0)
            {
                printf("Carta Encontrada %s\n", cartasFonte[i].nome);
                cartaEncontrada = 1;
                salvaIndice = i;
                break;
            } // if
        } // for
        if (!cartaEncontrada)
        {
            printf("A Carta %s NAO foi encontrada\n", nomeCompara);
            printf("Tente Novamente\n");
        } // if
    } while (!cartaEncontrada);

    // Requere as informacoes
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
            cartaEncontrada = 1;
            break;
        } // if
    } // for

    do
    {
        printf("Potencia: ");
        scanf("%f", &cartasFonte[salvaIndice].end.potencia);
        setbuf(stdin, NULL);
    } while (cartasFonte[salvaIndice].end.potencia < 0); // do while que aceita somente numeros maiores que 0

    do
    {

        printf("Economia: ");
        scanf("%f", &cartasFonte[salvaIndice].end.economia);
        setbuf(stdin, NULL);
    } while (cartasFonte[salvaIndice].end.economia < 0); // do while que aceita somente numeros maiores que 0

    do
    {

        printf("cilindros: ");
        scanf("%d", &cartasFonte[salvaIndice].end.cilindros);
        setbuf(stdin, NULL);
    } while (cartasFonte[salvaIndice].end.cilindros < 0); // do while que aceita somente numeros maiores que 0

    do
    {

        printf("Velocidade Maxima: ");
        scanf("%f", &cartasFonte[salvaIndice].end.velocidadeMaxima);
        setbuf(stdin, NULL);
    } while (cartasFonte[salvaIndice].end.velocidadeMaxima < 0); // do while que aceita somente numeros maiores que 0

    do
    {

        printf("Quantidade de macos de cigarro no porta malas: ");
        scanf("%f", &cartasFonte[salvaIndice].end.quantidadeMacosCigarroPortamalas);
        setbuf(stdin, NULL);
    } while (cartasFonte[salvaIndice].end.quantidadeMacosCigarroPortamalas < 0); // do while que aceita somente numeros maiores que 0

    EscreverCsv(cartasFonte, *structTamanho);

    // mensagem de exito
    printf("As informacoes foram atualizadas com sucesso\n");

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
    if (*quantidadeCartas <= 32)
    {
        printf("Não é possível deletar mais cartas. O baralho deve ter pelo menos 32 cartas.\n");
        return;
    } // if

    printf("Escolha uma carta para deletar (por número):\n");
    for (int i = 0; i < *quantidadeCartas; i++)
    {
        printf("%d - %s\n", i + 1, (*cartas)[i].nome);
    } // for

    int indice;
    do
    {
        printf("Digite o número da carta que deseja deletar (1 a %d): ", *quantidadeCartas);
        scanf("%d", &indice);
        setbuf(stdin, NULL);
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
            exit(1);
        } // if
        *cartas = temp;
    }
    (*quantidadeCartas)--;

    // Atualiza o arquivo CSV utilizando as funções de manipulação CSV
    EscreverCsv(*cartas, *quantidadeCartas);
    printf("Carta deletada com sucesso!\n");

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
    printf("pesquisarAtributos\n");

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

    do
    {
        setbuf(stdin, NULL);
        // Requisitando opcao
        printf("Digite sua opcao: ");
        scanf("%d", &opcaoAtributoMenu1);
    } while (opcaoAtributoMenu1 < 1 || opcaoAtributoMenu1 > 7);

    // Switch Menor - Responsavel por Menu: 1 - Pesquisar por atributos
    switch (opcaoAtributoMenu1)
    {
    case 1: // Economia

        printf("Digite a Economia: ");
        scanf("%f", &economiaCompara);
        setbuf(stdin, NULL);

        printf("Cartas com economia %f \n", economiaCompara);
        for (int i = 0; i < quantidadeCartas; i++)
        {
            if (economiaCompara == cartas[i].end.economia)
            {
                printf("%s: Economia %.2f\n", cartas[i].nome, cartas[i].end.economia);
            } // if
        } // for
        break;

    case 2: // Cilindros

        printf("Digite a quantidade de cilindros: ");
        scanf("%d", &cilindrosCompara);
        setbuf(stdin, NULL);

        printf("Cartas com %d cilindros\n", cilindrosCompara);
        for (int i = 0; i < quantidadeCartas; i++)
        {
            if (cilindrosCompara == cartas[i].end.cilindros)
            {
                printf("%s: Cilindros %d\n", cartas[i].nome, cartas[i].end.cilindros);
            } // if
        } // for
        break;

    case 3: // Velocidade Maxima

        printf("Digite a velocidade maxima: ");
        scanf("%f", &velocidadeCompara);
        setbuf(stdin, NULL);

        printf("Cartas com velocidade maxima %f\n", velocidadeCompara);
        for (int i = 0; i < quantidadeCartas; i++)
        {
            if (velocidadeCompara == cartas[i].end.velocidadeMaxima)
            {
                printf("%s: Velocidade Maxima %.2ff\n", cartas[i].nome, cartas[i].end.quantidadeMacosCigarroPortamalas);
            } // if
        } // for
        break;

    case 4: // Macos de cigarros no porta malas

        printf("Digite o macos de cigarros: ");
        scanf("%f", &cigarrosCompara);
        setbuf(stdin, NULL);

        printf("Cartas com %f macos de cigarros no porta malas\n", cigarrosCompara);
        for (int i = 0; i < quantidadeCartas; i++)
        {
            if (cigarrosCompara == cartas[i].end.quantidadeMacosCigarroPortamalas)
            {
                printf("%s: Macos p/porta malas %.2f\n", cartas[i].nome, cartas[i].end.quantidadeMacosCigarroPortamalas);
            } // if
        } // for
        break;

    case 5: // Numero

        printf("Digite o numero: ");
        scanf("%d", &numeroCompara);
        setbuf(stdin, NULL);

        printf("Cartas com numero %d\n", numeroCompara);
        for (int i = 0; i < quantidadeCartas; i++)
        {
            if (numeroCompara == cartas[i].numero)
            {
                printf("%s: Numero %d\n", cartas[i].nome, cartas[i].numero);
            } // if
        } // for
        break;

    case 6: // Letra

        printf("Digite a letra: ");
        fgets(letraCompara, 1, stdin);
        letraCompara[strcspn(letraCompara, "\n")] = '\0';
        setbuf(stdin, NULL);

        // printf("Cartas com a letra %c\n", letraCompara);
        for (int i = 0; i < quantidadeCartas; i++)
        {
            if (cartas[i].letra == letraCompara[0])
            {
                printf("%s : Letra %c\n", cartas[i].nome, cartas[i].letra);
            } // if

        } // For
        break;

    case 7: // Nome

        printf("Digite o nome da carta que deseja pesquisar: ");
        fgets(nomeCompara, 50, stdin);
        nomeCompara[strcspn(nomeCompara, "\n")] = '\0';
        setbuf(stdin, NULL);

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
            } // if

        case 8: // Potencia

            printf("Digite a potencia: ");
            scanf("%f", &potenciaCompara);
            setbuf(stdin, NULL);

            printf("Cartas com potencia %f \n", potenciaCompara);
            for (int i = 0; i < quantidadeCartas; i++)
            {
                if (potenciaCompara == cartas[i].end.potencia)
                {
                    printf("%s: Potencia %.2f\n", cartas[i].nome, cartas[i].end.potencia);
                } // if
            } // for
            break;
        } // for

        if (!encontrado)
        {
            perror("Carta não encontrada!\n");
            break;
        } // if

    default:

        perror("ERRO! Opcao invalida\n");
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
void PesquisarAtributosMaiorMemor(Cartas cartas[], int quantidadeCartas)
{
    int maior, menor;
    char letraMenor, letraMaior;
    int opcaoAtributoMenu2;

    printf("\n");
    printf("Pesquisar_atributos_MaiorMemor\n");
    // Menu 2 - Pesquisar por atributos, dentro de um intervalo
    // Atributos da carta
    printf("1 - Economia\n");
    printf("2 - Cilindros\n");
    printf("3 - VelocidadeMaxima\n");
    printf("4 - Quantidade macos de cigarro no portamalas\n");
    // Informacoes Gerais da Carta
    printf("5 - Numero\n");
    printf("6 - Letra\n");

    do
    {
        // Requisitando
        printf("Digite sua opcao: ");
        setbuf(stdin, NULL);
        scanf("%d", &opcaoAtributoMenu2);
    } while (opcaoAtributoMenu2 < 1 || opcaoAtributoMenu2 > 6);

    if (opcaoAtributoMenu2 == 6)
    {
        printf("Letras Maiusculas, entre A - D\n");

        do
        {
            printf("Digite a letra de menor valor: ");
            scanf("%c", &letraMenor);
            setbuf(stdin, NULL);
        } while (letraMenor < 'A' || letraMenor > 'D'); // do while para aceitar somente A ao D

        do
        {
            printf("Digite a letra de maior valor: ");
            scanf("%c", &letraMaior);
            setbuf(stdin, NULL);
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

        printf("Digite o limite superior: ");
        scanf("%d", &maior);
        setbuf(stdin, NULL);

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
    printf("VizualizaCarta\n");
    int opcaoMenu;

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
        scanf("%d", &opcaoMenu);
        setbuf(stdin, NULL);

    } while (opcaoMenu < 1 || opcaoMenu > 3); // do while para aceitar somente 1 ao 3

    switch (opcaoMenu)
    {

    case 1:
        PesquisaAtributos(cartas, quantidadeCartas);

        break;
    case 2:
        PesquisarAtributosMaiorMemor(cartas, quantidadeCartas);
        break;

    case 3:
        NavTodasCartas(cartas, quantidadeCartas);
        break;

    default:
        printf("Opcao invalida\n");

        break;
    } // switch
} // VizualizaCarta

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
    FILE *arquivoPointer = fopen("cartas.csv", "r");
    if (arquivoPointer == NULL)
    {
        perror("Erro ao abrir o arquivo CSV para leitura.");
        exit(1);
    } // if

    // Conta o número de linhas no arquivo
    char buffer[1024];
    int linhas = 0;
    while (fgets(buffer, sizeof(buffer), arquivoPointer))
    {
        if (buffer[0] != '\n' && buffer[0] != '\0')
        {
            linhas++;
        } // if
    } // w while

    rewind(arquivoPointer);

    // Aloca memória para as cartas
    *cartas = malloc(linhas * sizeof(Cartas));
    if (*cartas == NULL)
    {
        perror("ERRO! Nao foi possivel alocar memória\n.");
        exit(1);
    } // if

    // Lê os dados do arquivo CSV
    *quantidadeCartas = 0;
    while (fgets(buffer, sizeof(buffer), arquivoPointer))
    {
        if (buffer[0] == '\n' || buffer[0] == '\0')
        {
            continue;
        } // if

        Cartas *cartaAtual = &(*cartas)[*quantidadeCartas];

        char superTrunfoTexto[6];

        sscanf(buffer, "%49[^,],%c,%d,%5[^,],%f,%f,%f,%f,%d",
               cartaAtual->nome,
               &cartaAtual->letra,
               &cartaAtual->numero,
               superTrunfoTexto,
               // &cartaAtual->super_trunfo,
               &cartaAtual->end.potencia,
               &cartaAtual->end.economia,
               &cartaAtual->end.quantidadeMacosCigarroPortamalas,
               &cartaAtual->end.velocidadeMaxima,
               &cartaAtual->end.cilindros);

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
            exit(1);
        } // ekse

        (*quantidadeCartas)++;
    } // while

    fclose(arquivoPointer);

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
    int subOpcao;
    do
    {
        printf("Gerenciar Cartas:\n");
        printf("1 - Inserir Carta\n");
        printf("2 - Alterar Carta\n");
        printf("3 - Deletar Carta\n");
        printf("4 - Sair\n");

        printf("Escolha uma opção: ");
        scanf("%d", &subOpcao);

        switch (subOpcao)
        {
        case 1:
            InserirCarta(&cartas, &quantidadeCartas);
            break;

        case 2:
            AlterarCartas(cartas, &quantidadeCartas);
            break;

        case 3:
            DeletarCartas(&cartas, &quantidadeCartas);
            break;
        case 4:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao Invalida\n");
        } // switch case 5

    } while (subOpcao != 4);

    return;

} // Sub Menu Gererencir cartas