#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

#include "ordenacao.h"


void getNome(char nome[])
{
    // substitua por seu nome
    strncpy(nome, "Gabriel Augusto Fabri Soltovski", MAX_CHAR);

    // adicionada terminação manual para caso de overflow
    nome[MAX_CHAR - 1] = '\0';
}

// a função a seguir deve retornar o seu número de GRR
uint32_t getGRR() { return 20222546; }

/*======================================================== FUNÇÕES GERAIS ========================================================*/

int trocar(int *vetor, int j, int t)
{
    int aux;

    // realiza as trocas e retorna o vetor com os elementos trocados
    aux = vetor[j];
    vetor[j] = vetor[t];
    vetor[t] = aux;

    return (*vetor);
}

void copia(int *vetor, int *vet_aux, int j, int t)
{
    int k;
    for (k = j; k <= t; k++) // percorre o vetor copiando os valores do mesmo
    {
        vetor[k] = vet_aux[k - j];
    }
}

/*========================================================== MERGE SORT RECURSIVO ===========================================================*/
void mergeRec(int *vetor, int *vet_aux, int a, int meio, int b, uint64_t *mergeCompRec)
{
    int k;
    int m;
    int i = a;
    int l = meio + 1;

    // Itera sobre os elementos entre os índices 'a' e 'b'
    for (k = 0; k <= b - a; k++)
    {
        // Compara elementos dos dois subvetores e seleciona o menor
        if (l > b || (i <= meio && vetor[i] <= vetor[l]))
        {
            (*mergeCompRec)++;
            m = i;
            i++;
        }
        else
        {
            (*mergeCompRec)++;
            m = l;
            l++;
        }

        // Copia o menor elemento para o vetor auxiliar
        vet_aux[k] = vetor[m];
    }

    copia(vetor, vet_aux, a, b);
}

void aux_mergeRec(int *vetor, int vet_aux[], int a, int b, uint64_t *mergeCompRec)
{
    if (a >= b)
    {
        return;
    }

    int meio = (a + b) / 2;

    // Chama recursivamente para a primeira metade
    aux_mergeRec(vetor, vet_aux, a, meio, mergeCompRec);

    // Chama recursivamente para a segunda metade
    aux_mergeRec(vetor, vet_aux, meio + 1, b, mergeCompRec);

    // Mescla as duas metades
    mergeRec(vetor, vet_aux, a, meio, b, mergeCompRec);
}

uint64_t mergeSort(int vetor[], size_t tam)
{
    int a = 0;

    uint64_t mergeCompRec = 0;

    int *vet_aux = (int *)malloc(tam * sizeof(int));

    if (vet_aux == NULL)
    {
        printf("Falha fatal. Impossível alocar memória.");
        return (1);
    }

    // Chama a função auxiliar para iniciar o merge sort
    aux_mergeRec(vetor, vet_aux, a, tam - 1, &mergeCompRec);

    // Libera a memória alocada para o vetor auxiliar
    free(vet_aux);

    // Retorna o número de comparações feitas
    return (mergeCompRec);
}

/*========================================================== QUICK SORT RECURSIVO ===========================================================*/

int particionaRec(int vetor[], int a, int b, uint64_t *quickComp)
{
    int pivo = vetor[b]; 
    int k = a;

    for (int i = a; i < b; i++)
    {
        if (vetor[i] <= pivo)
        {
            // Troca elementos que são menores ou iguais ao pivô para a esquerda
            trocar(vetor, k, i);
            k++;
            (*quickComp)++;
        }
        (*quickComp)++;
    }

    // Coloca o pivô em sua posição correta
    trocar(vetor, k, b);

    return (k); // Retorna o índice do pivô
}

void auxQuick(int vetor[], int a, int b, uint64_t *quickComp)
{
    if (a >= b)
    {
        return;
    }

    // Particiona o vetor e obtém o índice do pivô
    int meio = particionaRec(vetor, a, b, quickComp);

    // Chama recursivamente para a primeira metade
    auxQuick(vetor, a, meio - 1, quickComp);

    // Chama recursivamente para a segunda metade
    auxQuick(vetor, meio + 1, b, quickComp);
}

uint64_t quickSort(int vetor[], size_t tam)
{
    int a = 0;
    int b = tam - 1;
    uint64_t quickComp = 0;

    // Chama a função auxiliar para iniciar o quicksort
    auxQuick(vetor, a, b, &quickComp);

    // Retorna o número de comparações feitas
    return (quickComp);
}

/*=========================================================== HEAP SORT RECURSIVO ===========================================================*/

void maxHeapifyRec(int h[], int i, int n, uint64_t *heapCompRec)
{
    int maior = i;
    int l = 2 * i + 1; // Calcula o índice do filho esquerdo
    int r = 2 * i + 2; // Calcula o índice do filho direito

    if (l < n && h[l] > h[i])
    {
        maior = l;
    }

    if (r < n && h[r] > h[maior])
    {
        maior = r;
    }

    // Se o maior não é o pai, faz a troca e continua a heap
    if (maior != i)
    {
        trocar(h, i, maior);
        maxHeapifyRec(h, maior, n, heapCompRec);
    }

    (*heapCompRec)++; 
}

