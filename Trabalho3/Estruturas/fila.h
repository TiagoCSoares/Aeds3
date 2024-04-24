#ifndef FILA_H
#define FILA_H

#include <stdbool.h>
#include "no.h"

#define LINHAS 10
#define COLUNAS 10



typedef struct Fila {
    struct {
        No* filho;
        No* pai; 
    } itens[LINHAS * COLUNAS];
    int frente;
    int fim;
} Fila;


void inicializarFila(Fila* fila);
int filaVazia(Fila* fila);
void enfileirar(Fila* fila, No* pai, No*atual);
No* desenfileirar(Fila* fila);

#endif