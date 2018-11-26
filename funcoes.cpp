#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <string>
#include <thread>
#include <omp.h>
#include "funcoes.h"

//Define padrao para salvar arquivos
#define STRING_FILE_NAME "arquivos/%s/%s%d.txt"

using namespace std;

const char* defineOrd(int tipo){
    string a;
    if(tipo==1)
        return "Sequencial";
    else if(tipo==2)
        return "Concorrente";
    else if(tipo==3)
        return "Entradas";
}

const char* defineArq(int tipo){
    if(tipo==1)
        return "EntradaVetor";
    else if(tipo==2)
        return "SaidaVetor-Sequencial";
    else if(tipo==3)
        return "SaidaVetor-Concorrente";
    else if(tipo==4)
        return "Tempo-Sequencial";
    else if(tipo==5)
        return "Tempo-Concorrente";
}

void salvaArquivo(int *vet ,int tipoOrd,int tipoArq,int numVet){
    FILE *arq;
    char nomeArq[50];
    //definindo o nome do arquivo
    sprintf(nomeArq,STRING_FILE_NAME,defineOrd(tipoOrd),defineArq(tipoArq),numVet);

    arq = fopen(nomeArq, "w");

    if (arq == NULL){
        cout<<"Problemas na CRIACAO do arquivo\n";
        exit(1);
    }
    for(int i=0;i < COLUNAS;i++){
        fprintf(arq,"%d\n",vet[i]);
    }
    //cout<<"Arquivo Salvo";
    fclose(arq);
}

void preencheArqEntrada(int **matriz){
    for(int i=0;i <LINHAS;i++){
        for(int j=0;j <COLUNAS;j++){
            matriz[i][j]=rand()%COLUNAS + 1;
            //cout << matriz[i][j] << "\n";
        }
        //salvaArquivo(matriz[i],3,1,i+1);
    }
    //cout<<"Matriz Preenchida com sucesso!";
}

void quicksort(int values[], int began, int end){
    int i, j, pivo, aux;
    i = began;
    j = end-1;
    pivo = values[(began + end) / 2];
    while(i <= j){
        while(values[i] < pivo && i < end){
            i++;
        }
        while(values[j] > pivo && j > began){
            j--;
        }
        if(i <= j){
            aux = values[i];
            values[i] = values[j];
            values[j] = aux;
            i++;
            j--;
        }
    }
    if(j > began)
        quicksort(values, began, j+1);
    if(i < end)
        quicksort(values, i, end);
}

