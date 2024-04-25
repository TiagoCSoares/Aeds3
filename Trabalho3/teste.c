#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "Grafo/grafo.h"


void adicionarAresta(Aresta** listaAdjacencia, No* destino, int peso) { //Adicionar peso máximo?
    Aresta* novaAresta = (Aresta*)malloc(sizeof(Aresta));
    novaAresta->peso = peso; //(rand() % 10) +1;  
    novaAresta->destino = destino;
    novaAresta->proximaAresta = *listaAdjacencia;
    *listaAdjacencia = novaAresta;
}



void watts_strogatz(int numVertices, int ligacoesIniciais, float p) {
    No** grafo = criarGrafo(numVertices);
    int i, j, target;
    bool conectado;

    //srand(time(NULL)); // Inicialização do gerador de números aleatórios

    // Criação do grafo em anel
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < ligacoesIniciais / 2; j++) {
            adicionarAresta(&(grafo[i]->listaAdjacencia), grafo[(i + j + 1) % numVertices], 1);
            adicionarAresta(&(grafo[i]->listaAdjacencia), grafo[(i - j - 1 + numVertices) % numVertices], 1);
        }
    }

    // Reconexão com probabilidade p
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < ligacoesIniciais; j++) {
            if ((float)rand() / RAND_MAX < p) {
                do {
                    target = rand() % numVertices;
                    conectado = false;
                    Aresta* adj = grafo[i]->listaAdjacencia;
                    while (adj != NULL) {
                        if (adj->destino->posicao == target) {
                            conectado = true;
                            break;
                        }
                        adj = adj->proximaAresta;
                    }
                } while (target == i || conectado);
                
                // Atualizar as conexões bidirecionais
                adicionarAresta(&(grafo[i]->listaAdjacencia), grafo[target], 1);
                adicionarAresta(&(grafo[target]->listaAdjacencia), grafo[i], 1);
            }
        }
    }

    // Impressão do grafo resultante 
    for (i = 0; i < numVertices; i++) {
        Aresta* adj = grafo[i]->listaAdjacencia;
        printf("Node %d: ", i);
        while (adj != NULL) {
            printf("%d ", adj->destino->posicao);
            adj = adj->proximaAresta;
        }
        printf("\n");
    }

    // Liberar memória
    for (i = 0; i < numVertices; i++) {
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

int main() {
    int n = 75;  // Número de nós
    int k = 4;   // Cada nó é inicialmente conectado a k vizinhos próximos
    float p = 0.1;  // Probabilidade de reconexão

    watts_strogatz(n, k, p);
    return 0;
}