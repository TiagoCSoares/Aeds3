#ifndef EVOLUTIVA_H
#define EVOLUTIVA_H

#include <stdio.h>
#include <time.h>

#include "../Estruturas/no.h"

#define POPULACAO_SIZE 50
#define NUM_GERACOES 1000
#define TAXA_MUTACAO 0.1


void atribuirCoresAleatorias(No** grafo, int numVertices, int numCores);
int calcularConflitos(No** grafo, int numVertices);
void inicializar_populacao(No** grafo, int numVertices, int numCores, int populacao[][numVertices]);
void avaliar_aptidao(No** grafo, int numVertices, int populacao[][numVertices], int aptidao[]);
void crossover(int pai1[], int pai2[], int filho[], int numVertices);
void mutacao(int individuo[], int numVertices, int numCores);
void selecao_pais(int aptidao[], int pai1[], int pai2[], int numVertices);
int heuristica_evolutiva(No** grafo, int numVertices);

#endif