// Função para atribuir cores aleatórias aos nós
#include "buscaLocal.h"

void atribuir_cores_aleatorias(No** grafo, int numVertices) {
    srand(time(NULL));  // Inicializa a semente aleatória

    int numCores = numVertices/10;
    for (int i = 0; i < numVertices; i++) {
        grafo[i]->cor = rand() % numCores;  
    }
}

// Função para calcular o número de conflitos no grafo
int calcular_conflitos(No** grafo, int numVertices) {
    int conflitos = 0;
    for (int i = 0; i < numVertices; i++) {
        No* no_atual = grafo[i];
        Aresta* adjacente = no_atual->listaAdjacencia;
        while (adjacente != NULL) {
            if (no_atual->cor == adjacente->destino->cor) {
                conflitos++;
            }
            adjacente = adjacente->proximaAresta;
        }
    }
    return conflitos / 2;  // Cada conflito é contado duas vezes
}


// Função de busca local para coloração de grafos
int busca_local(No** grafo, int numVertices) {
    int iteracoes_max = 1000;  // Número máximo de iterações
    int iteracao = 0;

    int numCores = numVertices / 3;

    atribuir_cores_aleatorias(grafo, numVertices);

    while (iteracao < iteracoes_max) {
        int nodo = rand() % numVertices;  // Seleciona um nó aleatoriamente
        int cor_original = grafo[nodo]->cor;
        int cor_vizinha = (cor_original + 1) % numCores;  // Troca para a próxima cor

        // Verifica se a troca reduz o número de conflitos
        grafo[nodo]->cor = cor_vizinha;
        int conflitos_nova_cor = calcular_conflitos(grafo, numVertices);
        if (conflitos_nova_cor < calcular_conflitos(grafo, numVertices)) {
            // Se a troca reduz os conflitos, mantenha a nova cor
            continue;
        } else {
            // Caso contrário, desfaz a troca
            grafo[nodo]->cor = cor_original;
        }

        iteracao++;
    }

    
    
    // Encontrar cores únicas utilizadas
    bool cores_utilizadas[numCores];
    for (int i = 0; i < numCores; i++) {
        cores_utilizadas[i] = false; // Inicializa todas as cores como não utilizadas
    }

    for (int i = 0; i < numVertices; i++) {
        cores_utilizadas[grafo[i]->cor] = true; // Marca a cor como utilizada
    }

    // Contar quantas cores estão sendo utilizadas
    int cores_utilizadas_count = 0;
    for (int i = 0; i < numCores; i++) {
        if (cores_utilizadas[i]) {
            cores_utilizadas_count++;
        }
    }

    return cores_utilizadas_count;
}