void construirMaxHeapRec(int v[], int n, uint64_t *heapCompRec)
{
    // Constrói o max heap a partir do meio do vetor até o início
    for (int i = n / 2; i > 0; i--)
    {
        maxHeapifyRec(v, i - 1, n, heapCompRec);
    }

    // Chama maxHeapifyRec para o primeiro elemento
    maxHeapifyRec(v, 0, n, heapCompRec);
}

uint64_t heapSort(int vetor[], size_t tam)
{
    uint64_t heapCompRec = 0;

    if (tam <= 1)
    {
        return (heapCompRec);
    }

    // Constrói o max heap
    construirMaxHeapRec(vetor, tam, &heapCompRec);

    // Ordena o vetor extraindo o maior elemento e ajustando o heap
    for (int i = tam - 1; i > 0; i--)
    {
        trocar(vetor, 0, i);                      // Troca o maior elemento com o último não ordenado
        maxHeapifyRec(vetor, 0, i, &heapCompRec);
    }

    return (heapCompRec);
}

/*========================================================== MERGE SORT ITERATIVO ===========================================================*/
uint64_t merge(int vetor[], int esq, int meio, int dir)
{
    int i = 0, j = 0, k = esq;
    uint64_t compMergeSR = 0; 
    int n1 = meio - esq + 1;                       // Tamanho do subvetor esquerdo
    int n2 = dir - meio;                           // Tamanho do subvetor direito
    int *vetEsq = (int *)malloc(n1 * sizeof(int)); // Aloca memória para o subvetor esquerdo
    int *vetDir = (int *)malloc(n2 * sizeof(int)); // Aloca memória para o subvetor direito

    // Copia os elementos para os subvetores auxiliares
    for (int idx = 0; idx < n1; idx++) // Usando 'idx' para evitar conflito com 'i' de fora
    {
        vetEsq[idx] = vetor[esq + idx];
    }

    for (int idx = 0; idx < n2; idx++) // Usando 'idx' para evitar conflito com 'i' de fora
    {
        vetDir[idx] = vetor[meio + 1 + idx];
    }

    while (i < n1 && j < n2)
    {
        if (vetEsq[i] <= vetDir[j])
        {
            vetor[k] = vetEsq[i];
            i++;
        }
        else
        {
            vetor[k] = vetDir[j];
            j++;
        }
        k++;
        compMergeSR++;
    }

    // Copia os elementos restantes do subvetor esquerdo, se houver
    while (i < n1)
    {
        vetor[k] = vetEsq[i];
        i++;
        k++;
    }

    // Copia os elementos restantes do subvetor direito, se houver
    while (j < n2)
    {
        vetor[k] = vetDir[j];
        j++;
        k++;
    }

    free(vetEsq);
    free(vetDir);

    return (compMergeSR);
}

uint64_t mergeSortSR(int vetor[], size_t tam)
{
    // Se o tamanho do vetor for menor que 2, não há nada para ordenar
    if (tam < 2)
    {
        return 0;
    }

    // Aloca memória para as pilhas auxiliares
    int *pilhaEsq = (int *)malloc(tam * sizeof(int));
    int *pilhaDir = (int *)malloc(tam * sizeof(int));
    int *pilhaMeio = (int *)malloc(tam * sizeof(int));

    int topo = -1;       // Inicializa o topo da pilha
    uint64_t compMergeSR = 0; // Contador de comparações

    // Inicializa a pilha com os índices iniciais do vetor
    pilhaEsq[++topo] = 0;
    pilhaDir[topo] = tam - 1;
    pilhaMeio[topo] = -1;

    // Enquanto houver elementos na pilha
    while (topo >= 0)
    {
        int esq = pilhaEsq[topo];
        int dir = pilhaDir[topo];
        int meio = pilhaMeio[topo];
        topo--;

        if (meio == -1)
        {
            if (esq < dir)
            {
                meio = esq + (dir - esq) / 2;

                // Empilha os índices atuais com o meio atualizado
                pilhaEsq[++topo] = esq;
                pilhaDir[topo] = dir;
                pilhaMeio[topo] = meio;

                // Empilha a parte esquerda
                pilhaEsq[++topo] = esq;
                pilhaDir[topo] = meio;
                pilhaMeio[topo] = -1;

                // Empilha a parte direita
                pilhaEsq[++topo] = meio + 1;
                pilhaDir[topo] = dir;
                pilhaMeio[topo] = -1;
            }
        }
        else
        {
            compMergeSR += merge(vetor, esq, meio, dir);
        }
    }

    free(pilhaEsq);
    free(pilhaDir);
    free(pilhaMeio);

    return (compMergeSR);
}

/*========================================================== QUICK SORT ITERATIVO ===========================================================*/

