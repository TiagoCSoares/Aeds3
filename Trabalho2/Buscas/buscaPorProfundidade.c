#include "../Estruturas/pilha.h"
#include <stdlib.h>

void buscaPorProfundidade(No* nos[LINHAS][COLUNAS], No* entrada, No* saida, Pilha* pilha) {

    if(topoDaPilha(pilha) == saida) {
        return;
    } else {
        No* atual = topoDaPilha(pilha);
        Aresta* listaAdjacencia = atual->listaAdjacencia;
        while(listaAdjacencia != NULL) {
            if(listaAdjacencia->destino->visitado == 0) {
                listaAdjacencia->destino->visitado = 1;
                empilhar(pilha, listaAdjacencia->destino);
                buscaPorProfundidade(nos, entrada, saida, pilha);
            }
            listaAdjacencia = listaAdjacencia->proximaAresta;
        }
        if(topoDaPilha(pilha) != saida) {
            desempilhar(pilha);
        }
    }
}