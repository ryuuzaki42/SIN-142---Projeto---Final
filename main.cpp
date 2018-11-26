#include <iostream>
#include <stdio.h>

#include "funcoes.h"

int main(){
    //alocacao das linhas da matriz
    int** matriz = (int**) malloc(LINHAS*sizeof(int*));
    //alocacao das colunas da matriz
    for(int n = 0; n < LINHAS; n++){
    matriz[n] = (int*) malloc(COLUNAS*sizeof(int));
    }

    if(matriz==NULL){
        cout<<"Erro ao alocar matriz";
        exit(1);
    }

    executaOrdenacao(matriz);
    free(matriz);

    return 0;
}
