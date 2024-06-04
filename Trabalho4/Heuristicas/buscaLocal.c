// Função para atribuir cores aleatórias aos nós
#include "buscaLocal.h"


// Função para calcular o número de conflitos
int calcularNumeroConflitos(No** grafo, int numVertices) {
    int conflitos = 0;
    for (int i = 0; i < numVertices; i++) {
        Aresta* adj = grafo[i]->listaAdjacencia;
        while (adj != NULL) {
            if (grafo[i]->cor == adj->destino->cor) {
                conflitos++;
            }
            adj = adj->proximaAresta;
        }
    }
    return conflitos / 2; // Cada conflito é contado duas vezes
}

// Função para calcular o número de cores usadas
int numCoresUsadas(No** grafo, int numVertices) {
    int cores[numVertices];
    for (int i = 0; i < numVertices; i++) {
        cores[i] = 0;
    }

    int numCoresUsadas = 0;
    for (int i = 0; i < numVertices; i++) {
        if (grafo[i]->cor > 0 && cores[grafo[i]->cor - 1] == 0) {
            cores[grafo[i]->cor - 1] = 1;
            numCoresUsadas++;
        }
    }

    return numCoresUsadas;
}

// Função para perturbar a solução atual
void perturbarSolucao(No** grafo, int numVertices) {
    int verticeAleatorio = rand() % numVertices;
    int novaCor = rand() % numVertices + 1;
    grafo[verticeAleatorio]->cor = novaCor;
}

// Função para buscar uma nova solução próxima da atual com limite de tentativas
void buscaLocal(No** grafo, int numVertices, int maxTentativas) {
    int menorConflitos = calcularNumeroConflitos(grafo, numVertices);

    for (int i = 0; i < numVertices; i++) {
        int corOriginal = grafo[i]->cor;
        for (int tentativa = 0; tentativa < maxTentativas; tentativa++) {
            int novaCor = rand() % numVertices + 1;
            if (novaCor != corOriginal) {
                grafo[i]->cor = novaCor;
                int conflitosAtual = calcularNumeroConflitos(grafo, numVertices);
                if (conflitosAtual < menorConflitos) {
                    menorConflitos = conflitosAtual;
                } else {
                    grafo[i]->cor = corOriginal;
                }
            }
        }
    }
}

// Função para resolver o problema de coloração de grafos usando ILS
int ILSColoracao(No** grafo, int numVertices, int maxIteracoes, int maxTentativasBuscaLocal) {
    int melhorSolucao = heuristicaConstrutivaColoracao(grafo, numVertices);
    int melhorNumeroConflitos = calcularNumeroConflitos(grafo, numVertices);
    int iteracoes = 0;

    while (iteracoes < maxIteracoes) {
        No** copiaGrafo = copiarGrafo(grafo, numVertices);
        perturbarSolucao(copiaGrafo, numVertices);
        buscaLocal(copiaGrafo, numVertices, maxTentativasBuscaLocal);

        int numConflitos = calcularNumeroConflitos(copiaGrafo, numVertices);
        int coresUsadas = numCoresUsadas(copiaGrafo, numVertices);

        if (numConflitos == 0) {
            copiarSolucao(copiaGrafo, grafo, numVertices);
            liberarGrafo(copiaGrafo, numVertices);
            return coresUsadas;
        }

        if (numConflitos < melhorNumeroConflitos || (numConflitos == melhorNumeroConflitos && coresUsadas < melhorSolucao)) {
            melhorNumeroConflitos = numConflitos;
            melhorSolucao = coresUsadas;
            copiarSolucao(copiaGrafo, grafo, numVertices);
        }

        liberarGrafo(copiaGrafo, numVertices);
        iteracoes++;
    }

    return melhorSolucao;
}

// Função para copiar o grafo
No** copiarGrafo(No** grafo, int numVertices) {
    No** copia = malloc(numVertices * sizeof(No*));
    for (int i = 0; i < numVertices; i++) {
        copia[i] = malloc(sizeof(No));
        copia[i]->cor = grafo[i]->cor;
        copia[i]->listaAdjacencia = grafo[i]->listaAdjacencia; // Assumindo que listaAdjacencia não precisa ser copiada profundamente
    }
    return copia;
}

// Função para copiar a solução de um grafo para outro
void copiarSolucao(No** fonte, No** destino, int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        destino[i]->cor = fonte[i]->cor;
    }
}

// Função para liberar a memória do grafo
void liberarGrafo(No** grafo, int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        free(grafo[i]);
    }
    free(grafo);
}