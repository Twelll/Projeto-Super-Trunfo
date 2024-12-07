/**
 * @author Thiago Wesley Pasquim de Melo     (tmelo@alunos.utfpr.edu.br)
 * @author Lucas Gabriel Rodrigues de Moraes (lucasgabrielmoraes@alunos.utfpr.edu.br)
 * @author Vinicius Gabriel Giordani Barbosa (vinciusb.2024@alunos.utfpr.edu.br)
 * @brief
 * @version 0.9
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
#define BARALHO 32

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

/*void Inicializar_Struct(Cartas cartas[])
{ // Por enquanto, preenchido com informacoes aleatorias
    // nome, letra, numero, super_trunfo?/ ID, letra para numero, potencia, economia, cilindros, velocidade_maxima, quantidade_maxima_de_macos_de_cigarros_no_porta_malas

    //INDICE                   NOME                       L   N   S.P     RG    L.N  P      E      C   V.L    MACOS
    cartas[0] = (Cartas){"Volkswagen Fuscão Preto",      'A', 1, false, CARTA1,  A, {46,    8,     4,  105, 1627.61}};
    cartas[1] = (Cartas){"Fiat Uno C/Escada",            'B', 1, true,  CARTA2,  B, {20911, 100,   16, 299792458, 3347.57}};
    cartas[2] = (Cartas){"Volkswagen Saveiro",           'C', 1, false, CARTA3,  C, {104,   8.5,   4,  176, 10666.25}};
    cartas[3] = (Cartas){"Volkswagen Kombi",             'D', 1, false, CARTA4,  D, {78,    8.4,   4,  130, 9303.93}};

    cartas[4] = (Cartas){"Peugeot 206",                  'A', 2, false, CARTA5,  A, {90,    10.6,  4,  185, 2821.60}};
    cartas[5] = (Cartas){"Fiat Marea Perua",             'B', 2, false, CARTA6,  B, {142,   7.3,   5,  201, 4501.24}};
    cartas[6] = (Cartas){"Volkswagen Santana",           'C', 2, false, CARTA7,  C, {114,   13.5,  4,  186, 4767.01}};
    cartas[7] = (Cartas){"Renault Sandero",              'D', 2, false, CARTA8,  D, {92,    12.1,  4,  172, 3693.63}};

    cartas[8]  = (Cartas){"Volkswagen Gol GTI Rebaixado",'A', 3, false, CARTA9,  A, {120,   8.5,   4,  185, 3151.33}};
    cartas[9]  = (Cartas){"Chevrolet Astra",             'B', 3, false, CARTA10, B, {116,   7.5,   4,  180, 4271.03}};
    cartas[10] = (Cartas){"Chevrolet Vectra",            'C', 3, false, CARTA11, C, {141,   8.4,   4,  208, 5771.67}};
    cartas[11] = (Cartas){"Volkswagen Golf Sapao",       'D', 3, false, CARTA12, D, {116,   8.5,   4,  195, 3809.05}};

    cartas[12] = (Cartas){"Troller T4",                  'A', 4, false, CARTA13, A, {200,   6.5,   5,  180, 1719.95}};
    cartas[13] = (Cartas){"Ford Ranger",                 'B', 4, false, CARTA14, B, {173,   5.2,   4,  171, 14556.15}};
    cartas[14] = (Cartas){"Volkswagen Amarok",           'C', 4, false, CARTA15, C, {140,   9,     4,  168, 14025.16}};
    cartas[15] = (Cartas){"Toyota Hilux",                'D', 4, false, CARTA16, D, {177,   9,     4,  180, 11601.01}};

    cartas[16] = (Cartas){"Gurgel BR-800",               'A', 5, false, CARTA17, A, {26,    11.5,  2,  108, 1592.98}};
    cartas[17] = (Cartas){"Volkswagen Brasilia",         'B', 5, false, CARTA18, B, {65,    8.9,   4,  128, 1616.08}};
    cartas[18] = (Cartas){"Volkswagen Parati",           'C', 5, false, CARTA19, C, {81,    7,     4,  157, 6117.97}};
    cartas[19] = (Cartas){"Chevrolet Kadett",            'D', 5, false, CARTA20, D, {110,   8.6,   4,  181, 4491.53}};

    cartas[20] = (Cartas){"Chevrolet Celta",             'A', 6, false, CARTA21, A, {77,    10.7,  4,  161, 3001.26}};
    cartas[21] = (Cartas){"Chevrolet Corsa",             'B', 5, false, CARTA22, B, {95,    12.7,  4,  177, 3001.26}};
    cartas[22] = (Cartas){"Fiat Palio",                  'C', 6, false, CARTA23, C, {75,    12.3,  4,  157, 2527.73}};
    cartas[23] = (Cartas){"Volkswagen Polo",             'D', 6, false, CARTA24, D, {104,   6.2,   4,  189, 3116.10}};

    cartas[24] = (Cartas){"Fiat Strada",                 'A', 7, false, CARTA24, A, {85,    10.1,  4,  170, 9580.67}};
    cartas[25] = (Cartas){"Toyota Bandeirantes",         'B', 7, false, CARTA25, B, {90,    9,     4,  125, 23086.69}};
    cartas[26] = (Cartas){"Volkswagen Voyage",           'C', 7, false, CARTA26, C, {90,    7.6,   4,  167, 4409.27}};
    cartas[27] = (Cartas){"Ford Escort",                 'D', 7, false, CARTA27, D, {115,   7.5,   4,  196, 4386.69}};

    cartas[28] = (Cartas){"Chevrolet Opala 6 caneco",    'A', 8, false, CARTA28, A, {171,   6,     6,  190, 4963.63}};
    cartas[29] = (Cartas){"Ford Maverick",               'B', 8, false, CARTA30, B, {196,   4.5,   8,  200, 4813.57}};
    cartas[30] = (Cartas){"Chevrolet Omega",             'C', 8, false, CARTA31, C, {165,   6.9,   6,  207, 5217.59}};
    cartas[31] = (Cartas){"Chevrolet Monza",             'D', 8, false, CARTA32, D, {110,   8,     4,  172, 6521.99}};

    return;
} // Inicializar_Struct
*/

