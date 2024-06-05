#ifndef BUSCALOCAL_H
#define BUSCALOCAL_H

#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define MAX_ITERACOES 100
#define MAX_BUSCAS 10

#include "../Estruturas/no.h"
#include "algoritmoConstrutivo.h"


int calcularNumeroConflitos(No** grafo, int numVertices);
int numCoresUsadas(No** grafo, int numVertices);
void perturbarSolucao(No** grafo, int numVertices);
void buscaLocal(No** grafo, int numVertices, int maxTentativas) ;
int ILSColoracao(No** grafo, int numVertices);
No** copiarGrafo(No** grafo, int numVertices);
void copiarSolucao(No** fonte, No** destino, int numVertices);
void liberarGrafo(No** grafo, int numVertices);

#endif