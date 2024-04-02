#include "pilha.h"
#include <stdlib.h>

void inicializarPilha(Pilha* pilha) {
    pilha->topo = -1;
}

int pilhaVazia(Pilha* pilha) {
    return pilha->topo == -1;
}

void empilhar(Pilha* pilha, No* item) {
    pilha->itens[++pilha->topo] = item;
}

No* desempilhar(Pilha* pilha) {
    if(pilhaVazia(pilha)) {
        return NULL;
    }
    return pilha->itens[pilha->topo--];
}

No* topoDaPilha(Pilha* pilha) {
    if(pilhaVazia(pilha)) {
        return NULL;
    }
    return pilha->itens[pilha->topo];
}