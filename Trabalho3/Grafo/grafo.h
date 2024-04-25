#ifndef GRAFO_H
#define GRAFO_H

#include "../Estruturas/pilha.h"
#include "../Estruturas/fila.h"

void adicionarAresta(Aresta** listaAdjacencia, No* destino, int peso);
No** criarGrafo(int numVertices);
void liberarMemoria(No** grafo, int numVertices);
void imprimirGrafo(No** grafo, int numVertices);

#endif
