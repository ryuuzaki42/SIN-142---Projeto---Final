#ifndef FUNCOES_H
#define FUNCOES_H
#include <iostream>

#define LINHAS 6
#define COLUNAS 1000000

using namespace std;



char* defineOrd(int tipo);
char* defineArq(int tipo);
void salvaArquivo(int *vet ,int tipoOrd,int tipoArq,int numVet);
void preencheArqEntrada(int **matriz);

/*********************ALGORITMO DE ORDENACAO****************/	
void quicksort(int values[], int began, int end);

void salvaTempo(int tipoOrd,int tipoArq,double tempoGasto);
//Salva Arquivo de saida de acordo com o tipo
void salvaSaida(int *vet,int tipoOrd,int tipoArq,int numVet);
/****************ORDENAÇÃO SEQUENCIAL**********************/

void ordenacaoSequencial(int **mat);

void preencheArqSaida(int **matriz,int tipoOrd,int tipoArq);
//executa a ordenação sequencial dos 6 vetores
void executaOrdSeq(int **mat);
/****************ORDENAÇÃO CONCORRENTE**********************/
void ordenacaoConcorrente(int **mat);
void executaOrdConc(int **mat);
void executaOrdenacao(int **mat);
#endif

