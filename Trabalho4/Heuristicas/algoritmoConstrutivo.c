#include "algoritmoConstrutivo.h"

int heuristicaConstrutivaColoracao(No** grafo, int numVertices) {
    // Inicializa todas as cores dos vértices como não colorido (-1)
    int numCores = numVertices;

    for (int i = 0; i < numVertices; i++) {
        grafo[i]->cor = -1;
    }

    int cores[numCores];
    for (int i = 0; i < numCores; i++) {
        cores[i] = i+1;
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
        int cor = 1;
        while (true) {

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

    // encontrar a maior cor
    int maiorCor = 0;
    for (int i = 0; i < numVertices; i++) {
        if(grafo[i]->cor > maiorCor) {
            maiorCor = grafo[i]->cor;
        }
    }

    return maiorCor;
}