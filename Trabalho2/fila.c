#include "fila.h"
#include <stdlib.h>

void inicializarFila(Fila* fila) {
    fila->frente = 0;
    fila->fim = -1;
}

int filaVazia(Fila* fila) {
    return fila->fim < fila->frente;
}

void enfileirar(Fila* fila, No* filho, No* pai) {
    fila->fim++; // Incrementa o índice do final da fila
    fila->items[fila->fim].filho = filho;
    fila->items[fila->fim].pai = pai;
}

No* desenfileirar(Fila* fila) {
    if (filaVazia(fila)) {
        return NULL;
    }
    No* item = fila->items[fila->fim].filho; // Remove o último elemento da fila
    fila->fim--; // Decrementa o índice do final da fila
    return item;
}