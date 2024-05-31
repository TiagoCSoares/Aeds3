#include "closeness.h"


void closeness(No** grafo, int numVertices) {
    // Implementar
    float closeness[numVertices];

    for(int i = 0; i < numVertices; i++) {
        int *dist = dijkstra(grafo, numVertices, i);
        int soma = 0;
        for(int j = 0; j < numVertices; j++) {
            soma += dist[j];
        }
        closeness[i] = (float)(numVertices-1) / soma;
    }

    escreverOutputCloseness("Output/closeness.txt" ,closeness, numVertices);
}