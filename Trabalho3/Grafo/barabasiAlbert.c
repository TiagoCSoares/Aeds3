#include "barabasiAlbert.h"


void barabasiAlbert(int numVertices, int numInicial){
    No** grafo = criarGrafo(numVertices);

    int novasConexoes = rand() % numInicial + 2;
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
                int peso = rand() % 10 + 1;
                adicionarAresta(&(grafo[i]->listaAdjacencia), grafo[target], peso);
                adicionarAresta(&(grafo[target]->listaAdjacencia), grafo[i], peso);
                conexoesDoNo[i] += 1;
                conexoesDoNo[target] += 1;
                conexoesTotais+=2;
            }
        }
    }

    
    for(int i = numInicial; i < numVertices; i++){
        int conexoes = 0;
        for(int j = 0; j < i; j++){
            float probabilidadeConectar = (float)conexoesDoNo[j] / conexoesTotais;
            float chance = ((float)rand() / RAND_MAX);  // Gerar um número aleatório entre 0 e 1
            if (chance <= probabilidadeConectar) { 
                int peso = rand() % 10 + 1;
                adicionarAresta(&grafo[i]->listaAdjacencia, grafo[j], peso);
                adicionarAresta(&(grafo[j]->listaAdjacencia), grafo[i], peso);
                conexoesDoNo[i]++;
                conexoesDoNo[j]++;
                conexoes+=2;
            }
        }
        while(conexoesDoNo[i] == 0){
                int index = (rand() % i);
                if(index != i) {
                    int peso = rand() % 10 + 1;
                    adicionarAresta(&grafo[i]->listaAdjacencia, grafo[index], peso);
                    adicionarAresta(&(grafo[index]->listaAdjacencia), grafo[i], peso);
                    conexoesDoNo[i]++;
                    conexoesDoNo[index]++;
                    conexoesTotais+=2;     
                }
            }
        conexoesTotais += conexoes;
    }

    //imprimirGrafo(grafo, numVertices);
    escreverOutputGrafos("Output/grafos.txt", grafo, numVertices);
    closeness(grafo, numVertices);
    // Liberar memória
    liberarMemoria(grafo, numVertices);
}
