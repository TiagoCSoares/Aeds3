#include "grafo.h"

No* criarNo(int posicao) {
    No* novoNo = (No*)malloc(sizeof(No));
    if(novoNo != NULL) {
        novoNo->posicao = posicao;;
        novoNo->listaAdjacencia = NULL;
    }
    return novoNo;
}
