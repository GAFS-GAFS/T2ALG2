#ifndef ORDENACAO_H_
#define ORDENACAO_H_

#include <stdint.h>
#include <sys/types.h>

#define MAX_CHAR 50

// a função getNome deve colocar o seu nome no vetor
// seu nome pode ter no máximo MAX_CHAR_NOME - 1 caracteres
void getNome(char nome[]);

// a função getNomeAlgoritmoExtra deve colocar o nome do algoritmo
// extra implementado no trabalho
void getNomeAlgoritmoExtra(char nomeAlg[]);

// a função a seguir deve retornar o seu número de GRR
uint32_t getGRR();

// Cada uma das funções deve ordenar o vetor passado como parâmetro

// O retorno das funções de ordenação é o número de comparações
// entre elementos do vetor

uint64_t mergeSort(int vetor[], size_t tam);

uint64_t quickSort(int vetor[], size_t tam);

uint64_t heapSort(int vetor[], size_t tam);

// As funções que terminam em SR são "Sem Recursão"
uint64_t mergeSortSR(int vetor[], size_t tam);

uint64_t quickSortSR(int vetor[], size_t tam);

uint64_t heapSortSR(int vetor[], size_t tam);

// Na função algoritmoExtra implemente o algoritmo extra solicitado.
// Se o seu algoritmo escolhido não faz comparações, retorne -1.
uint64_t algoritmoExtra(int vetor[], size_t tam);

#endif  // ORDENACAO_H_