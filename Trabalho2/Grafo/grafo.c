#include <stdlib.h>
#include <stdio.h>

#include "grafo.h"

void adicionarAresta(Aresta** listaAdjacencia, No* destino) {
    Aresta* novaAresta = (Aresta*)malloc(sizeof(Aresta));
    novaAresta->destino = destino;
    novaAresta->proximaAresta = *listaAdjacencia;
    *listaAdjacencia = novaAresta;
}



void criarGrafo(char labirinto[LINHAS][COLUNAS], No* nos[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (labirinto[i][j] != PAREDE) {
                No* atual = nos[i][j];
                atual->linha = i;
                atual->coluna = j;
                atual->visitado = false;
                atual->percorrido = false;
                atual->listaAdjacencia = NULL;

                // Adicionar arestas para células adjacentes válidas
                if (i > 0 && labirinto[i - 1][j] != PAREDE) {
                    adicionarAresta(&(atual->listaAdjacencia), nos[i - 1][j]);
                }
                if (i < LINHAS - 1 && labirinto[i + 1][j] != PAREDE) {
                    adicionarAresta(&(atual->listaAdjacencia), nos[i + 1][j]);
                }
                if (j > 0 && labirinto[i][j - 1] != PAREDE) {
                    adicionarAresta(&(atual->listaAdjacencia), nos[i][j - 1]);
                }
                if (j < COLUNAS - 1 && labirinto[i][j + 1] != PAREDE) {
                    adicionarAresta(&(atual->listaAdjacencia), nos[i][j + 1]);
                }
            }
        }
    }
}