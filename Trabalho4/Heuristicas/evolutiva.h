#ifndef EVOLUTIVA_H
#define EVOLUTIVA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define POPULATION_SIZE 100
#define MAX_GENERATIONS 1000
#define MUTATION_RATE 0.01

#include "../Estruturas/no.h"
#include "algoritmoConstrutivo.h"

#define POPULATION_SIZE 100
#define MAX_GENERATIONS 1000
#define MUTATION_RATE 0.01


typedef struct {
    int* colors;
    int fitness;
} Individual;


int numeroConflitos(No** grafo, int numVertices);
void inicializarIndividuo(Individual* individuo, No** grafo, int numVertices);
void liberarIndividuo(Individual* individuo);
void avaliarIndividuo(Individual* individuo, No** grafo, int numVertices);
void inicializarPopulacao(Individual* populacao, No** grafo, int numVertices);
void liberarPopulacao(Individual* populacao);
void avaliarPopulacao(Individual* populacao, No** grafo, int numVertices);
int compararIndividuos(const void* a, const void* b);
void selecionarPais(Individual* populacao, Individual* pais);
void cruzar(Individual* pai1, Individual* pai2, Individual* filho, int numVertices);
void mutar(Individual* individuo, int numVertices);
int coresUsadas(Individual* individuo, int numVertices);
int algoritmoGenetico(No** grafo, int numVertices);



#endif