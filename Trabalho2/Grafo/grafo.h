#ifndef GRAFO_H
#define GRAFO_H

#include "../Estruturas/pilha.h"
#include "../Estruturas/fila.h"
#include "../LabirintoOperacoes/labirinto.h"

void adicionarAresta(Aresta** listaAdjacencia, No* destino);
void criarGrafo(char labirinto[LINHAS][COLUNAS], No* nos[LINHAS][COLUNAS]);

#endif