void salvaTempo(int tipoOrd,int tipoArq,double tempoGasto){
    FILE *arq;
    char nomeArq[50];

    sprintf(nomeArq,STRING_FILE_NAME,defineOrd(tipoOrd),defineArq(tipoArq),1000000);
    arq=fopen(nomeArq,"w");
    //verifica se o arquivo foi aberto corretamente
    if(arq==NULL){
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    fprintf(arq, "TempoGasto:%.20f", tempoGasto );
    fclose(arq);
    //printf("\nArquivo de Tempo gerado com sucesso!\n");
}

//Salva Arquivo de saida de acordo com o tipo
void salvaSaida(int *vet,int tipoOrd,int tipoArq,int numVet){
    FILE *arq;
    char nomeArq[50];
    int i;
    sprintf(nomeArq,STRING_FILE_NAME,defineOrd(tipoOrd),defineArq(tipoArq),numVet);
    arq=fopen(nomeArq,"w");
    //verifica se o arquivo foi aberto corretamente
    if(arq==NULL){
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    for(int i=0;i < COLUNAS;i++){
        fprintf(arq,"%d\n",vet[i]);
    }
    //cout<<"Arquivo Salvo";
    fclose(arq);
}

void preencheArqSaida(int **matriz,int tipoOrd,int tipoArq){
    for(int i=0;i < LINHAS;i++){
        salvaSaida(matriz[i],tipoOrd,tipoArq,i+1);
    }
    //cout<<"Arquivo de saida gerado com sucesso!";
}

void insertionSort(int vet[]){
    int i, key, j;
    for (i=1; i<COLUNAS; i++){
        key = vet[i];
        j = i-1;

        while ((j>=0) && (vet[j]>key)){
            vet[j+1] = vet[j];
            j = j-1;
        }
        vet[j+1] = key;

        if (i%1000==0){ // Test
            //printf("%d\n", i);
        }
    }
}

void ordenacaoS012(int **mat){
     quicksort(mat[0],0,COLUNAS);
     quicksort(mat[1],0,COLUNAS);
     quicksort(mat[2],0,COLUNAS);
}

void ordenacaoS345(int **mat){
    quicksort(mat[3],0,COLUNAS);
    quicksort(mat[4],0,COLUNAS);
    quicksort(mat[5],0,COLUNAS);
}

void ordenacaoS01(int **mat){
    quicksort(mat[0],0,COLUNAS);
    quicksort(mat[1],0,COLUNAS);
}

void ordenacaoS2(int **mat){
    quicksort(mat[2],0,COLUNAS);
}

void ordenacaoS34(int **mat){
    quicksort(mat[3],0,COLUNAS);
    quicksort(mat[4],0,COLUNAS);
}

void ordenacaoS5(int **mat){
     quicksort(mat[5],0,COLUNAS);
}

void ordenacaoS012345(int **mat){
    quicksort(mat[0],0,COLUNAS);
    quicksort(mat[1],0,COLUNAS);
    quicksort(mat[2],0,COLUNAS);
    quicksort(mat[3],0,COLUNAS);
    quicksort(mat[4],0,COLUNAS);
    quicksort(mat[5],0,COLUNAS);
}

void ordenacaoSequencial(int **mat){
    std::thread t0 = std::thread (ordenacaoS012345, mat);

    t0.join();
}

void ordenacaoConcorrente(int **mat){
    std::thread t0 = std::thread (ordenacaoS012, mat);
    std::thread t1 = std::thread (ordenacaoS345, mat);

    t0.join();
    t1.join();
}

void ordenacaoConcorrente2(int **mat){
    std::thread t0 = std::thread (ordenacaoS01, mat);
    std::thread t1 = std::thread (ordenacaoS2, mat);
    std::thread t2= std::thread (ordenacaoS34, mat);
    std::thread t3= std::thread (ordenacaoS5, mat);

    t0.join();
    t1.join();
    t2.join();
    t3.join();
}

void preenche(int **mat){
    srand(1);
    preencheArqEntrada(mat);
}

void executaOrdConc(int **mat){
    //funcoes para calcular o tempo
    clock_t start_t,end_t;
    double tempoGasto;

    //calcula o tempo atual
    start_t=clock();
    //executa o algoritmo de ordenacao
    preenche(mat);
    //ordenacaoConcorrente(mat);
    ordenacaoConcorrente2(mat);
    //calcula tempo apos ordenacao
    end_t=clock();
    //calcula o tempo gasto com a diferença dos tempos (antes e depois da ordenacao)
    tempoGasto=((end_t - start_t) / (double)CLOCKS_PER_SEC);
    //salva arquivo de tempo
    cout << "\nexecutaOrdConc: " << tempoGasto;

    //salvaTempo(2,5,tempoGasto);
    //salva arquivo de saida
    //preencheArqSaida(mat,2,3);
}

//executa a ordenação sequencial dos 6 vetores
void executaOrdSeq(int **mat){
    //funcoes para calcular o tempo
    clock_t start_t,end_t;
    double tempoGasto;

    //calcula o tempo atual
    start_t=clock();
    //executa o algoritmo de ordenacao
    preenche(mat);
    ordenacaoSequencial(mat);
    //calcula tempo apos ordenacao
    end_t=clock();
    //calcula o tempo gasto com a diferença dos tempos (antes e depois da ordenacao)
    tempoGasto=((end_t - start_t) / (double)CLOCKS_PER_SEC);
    //salva arquivo de tempo

    cout << "\nexecutaOrdSeq: " << tempoGasto;
    //salvaTempo(1,4,tempoGasto);
    //salva arquivo de saida
    //preencheArqSaida(mat,1,2);
}

void executaOrdenacao(int **mat){
    executaOrdSeq(mat);

    executaOrdConc(mat);

    cout << "\n";
}