void ler_csv(Cartas cartas[], int *quantidade)
{
    FILE *csv = fopen("C:\\Users\\thiag\\OneDrive\\Documentos\\Documentos\\Faculdade\\2. Periodo\\FDCO2B\\FDCO2B\\Projeto_Trunfo\\csv\\output\\cartas.csv", "r");
    if (csv == NULL)
    {
        printf("Erro ao abrir o arquivo CSV.\n");
        return;
    }

    char linha[256];          // Buffer para armazenar cada linha
    char super_trunfo_str[6]; // Buffer para capturar "true" ou "false"
    int i = 0;

    while (fgets(linha, sizeof(linha), csv))
    {
        // Usar sscanf para parsear cada linha
        sscanf(linha,
               "\"%[^\"]\",%c,%d,%5[^,],%d,%d,%f,%f,%d,%f,%f",
               cartas[i].nome,                                    // Nome
               &cartas[i].letra,                                  // Letra
               &cartas[i].numero,                                 // Número
               super_trunfo_str,                                  // Super Trunfo como string
               (int *)&cartas[i].letras_numero,                   // Enum Letra_Para_Numero
               (int *)&cartas[i].ID,                              // Enum Cartas_enum
               &cartas[i].end.potencia,                           // Potência
               &cartas[i].end.economia,                           // Economia
               &cartas[i].end.cilindros,                          // Cilindros
               &cartas[i].end.velocidade_maxima,                  // Velocidade Máxima
               &cartas[i].end.quantidade_macos_cigarro_portamalas // Maços
        );

        // Remove espaços em branco e caracteres adicionais
        for (char *p = super_trunfo_str; *p; p++)
        {
            if (*p == '\n' || *p == '\r')
                *p = '\0';
        } // For

        // Conversão de "true"/"false" para bool
        if (strcmp(super_trunfo_str, "true") == 0)
        {
            cartas[i].super_trunfo = true;
        } else {
            cartas[i].super_trunfo = false;
        } // If else

        i++;
    } // While

    *quantidade = i;
    fclose(csv);
    printf("CSV lido com sucesso. %d cartas carregadas.\n", *quantidade);
}

int Inserir_Deletar(Cartas cartas[])
{

    int opcao;

    while (1)
    {
        do
        {
            printf("Digite sua opcao\n");
            printf("1 - Inserir\n");
            printf("2 - Deletar\n");
            printf("3 - Sair da funcao\n");

            scanf("%d", &opcao);

        } while (opcao < 1 || opcao > 3);

        switch (opcao)
        {
        case 1:
            printf("1 - Inserir\n");
                printf("Digite o nome: ");
               // fscanf("");
               // fwrite("");
                
            break;
        case 2:
            printf("2 - Deletar\n");
            
            break;
        
        case 3:
            printf("3 - Sair\n");
            return 1;
            break;
        
        default:
            printf("Erro!\n");
            break;
        } // while
    } // while
} // Inserir_Deletar   

