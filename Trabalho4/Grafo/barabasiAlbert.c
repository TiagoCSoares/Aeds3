#include "barabasiAlbert.h"


void barabasiAlbert(int numVertices, int numInicial, int adjMaximo, char nome[], int numNomes) {
    No** grafo = criarGrafo(numVertices);

    srand(time(NULL));

    int novasConexoes = rand() % adjMaximo + 1; // Número de conexões que cada novo nó deve ter, será no intervalo [2, numInicial+1]
    int conexoesTotais = 0;
    int conexoesDoNo[numVertices];
    for (int i = 0; i < numVertices; i++) {
        conexoesDoNo[i] = 0;
    }

    for (int i = 0; i < numInicial; i++) {
        // Conecta cada novo nó a um conjunto aleatório de nós existentes
        for (int j = 0; j < novasConexoes; j++) {
            int target = rand() % numInicial; // Escolhe um nó existente aleatoriamente
            if(target == i) {
                j--;
                continue;
            }

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
            if (!arestaExiste && grafo[target]->grau < adjMaximo && grafo[i]->grau < adjMaximo) {
                adicionarAresta(&(grafo[i]->listaAdjacencia), grafo[target]);
                adicionarAresta(&(grafo[target]->listaAdjacencia), grafo[i]);
                grafo[i]->grau++;
                grafo[target]->grau++;
                conexoesDoNo[i]++;
                conexoesDoNo[target]++;
                conexoesTotais += 2;
            }
        }
    }

    for (int i = numInicial; i < numVertices; i++) {
        int conexoes = 0;
        for (int j = 0; j < i; j++) {
            float probabilidadeConectar = (float)conexoesDoNo[j] / conexoesTotais;
            float chance = ((float)rand() / RAND_MAX);  // Gerar um número aleatório entre 0 e 1
            if (chance <= probabilidadeConectar && grafo[i]->grau < adjMaximo && grafo[j]->grau < adjMaximo) {
                adicionarAresta(&(grafo[i]->listaAdjacencia), grafo[j]);
                adicionarAresta(&(grafo[j]->listaAdjacencia), grafo[i]);
                grafo[i]->grau++;
                grafo[j]->grau++;
                conexoesDoNo[i]++;
                conexoesDoNo[j]++;
                conexoes += 2;
            }
        }
        // Garante que cada nó tem pelo menos uma conexão
        int tentativa = 0;
        while (conexoesDoNo[i] == 0 && tentativa < i) { // Limite o número de tentativas
            int index = (rand() % i);
            if (index != i && grafo[i]->grau < adjMaximo && grafo[index]->grau < adjMaximo) {
                adicionarAresta(&(grafo[i]->listaAdjacencia), grafo[index]);
                adicionarAresta(&(grafo[index]->listaAdjacencia), grafo[i]);
                grafo[i]->grau++;
                grafo[index]->grau++;
                conexoesDoNo[i]++;
                conexoesDoNo[index]++;
                conexoesTotais += 2;
            }
            tentativa++;
        }
        conexoesTotais += conexoes;
    }

    // Cria string com o nome do arquivo
    char nomeArquivoGrafo[256];
    snprintf(nomeArquivoGrafo, sizeof(nomeArquivoGrafo), "Output/%s/ba%d.txt", nome, numNomes);

    // Escreve o grafo no arquivo
    escreverOutputGrafos(nomeArquivoGrafo, grafo, numVertices);

    // Libera memória
    //liberarMemoria(grafo, numVertices);
}
