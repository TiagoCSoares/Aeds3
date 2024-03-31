#include "../Estruturas/pilha.h"
#include "../Estruturas/fila.h"
#include "../labirinto.h"
#include <stdlib.h>

No* buscaPorLargura(No* nos[LINHAS][COLUNAS], No entrada, No saida, Fila* fila, char labirinto[LINHAS][COLUNAS]) {
    while (!filaVazia(fila)) {
        No* atual = desenfileirar(fila); // Obtemos o próximo nó da fila

        // Verifica se o nó atual é a saída
        if (atual->linha == saida.linha && atual->coluna == saida.coluna) {
            return atual; // Achou o nó de saída
        }

        // Marca o nó atual como visitado
        atual->visitado = true;

        // Itera sobre os nós adjacentes
        Aresta* listaAdjacencia = atual->listaAdjacencia;
        while (listaAdjacencia != NULL) {
            No* adjacente = listaAdjacencia->destino;
            // Verifica se o nó adjacente não foi visitado e não é uma parede
            if (!adjacente->visitado && labirinto[adjacente->linha][adjacente->coluna] != PAREDE) {
                // Marca o nó adjacente como visitado
                adjacente->visitado = true;
                // Enfileira o nó adjacente e seu nó pai
                enfileirar(fila, adjacente, atual);
            }
            listaAdjacencia = listaAdjacencia->proximaAresta;
        }
    }
    return NULL; // Não encontrou o caminho até a saída
}