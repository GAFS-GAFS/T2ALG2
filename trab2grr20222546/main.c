#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <string.h> 

#include "ordenacao.h"

/*======================================================== FUNÇÕES GERAIS ========================================================*/

void completaVetor(int *vetor, size_t tamVetor)
{
    int i;

    for (i = 0; i < (int)tamVetor; i++) // preenche o vetor com valores aleatórios
    {
        vetor[i] = rand() % (int)tamVetor + 1;
    }
}

void imprimeVetor(int *vetor, size_t tamVetor)
{
    int i;

    printf("Vetor = [");

    for (i = 0; i < (int)tamVetor; i++) // percorre o vetor imprimindo seus valores
    {
        printf(" %d", vetor[i]);
    }

    printf(" ] \n");
}

/*======================================================= FUNÇÕES DO MAIN ========================================================*/

void mergeSortRec(int *vetor, size_t tam, uint64_t *numComparacoes, clock_t start, clock_t end)
{
    double total;

    completaVetor(vetor, tam); // preenche o vetor
    start = clock();           // inicia o temporizador
    *numComparacoes = 0;
    *numComparacoes = mergeSort(vetor, tam); // recebe o total de comparacoes do algoritimo
    end = clock();                           // termina o temporizador

    total = (double)(end - start) / CLOCKS_PER_SEC; // calcula os segundos

    printf("\nMERGE SORT RECURSIVO:\n%f (tempo de execução em segundos)\nComparacoes: %lu\n", total, *numComparacoes);

    imprimeVetor(vetor, tam);
}

void quickSortRec(int *vetor, size_t tam, uint64_t *numComparacoes, clock_t start, clock_t end)
{
    double total;

    completaVetor(vetor, tam); // preenche o vetor
    start = clock();           // inicia o temporizador
    *numComparacoes = 0;
    *numComparacoes = quickSort(vetor, tam); // recebe o total de comparacoes do algoritimo
    end = clock();                           // termina o temporizador

    total = (double)(end - start) / CLOCKS_PER_SEC; // calcula os segundos

    printf("\nQUICK SORT RECURSIVO:\n%f (tempo de execução em segundos)\nComparacoes: %lu\n", total, *numComparacoes);

    imprimeVetor(vetor, tam);
}

void heapSortRec(int *vetor, size_t tam, uint64_t *numComparacoes, clock_t start, clock_t end)
{
    double total;

    completaVetor(vetor, tam); // preenche o vetor
    start = clock();           // inicia o temporizador
    *numComparacoes = 0;
    *numComparacoes = heapSort(vetor, tam); // recebe o total de comparacoes do algoritimo
    end = clock();                          // termina o temporizador

    total = (double)(end - start) / CLOCKS_PER_SEC; // calcula os segundos

    printf("\nHEAP SORT RECURSIVO:\n%f (tempo de execução em segundos)\nComparacoes: %lu\n", total, *numComparacoes);

    imprimeVetor(vetor, tam);
}

void mergeSortIte(int *vetor, size_t tam, uint64_t *numComparacoes, clock_t start, clock_t end)
{
    double total;

    completaVetor(vetor, tam); // preenche o vetor
    start = clock();           // inicia o temporizador
    *numComparacoes = 0;
    *numComparacoes = mergeSortSR(vetor, tam); // recebe o total de comparacoes do algoritimo
    end = clock();                             // termina o temporizador

    total = (double)(end - start) / CLOCKS_PER_SEC; // calcula os segundos

    printf("\nMERGE SORT ITERATIVO:\n%f (tempo de execução em segundos)\nComparacoes: %lu\n", total, *numComparacoes);

    imprimeVetor(vetor, tam);
}

void quickSortIte(int *vetor, size_t tam, uint64_t *numComparacoes, clock_t start, clock_t end)
{
    double total;

    completaVetor(vetor, tam); // preenche o vetor
    start = clock();           // inicia o temporizador
    *numComparacoes = 0;
    *numComparacoes = quickSortSR(vetor, tam); // recebe o total de comparacoes do algoritimo
    end = clock();                             // termina o temporizador

    total = (double)(end - start) / CLOCKS_PER_SEC; // calcula os segundos

    printf("\nQUICK SORT ITERATIVO:\n%f (tempo de execução em segundos)\nComparacoes: %lu\n", total, *numComparacoes);

    imprimeVetor(vetor, tam);
}

void heapSortIte(int *vetor, size_t tam, uint64_t *numComparacoes, clock_t start, clock_t end)
{
    double total;

    completaVetor(vetor, tam); // preenche o vetor
    start = clock();           // inicia o temporizador
    *numComparacoes = 0;
    *numComparacoes = heapSortSR(vetor, tam); // recebe o total de comparacoes do algoritimo
    end = clock();                            // termina o temporizador

    total = (double)(end - start) / CLOCKS_PER_SEC; // calcula os segundos

    printf("\nHEAP SORT ITERATIVO:\n%f (tempo de execução em segundos)\nComparacoes: %lu\n", total, *numComparacoes);

    imprimeVetor(vetor, tam);
}

void introSortRec(int *vetor, size_t tam, uint64_t *numComparacoes, clock_t start, clock_t end)
{
    double total;

    completaVetor(vetor, tam); // preenche o vetor
    start = clock();           // inicia o temporizador
    *numComparacoes = 0;
    *numComparacoes = algoritmoExtra(vetor, tam); // recebe o total de comparacoes do algoritimo
    end = clock();                                // termina o temporizador

    total = (double)(end - start) / CLOCKS_PER_SEC; // calcula os segundos

    printf("\nINTRO SORT RECURSIVO:\n%f (tempo de execução em segundos)\nComparacoes: %lu\n", total, *numComparacoes);

    imprimeVetor(vetor, tam);
}

int main()
{
    char nome[MAX_CHAR];
    uint64_t numComp;
    ssize_t tamVetor;
    clock_t start = 0, end = 0;

    getNome(nome);
    printf("Trabalho de %s\n", nome);
    printf("GRR %u\n", getGRR());

    printf("\n");

    tamVetor = 100; // tamanho do vetor, e os elementos que irão estar presente dentro do vetor, que vai de 0 até tamVetor -1

    if ( tamVetor < 0)
    {
        printf("Falha Fatal. Impossivel trabalhar com vetores de tamanho negativo.\n");
        return(1);
    }
    
    printf("Trabalhando com um vetor de tamanho: %zd \nE com números de 0 até %zd \n", tamVetor, tamVetor);

    printf("\n");

    int *vetor = (int *)malloc((size_t)tamVetor * sizeof(int));

    if (vetor == NULL)
    {
        printf("Falha fatal. Impossível alocar memoria. \n");
        return (1);
    }

    /*==================================== FUNÇÕES INICIAIS PARA DAR INICIO NOS ALGORITIMOS ====================================*/

    mergeSortRec(vetor, (size_t)tamVetor, &numComp, start, end);

    quickSortRec(vetor, (size_t)tamVetor, &numComp, start, end);

    heapSortRec(vetor, (size_t)tamVetor, &numComp, start, end);

    mergeSortIte(vetor, (size_t)tamVetor, &numComp, start, end);

    quickSortIte(vetor, (size_t)tamVetor, &numComp, start, end);

    heapSortIte(vetor, (size_t)tamVetor, &numComp, start, end);
    
    introSortRec(vetor, (size_t)tamVetor, &numComp, start, end);

    free(vetor);

    return (0);
}
