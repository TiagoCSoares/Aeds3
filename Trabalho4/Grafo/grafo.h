#ifndef GRAFO_H
#define GRAFO_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../Estruturas/pilha.h"
#include "../Estruturas/fila.h"

void adicionarAresta(Aresta** listaAdjacencia, No* destino);
No** criarGrafo(int numVertices);
void liberarMemoria(No** grafo, int numVertices);
void imprimirGrafo(No** grafo, int numVertices);
int grauNo(No* no);
int tamanhoGrafo(No** grafo);

#endif