void sorteia_numeros(int quant_jogadores, int quant_cartas_jogador, int cartas_sorteadas[quant_jogadores][quant_cartas_jogador])
{

    int total_cartas = quant_cartas_jogador * quant_jogadores;
    int *sorteadas = calloc(total_cartas + 1, sizeof(int)); // Aloca e inicializa com 0
    srand(time(NULL));                                      // Inicializa o gerador de números aleatórios

    for (int jogador = 0; jogador < quant_jogadores; jogador++)
    {
        for (int carta = 0; carta < quant_cartas_jogador; carta++)
        {
            int numero;
            do
            {
                numero = rand() % total_cartas + 1; // Sorteia um número entre 1 e total_cartas
            } while (sorteadas[numero]); // Verifica se a carta já foi sorteada

            cartas_sorteadas[jogador][carta] = numero; // Atribui a carta ao jogador
            sorteadas[numero] = 1;                     // Marca a carta como sorteada
        } // For
    } // For
} // Função

// Função principal do jogo
void gameplay(int quant_jogadores, int quant_cartas_jogador)
{
    char nomes_jogadores[quant_jogadores][50];                   // Fazer alocação dinâmica
    int cartas_sorteadas[quant_jogadores][quant_cartas_jogador]; // Fazer alocação dinâmica

    sorteia_numeros(quant_jogadores, quant_cartas_jogador, cartas_sorteadas);
    for (int i = 0; i < quant_jogadores; i++)
    {
        printf("Jogador %d. Insira seu nome: ", i + 1);
        fgets(nomes_jogadores[i], 50, stdin);
        setbuf(stdin, NULL);
        nomes_jogadores[i][strcspn(nomes_jogadores[i], "\n")] = '\0';
    } // for

    printf("Voce selecionou %d jogadores\n", quant_jogadores);
    printf("%d cartas por jogador\n\n", quant_cartas_jogador);

    for (int jogador = 0; jogador < quant_jogadores; jogador++)
    {
        printf("Cartas do Jogador %d: %s\n", jogador + 1, nomes_jogadores[jogador]);
        for (int carta = 0; carta < quant_cartas_jogador; carta++)
        {
            printf("- Carta %d\n", cartas_sorteadas[jogador][carta]);
        }
        printf("\n");
    }
}

// Funcoes Acopladas a funcao Principal: void VizualizaCarta
void Pesquisa_atributos(Cartas cartas[])
{

    char nome_compara[50];
    int encontrado = 0;
    int opcao_atributo_menu1;

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

    default:
        printf("Erro\n");
        break;
    } // Switch
    return;

} // Pesquisar_atributos

