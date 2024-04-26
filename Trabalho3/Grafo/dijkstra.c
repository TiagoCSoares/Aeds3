#include "dijkstra.h"

int minDistance(int dist[], int sptSet[], int numVertices) {
    int min = INT_MAX;
    int min_index = -1;
    
    for (int v = 0; v < numVertices; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}


void printSolution(int dist[], int numVertices) {
    printf("Vértice \t Distância até a Origem\n");
    for (int i = 0; i < numVertices; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}



int* dijkstra(No** grafo, int numVertices, int raiz) {
    // dist[i] será a distância mínima de raiz até i
    int *dist = (int*)malloc(numVertices * sizeof(int)); // Aloca memória para o array dist
        if (dist == NULL) {
            // Se a alocação de memória falhar, retorne NULL ou trate o erro de outra forma
            return NULL;
        }

    int sptSet[numVertices];   // sptSet[i] será verdadeiro se o vértice i estiver incluído no caminho mais curto

    // Inicializa todas as distâncias como infinito e sptSet[] como falso
    for (int i = 0; i < numVertices; i++)
        dist[i] = INT_MAX, sptSet[i] = 0;

    // A distância do vértice origem para ele mesmo é sempre zero
    dist[raiz] = 0;

    // Encontre o caminho mais curto para todos os vértices
    for (int count = 0; count < numVertices-1; count++) {
        // Escolhe o vértice de menor distância do conjunto de vértices ainda não processados
        int u = minDistance(dist, sptSet, numVertices);
        if(u != -1){
        // Marca o vértice escolhido como processado
            sptSet[u] = 1;

            Aresta* cursor = grafo[u]->listaAdjacencia;
            while(cursor != NULL){
                int v = cursor->destino->posicao;
                if(!sptSet[v] && dist[u] != INT_MAX && dist[u] + cursor->peso < dist[v]){
                    dist[v] = dist[u] + cursor->peso;
                }
                cursor = cursor->proximaAresta;
            }
        }
    }

    // Imprime o array de distâncias construído
    //printSolution(dist, numVertices);
    return dist;
}