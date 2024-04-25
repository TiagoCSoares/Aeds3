#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "grafo.h"


void adicionarAresta(Aresta** listaAdjacencia, No* destino, int peso) { //Adicionar peso máximo?
    Aresta* novaAresta = (Aresta*)malloc(sizeof(Aresta));
    novaAresta->peso = peso; //(rand() % 10) +1;  
    novaAresta->destino = destino;
    novaAresta->proximaAresta = *listaAdjacencia;
    *listaAdjacencia = novaAresta;
}



void liberarMemoria(No** grafo, int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        Aresta* adj = grafo[i]->listaAdjacencia;
        while (adj != NULL) {
            Aresta* temp = adj;
            adj = adj->proximaAresta;
            free(temp);
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




void grafoErdosRenyi(No** grafo, int numVertices, float p) {
    int i, j;
    for(i = 0; i < numVertices; i++) {
        for(j = i+1; j < numVertices; j++) {
            if((float)rand() / RAND_MAX <= p) {
                adicionarAresta(grafo[i]->listaAdjacencia, grafo[j], 1);
                adicionarAresta(grafo[j]->listaAdjacencia, grafo[i], 1);
            }
        }
    }
}