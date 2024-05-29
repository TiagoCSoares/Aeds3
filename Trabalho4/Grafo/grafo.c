#include "grafo.h"


void adicionarAresta(Aresta** listaAdjacencia, No* destino, int peso) { //Adicionar peso máximo?
    Aresta* novaAresta = (Aresta*)malloc(sizeof(Aresta));
    novaAresta->destino = destino;
    novaAresta->proximaAresta = *listaAdjacencia;
    *listaAdjacencia = novaAresta;
}



void liberarMemoria(No** grafo, int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        Aresta* atual = grafo[i]->listaAdjacencia;
        while (atual != NULL) {
            Aresta* proximo = atual->proximaAresta;
            free(atual);
            atual = proximo;
        }
        free(grafo[i]);
    }
    free(grafo);
}



No** criarGrafo(int numVertices) {
    No** grafo = (No**)malloc(numVertices * sizeof(No*));
    for (int i = 0; i < numVertices; i++) {
        grafo[i] = (No*)malloc(sizeof(No));
        grafo[i]->posicao = i;
        grafo[i]->cor = -1;
        grafo[i]->listaAdjacencia = NULL; // Inicialmente, não há adjacências
    }
    return grafo;
}


void imprimirGrafo(No** grafo, int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        Aresta* adj = grafo[i]->listaAdjacencia;
        printf("Node %d: ", i);
        while (adj != NULL) {
            printf("%d ", adj->destino->posicao);
            adj = adj->proximaAresta;
        }
        printf("\n");
    }
}

int grauNo(No* no) {
    int contador = 0;
    Aresta* adj = no->listaAdjacencia;
    while (adj != NULL) {
        contador++;
        adj = adj->proximaAresta;
    }
    return contador;
}

int tamanhoGrafo(No** grafo) {
    int contador = 0;
    while (grafo[contador] != NULL) {
        contador++;
    }
    return contador-1;
}