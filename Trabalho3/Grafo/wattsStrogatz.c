#include "wattsStrogatz.h"

void wattsStrogatz(int numVertices, int ligacoesIniciais, float p) {
    No** grafo = criarGrafo(numVertices);
    int i, j, target;
    bool conectado;

    //srand(time(NULL)); // Inicialização do gerador de números aleatórios

    // Criação do grafo em anel
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < ligacoesIniciais / 2; j++) {
            int peso = rand() % 10 + 1;
            adicionarAresta(&(grafo[i]->listaAdjacencia), grafo[(i + j + 1) % numVertices], peso);
            adicionarAresta(&(grafo[i]->listaAdjacencia), grafo[(i - j - 1 + numVertices) % numVertices], peso);
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
                int peso = rand() % 10 + 1;
                adicionarAresta(&(grafo[i]->listaAdjacencia), grafo[target], peso);
                adicionarAresta(&(grafo[target]->listaAdjacencia), grafo[i], peso);
            }
        }
    }

    escreverOutputGrafos("Output/grafos.txt", grafo, numVertices);
    closeness(grafo, numVertices);
    //imprimirGrafo(grafo, numVertices);
    // Liberar memória
    liberarMemoria(grafo, numVertices);
}