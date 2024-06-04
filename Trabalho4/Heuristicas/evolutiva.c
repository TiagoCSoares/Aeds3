// Função para atribuir cores aleatórias aos nós
#include "evolutiva.h"

void atribuirCoresAleatorias(No** grafo, int numVertices, int numCores) {
    srand(time(NULL));  // Inicializa a semente aleatória
    for (int i = 0; i < numVertices; i++) {
        grafo[i]->cor = rand() % numCores;  // Atribui uma cor aleatória de 0 a numCores-1
    }
}

// Função para calcular o número de conflitos no grafo
int calcularConflitos(No** grafo, int numVertices) {
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

// Função para inicializar a população com atribuições de cores aleatórias
void inicializar_populacao(No** grafo, int numVertices, int numCores, int populacao[][numVertices]) {
    for (int i = 0; i < POPULACAO_SIZE; i++) {
        atribuirCoresAleatorias(grafo, numVertices, numCores);
        for (int j = 0; j < numVertices; j++) {
            populacao[i][j] = grafo[j]->cor;
        }
    }
}

// Função para avaliar a aptidão de cada solução na população (número de conflitos)
void avaliar_aptidao(No** grafo, int numVertices, int populacao[][numVertices], int aptidao[]) {
    for (int i = 0; i < POPULACAO_SIZE; i++) {
        for (int j = 0; j < numVertices; j++) {
            grafo[j]->cor = populacao[i][j];
        }
        aptidao[i] = calcularConflitos(grafo, numVertices);
    }
}

// Função para realizar o crossover entre dois pais para gerar um filho
void crossover(int pai1[], int pai2[], int filho[], int numVertices) {
    // Pontos de corte para o crossover
    int ponto_corte1 = rand() % numVertices;
    int ponto_corte2 = rand() % numVertices;

    // Garante que ponto_corte1 < ponto_corte2
    if (ponto_corte1 > ponto_corte2) {
        int temp = ponto_corte1;
        ponto_corte1 = ponto_corte2;
        ponto_corte2 = temp;
    }

    // Copia as seções dos pais para o filho
    for (int i = 0; i < numVertices; i++) {
        if (i < ponto_corte1 || i >= ponto_corte2) {
            filho[i] = pai1[i];
        } else {
            filho[i] = pai2[i];
        }
    }
}

// Função para realizar a mutação em um indivíduo (cromossomo)
void mutacao(int individuo[], int numVertices, int numCores) {
    for (int i = 0; i < numVertices; i++) {
        if ((double)rand() / RAND_MAX < TAXA_MUTACAO) {
            individuo[i] = rand() % numCores;
        }
    }
}

// Função para selecionar os pais para reprodução com base na aptidão
void selecao_pais(int aptidao[], int pai1[], int pai2[], int numVertices) {
    int index_pai1 = 0, index_pai2 = 0;
    int menor_aptidao = numVertices * numVertices;  // Valor máximo possível para o número de conflitos

    // Seleciona os dois pais com menor aptidão
    for (int i = 0; i < POPULACAO_SIZE; i++) {
        if (aptidao[i] < menor_aptidao) {
            index_pai2 = index_pai1;
            index_pai1 = i;
            menor_aptidao = aptidao[i];
        }
    }

    // Copia os pais selecionados
    for (int i = 0; i < numVertices; i++) {
        pai1[i] = index_pai1;
        pai2[i] = index_pai2;
    }
}

// Função principal para a heurística evolutiva
int heuristica_evolutiva(No** grafo, int numVertices) {
    
    int numCores = numVertices / 3;

    int populacao[POPULACAO_SIZE][numVertices];
    int aptidao[POPULACAO_SIZE];
    int pai1[numVertices], pai2[numVertices], filho[numVertices];

    inicializar_populacao(grafo, numVertices, numCores, populacao);
    avaliar_aptidao(grafo, numVertices, populacao, aptidao);

    // Loop das gerações
    for (int geracao = 0; geracao < NUM_GERACOES; geracao++) {
        // Seleção dos pais para reprodução
        selecao_pais(aptidao, pai1, pai2, numVertices);

        // Reprodução (crossover)
        crossover(populacao[pai1[0]], populacao[pai2[0]], filho, numVertices);

        // Mutação
        mutacao(filho, numVertices, numCores);

        // Avaliação da aptidão do filho
        for (int j = 0; j < numVertices; j++) {
            grafo[j]->cor = filho[j];
        }
        aptidao[POPULACAO_SIZE - 1] = calcularConflitos(grafo, numVertices);

        // Atualização da população
        for (int i = 0 ; i < POPULACAO_SIZE - 1; i++) {
            if (aptidao[i] > aptidao[POPULACAO_SIZE - 1]) {
                for (int j = 0; j < numVertices; j++) {
                    populacao[i][j] = filho[j];
                }
                break;
            }
        }
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