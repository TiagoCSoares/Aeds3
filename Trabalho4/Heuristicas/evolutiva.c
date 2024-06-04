#include "evolutiva.h"


int numeroConflitos(No** grafo, int numVertices) {
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


void inicializarIndividuo(Individual* individuo, No** grafo, int numVertices) {
    // Usar a heurística construtiva para inicializar as cores do grafo
    heuristicaConstrutivaColoracao(grafo, numVertices);

    // Copiar as cores do grafo para o indivíduo
    individuo->colors = (int*)malloc(numVertices * sizeof(int));
    if (individuo->colors == NULL) {
        fprintf(stderr, "Erro ao alocar memória para individuo->colors\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < numVertices; i++) {
        individuo->colors[i] = grafo[i]->cor;
    }
    individuo->fitness = numeroConflitos(grafo, numVertices);
}

void liberarIndividuo(Individual* individuo) {
    free(individuo->colors);
}

void avaliarIndividuo(Individual* individuo, No** grafo, int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        grafo[i]->cor = individuo->colors[i];
    }
    individuo->fitness = numeroConflitos(grafo, numVertices);
}

void inicializarPopulacao(Individual* populacao, No** grafo, int numVertices) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        inicializarIndividuo(&populacao[i], grafo, numVertices);
    }
}

void liberarPopulacao(Individual* populacao) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        liberarIndividuo(&populacao[i]);
    }
}

void avaliarPopulacao(Individual* populacao, No** grafo, int numVertices) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        avaliarIndividuo(&populacao[i], grafo, numVertices);
    }
}

int compararIndividuos(const void* a, const void* b) {
    return ((Individual*)a)->fitness - ((Individual*)b)->fitness;
}

void selecionarPais(Individual* populacao, Individual* pais) {
    qsort(populacao, POPULATION_SIZE, sizeof(Individual), compararIndividuos);
    for (int i = 0; i < POPULATION_SIZE / 2; i++) {
        pais[i] = populacao[i];
    }
}

void cruzar(Individual* pai1, Individual* pai2, Individual* filho, int numVertices) {
    // Alocar memória para filho->colors se ainda não estiver alocada
    if (filho->colors == NULL) {
        filho->colors = (int*)malloc(numVertices * sizeof(int));
        if (filho->colors == NULL) {
            fprintf(stderr, "Erro ao alocar memória para filho->colors\n");
            exit(EXIT_FAILURE);
        }
    }

    int pontoCruzamento = rand() % numVertices;
    for (int i = 0; i < pontoCruzamento; i++) {
        filho->colors[i] = pai1->colors[i];
    }
    for (int i = pontoCruzamento; i < numVertices; i++) {
        filho->colors[i] = pai2->colors[i];
    }
}

void mutar(Individual* individuo, int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        if ((rand() / (double)RAND_MAX) < MUTATION_RATE) {
            individuo->colors[i] = rand() % numVertices;
        }
    }
}

int coresUsadas(Individual* individuo, int numVertices) {
    int* coresUsadas = (int*)calloc(numVertices, sizeof(int));
    int numCores = 0;

    for (int i = 0; i < numVertices; i++) {
        if (coresUsadas[individuo->colors[i]] == 0) {
            coresUsadas[individuo->colors[i]] = 1;
            numCores++;
        }
    }

    free(coresUsadas);
    return numCores;
}

int algoritmoGenetico(No** grafo, int numVertices) {
    Individual populacao[POPULATION_SIZE];
    Individual pais[POPULATION_SIZE / 2];
    Individual filhos[POPULATION_SIZE];

    inicializarPopulacao(populacao, grafo, numVertices);
    avaliarPopulacao(populacao, grafo, numVertices);

    for (int i = 0; i < POPULATION_SIZE; i++) {
        filhos[i].colors = NULL; // Inicialmente, filhos não têm memória alocada
    }

    for (int geracao = 0; geracao < MAX_GENERATIONS; geracao++) {
        selecionarPais(populacao, pais);

        for (int i = 0; i < POPULATION_SIZE; i++) {
            int indicePai1 = rand() % (POPULATION_SIZE / 2);
            int indicePai2 = rand() % (POPULATION_SIZE / 2);
            cruzar(&pais[indicePai1], &pais[indicePai2], &filhos[i], numVertices);
            mutar(&filhos[i], numVertices);
            avaliarIndividuo(&filhos[i], grafo, numVertices);
        }

        for (int i = 0; i < POPULATION_SIZE; i++) {
            liberarIndividuo(&populacao[i]);
            populacao[i] = filhos[i];
            filhos[i].colors = NULL; // Resetar para evitar liberar memória que ainda será usada
        }

        qsort(populacao, POPULATION_SIZE, sizeof(Individual), compararIndividuos);

        //printf("Geracao %d: Melhor Fitness = %d\n", geracao, populacao[0].fitness);

        if (populacao[0].fitness == 0) {
            break;
        }
    }

    int melhorNumCores = coresUsadas(&populacao[0], numVertices);
    //printf("Melhor solução encontrada com fitness = %d e usando %d cores\n", populacao[0].fitness, melhorNumCores);

    liberarPopulacao(populacao);

    return melhorNumCores;
}