void Pesquisar_atributos_MaiorMemor(Cartas cartas[])
{
    int maior, menor, letra_menor, letra_maior;
    int opcao_atributo_menu2;

    printf("\n");
    printf("Pesquisar_atributos_MaiorMemor\n");
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

    if (opcao_atributo_menu2 == 6)
    {
        printf("Opcoes\n");
        printf("1 = A\n");
        printf("2 = B\n");
        printf("3 = C\n");
        printf("4 = D\n");

        do
        {
            printf("Digite a letra de menor valor: ");
            scanf("%d", &letra_menor);
            setbuf(stdin, NULL);
        } while (letra_menor < 1 || letra_menor > 4); // do while para aceitar somente 1 ao 4

        do
        {
            printf("Digite a letra de maior valor: ");
            scanf("%d", &letra_maior);
            setbuf(stdin, NULL);
        } while (letra_maior < 1 || letra_maior > 4); // do while para aceitar somente 1 ao 4

        for (int i = 0; i < 32; i++)
        {
            if ((unsigned int)cartas[i].letras_numero >= (unsigned int)letra_maior && (unsigned int)cartas[i].letras_numero <= (unsigned int)letra_menor)
            {
                printf("%s: %c", cartas[i].nome, cartas[i].letra);
                printf("\n");

            } // if para comparar as letras

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
        switch (opcao_atributo_menu2)
        {

        case 1: // Economia
            for (int i = 0; i < 32; i++)
            {
                if (cartas[i].end.economia >= menor && cartas[i].end.economia <= maior)
                {
                    printf("%s: Economia %.2f", cartas[i].nome, cartas[i].end.economia);
                    printf("\n");
                } // if

            } // For
            break;

        case 2: // Cilindros
            for (int i = 0; i < 32; i++)
            {
                if (cartas[i].end.cilindros >= menor && cartas[i].end.cilindros <= maior)
                {
                    printf("%s: Cilidros %d", cartas[i].nome, cartas[i].end.cilindros);
                    printf("\n");
                } // if
            } // For
            break;

        case 3: // Velocidade Maxima
            for (int i = 0; i < 32; i++)
            {
                if (cartas[i].end.velocidade_maxima >= menor && cartas[i].end.velocidade_maxima <= maior)
                {
                    printf("%s: Velocidade %.2f", cartas[i].nome, cartas[i].end.velocidade_maxima);
                    printf("\n");
                } // if
            } // for
            break;

        case 4: // Macos de cigarros no porta malas
            for (int i = 0; i < 32; i++)
            {
                if (cartas[i].end.quantidade_macos_cigarro_portamalas >= menor && cartas[i].end.quantidade_macos_cigarro_portamalas <= maior)
                {
                    printf("%s: Quantidade Max. de cigarros no porta malas %.2f", cartas[i].nome, cartas[i].end.quantidade_macos_cigarro_portamalas);
                    printf("\n");
                } // if
            } // For
            break;

        case 5: // Numero
            for (int i = 0; i < 32; i++)
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

    } // If else - Letras

} // Pesquisar_atributos_MaiorMemor

void Nav_todas_cartas(Cartas cartas[])
{
    printf("Navegar por todas as cartas\n");
    printf("\n");
    for (int i = 0; i < 32; i++)
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
        printf("Velocidade Max: %.2f Km/h\n", cartas[i].end.velocidade_maxima);
        printf("Quantidade maxima de macos de cigarros no porta malas: %.2f\n", cartas[i].end.quantidade_macos_cigarro_portamalas);

        printf("\n\n");
    } // for

} // nav_todas_cartas

// Buscando as cartas para visualizar por atributos, maior e menor
void VizualizaCarta(Cartas cartas[])
{
    int opcao_menu;

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

    } while (opcao_menu < 1 || opcao_menu > 3); // do while para aceitar somente 1 ao 3

    switch (opcao_menu)
    {

    case OPCAO_PESQUISAR_ATRIBUTOS:
        Pesquisa_atributos(cartas);

        break;
    case OPCAO_PESQUISAR_ATRIBUTOS_MAIOR_MENOR:
        Pesquisar_atributos_MaiorMemor(cartas);
        break;

    case OPCAO_TODAS_CARTAS:
        Nav_todas_cartas(cartas);
        break;

    default:
        printf("Erro!!\n");

        break;
    } // switch
} // VizualizaCarta

int main()
{
    int *total_cartas;
    total_cartas = (int *)malloc(64 * sizeof(int));
    if (total_cartas == NULL)
    {
        printf("Erro ao alocar memória.\n");
        exit(1);
    } // If

    while (1)
    {
        int opcao = 0;
        int quant_jogadores = 0;
        Cartas *cartas = (Cartas *)malloc((unsigned int)64 * sizeof(Cartas));
        if (cartas == NULL)
        {
            printf("Erro ao alocar memória.\n");
            exit(1);
        } // If

        // Inicializar_Struct(cartas);
        // Cartas cartas[50]; // Array para armazenar até 50 cartas
        int quantidade = 0;

        // Chamar a função para ler o arquivo CSV
        ler_csv(cartas, &quantidade);

        // MENU
        printf("MENU\n");
        printf("1 - Jogar\n");
        printf("2 - Buscar/Vizualizar Cartas\n");
        printf("3 - Estatisticas e Rankings\n");
        printf("4 - Conquistas\n");
        printf("5 - Inserir/Deletar Cartas\n");
        printf("6 - para sair\n");

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
                setbuf(stdin, NULL);

            } while (quant_jogadores < 2 || quant_jogadores > 8);

            int quant_cartas_jogador = BARALHO / quant_jogadores; // divide a quantidade de cartas por 32 ingnorando o resto

            gameplay(quant_jogadores, quant_cartas_jogador);
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

            printf("Voce escolheu Inserir/Deletar\n"); // Apenas Testes
            Inserir_Deletar(cartas);
            break;

            // Funcao
        case 6:
            printf("O Programa sera encerrado\n");
            return 1;
            break;

        // NENHUMA OPCAO
        default:
            printf("Erro\n");
            break;
        } // Switch

    } // while

    return 0;

} // main

/*
ADICIONADO:
Nomes dos jogadores

PENDENCIAS:
Ver apenas a carta mais acima, pelo nome e seus atributos, nao pelo seus IDs
Implementar restante da funcao gameplay
Implementar Estatisticas, Rankings e Conquistas
*/