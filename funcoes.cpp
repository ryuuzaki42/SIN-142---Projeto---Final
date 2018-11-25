#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <string>
#include <thread> 
#include <omp.h>  
//Define padrao para salvar arquivos
#define STRING_FILE_NAME "arquivos/%s/%s%d.txt"

//define o número de linhas e colunas da matriz de vetores
#define LINHAS 6
#define COLUNAS 1000000

using namespace std;



char* defineOrd(int tipo)
{
    if(tipo==1)
        return "Sequencial";
    else if(tipo==2)
        return "Concorrente";
    else if(tipo==3)
        return "Entradas";	
  		
}
char* defineArq(int tipo)
{
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
void salvaArquivo(int *vet ,int tipoOrd,int tipoArq,int numVet)
{
	FILE *arq;
	char nomeArq[50];
	//definindo o nome do arquivo
	sprintf(nomeArq,STRING_FILE_NAME,defineOrd(tipoOrd),defineArq(tipoArq),numVet);
	
	arq = fopen(nomeArq, "w");

	if (arq == NULL)
	{
	    cout<<"Problemas na CRIACAO do arquivo\n";
	    exit(1);
	} 
	for(int i=0;i < COLUNAS;i++)
    	{
        	fprintf(arq,"%d\n",vet[i]);
    	}
	//cout<<"Arquivo Salvo";
	fclose(arq);
    
}
void preencheArqEntrada(int **matriz)
{
	//gerar os números aleátorios	
	srand( (unsigned)time(NULL) );

	for(int i=0;i <LINHAS;i++)
	{
		for(int j=0;j <COLUNAS;j++)
		{
			matriz[i][j]=(rand()%COLUNAS);
			
		}
		salvaArquivo(matriz[i],3,1,i+1);
		
	}
	//cout<<"Matriz Preenchida com sucesso!";
	
}

/*********************ALGORITMO DE ORDENACAO****************/	
void quicksort(int values[], int began, int end)
{
    int i, j, pivo, aux;
    i = began;
    j = end-1;
    pivo = values[(began + end) / 2];
    while(i <= j)
    {
        while(values[i] < pivo && i < end)
        {
            i++;
        }
        while(values[j] > pivo && j > began)
        {
            j--;
        }
        if(i <= j)
        {
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

void salvaTempo(int tipoOrd,int tipoArq,double tempoGasto)
{
    FILE *arq;
    char nomeArq[50];
 
    sprintf(nomeArq,STRING_FILE_NAME,defineOrd(tipoOrd),defineArq(tipoArq),1000000);
    arq=fopen(nomeArq,"w");
    //verifica se o arquivo foi aberto corretamente
    if(arq==NULL)
    {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
 
    fprintf(arq, "TempoGasto:%.20f", tempoGasto );
    fclose(arq);
    //printf("\nArquivo de Tempo gerado com sucesso!\n");
}
//Salva Arquivo de saida de acordo com o tipo
void salvaSaida(int *vet,int tipoOrd,int tipoArq,int numVet)
{
    FILE *arq;
    char nomeArq[50];
    int i;
    sprintf(nomeArq,STRING_FILE_NAME,defineOrd(tipoOrd),defineArq(tipoArq),numVet);
    arq=fopen(nomeArq,"w");
    //verifica se o arquivo foi aberto corretamente
    if(arq==NULL)
    {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
 
    
    for(int i=0;i < COLUNAS;i++)
    {
	fprintf(arq,"%d\n",vet[i]);
    }
    //cout<<"Arquivo Salvo";
    fclose(arq);
}
/****************ORDENAÇÃO SEQUENCIAL**********************/

void ordenacaoSequencial(int **mat)
{

	for(int i=0; i<2; i++)
	{
	   quicksort(mat[i],0,COLUNAS);
    }
}

void preencheArqSaida(int **matriz,int tipoOrd,int tipoArq)
{
	

    for(int i=0;i < LINHAS;i++)
    {
	
      salvaSaida(matriz[i],tipoOrd,tipoArq,i+1);
	
    }
    //cout<<"Arquivo de saida gerado com sucesso!";
	
}
//executa a ordenação sequencial dos 6 vetores
void executaOrdSeq(int **mat)
{
    //funcoes para calcular o tempo
    clock_t start_t,end_t;
    double tempoGasto;
   	
    //calcula o tempo atual
    start_t=clock(); 
    //executa o algoritmo de ordenacao	
    ordenacaoSequencial(mat);
    //calcula tempo apos ordenacao	
    end_t=clock();
    //calcula o tempo gasto com a diferença dos tempos (antes e depois 	   da ordenacao)
    tempoGasto=((end_t - start_t) / (double)CLOCKS_PER_SEC);
    //salva arquivo de tempo
	cout<<"Tempo Gasto:"<<tempoGasto;
    salvaTempo(1,4,tempoGasto);
    //salva arquivo de saida
    preencheArqSaida(mat,1,2);	
}
/****************ORDENAÇÃO CONCORRENTE**********************/
void ordenacaoConcorrente(int **mat)
{
   std::thread t[2];
    

    for(int i=0; i<2; i++)
    {
       
       t[i]= std:: thread (quicksort,mat[i],0,COLUNAS);
      
       cout<<"Thread \n"<<i;
    }
    for(int i=0; i<2; i++)
    {
       t[i].join();
    }
}
void executaOrdConc(int **mat)
{
    //funcoes para calcular o tempo
    clock_t start_t,end_t;
    double tempoGasto;
    
    //calcula o tempo atual
    start_t=clock(); 
    //executa o algoritmo de ordenacao  
    ordenacaoConcorrente(mat);
    //calcula tempo apos ordenacao  
    end_t=clock();
    //calcula o tempo gasto com a diferença dos tempos (antes e depois     da ordenacao)
    tempoGasto=((end_t - start_t) / (double)CLOCKS_PER_SEC);
    //salva arquivo de tempo
    cout<<"Tempo Gasto:"<<tempoGasto;
    salvaTempo(2,5,tempoGasto);
    //salva arquivo de saida
    preencheArqSaida(mat,2,3);  
}
void executaOrdenacao(int **mat)
{
   
    preencheArqEntrada(mat);
    executaOrdSeq(mat);	
    //executaOrdConc(mat);
	
}


