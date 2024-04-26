#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>

#include "Grafo/grafo.h"

/*
Para cada nó existente na lista de nós:
    // Calcule a probabilidade proporcional ao número de conexões do nó
    probabilidade_conexão = (número_de_conexões_do_nó_existente + 1) / (soma_total_de_conexões + número_de_nós)

    // Adicione a probabilidade acumulada ao nó na lista de probabilidade acumulada
    Se a lista de probabilidade acumulada não estiver vazia:
        probabilidade_acumulada = probabilidade_acumulada_do_nó_anterior + probabilidade_conexão
    Senão:
        probabilidade_acumulada = probabilidade_conexão

    Adicione (nó_existente, probabilidade_acumulada) à lista de probabilidade acumulada
Fim Para
*/


void adicionarAresta(Aresta** listaAdjacencia, No* destino, int peso) { //Adicionar peso máximo?
    Aresta* novaAresta = (Aresta*)malloc(sizeof(Aresta));
    novaAresta->peso = peso; //(rand() % 10) +1;  
    novaAresta->destino = destino;
    novaAresta->proximaAresta = *listaAdjacencia;
    *listaAdjacencia = novaAresta;
}



int grauNo(No* no) {
    int contador = 0;
    Aresta* adj = no->listaAdjacencia;
    while (adj != NULL) {
        contador++;
        adj = adj->proximaAresta;
    }
    return contador;
}

void imprimirGrafo(No** grafo, int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        Aresta* adj = grafo[i]->listaAdjacencia;
        printf("Node %d: ", i);
        while (adj != NULL) {
            printf("%d ", adj->destino->posicao);
            adj = adj->proximaAresta;
        }
        printf("\n");
    }
}



/*void watts_strogatz(int numVertices, int ligacoesIniciais, float p) {
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

*/

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

// Função para imprimir o vetor de distâncias
void printSolution(int dist[], int numVertices) {
    printf("Vértice \t Distância até a Origem\n");
    for (int i = 0; i < numVertices; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Função que implementa o algoritmo de Dijkstra para um grafo representado
// por uma matriz de adjacências
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



No** barabaseAlbert(int numVertices, int numInicial){
    No** grafo = criarGrafo(numVertices);

    int novasConexoes = 2;//rand() % numInicial;
    int conexoesTotais = 0;
    int conexoesDoNo[75] = {0};

    //srand(time(NULL));
    for (int i = 1; i < numInicial; i++) {
        // Conecta cada novo nó a um conjunto aleatório de nós existentes
        for (int j = 0; j < novasConexoes; j++) {
            int target = rand() % i; // Escolhe um nó existente aleatoriamente

            // Verifica se a aresta já existe na lista de adjacência de grafo[i]
            Aresta* adj = grafo[i]->listaAdjacencia;
            bool arestaExiste = false;
            while (adj != NULL) {
                if (adj->destino->posicao == target) {
                    arestaExiste = true;
                    break;
                }
                adj = adj->proximaAresta;
            }

            // Se a aresta não existir, adiciona a nova aresta
            if (!arestaExiste) {
                adicionarAresta(&(grafo[i]->listaAdjacencia), grafo[target], 1);
                adicionarAresta(&(grafo[target]->listaAdjacencia), grafo[i], 1);
                conexoesDoNo[i] += 1;
                conexoesDoNo[target] += 1;
                conexoesTotais+=2;
            }
        }
    }

    
    for(int i = numInicial; i < numVertices; i++){
        int novasConexoes = 0;
        for(int j = 0; j < i; j++){
            float probabilidadeConectar = (float)conexoesDoNo[j] / conexoesTotais;
            float chance = ((float)rand() / RAND_MAX);  // Gerar um número aleatório entre 0 e 1
            if (chance <= probabilidadeConectar) { 
                adicionarAresta(&grafo[i]->listaAdjacencia, grafo[j], i);
                adicionarAresta(&(grafo[j]->listaAdjacencia), grafo[i], 1);
                conexoesDoNo[i]++;
                conexoesDoNo[j]++;
                novasConexoes+=2;
            }
        }
        while(conexoesDoNo[i] == 0){
                int index = (rand() % i);
                if(index != i)
                adicionarAresta(&grafo[i]->listaAdjacencia, grafo[index], i);
                adicionarAresta(&(grafo[index]->listaAdjacencia), grafo[i], 1);
                conexoesDoNo[i]++;
                conexoesDoNo[index]++;
                conexoesTotais+=2;     
            }
        conexoesTotais += novasConexoes;
    }
    //imprimirGrafo(grafo, numVertices);
    return grafo;
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

void closeness(No** grafo, int numVertices) {
    // Implementar
    float closeness[numVertices];

    for(int i = 0; i < numVertices; i++) {
        int *dist = dijkstra(grafo, numVertices, i);
        int soma = 0;
        for(int j = 0; j < numVertices; j++) {
            soma += dist[j];
        }
        closeness[i] = (float)soma / (numVertices - 1);
    }
}

int main() {
    int n = 75;  // Número de nós
    int k = 8;   // Cada nó é inicialmente conectado a k vizinhos próximos
    float p = 0.1;  // Probabilidade de reconexão

    No** grafo = barabaseAlbert(n, k);
    /*imprimirGrafo(grafo, n);
    int *dist = (int*)malloc(n * sizeof(int));
    dist = dijkstra(grafo, n, 0);
    printSolution(dist, n);*/
    closeness(grafo, n);

    //float chance = ((float)rand() / RAND_MAX);
    //printf("%f\n", chance);
    return 0;
}