#ifndef GRAFO_H
#define GRAFO_H

#include "../Estruturas/pilha.h"
#include "../Estruturas/fila.h"

void adicionarAresta(Aresta** listaAdjacencia, No* destino);
void criarGrafo(No* nos[LINHAS][COLUNAS]);

#endif
