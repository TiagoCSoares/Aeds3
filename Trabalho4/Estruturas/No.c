#include "no.h"

No* criarNo(int posicao) {
    No* novoNo = (No*)malloc(sizeof(No));
    if(novoNo != NULL) {
        novoNo->posicao = posicao;
        novoNo->cor = -1;
        novoNo->grau = 0;
        novoNo->listaAdjacencia = NULL;
    }
    return novoNo;
}
