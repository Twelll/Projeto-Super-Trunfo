#ifndef PROJETO_H
#define PROJETO_H
#include <stdbool.h>
typedef struct
{
    float potencia;
    float economia;
    int cilindros;
    float velocidadeMaxima;
    float quantidadeMacosCigarroPortamalas;
} Atributos;

// Struct de todas as informacoes das cartas
typedef struct
{
    char nome[50];
    char letra;
    int numero;
    bool super_trunfo;
    // Cartas_enum ID;
    Atributos end;
} Cartas;



void escreverCsv(Cartas *cartasFonte, int quantidadeCartas);
int contarCartas();
void inserirCarta(Cartas **cartas, int *quantidadeCartas);
void alterarCartas(Cartas *cartasFonte, int *structTamanho);
void deletarCartas(Cartas **cartas, int *quantidadeCartas);
void PesquisaAtributos(Cartas cartas[], int quantidadeCartas);
void PesquisarAtributosMaiorMemor(Cartas cartas[], int quantidadeCartas);
void NavTodasCartas(Cartas cartas[], int quantidadeCartas);
void VizualizaCarta(Cartas cartas[], int quantidadeCartas);
void carregarCartas(Cartas **cartas, int *quantidadeCartas);
void subMenuGerenciaCartas(Cartas cartas[], int quantidadeCartas);

#endif