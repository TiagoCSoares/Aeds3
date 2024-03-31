#ifndef GRAFO_H
#define GRAFO_H

#include "pilha.h"

void adicionarAresta(Aresta** listaAdjacencia, No* destino);
void criarGrafo(char labirinto[LINHAS][COLUNAS], No* nos[LINHAS][COLUNAS]);

#endif
