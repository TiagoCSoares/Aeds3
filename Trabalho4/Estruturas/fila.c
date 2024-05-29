#include "fila.h"

void inicializarFila(Fila* fila) {
    fila->frente = 0;
    fila->fim = -1;
}

int filaVazia(Fila* fila) {
    return fila->fim < fila->frente;
}

void enfileirar(Fila* fila, No* filho, No* pai) {
    fila->fim++; // Incrementa o índice do final da fila
    fila->itens[fila->fim].filho = filho;
    fila->itens[fila->fim].pai = pai;
}

No* desenfileirar(Fila* fila) {
    if (filaVazia(fila)) {
        return NULL;
    }
    No* item = fila->itens[fila->frente].filho; // Remove o último elemento da fila
    fila->frente++; // Decrementa o índice do final da fila
    return item;
}