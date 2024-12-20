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

void EscreverCsv(Cartas *cartasFonte, int quantidadeCartas);
int  ContarCartas();
void InserirCarta(Cartas **cartas, int *quantidadeCartas);
void AlterarCartas(Cartas *cartasFonte, int *structTamanho);
void DeletarCartas(Cartas **cartas, int *quantidadeCartas);
void PesquisaAtributos(Cartas cartas[], int quantidadeCartas);
void PesquisarAtributosMaiorMemor(Cartas cartas[], int quantidadeCartas);
void NavTodasCartas(Cartas cartas[], int quantidadeCartas);
void VizualizaCarta(Cartas cartas[], int quantidadeCartas);
void CarregarCartas(Cartas **cartas, int *quantidadeCartas);
void SubMenuGerenciaCartas(Cartas cartas[], int quantidadeCartas);

#endif