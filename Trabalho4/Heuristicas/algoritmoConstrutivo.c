#include <stdio.h>
#include "../Estruturas/no.h"


void heuristicaConstrutivaColoracao(No** grafo, int numVertices, int numCores) {
    // Inicializa todas as cores dos vértices como não colorido (-1)
    for (int i = 0; i < numVertices; i++) {
        grafo[i]->cor = -1;
    }

    int cores[numCores];
    for (int i = 0; i < numCores; i++) {
        cores[i] = i;
    }

    // Organiza de acordo com o grau
    for (int i = 0; i < numVertices; i++) {
        for (int j = i + 1; j < numVertices; j++) {
            if (grauNo(grafo[i]) < grauNo(grafo[j])) {
                No* temp = grafo[i];
                grafo[i] = grafo[j];
                grafo[j] = temp;
            }
        }
    }

    // Colorir
    for (int i = 0; i < numVertices; i++) {
        int cor = 0;
        while (true) {
            if (cor >= numCores) {
                printf("Não foi possível colorir o grafo com %d cores\n", numCores);
                return;
            }

            bool corDisponivel = true;
            Aresta* adj = grafo[i]->listaAdjacencia;
            while (adj != NULL) {
                if (adj->destino->cor == cor) {
                    corDisponivel = false;
                    break;
                }
                adj = adj->proximaAresta;
            }

            if (corDisponivel) {
                grafo[i]->cor = cor;
                break;
            }
            cor++;
        }
    }

    // printar a cor
    for (int i = 0; i < numVertices; i++) {
        printf("Vértice %d: cor %d\n", i, grafo[i]->cor);
    }
}