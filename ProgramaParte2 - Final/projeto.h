#ifndef PROJETO_H
#define PROJETO_H
#include <stdbool.h>
// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <string.h>
#include <ctype.h>
#include <time.h>
#include <winsock2.h>

#define PORTA 8080
#define TAMANHO_BUFFER 1024
#define MAX_JOGADORES 2
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

typedef struct 
{
    char nome[30];
    char descricao[100];
    int condicao;
    bool desbloqueada;
} Conquista;

typedef struct
{
    char nome[30];
    int partidasJogadas;
    int vitorias;
    float taxaVitoria;
    Conquista conquistas[4];
} Estatisticas;

typedef struct
{
    char nome[30];
    int pontuacao;
} Ranking;


void ExportaCsv(Cartas *cartasFonte, int quantidadeCartas);
void EscreverCsv(Cartas *cartasFonte, int quantidadeCartas);
int  ContarCartas();
void InserirCarta(Cartas **cartas, int *quantidadeCartas);
void AlterarCartas(Cartas *cartasFonte, int *structTamanho);
void DeletarCartas(Cartas **cartas, int *quantidadeCartas);
void tocaEfeitoSonoros(Cartas cartas[], int cartaAtual);
void PesquisaAtributos(Cartas cartas[], int quantidadeCartas);
void PesquisarAtributosMaiorMenor(Cartas cartas[], int quantidadeCartas);
void NavTodasCartas(Cartas cartas[], int quantidadeCartas);
void VizualizaCarta(Cartas cartas[], int quantidadeCartas);
void MostrarEstatistica(Estatisticas *estatistica, int quantJogadores);
void CarregaEstatistica(Estatisticas *estatistica, char nomeJogador[][50], int quantJogadores);
void SalvarEstatistica(Estatisticas *estatistica, int quantJogadores);
void MostrarRanking(Ranking *rank);
void CarregaRanking(Ranking *rank);
void SalvarRanking(Ranking *rank);
int  AddJogadorRanking(Ranking *rank, char* nome, int pontuacao);
void IniciaConquistas(Conquista *conquistas);
void VerificaConquistas(Estatisticas *estatistica);
void SalvarConquistas(Conquista *conquistas);
void CarregaConquistas(Conquista *conquistas);
void MostrarConquistas(Estatisticas *estatistica, int quantJogadores);
void CarregarCartas(Cartas **cartas, int *quantidadeCartas);
void SubMenuGerenciaCartas(Cartas cartas[], int quantidadeCartas);
void SorteiaNumeros(int quantJogadores, int quantCartasJogador, int cartasSorteadas);
void Gameplay(int quantJogadores, Cartas cartas[], int quantidadeCartas, char nomesJogadores[][50], Estatisticas *estatistica, Ranking *rank);
void GameplayBot(int quantJogadores, Cartas cartas[], int quantidadeCartas, char nomesJogadores[][50], Estatisticas *estatistica, Ranking *rank);
int  send_all(SOCKET s, const char *buf, int len);
int  recv_all(SOCKET s, const char *buf, int len);
void jogarServidor(SOCKET socketClientes[], int numJogadores, int quantidadeCartas, Estatisticas *estatistica, Ranking *rank);
void iniciarServidor(int quantJogadores, Cartas cartas[], int quantidadeCartas, Estatisticas *estatistica, Ranking *rank);
void jogarCliente(SOCKET socketServidor); //void jogarCliente(SOCKET socketServidor, int quantidadeCartas, int maxJogadores, Cartas cartas[]);
void iniciarCliente(const char *enderecoIP); //void iniciarCliente(const char *enderecoIP, int quantidadeCartas, int maxJogadores, Cartas cartas[]);
    
#endif