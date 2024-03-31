#ifndef PILHA_H
#define PILHA_H

#define LINHAS 10
#define COLUNAS 10

#include "no.h"


typedef struct Pilha {
    No* items[LINHAS * COLUNAS];
    int topo;
} Pilha;

void inicializarPilha(Pilha* pilha);
int pilhaVazia(Pilha* pilha);
void empilhar(Pilha* pilha, No* item);
No* desempilhar(Pilha* pilha);
No* topoDaPilha(Pilha* pilha);

#endif
