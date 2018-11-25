#include <iostream>
#include<stdio.h>
#include "funcoes.h"

//define o número de linhas e colunas da matriz de vetores
#define LINHAS 6
#define COLUNAS 1000000
int main()
{	
	//alocacao das linhas da matriz
	int** matriz = (int**) malloc(LINHAS*sizeof(int*));
	//alocacao das colunas da matriz
	for(int n = 0; n < LINHAS; n++)
		matriz[n] = (int*) malloc(COLUNAS*sizeof(int));

		
	if(matriz==NULL)
        {
		cout<<"Erro ao alocar matriz";
		exit(1);
    	}
	
	executaOrdenacao(matriz);
	cout<<"---------------Ordenação Sequencial------------------";
	free(matriz);
	
	return 0;
}