int particionar(int vetor[], int a, int b, uint64_t *compQuickSR)
{
    int m = a;
    int x = vetor[b]; // Define o pivô como o último elemento do vetor

    for (int i = a; i < b; i++)
    {
        if (vetor[i] <= x)
        {
            trocar(vetor, m, i); // Troca elementos que são menores ou iguais ao pivô para a esquerda
            m++;
        }
        (*compQuickSR)++; 
    }

    trocar(vetor, m, b); // Coloca o pivô em sua posição correta

    return (m); 
}

uint64_t quickSortSR(int vetor[], size_t tam)
{
    int topo = 0;
    uint64_t compQuickSR = 0; 

    if (tam <= 1)
    {
        return (compQuickSR);
    }

    int *p = (int *)malloc(tam * sizeof(int) * 2);

    if (p == NULL)
    {
        return (compQuickSR);
    }

    // Inicializa a pilha com os índices iniciais do vetor
    p[topo++] = 0;
    p[topo++] = (int)(tam - 1);

    while (topo > 0)
    {
        int b = p[--topo];
        int a = p[--topo];

        if (a < b)
        {
            int m = particionar(vetor, a, b, &compQuickSR);

            // Empilha os índices das sub-partições
            p[topo++] = a;
            p[topo++] = m - 1;
            p[topo++] = m + 1;
            p[topo++] = b;
        }
    }

    free(p);

    return (compQuickSR);
}

/*=========================================================== HEAP SORT ITERATIVO ===========================================================*/

void maxHeapify(int h[], int n, int i, uint64_t *compHeapSR)
{
    int maior = i;     // Inicializa o maior como o índice do nó atual
    int l = 2 * i + 1; // Índice do filho esquerdo
    int r = 2 * i + 2; // Índice do filho direito


    while (l < n)
    {
        if (h[l] > h[maior])
        {
            maior = l;
        }

        if (r < n && h[r] > h[maior])
        {
            maior = r;
        }

        if (maior != i)
        {
            trocar(h, i, maior);

            i = maior;
            l = 2 * i + 1;
            r = 2 * i + 2;

            (*compHeapSR)++; 
        }
        else
        {
            return;
        }
    }
}

void construirMaxHeap(int v[], int n, uint64_t *compHeapSR)
{
    // Constrói o max heap a partir do meio do vetor até o início
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        maxHeapify(v, n, i, compHeapSR);

        if (i == 0)
        {
            return; // Se chegarmos ao início, não há mais elementos para ajustar
        }
    }
}

uint64_t heapSortSR(int vetor[], size_t tam)
{
    uint64_t compHeapSR = 0;

    if (tam <= 1)
    {
        return (compHeapSR);
    }

    construirMaxHeap(vetor, tam, &compHeapSR);

    for (int i = tam - 1; i > 0; i--)
    {
        trocar(vetor, 0, i);                  // Move o maior elemento para o final do vetor
        maxHeapify(vetor, i, 0, &compHeapSR); // Ajusta o heap para o tamanho reduzido
    }

    return (compHeapSR);
}

/*=========================================================== INTRO SORT RECURSIVO ===========================================================*/

void insertionSort(int vetor[], int inicio, int fim, uint64_t *comparacoes) 
{
    for (int i = inicio + 1; i <= fim; i++) 
    {
        int j = i - 1;
        int chave = vetor[i];

        // Move os elementos maiores que a chave para a frente
        while (j >= inicio && vetor[j] > chave) 
        {
            vetor[j + 1] = vetor[j];
            j--;
            (*comparacoes)++;
        }
        vetor[j + 1] = chave;
        (*comparacoes)++;
    }
}

void introsortRec(int vetor[], int inicio, int fim, int maxDepth, uint64_t *comparacoes) 
{
    int tamanho = fim - inicio + 1;

    // Limite para o uso de InsertionSort (10% do tamanho do vetor)
    int InsertionSortLimit = tamanho / 10; 

    // Usa InsertionSort para subarrays pequenos
    if (tamanho <= InsertionSortLimit) 
    {
        insertionSort(vetor, inicio, fim, comparacoes);
        return;
    }

    // Muda para HeapSort se a profundidade máxima for atingida
    if (maxDepth == 0)
    {
        *comparacoes += heapSort(&vetor[inicio], tamanho);
        return;
    }

    // Usa QuickSort como padrão
    int pivo = particionaRec(vetor, inicio, fim, comparacoes);

    introsortRec(vetor, inicio, pivo - 1, maxDepth - 1, comparacoes);
    introsortRec(vetor, pivo + 1, fim, maxDepth - 1, comparacoes);
}

uint64_t algoritmoExtra(int vetor[], size_t tam) 
{
    uint64_t comparacoes = 0;

    // Calcula log2(tam) manualmente
    int maxDepth = 0;

    size_t tempTam = tam;

    while (tempTam > 1) 
    {
        tempTam >>= 1; // Desloca os bits para a direita (divisão por 2)
        maxDepth++;
    }

    // Define a profundidade máxima como 2 * log2(tamanho)
    maxDepth *= 2;

    introsortRec(vetor, 0, tam - 1, maxDepth, &comparacoes);

    return (comparacoes);
}
